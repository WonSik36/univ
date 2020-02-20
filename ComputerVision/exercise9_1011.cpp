#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob3

#ifdef prob1
int main() {
	Mat image = imread("lena.png");
	Mat HSV;
	Mat RGB = image.clone();
	vector<Mat> splitHSV(3);	
	vector<Mat> splitRGB(3);

	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, splitHSV);
	split(RGB, splitRGB);

	float gamma = 0.5;
	unsigned char pix[256];

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	MatIterator_<uchar> it, end;
	// HSV
	for (it = splitHSV[2].begin<uchar>(), end = splitHSV[2].end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	//BGR
	for (it = splitRGB[0].begin<uchar>(), end = splitRGB[0].end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}
	for (it = splitRGB[1].begin<uchar>(), end = splitRGB[1].end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}
	for (it = splitRGB[2].begin<uchar>(), end = splitRGB[2].end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	merge(splitHSV, HSV);
	merge(splitRGB, RGB);
	cvtColor(HSV, HSV, CV_HSV2BGR);
	imshow("Input image", image);
	imshow("HSV", HSV);
	imshow("RGB", RGB);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	// Mat image = imread("colorful.jpg");
	Mat image = imread("Apple.jpg");

	Mat HSV, mask_out;
	vector<Mat> mo(3);	// mask out
	int rows = image.rows;
	int cols = image.cols;
	uchar* h;
	uchar* s;
	uchar* v;	// v is intensity
	cvtColor(image, HSV, CV_BGR2HSV);

	// split Mat to 3 channels
	split(HSV, mo);

	//masking out except red
	for (int j = 0; j < rows; j++) {
		h = mo[0].ptr<uchar>(j);
		s = mo[1].ptr<uchar>(j);
		for (int i = 0; i < cols; i++) {
			// if color is orange than keep it
			if ((h[i] >= 0 && h[i] < 30) || (h[i] > 160)) s[i] = s[i];
			// else set 0
			else s[i] = 0;
		}
	}

	// merge 3 channels to 1 image
	merge(mo, mask_out);
	// convert HSV to BGR
	cvtColor(mask_out, mask_out, CV_HSV2BGR);

	imshow("image", image);
	imshow("mask out", mask_out);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob3
int main() {
	Mat image = imread("balancing.jpg");
	resize(image, image, Size(image.cols / 2, image.rows / 2), 0, 0, CV_INTER_LINEAR);
	Mat balance = image.clone();
	vector<Mat> splitRGB(3);

	split(balance, splitRGB);
	long long averR = 0, averG = 0, averB = 0;
	long long totalPix = (long long)image.rows * image.cols;

	MatIterator_<uchar> it, end;
	//get average of each R,G,B
	for (it = splitRGB[0].begin<uchar>(), end = splitRGB[0].end<uchar>(); it != end; it++) {
		averB += *it;
	}
	for (it = splitRGB[1].begin<uchar>(), end = splitRGB[1].end<uchar>(); it != end; it++) {
		averG += *it;
	}
	for (it = splitRGB[2].begin<uchar>(), end = splitRGB[2].end<uchar>(); it != end; it++) {
		averR += *it;
	}
	
	averB /= totalPix;
	averG /= totalPix;
	averR /= totalPix;

	cout << "average of R: " << averR << endl;
	cout << "average of G: " << averG << endl;
	cout << "average of B: " << averB << endl;

	// white balancing by using gray world assumption
	// this is very important to use 128.0 not 128
	for (it = splitRGB[0].begin<uchar>(), end = splitRGB[0].end<uchar>(); it != end; it++) {
		*it = saturate_cast<uchar>(128.0 / averB * (*it));
	}
	for (it = splitRGB[1].begin<uchar>(), end = splitRGB[1].end<uchar>(); it != end; it++) {
		*it = saturate_cast<uchar>(128.0 / averG * (*it));
	}
	for (it = splitRGB[2].begin<uchar>(), end = splitRGB[2].end<uchar>(); it != end; it++) {
		*it = saturate_cast<uchar>(128.0 / averR * (*it));
	}

	merge(splitRGB, balance);
	imshow("Input image", image);
	imshow("white balancing", balance);
	waitKey(0);
	return 0;
}
#endif