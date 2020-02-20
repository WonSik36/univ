#include "cv.hpp"
#include <iostream>

#define PROBLEM 1

using namespace cv;
using namespace std;

#if PROBLEM==1

void drawLine(vector<Vec2f> lines, float x, float y, float angle_th1, float angle_th2, Mat & result);

int main() {
	Mat frame, edge_l, edge_r, frame_roi_l, frame_roi_r, result;
	float x_l = 180, x_r = 270, y = 150;

	vector<Vec2f> lines_l, lines_r;

	VideoCapture cap("downtown_road.mp4");

	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}
	while (1) {

		cap >> frame;
		if (frame.empty()) break;

		result = frame.clone();
		cvtColor(frame, frame, CV_BGR2GRAY);

		Rect rect_l(x_l, y, 100, 100);
		Rect rect_r(x_r, y, 100, 100);

		frame_roi_l = frame(rect_l);
		frame_roi_r = frame(rect_r);

		Canny(frame_roi_l, edge_l, 50, 150, 3);
		Canny(frame_roi_r, edge_r, 50, 150, 3);

		HoughLines(edge_l, lines_l, 1, CV_PI / 180, 50);
		HoughLines(edge_r, lines_r, 1, CV_PI / 180, 50);

		drawLine(lines_l, x_l, y, 45, 60, result);
		drawLine(lines_r, x_r, y, 115, 126, result);

		imshow("Hough Transform", result);
		imshow("edge left Transform", edge_l);
		imshow("edge right Transform", edge_r);

		waitKey(33);
	}

}

void drawLine(vector<Vec2f> lines, float x, float y, float angle_th1, float angle_th2, Mat& result) {
	float rho, theta, a, b, x0, y0;
	float avr_rho = 0., avr_theta = 0.;
	int count = 0;
	Point p1, p2;

	for (int i = 0; i < lines.size(); i++) {
		rho = lines[i][0];
		theta = lines[i][1];

		// filter angle of line
		if (theta < CV_PI / 180 * angle_th1 || theta > CV_PI / 180 * angle_th2) continue;

		avr_rho += rho;
		avr_theta += theta;
		count++;
	}

	avr_rho /= count;
	avr_theta /= count;
	a = cos(avr_theta);
	b = sin(avr_theta);

	x0 = a * avr_rho;
	y0 = b * avr_rho;

	// draw line
	p1 = Point(cvRound(x0 + 1000 * (-b)) + x, cvRound(y0 + 1000 * a) + y);
	p2 = Point(cvRound(x0 - 1000 * (-b)) + x, cvRound(y0 - 1000 * a) + y);

	line(result, p1, p2, Scalar(0, 0, 255), 3, 8);
}
#endif
