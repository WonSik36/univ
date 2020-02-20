#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob1

#ifdef prob1
int main() {
	Mat image, blur, grad_x, grad_y, abs_grad_x, abs_grad_y, mresult, aresult;
	image = imread("lena.png", 0);
	GaussianBlur(image, blur, Size(5, 5), 5, 5, BORDER_DEFAULT);
	//performs Sobel operation which is a discrete differentiation
	//blur: input Mat, grad_x: output Mat, CV_16S: depth of the output Mat
	//1: order of derivative in x direction, 0: order of derivative in y direction
	//3: size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
	Sobel(blur, grad_x, CV_16S, 1, 0, 3);
	convertScaleAbs(grad_x, abs_grad_x);
	Sobel(blur, grad_y, CV_16S, 0, 1, 3);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, mresult);

	aresult = Mat(image.size(), CV_64F);
	for (int i = 0; i < aresult.rows; i ++) {
		for (int j = 0; j < aresult.cols; j++) {
			aresult.at<double>(i, j) = 90 - atan2((double)grad_y.at<short>(i, j), (double)grad_x.at<short>(i, j));
		}
	}
	convertScaleAbs(aresult, aresult);

	imshow("X", abs_grad_x);
	imshow("Y", abs_grad_y);
	imshow("Input image", image);
	imshow("Sobel Edge Detector Magnitue", mresult);
	imshow("Sobel Edge Detector Angle", aresult);
	waitKey(0);
}
#endif

#ifdef prob2
int main() {

	VideoCapture cap("downtown_road.mp4");
	Mat image, canny;
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> image;
		Canny(image, canny, 180, 200, 3);
		imshow("canny", canny);
	}

	return 0;
}
#endif