#include "cv.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#define PROBLEM 1

using namespace cv;
using namespace std;

#if PROBLEM==1
int main() {
	Mat image, blur, grad_x, grad_y, abs_grad_x, abs_grad_y, magnitude, magnitude2, angle2, result;

	image = imread("lena.png", 0);
	Mat angle(image.cols, image.rows, CV_32F);
	GaussianBlur(image, blur, Size(5, 5), 5, 5, BORDER_DEFAULT);

	Sobel(blur, grad_x, CV_32F, 1, 0, 3);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(blur, grad_y, CV_32F, 0, 1, 3);
	convertScaleAbs(grad_y, abs_grad_y);

	sqrt((grad_x).mul(grad_x) + (grad_y).mul(grad_y), magnitude);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			angle.at<float>(i, j) = atan(grad_y.at<float>(i, j) / grad_x.at<float>(i, j)) * 180 / M_PI;
			if (angle.at<float>(i, j) < 0)
				angle.at<float>(i, j) = 360 + angle.at<float>(i, j);

		}
	}

	imshow("magnitude", magnitude);
	imshow("angle", angle);


	waitKey(0);
}
#endif

#if PROBLEM==2

int main() {
	Mat image, canny, frame;
	int th_l = 190;
	int th_r = 200;

	VideoCapture cap("Background.mp4");
	char ch;

	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}
	while (1) {
		cap >> frame;
		if (frame.empty()) break;

		Canny(frame, canny, th_l, th_r, 3);

		imshow("Canny", canny);
		ch = waitKey(10);
		if (ch == 27) break;

	}
}
#endif
