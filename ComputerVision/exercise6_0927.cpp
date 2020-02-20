#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define	prob4

int getMatAverage(Mat image);
double getGamma(Mat image);
double _getGamma(Mat image, double left, double right);
double getLogAver(double a, double b);

#ifdef prob1
int main() {
	Mat image = imread("Binary.png", 0);
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

#ifdef prob2
int main() {
	Mat image_aerial = imread("Aerial_image.png", 0);
	Mat gamma_img_aerial = image_aerial.clone();
	Mat image_fracture = imread("Fracture_spine.png", 0);
	Mat gamma_img_fracture = image_fracture.clone();
	float gamma = 2;
	unsigned char pix[256];

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	MatIterator_<uchar> it, end;
	for (it = gamma_img_aerial.begin<uchar>(), end = gamma_img_aerial.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	gamma = 0.5;
	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	for (it = gamma_img_fracture.begin<uchar>(), end = gamma_img_fracture.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	imshow("Input image Aerial", image_aerial);
	imshow("Gamma Aerial", gamma_img_aerial);
	imshow("Input image Fracture", image_fracture);
	imshow("Gamma Fracture", gamma_img_fracture);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob3
int main() {
	Mat image = imread("reverse_light_1.jpg", 0);
	Mat addImage;
	image.convertTo(addImage, image.type(), 1, 50);
	Mat gamma_img = image.clone();
	float gamma = 0.5f;
	unsigned char pix[256];

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	MatIterator_<uchar> it, end;
	for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}
	imshow("Input image", image);
	imshow("Adding image", addImage);
	imshow("Gamma transformation", gamma_img);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob4
int main() {
	Mat image = imread("bright.jpg", 0);
	Mat gamma_img_bright = image.clone();
	float gamma = getGamma(gamma_img_bright);
	//float gamma = 31.6228f;
	unsigned char pix[256];

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	MatIterator_<uchar> it, end;
	for (it = gamma_img_bright.begin<uchar>(), end = gamma_img_bright.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	image = imread("dark.jpg", 0);
	Mat gamma_img_dark = image.clone();

	gamma = getGamma(gamma_img_dark);
	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	for (it = gamma_img_dark.begin<uchar>(), end = gamma_img_dark.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	imshow("Gamma transformation Bright", gamma_img_bright);
	imshow("Gamma transformation Dark", gamma_img_dark);


	cout << "Gamma transformation Bright Average: " <<getMatAverage(gamma_img_bright) << endl;
	cout << "Gamma transformation Dark Average: " << getMatAverage(gamma_img_dark) << endl;
	waitKey(0);
	return 0;
}
#endif

int getMatAverage(Mat image) {
	int sum = 0;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			sum += image.at<uchar>(i, j);
		}
	}
	return sum / (image.rows * image.cols);
}

double getGamma(Mat image) {
	Mat clone = image.clone();
	return _getGamma(clone, 0.00001f, 100000.0f);
}

double _getGamma(Mat image, double left, double right) {
	double gamma = getLogAver(left,right);
	int leftTh = 100, rightTh = 150;
	unsigned char pix[256];
	cout << "left: "<<left<<" right: "<<right << " gamma: "<<gamma<<endl;
	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}
	MatIterator_<uchar> it, end;
	int sum = 0;
	int totalPix = image.rows * image.cols;
	for (it = image.begin<uchar>(), end = image.end<uchar>(); it != end; it++) {
		sum += pix[(*it)];
	}
	double value = sum / totalPix;
	cout << "value: " << value << endl;
	if (value >= leftTh && value <= rightTh) {
		return gamma;
	}else if (value < leftTh) {
		return _getGamma(image,left, gamma);
	}
	else {
		return _getGamma(image, gamma, right);
	}
}

double getLogAver(double a, double b) {
	return pow(10,(log10(a) + log10(b))/2);
}