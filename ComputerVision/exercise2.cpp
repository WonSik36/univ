#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob3

#ifdef prob1
int main() {
	Mat image, hsv;
	Mat HSV_channel[3];

	image = imread("lena.png");
	cvtColor(image,hsv, COLOR_BGR2HSV);
	split(hsv, HSV_channel);


	imshow("input image", image);
	//imshow("H", HSV_channel[0]);
	imshow("S", HSV_channel[1]);
	//imshow("V", HSV_channel[2]);
	//imshow("HSV image", hsv);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat image = imread("sun.jpg");
	// point (100,3) width: 250 height: 300
	Rect rect(50, 50, 350, 150);
	Mat rect_roi = image(rect);
	rect_roi.setTo(Scalar(255, 255, 0));
	imshow("ROI", rect_roi);
	imshow("original", image);


	cout << "width: " << image.cols << " height: " << image.rows << endl;
	waitKey(0);
}
#endif

#ifdef prob3
int main() {
	Mat frame;
	Mat after_convert;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("night.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		if (frame.empty())
			break;
		convertScaleAbs(frame, after_convert, 5, 10);
		imshow("video", after_convert);
	}
	return 0;
}
#endif