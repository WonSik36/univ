#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob2

#ifdef prob1
int main() {
	Mat image = imread("saltnpepper.png", 0);
	imshow("Original", image);
	Mat AvgImg, MedImg;

	blur(image, AvgImg, Size(7, 7));
	medianBlur(image, MedImg, 7);
	imshow("MedianFiltered", MedImg);
	imshow("AverageFiltered", AvgImg);
	waitKey(0);
	return 0;
}
#endif


// use unsharp mask
#ifdef prob2
int main() {
	Mat image = imread("Moon.png", 0);
	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat img16S, BlurredImg16S, unsharpMask16S, sharpenImg16S;
	Mat result;
	image.convertTo(img16S, CV_16S);
	blur(img16S, BlurredImg16S, Size(5, 5));
	subtract(img16S, BlurredImg16S, unsharpMask16S);
	scaleAdd(unsharpMask16S, 0.5, img16S, sharpenImg16S);
	sharpenImg16S.convertTo(result, CV_8U);

	imshow("original", image);
	imshow("result", result);

	waitKey(0);
	return 0;
}
#endif