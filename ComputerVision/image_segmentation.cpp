#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define LOCAL

#ifdef BASIC
int main() {
	Mat image, thresh;
	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th;
	thresh_T = 200;
	th = 10;
	low_cnt = high_cnt = low_sum = high_sum = 0;
	image = imread("xray.png", 0);
	cout << "threshold value:" << thresh_T << endl;
	while (1) {
		for (j = 0; j < image.rows; j++) {
			for (i = 0; i < image.cols; i++) {
				if (image.at<uchar>(j, i) < thresh_T) {
					low_sum += image.at<uchar>(j, i);
					low_cnt++;
				}
				else {
					high_sum += image.at<uchar>(j, i);
					high_cnt++;
				}
			}
		}
		if (abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) {
			cout << "threshold value:" << thresh_T << endl;
			break;
		}
		else {
			thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
			cout << "threshold value:" << thresh_T << endl;
			low_cnt = high_cnt = low_sum = high_sum = 0;
		}
	}
	threshold(image, thresh, thresh_T, 255, THRESH_BINARY);
	imshow("Input image", image);
	imshow("thresholding", thresh);
	waitKey(0);
}
#endif

#ifdef OTSU
int main() {
	Mat image, result;
	image = imread("lena.png", 0);
	threshold(image, result, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("Input image", image);
	imshow("result", result);
	waitKey(0);
	return 0;
}
#endif

#ifdef LOCAL
int main() {
	Mat image, binary, adaptive_binary, adaptive_binary_m15, adaptive_binary_b31;
	image = imread("colors.jpg", 0);
	resize(image, image, Size(image.cols / 2, image.rows / 2), 0, 0, CV_INTER_LINEAR);
	threshold(image, binary, 150, 255, THRESH_BINARY);
	adaptiveThreshold(image, adaptive_binary_b31, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 31, 0);
	adaptiveThreshold(image, adaptive_binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 131, 0);
	adaptiveThreshold(image, adaptive_binary_m15, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);
	imshow("Input image", image);
	imshow("binary", binary);
	imshow("adaptive binary", adaptive_binary);
	imshow("adaptive binary box size 31", adaptive_binary_b31);
	imshow("adaptive binary minus 15", adaptive_binary_m15);
	waitKey(0);
	return 0;
}
#endif