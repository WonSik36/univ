#include "cv.hpp"
#include <iostream>

#define UNDERTH 110
#define OVERTH 130

using namespace cv;
using namespace std;

Mat adjustIntensity(Mat mat);
int getMatAverage(Mat image);
double getGamma(Mat image);
double _getGamma(Mat image, double left, double right);
double getLogAver(double a, double b);

int main() {
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
	Mat image, adjustImg, foregroundMask, backgroundImg, foregroundImg;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
	VideoCapture cap("Data/cv_live.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> image;
		if (image.empty())
			break;
		
		// for decrease calculation
		resize(image, image, Size(image.cols/2, image.rows / 2));
		adjustImg = adjustIntensity(image);

		if (foregroundMask.empty())
			foregroundMask.create(image.size(), image.type());

		// perform background substraction
		// input: image, output: foregroundMask
		bg_model->apply(adjustImg, foregroundMask);
		// for obtain better mask
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 40, 255, THRESH_BINARY);
		morphologyEx(foregroundMask, foregroundMask, MORPH_OPEN, element);

		// get foreground image using mask
		foregroundImg = Scalar::all(0);
		image.copyTo(foregroundImg, foregroundMask);

		// update background image automatically
		bg_model->getBackgroundImage(backgroundImg);

		// get contour from foreground mask
		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;
		findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//defining bounding rectangle
		vector<Rect> boundRect(contours.size());
		for (int i = 0; i < contours.size(); i++)
			boundRect[i] = boundingRect(Mat(contours[i]));

		//draw rectangles to image on the contours
		for (int i = 0; i < contours.size(); i++)
			rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8, 0);

		//imshow("foreground mask", foregroundMask);
		imshow("foreground image", foregroundImg);
		imshow("original with contour", image);
		imshow("adjusted image", adjustImg);
	}
	return 0;
}

Mat adjustIntensity(Mat mat) {
	Mat HSV, ret;
	vector<Mat> splitHSV(3);

	cvtColor(mat, HSV, CV_BGR2HSV);
	split(HSV, splitHSV);

	// calculate correct gamma
	float gamma = getGamma(splitHSV[2]);
	unsigned char pix[256];
	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	// adjust image intensity
	MatIterator_<uchar> it, end;
	for (it = splitHSV[2].begin<uchar>(), end = splitHSV[2].end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	merge(splitHSV, HSV);
	cvtColor(HSV, ret, CV_HSV2BGR);

	return ret;
}

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
	double gamma = getLogAver(left, right);
	int leftTh = UNDERTH, rightTh = OVERTH;
	unsigned char pix[256];
	//cout << "left: " << left << " right: " << right << " gamma: " << gamma << endl;
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
	//cout << "value: " << value << endl;
	if (value >= leftTh && value <= rightTh) {
		return gamma;
	}
	else if (value < leftTh) {
		return _getGamma(image, left, gamma);
	}
	else {
		return _getGamma(image, gamma, right);
	}
}

double getLogAver(double a, double b) {
	return pow(10, (log10(a) + log10(b)) / 2);
}