#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat img = imread("apple.jpg");
	Mat cvt, dst;
	Rect rect(160, 140, 180, 230);
	Mat rect_roi = img(rect);
	cvtColor(rect_roi, rect_roi, CV_BGR2YCrCb);
	rect_roi = img(rect);
	inRange(rect_roi, Scalar(30, 150, 100), Scalar(190, 230, 140), rect_roi); // because output array is 1 channel -> create output array

	for (int i = 0; i < 230; i++) {
		for (int j = 0; j < 180; j++) {
			if (rect_roi.at<uchar>(i, j) == 255) {
				img.at<Vec3b>(140 + i, 160 + j)[0] = 255;
				img.at<Vec3b>(140 + i, 160 + j)[1] = 255;
				img.at<Vec3b>(140 + i, 160 + j)[2] = 255;
			}
			else {
				img.at<Vec3b>(140 + i, 160 + j)[0] = 0;
				img.at<Vec3b>(140 + i, 160 + j)[1] = 0;
				img.at<Vec3b>(140 + i, 160 + j)[2] = 0;
			}
		}
	}

	for (int i = 400; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			int aver = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[0]) / 3;
			img.at<Vec3b>(i, j)[0] = aver;
			img.at<Vec3b>(i, j)[1] = aver;
			img.at<Vec3b>(i, j)[2] = aver;
		}
	}
	rectangle(img, rect, Scalar(255, 0, 0), 4, 8, 0);

	imshow("Original", img);
	waitKey(0);
	return 0;
}
