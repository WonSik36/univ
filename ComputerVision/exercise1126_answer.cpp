#include "cv.hpp"
#include <iostream>

#define PROBLEM 11

using namespace cv;
using namespace std;

#if PROBLEM==11
int main(int argc, char* argv[]) {
	VideoCapture cap("face.mp4");
	Mat frame, m_backproj, hsv;
	Mat m_model3d;

	Rect rect;

	CascadeClassifier face_classifier;
	Mat grayframe;
	vector<Rect> faces;
	float h = cap.get(CAP_PROP_FRAME_HEIGHT), w = cap.get(CAP_PROP_FRAME_WIDTH);
	float resize_factor = 1.0 / 2.0;
	float hrange[] = { 0,180 };
	float vrange[] = { 0,255 };
	float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange };
	int channels[] = { 0, 1, 2 };
	int hist_sizes[] = { 16, 16, 16 };
	bool tracking = false;
	bool is_face = false;

	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	face_classifier.load("haarcascade_frontalface_alt.xml");

	while (true) {
		cap >> frame;
		if (frame.empty()) break;
		resize(frame, frame, Size(w * resize_factor, h * resize_factor));
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);
		if (!tracking || waitKey(33) == 32) {
			face_classifier.detectMultiScale(grayframe,
				faces,
				1.1,
				3,
				0,
				Size(30, 30));
			if (faces.size() > 0)
				is_face = true;
			else {
				is_face = false;
				tracking = false;
			}
		}

		cvtColor(frame, hsv, COLOR_BGR2HSV);

		if (is_face) {
			rect = faces[0];
			Mat mask = Mat::zeros(rect.height, rect.width, CV_8U);
			ellipse(mask, Point(rect.width / 2, rect.height / 2), Size(rect.width / 2, rect.height / 2), 0, 0, 360, 255, CV_FILLED);
			Mat roi(hsv, rect);
			calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
			rectangle(frame, rect, Scalar(0, 255, 0), 3);
			tracking = true;
			is_face = false;
		}
		if (tracking) {
			calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges);
			meanShift(m_backproj, rect, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
			rectangle(frame, rect, Scalar(0, 0, 255), 3);
		}
		imshow("Face Tracking", frame);
		char ch = waitKey(33);
		if (ch == 27) break;
	}
	return 0;
}
#endif

#if PROBLEM == 12
int main() {
	CascadeClassifier face_classifier;
	Mat frame, grayframe;
	vector<Rect> faces;
	int i;

	VideoCapture cap("face.mp4");

	float h = cap.get(CAP_PROP_FRAME_HEIGHT), w = cap.get(CAP_PROP_FRAME_WIDTH);
	float resize_factor = 1.0 / 2.0;

	if (!cap.isOpened()) {
		cout << "Could not open camera" << endl;
		return -1;
	}

	face_classifier.load("haarcascade_frontalface_alt.xml");

	while (true) {
		cap >> frame;
		if (frame.empty()) break;
		resize(frame, frame, Size(w * resize_factor, h * resize_factor));
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);
		face_classifier.detectMultiScale(
			grayframe,
			faces,
			1.1,
			3,
			0,
			Size(30, 30)
		);

		for (i = 0; i < faces.size(); i++) {
			Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point tr(faces[i].x, faces[i].y);
			rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
		}
		imshow("Face Detection", frame);
		if (waitKey(33) == 27) break;
	}
}

#endif

#if PROBLEM ==2

struct CallbackParam
{
	Mat frame;
	Point pt1, pt2;
	Rect roi;
	bool drag;
	bool updated;
};

void onMouse(int event, int x, int y, int flags, void* param);
void DrawTrackingPoints(vector<Point2f>& points, Mat& image);

int main(int argc, char* argv[])
{
	VideoCapture cap("background.mp4");
	if (!cap.isOpened()) {
		cout << "Cannot open cap" << endl;
		return 0;
	}
	Mat currImage, prevImage, prevImage_roi;
	Mat frame, dstImage;
	cap >> frame >> prevImage;

	imshow("dstImage", frame);

	CallbackParam param;
	param.frame = frame;
	param.drag = false;
	param.updated = false;

	setMouseCallback("dstImage", onMouse, &param);

	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	int maxCorners = 500;

	TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	Size winSize(11, 11);

	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;

	while (1) {
		cap >> frame;
		if (frame.empty()) break;

		frame.copyTo(dstImage);

		cvtColor(dstImage, currImage, CV_BGR2GRAY);
		GaussianBlur(currImage, currImage, Size(5, 5), 0.5);

		if (param.updated) {
			Rect rect = param.roi;
			prevImage_roi = prevImage(rect);

			goodFeaturesToTrack(prevImage_roi, prevPoints, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
			cornerSubPix(prevImage_roi, prevPoints, winSize, Size(-1, -1), criteria);
			for (int i = 0; i < prevPoints.size(); i++) {
				prevPoints[i].x += rect.x;
				prevPoints[i].y += rect.y;
			}
			DrawTrackingPoints(prevPoints, dstImage);
			param.updated = false;
		}

		if (prevPoints.size() > 0) {
			vector<Mat> prevPyr, currPyr;
			Mat status, err;
			buildOpticalFlowPyramid(prevImage, prevPyr, winSize, 3, true);
			buildOpticalFlowPyramid(currImage, currPyr, winSize, 3, true);
			calcOpticalFlowPyrLK(prevPyr, currPyr, prevPoints, currPoints, status, err, winSize);

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

		int ch = waitKey(33);
		if (ch == 27) break;
	}
	return 0;
}

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
		int h = y - p->pt1.y;p->roi.x = p->pt1.x;
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
			imshow("dstImage", img);
		}
	}
}


void DrawTrackingPoints(vector<Point2f>& points, Mat& image) {
	for (int i = 0; i < points.size(); i++) {
		int x = cvRound(points[i].x);
		int y = cvRound(points[i].y);
		circle(image, Point(x, y), 3, Scalar(255, 0, 0), 2);
	}
}


#endif
