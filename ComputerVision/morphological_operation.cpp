#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define VIDEO_CLOSE

#ifdef EROD_DILA
int main() {
	Mat image, erosionELL, dilationELL, erosionRECT, dilationRECT, erosionCRS, dilationCRS;
	//Other options:MORPH_RECT, MORPH_CROSS
	Mat elementELL = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
	Mat elementRECT = getStructuringElement(MORPH_RECT, Size(10, 10));
	Mat elementCRS = getStructuringElement(MORPH_CROSS, Size(10, 10));
	
	image = imread("water_coins.jpg", 0);
	threshold(image, image, 128, 255, THRESH_BINARY);
	
	erode(image, erosionELL, elementELL);
	erode(image, erosionRECT, elementRECT);
	erode(image, erosionCRS, elementCRS);
	dilate(image, dilationELL, elementELL);
	dilate(image, dilationRECT, elementRECT);
	dilate(image, dilationCRS, elementCRS);

	imshow("Binary image", image);
	imshow("ErosionELL", erosionELL);
	imshow("DilationELL", dilationELL);
	imshow("Erosion RECT", erosionRECT);
	imshow("Dilation RECT", dilationRECT);
	imshow("Erosion CRS", erosionCRS);
	imshow("Dilation CRS", dilationCRS);

	waitKey(0);
	return 0;
}
#endif

#ifdef OPEN_CLOSE
int main() {
	Mat image, opening, closing, element;
	image = imread("water_coins.jpg", 0);
	threshold(image, image, 128, 255, THRESH_BINARY);
	element = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	
	morphologyEx(image, closing, MORPH_CLOSE, element);
	morphologyEx(image, opening, MORPH_OPEN, element);

	imshow("Binary image", image);
	imshow("opening", opening);
	imshow("closing", closing);
	waitKey(0);
}
#endif

#ifdef VIDEO_CLOSE
int main() {
	VideoCapture capture("background.mp4");
	Mat background, image, gray, result, foregroundMask, foregroundImg;
	double fps = capture.get(CAP_PROP_FPS);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));

	//set the first frame as background
	capture >> background;
	cvtColor(background, background, CV_BGR2GRAY);

	while (waitKey(1000 / fps) != 27) {
		if (capture.grab() == 0) break;
		capture.retrieve(image);

		cvtColor(image, gray, CV_BGR2GRAY);

		absdiff(background, gray, foregroundMask);
		morphologyEx(foregroundMask,foregroundMask,MORPH_CLOSE, element);
		threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY);

		//foregroundMask.copyTo(foregroundImg);
		foregroundImg.setTo(Scalar(0));
		gray.copyTo(foregroundImg, foregroundMask);

		imshow("foregroundImg", foregroundImg);
		imshow("foregroundMask", foregroundMask);
		imshow("background", background);
		imshow("original", gray);
	}
	return 0;
}
#endif