#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob2

#ifdef prob1
int main() {
	Mat image = imread("lena.png");
	Rect rect = Rect(240, 230, 120, 140); // LT position, width, height

	rectangle(image, rect, Scalar(0, 255, 0), -1, CV_AA, 0);
	imshow("image", image);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat image = Mat(Size(640,480),CV_8UC3,Scalar(0,255,255));	// yellow back ground
	Point trapezoid[2][6];
	int w = 300;
	// trapezoid
	trapezoid[0][0] = Point(w * 2 / 6, w / 4);			
	trapezoid[0][1] = Point(w * 4 / 6, w / 4);		
	trapezoid[0][2] = Point(w * 5 / 6, w * 3 / 4);
	trapezoid[0][3] = Point(w / 6, w * 3 / 4);

	//hexagon
	trapezoid[1][0] = Point(300, 200);			
	trapezoid[1][1] = Point(400, 200);			
	trapezoid[1][2] = Point(450, 300);
	trapezoid[1][3] = Point(400, 400);
	trapezoid[1][4] = Point(300, 400);
	trapezoid[1][5] = Point(250, 300);

	const Point* ppt[2] = { trapezoid[0],trapezoid[1] };
	int npt[2] = { 4,6 };
	// Mat& img: image, , const Point** pts: ppt, const int* npts: npt,int ncontours: 2
	fillPoly(image, ppt, npt, 2, Scalar(0, 0, 0), 8);
	imshow("image", image);
	waitKey(0);

	return 0;
}
#endif

#ifdef prob3
int main() {
	Mat frame;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("road.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		if (frame.empty())
			break;
		int row = frame.rows;
		int col = frame.cols;
		Point p1(col/3, 0), p2(2*col/3, row), p3(2*col/3, 0), p4(col / 3,row);
		line(frame, p1, p2, Scalar(0, 0, 255), 5, 8, 0);
		line(frame, p3, p4, Scalar(0, 0, 255), 5, 8, 0);
		imshow("video", frame);
	}
	return 0;
}
#endif

#ifdef prob4
int main() {
	Mat frame;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("NTH3.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	int total_frame = cap.get(CAP_PROP_FRAME_COUNT);
	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		if (frame.empty())
			break;
		int cur_frame = cap.get(CAP_PROP_POS_FRAMES);
		putText(frame, format("%d/%d", cur_frame, total_frame), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 4, CV_AA);
		imshow("video", frame);
	}
	return 0;
}
#endif