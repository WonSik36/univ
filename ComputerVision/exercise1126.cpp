#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob1_2

#ifdef prob1_1
int main() {
	CascadeClassifier face_clasifier;
	Mat frame, gray_frame;
	vector<Rect> faces;
	VideoCapture cap("face.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	if (!cap.isOpened()) {
		cout << "Could not open the camera" << endl;
		return -1;
	}
	// configuration
	face_clasifier.load("haarcascade_frontalface_alt.xml");

	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
		face_clasifier.detectMultiScale(gray_frame, faces,
			1.2,		// increase search scale by 10% each pass
			3,			// merge groups of three detection
			0			// not used for a new cascade
		);

		// draw the result
		for (int i = 0; i < faces.size(); i++) {
			Point lt(faces[i].x, faces[i].y);
			Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

			rectangle(frame, lt, rb, Scalar(0, 255, 0), 3, 4, 0);
		}

		imshow("Face detection", frame);
	}

}
#endif

#ifdef prob1_2
int main() {
	// variable for face detection
	CascadeClassifier face_clasifier;
	Mat frame, gray_frame;
	vector<Rect> faces;
	VideoCapture cap("face.mp4");
	double fps = cap.get(CAP_PROP_FPS);
	bool initialization = true;
	face_clasifier.load("haarcascade_frontalface_alt.xml");

	// variable for tracking
	Mat m_backproj, hsv;
	vector<Mat> m_model3d;
	vector<Rect> m_rc;
	float hrange[] = { 0,180 };
	float vrange[] = { 0,255 };
	float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
	int channels[] = { 0, 1, 2 };
	int hist_sizes[] = { 16, 16, 16 };
	bool tracking = false;

	while (true) {
		cap >> frame;
		if (frame.empty()) 
			break;
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		if (!initialization)
			tracking = true;

		// if first frame than detect face
		if (initialization) {
			// detect face
			cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
			face_clasifier.detectMultiScale(gray_frame, faces,
				1.2,		// increase search scale by 10% each pass
				3,			// merge groups of three detection
				0			// not used for a new cascade
			);

			// set roi
			for (int i = 0; i < faces.size(); i++) {
				Rect rc = faces[i];
				Mat m_model3d_tmp;

				Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
				ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255,CV_FILLED);
				Mat roi(hsv, rc);
				calcHist(&roi, 1, channels, mask, m_model3d_tmp, 3, hist_sizes, ranges); // calculate histogram -> get feature
				
				m_rc.push_back(rc);
				m_model3d.push_back(m_model3d_tmp);
			}

			initialization = false;
			// draw the result
			for (int i = 0; i < faces.size(); i++) {
				Point lt(faces[i].x, faces[i].y);
				Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

				rectangle(frame, lt, rb, Scalar(0, 255, 0), 2, 4, 0);
			}
		}

		// if it is not first frame than tracking face by roi
		if (tracking) {
			for (int i = 0; i < faces.size(); i++) {
				calcBackProject(&hsv, 1, channels, m_model3d[i], m_backproj, ranges); // calculate back project to m_backproj with m_model3d
				meanShift(m_backproj, m_rc[i], TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
				rectangle(frame, m_rc[i], Scalar(0,255,0), 2,4,0);
			}
		}

		// image display
		imshow("face detection with tracking", frame);

		// user input
		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(1000 / fps)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}

}
#endif

#ifdef prob2
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
			imshow("dstImage", img);
		}
	}
}

void DrawTrackingPoints(vector<Point2f>& points, Mat& image) {
	// Drawcornersdetected
	for (int i = 0; i < points.size(); i++) {
		int x = cvRound(points[i].x);
		int y = cvRound(points[i].y);
		circle(image, Point(x, y), 3, Scalar(255, 0, 0), 2);
	}
}

int main(int argc, char* argv[]) {
	VideoCapture cap("background.mp4");
	CallbackParam param;
	double fps = cap.get(CAP_PROP_FPS);
	Mat currImage, prevImage;
	Mat frame, dstImage;
	vector<Point2f> prevPoints;
	vector<Point2f> currPoints;
	vector<Point2f> boundPoints;
	bool init = true;
	bool tracking = false;

	const int maxCorners = 500;
	const double qualityLevel = 0.01;
	const double minDistance = 10;
	const int blockSize = 3;
	const bool useHarrisDetector = false;
	const double k = 0.04;
	const TermCriteria criteria = TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.01);
	const Size winSize(11, 11);

	// check if file is valid
	if (!cap.isOpened()) {
		cout << "Could not open the file" << endl;
		return -1;
	}


	param.drag = false;

	while (true) {
		if (param.drag) {
			if (waitKey(1000 / fps) == 27) break; // ESC key
			continue;
		}

		cap >> frame;
		if (frame.empty()) break;
		frame.copyTo(dstImage);
		cvtColor(dstImage, currImage, CV_BGR2GRAY);
		GaussianBlur(currImage, currImage, Size(5, 5), 0.5);

		if (init) {
			imshow("dstImage", dstImage);
			currImage.copyTo(prevImage);
			param.frame = frame;
			param.drag = false;
			param.updated = false;
			init = false;
			// initialize callback parameter
			setMouseCallback("dstImage", onMouse, &param);
			continue;
		}

		if (param.updated) {
			Rect rc = param.roi;
			goodFeaturesToTrack(prevImage, prevPoints, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k); // get feature
			cornerSubPix(prevImage, prevPoints, winSize, Size(-1, -1), criteria); // get  accurate corner pixel
			
			//delete point which is not in roi
			for (vector<Point2f>::iterator iter = prevPoints.begin(); iter != prevPoints.end();) {
				if (rc.x <= (*iter).x && rc.x + rc.width >= (*iter).x && rc.y <= (*iter).y && rc.y + rc.height >= (*iter).y)
					iter++;
				else
					iter = prevPoints.erase(iter);
			}

			DrawTrackingPoints(prevPoints, dstImage);
			param.updated = false;
			tracking = true;
		}

		// apply KLT
		if (tracking && prevPoints.size() > 0) {
			vector<Mat> prevPyr, currPyr;
			Mat status, err;
			buildOpticalFlowPyramid(prevImage, prevPyr, winSize, 3, true);
			buildOpticalFlowPyramid(currImage, currPyr, winSize, 3, true);
			calcOpticalFlowPyrLK(prevPyr, currPyr, prevPoints, currPoints, status, err, winSize);

			//delete invalid corresponding points
			for (int i = 0; i < prevPoints.size(); i++) {
				if (!status.at<uchar>(i)) {
					prevPoints.erase(prevPoints.begin() + i);
					currPoints.erase(currPoints.begin() + i);
				}
			}
			DrawTrackingPoints(currPoints, dstImage);
			prevPoints = currPoints;
		}

		// image display
		imshow("dstImage", dstImage);
		currImage.copyTo(prevImage);

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