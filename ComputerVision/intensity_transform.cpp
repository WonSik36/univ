#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define	AVER

#ifdef NEGATIVE
int main() {
	Mat image = imread("lena.png", 0);
	Mat negative_img = image.clone();
	
	for (int j = 0; j < image.rows; j++)
		for (int i = 0; i < image.cols; i++) {
			negative_img.at<uchar>(j, i) = 255 - negative_img.at<uchar>(j, i);
		}
			
	imshow("Input image", image);
	imshow("Negative transformation", negative_img);
	
	waitKey(0);
	return 0;
}
#endif

#ifdef LOG
int main() {
	Mat image = imread("lena.png", 0);
	Mat f_img, log_img;
	double c = 1.5f;
	image.convertTo(f_img, CV_32F);	//32-bit floating-point number
	f_img = abs(f_img) + 1;
	log(f_img, f_img);
	normalize(f_img, f_img, 0, 255, NORM_MINMAX); // normalize image to 0 -255
	convertScaleAbs(f_img, log_img, c);	//scaling by c(= alpha), conversion to an unsigned 8-bit type

	imshow("Input image", image);
	imshow("Log transformation", log_img);

	waitKey(0);
	return 0;
}
#endif

#ifdef GAMMA
int main() {
	Mat image = imread("lena.png", 0);
	Mat gamma_img = image.clone();
	float gamma = 1.5;
	unsigned char pix[256];

	for (int i = 0; i < 256; i++){
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	MatIterator_<uchar> it, end;
	for(it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}
	imshow("Input image", image);
	imshow("Gamma transformation", gamma_img);

	waitKey(0);
	return 0;
}
#endif

#ifdef AVER
int main() {
	Mat image = imread("lena.png", 0);
	Mat f_img, log_img;
	double c = 1.0f;
	image.convertTo(f_img, CV_32F);	//32-bit floating-point number
	f_img = abs(f_img) + 1;
	log(f_img, f_img);
	normalize(f_img, f_img, 0, 255, NORM_MINMAX); // normalize image to 0 -255
	convertScaleAbs(f_img, log_img, c);	//scaling by c(= alpha), conversion to an unsigned 8-bit type

	int sum = 0;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			sum += image.at<uchar>(i, j);
		}
	}
	int imageAver = sum / (image.rows * image.cols);

	sum = 0;
	for (int i = 0; i < log_img.rows; i++) {
		for (int j = 0; j < log_img.cols; j++) {
			sum += log_img.at<uchar>(i, j);
		}
	}
	int logAver = sum / (image.rows * image.cols);

	cout << "imageAver: " << imageAver << endl;
	cout << "logAver: " << logAver << endl;
	imshow("Input image", image);
	imshow("Gamma transformation", log_img);

	waitKey(0);
	return 0;
}
#endif