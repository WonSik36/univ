#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat frame, gray_frame, edge, poly_roi, poly_mask;
	Point poly[1][4];
	vector<Vec4i> lines;
	VideoCapture cap("Data/Go_1.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	if (!cap.isOpened()) {
		cout << "Could not open the camera" << endl;
		return -1;
	}

	// make polygonal mask that indicate ROI
	cap >> frame;
	poly_mask = Mat::zeros(frame.size(), CV_8U);
	poly[0][0] = Point(frame.cols / 10 * 5, frame.rows / 2);
	poly[0][1] = Point(frame.cols / 10 * 6, frame.rows / 2);
	poly[0][2] = Point(frame.cols / 10 * 8, frame.rows/8*7);
	poly[0][3] = Point(frame.cols / 10 * 4, frame.rows / 8 * 7);
	const Point* ppt[1] = { poly[0] };
	int npt[] = { 4 };
	fillPoly(poly_mask, ppt, npt, 1, Scalar(255), 8);


	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		// edge detection
		Canny(gray_frame, edge, 50, 200, 3);
		edge.copyTo(poly_roi, poly_mask);

		// line detection
		HoughLinesP(poly_roi, lines, 1, CV_PI / 180, 70, 10, 300);

		// draw the result
		for (int i = 0; i < lines.size(); i++) {
			Vec4i l = lines[i];
			line(frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, 8);
		}

		imshow("edge detection", edge);
		imshow("edge detection with mask", poly_roi);
		imshow("line detection", frame);
		imshow("ROI mask", poly_mask);
	}

}