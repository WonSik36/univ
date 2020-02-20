#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define MEAN_SHIFT
//#define OPTICAL_FLOW

#ifdef CAM_SHIFT
#define SHIFT
#endif

#ifdef MEAN_SHIFT
#define SHIFT
#endif

#ifdef SHIFT
struct CallbackParam
{
	Mat frame;
	Point pt1, pt2;
	Rect roi;
	bool drag;
	bool updated;
};

void onMouse(int event, int x, int y, int flags, void* param)
{
	CallbackParam* p = (CallbackParam*)param;
	if (event == EVENT_LBUTTONDOWN) {
		p->pt1.x = x;
		p->pt1.y = y;
		p->pt2 = p->pt1;
		p->drag = true;
	}
	if (event == EVENT_LBUTTONUP) {
		int w = x - p->pt1.x;
		int h = y - p->pt1.y; p->roi.x = p->pt1.x;
		p->roi.y = p->pt1.y;
		p->roi.width = w;
		p->roi.height = h;
		p->drag = false;
		if (w >= 10 && h >= 10) {
			p->updated = true;
		}
	}

	if (p->drag && event == EVENT_MOUSEMOVE) {
		if (p->pt2.x != x || p->pt2.y != y) {
			Mat img = p->frame.clone();
			p->pt2.x = x;
			p->pt2.y = y;
			rectangle(img, p->pt1, p->pt2, Scalar(0, 255, 0), 1);
			imshow("Tracker", img);
		}
	}
}

int main(int argc, char* argv[]) {
	VideoCapture cap("Data/Go_1.mp4");
	double fps = cap.get(CV_CAP_PROP_FPS);
	CallbackParam param;
	Mat frame, m_backproj, hsv;
	Mat m_model3d;
	Rect m_rc;
	float hrange[] = { 0,180 };
	float vrange[] = { 0,255 };
	float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
	int channels[] = { 0, 1, 2 };
	int hist_sizes[] = { 16, 16, 16 };

	// check if we succeeded
	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	// initialize callback parameter
	cap >> frame;
	imshow("Tracker", frame);
	param.frame = frame;
	param.drag = false;
	param.updated = false;
	setMouseCallback("Tracker", onMouse, &param);
	bool tracking = false;

	while (true) {
		// image acquisition & target init
		if (param.drag) {
			if (waitKey(1000 / fps) == 27) break; // ESC key
			continue;
		}

		cvtColor(frame, hsv, COLOR_BGR2HSV);
		if (param.updated) {
			Rect rc = param.roi;
			Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
			ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255,CV_FILLED);
			Mat roi(hsv, rc);
		
			calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges); // calculate histogram to m_model3d -> get feature
			m_rc = rc;
			param.updated = false;
			tracking = true;
		}
		cap >> frame;
		if (frame.empty()) break;
		// image processing
		if (tracking) {
			//histogram backprojection
			calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges); // calculate back project to m_backproj with m_model3d
#ifdef MEAN_SHIFT
			//tracking
			meanShift(m_backproj, m_rc, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
#endif

#ifdef CAM_SHIFT
			//tracking
			CamShift(m_backproj, m_rc, cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 1));
#endif
			rectangle(frame, m_rc, Scalar(0, 0, 255), 3);
		}
		// image display
		imshow("Tracker", frame);
		// user input
		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(1000 / fps)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}
	return 0;
}
#endif

#ifdef OPTICAL_FLOW
struct feature{
	Point2f pt;
	int val;
};
bool initialization = false;
void DrawTrackingPoints(vector<Point2f>& points, Mat& image);

int main(int argc, char* argv[])
{
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Cannotopencap" << endl;
		return 0;
	}

	double fps = cap.get(CV_CAP_PROP_FPS);
	Mat currImage, prevImage;
	Mat frame, dstImage;
	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;
	vector<Point2f> boundPoints;

	const int maxCorners = 500;
	const double qualityLevel = 0.01;
	const double minDistance = 10;
	const int blockSize = 3;
	const bool useHarrisDetector = false;
	const double k = 0.04;
	const TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	const Size winSize(11, 11);

	while (1) {
		cap >> frame;
		if (frame.empty()) break;
		frame.copyTo(dstImage);
		// Copy the source image
		cvtColor(dstImage, currImage, CV_BGR2GRAY);
		GaussianBlur(currImage, currImage, Size(5, 5), 0.5);

		// feature detection
		if (initialization) {
			goodFeaturesToTrack(prevImage, prevPoints, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k); // get feature
			cornerSubPix(prevImage, prevPoints, winSize, Size(-1, -1), criteria); // get  accurate corner pixel
			DrawTrackingPoints(prevPoints, dstImage);
			initialization = false;
		}

		// apply KLT
		if (prevPoints.size() > 0) {
			vector<Mat> prevPyr, currPyr;
			Mat status, err;
			buildOpticalFlowPyramid(prevImage, prevPyr, winSize, 3, true);
			buildOpticalFlowPyramid(currImage, currPyr, winSize, 3, true);
			calcOpticalFlowPyrLK(prevPyr, currPyr, prevPoints, currPoints, status, err, winSize);

			//delete invalid correspondinig points
			for (int i = 0; i < prevPoints.size(); i++) {
				if (!status.at<uchar>(i)) {
					prevPoints.erase(prevPoints.begin() + i);
					currPoints.erase(currPoints.begin() + i);
				}
			}
			DrawTrackingPoints(currPoints, dstImage);
			prevPoints = currPoints;
		}

		imshow("dstImage", dstImage);
		currImage.copyTo(prevImage);
		int ch = waitKey(1000 / fps);
		if (ch == 27) break;       // 27 == ESC key
		if (ch == 32) initialization = true;
	}

	return 0;
}

void DrawTrackingPoints(vector<Point2f>& points, Mat& image) {
	// Drawcornersdetected
	for (int i = 0; i < points.size(); i++) {
		int x = cvRound(points[i].x);
		int y = cvRound(points[i].y);
		circle(image, Point(x, y), 3, Scalar(255, 0, 0), 2);
	}
}
#endif