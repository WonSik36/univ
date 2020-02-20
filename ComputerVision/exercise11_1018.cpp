#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

bool equals(Mat a, Mat b);

int main() {
	VideoCapture capture("background.mp4");
	Mat image, gray, foregroundMask, avg;
	Mat beforeAvg, imgContainAllContours, firstFrame; // for test
	deque<Mat> dq;
	double fps = capture.get(CAP_PROP_FPS);


	// get average and deque which has 10 frame
	int cnt = 2;
	capture >> image;
	cvtColor(image, gray, CV_BGR2GRAY);
	avg = gray.clone();
	dq.push_back(gray.clone());
	firstFrame = gray.clone();

	for (int i = 0; i < 9; i++) {
		capture>>image;
		cvtColor(image, gray, CV_BGR2GRAY);
		add(gray / cnt, avg * (cnt - 1) / cnt, avg);
		cnt++;
		dq.push_back(gray.clone());
	}

	while (waitKey(1000 / fps) != 27) {
		// get current frame
		capture >> image;
		if (image.empty())
			break;
		cvtColor(image, gray, CV_BGR2GRAY);

		/*
		*	test code
		*	update image that has all contours, and before average
		*/
		imgContainAllContours = image.clone();
		beforeAvg = avg.clone();

		// make new average and update deque
		dq.push_back(gray.clone());
		dq.pop_front();
		for (int i = 0; i < 10; i++) {
			add(dq.at(i) / (i+1.0), (avg * i) / (i + 1.0), avg);
		}

		/*
		*	test code
		*	check deque and average
		*/
		// check deque size is 10
		if (dq.size() != 10)
			throw invalid_argument("deque size is not 10");
		// check average is same with before one
		if (equals(beforeAvg, avg))
			throw invalid_argument("before average is same with current avg");

		// get foreground mask by usng absolute difference
		absdiff(avg, gray, foregroundMask);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);

		// get contour from foreground mask
		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;
		findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//defining bounding rectangle
		vector<Rect> boundRect(contours.size());
		for (int i = 0; i < contours.size(); i++)
			boundRect[i] = boundingRect(Mat(contours[i]));

		/*
		*	test code
		*	draw rectangles to image on the all contours
		*/
		cnt = 0;
		for (int i = 0; i < contours.size(); i++) {
			rectangle(imgContainAllContours, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8, 0);
			cnt++;
		}
		putText(imgContainAllContours, format("contour count: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 4);


		//draw rectangles to image on the contours which bigger than 200
		cnt = 0;
		for (int i = 0; i < contours.size(); i++) {
			Point tl = boundRect[i].tl();
			Point br = boundRect[i].br();
			int size = (br.x - tl.x) * (br.y - tl.y);
			if (size > 200) {
				rectangle(image, tl, br, Scalar(0, 255, 255), 2, 8, 0);
				cnt++;
			}
		}
		putText(image, format("contour count bigger than 200 pixels: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,255), 4);


		/*
		*	test code
		*	check average is same with first frame or not
		*/
		if (equals(firstFrame, avg))
			throw invalid_argument("firstFrame and average equals");

		//imshow("firstFrame", firstFrame);
		imshow("foregroundMask", foregroundMask);
		//imshow("gray", gray);
		imshow("avg", avg);
		imshow("original with contours over 200", image);
		//imshow("original with all contours", imgContainAllContours);
	}
	return 0;
}

bool equals(Mat a, Mat b) {
	if (a.size().width != b.size().width || a.size().height != b.size().height)
		return false;

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.at<uchar>(j, i) != b.at<uchar>(j, i)) {
				return false;
			}
		}
	}
	return true;
}