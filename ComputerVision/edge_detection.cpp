#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define SOBEL

#ifdef SOBEL
int main() {
	Mat image, blur, grad_x, grad_y, abs_grad_x, abs_grad_y, result, RNG;
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
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, result);

	//threshold(result, RNG, 200, 255, CV_THRESH_BINARY);

	imshow("X", abs_grad_x);
	imshow("Y", abs_grad_y);
	imshow("Input image", image);
	imshow("Sobel Edge Detector", result);
	//imshow("rng", RNG);
	waitKey(0);
}

#endif

#ifdef CANNY
int main() {
	Mat image, canny;
	image = imread("lena.png", 0);
	//performs canny edge detection
	//image: input Mat, canny: output Mat
	//190: Thresh_lowof double thresholding
	//200: Thresh_highof double thresholding
	//3: aperture size of the Sobel operation it must be 1,3,5,or 7
	Canny(image, canny, 180, 200, 3);
	imshow("Input image", image);
	imshow("canny", canny);
	waitKey(0);
}

#endif