#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat frame;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("background.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	double time_in_msec = 0;

	while (time_in_msec < 5000) {
		cap >> frame;
		time_in_msec = cap.get(CAP_PROP_POS_MSEC);
		// cout << "times: " << time_in_msec << endl;
	}

	// cout << "start time 5000" << endl;
	while (time_in_msec <= 10000 && time_in_msec >= 5000) {
		for (int i = 0; i < frame.rows; i ++) {
			for (int j = 50; j <= 100; j++) {
				frame.at<Vec3b>(i, j)[0] = 0;
				frame.at<Vec3b>(i, j)[1] = 0;
				frame.at<Vec3b>(i, j)[2] = 255;
			}
		}
		putText(frame, format("%d/%d", frame.cols, frame.rows), Point(200, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 4, CV_AA);
		// cout << "times: " << time_in_msec << endl;
		imshow("Background", frame);
		cap >> frame;
		time_in_msec = cap.get(CAP_PROP_POS_MSEC);
		waitKey(1000 / fps);
	}

		return 0;
}