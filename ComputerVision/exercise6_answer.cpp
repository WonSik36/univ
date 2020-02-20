#include "cv.hpp"
#include <iostream>
#define PROBLEM 4          //Change this problem number

using namespace cv;
using namespace std;

#if PROBLEM==1
int main() {

	Mat gray = imread("Binary.png", 0);
	Mat result = Mat(gray.rows, gray.cols, CV_8UC1, Scalar(255));

	//Negative at grayScale
	result = result - gray;


	imshow("Original", gray);
	imshow("Negative", result);
	waitKey(0);
}
#endif

#if PROBLEM==2
int main()
{
	Mat Aerial = imread("Aerial_image.png", 0);
	Mat Fracture = imread("Fracture_spine.png", 0);
	Mat gamma_Aerial, gamma_Fracture;


	imshow("Aerial", Aerial);
	imshow("Fracture", Fracture);


	MatIterator_<uchar> it, end;
	float gammaValue_Aerial = 2.0;
	float gammaValue_Fracture = 0.3;
	unsigned char pix[256];

	gamma_Aerial = Aerial.clone();
	gamma_Fracture = Fracture.clone();

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gammaValue_Aerial) * 255.0f);
	}
	for (it = gamma_Aerial.begin<uchar>(), end = gamma_Aerial.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gammaValue_Fracture) * 255.0f);
	}
	for (it = gamma_Fracture.begin<uchar>(), end = gamma_Fracture.end<uchar>(); it != end; it++)
	{
		*it = pix[(*it)];
	}

	imshow("Gamma transformation2", gamma_Aerial);
	imshow("Gamma transformation3", gamma_Fracture);
	waitKey(0);
	return 0;
}
#endif

#if PROBLEM==3
int main() {

	Mat image_add = imread("reverse_light_1.jpg", 0);
	Mat image_gamma = imread("reverse_light_1.jpg", 0);
	float gamma = 0.6;
	unsigned char pix[256];
	MatIterator_<uchar> it, end;
	imshow("Original_image", image_add);


	//add50
	for (it = image_add.begin<uchar>(), end = image_add.end<uchar>(); it != end; it++)
	{
		*it = saturate_cast<uchar>(*it + 50);
	}

	//gamma correction
	for (int i = 0; i < 256; i++)
	{
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}
	for (it = image_gamma.begin<uchar>(), end = image_gamma.end<uchar>(); it != end; it++)
	{
		*it = pix[(*it)];
	}

	imshow("add50", image_add);
	imshow("gamma", image_gamma);
	waitKey(0);

	return 0;
}
#endif

#if PROBLEM==4
int main()
{
	Mat image_dark = imread("dark.jpg", 0);
	Mat image_bright = imread("bright.jpg", 0);
	Mat gamma_dark, gamma_bright;
	MatIterator_<uchar> it, end;

	imshow("Origin_dark", image_dark);
	imshow("Origin_bright", image_bright);


	//Automatically estimate gamma Value
	float gammaValue_dark = (sum(image_dark)[0] / image_dark.total()) / 10;
	float gammaValue_bright = (sum(image_bright)[0] / image_bright.total()) / 10;
	cout << "gamma value of dark: " << gammaValue_dark << endl;
	cout << "gamma value of bright: " << gammaValue_bright << endl;
	unsigned char pix[256];

	gamma_dark = image_dark.clone();
	gamma_bright = image_bright.clone();

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gammaValue_dark) * 255.0f);
	}
	for (it = gamma_dark.begin<uchar>(), end = gamma_dark.end<uchar>(); it != end; it++) {
		*it = pix[(*it)];
	}

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gammaValue_bright) * 255.0f);
	}
	for (it = gamma_bright.begin<uchar>(), end = gamma_bright.end<uchar>(); it != end; it++)
	{
		*it = pix[(*it)];
	}

	imshow("Gamma_dark", gamma_dark);
	imshow("Gamma_bright", gamma_bright);
	waitKey(0);
	return 0;
}
#endif