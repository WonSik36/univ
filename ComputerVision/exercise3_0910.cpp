#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob5

#ifdef prob1
int main() {
	Mat img1 = imread("apple.jpg");
	Mat img2 = imread("lena.png");
	Mat sub, absub;

	subtract(img1, img2, sub);
	absdiff(img1, img2, absub);
	imshow("subtraction", sub);
	imshow("absolute subtraction", absub);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat img1 = imread("Apple.jpg");
	Mat img2 = imread("Fracture_spine.png");
	Mat dst;

	add(img1, img2, dst);
	imshow("addition", dst);
	waitKey(0);
	//Error: Sizes of input arguments do not match
	return 0;
}
#endif

#ifdef prob3
int main() {
	Mat img = imread("lena.png");
	//Mat img = imread("lena.png", 0);
	Mat thresh_binary, thresh_binary_inv, thresh_trunc, thresh_2_zero, thresh_2_zero_inv;
	threshold(img, thresh_binary, 128, 200, THRESH_BINARY);
	threshold(img, thresh_binary_inv, 128, 200, THRESH_BINARY_INV);
	threshold(img, thresh_trunc, 128, 200, THRESH_TRUNC);
	threshold(img, thresh_2_zero, 128, 200, THRESH_TOZERO);
	threshold(img, thresh_2_zero_inv, 128, 200, THRESH_TOZERO_INV);

	imshow("original", img);
	imshow("threshold_binary", thresh_binary);
	imshow("threshold_binary_inv", thresh_binary_inv);
	imshow("threshold_trunc", thresh_trunc);
	imshow("threshold_tozero", thresh_2_zero);
	imshow("threshold_tozer_inv", thresh_2_zero_inv);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob4
int main() {
	Mat img = imread("lena.png", 0);
	Mat block3, block135,block513;

	adaptiveThreshold(img, block3, 200, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 10);
	adaptiveThreshold(img, block135, 200, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 135, 10);
	adaptiveThreshold(img, block513, 200, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 513, 10);
	cout << img.rows << " " << img.cols << endl;
	imshow("original", img);
	imshow("3 blocks", block3);
	imshow("135 blocks", block135);
	imshow("513 blocks", block513);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob5
int main() {
	Mat img = imread("apple.jpg");
	Mat cvt,dst;

	cvtColor(img, cvt, CV_BGR2YCrCb);
	inRange(cvt, Scalar(30, 150, 100), Scalar(190, 230, 140), dst);

	imshow("original", img);
	imshow("in range", dst);

	waitKey(0);
	return 0;
}
#endif