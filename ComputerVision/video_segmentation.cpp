#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define DRAW

#ifdef BACKGROUND
int main() {
	VideoCapture capture("background.mp4");
	Mat image, sum, avg;
	int cnt = 2;
	double fps = capture.get(CAP_PROP_FPS);

	capture >> avg;
	while (waitKey(1000 / fps) != 27) {
		if (!capture.read(image)) break;
		add(image / cnt, avg * (cnt - 1) / cnt, avg);
		imshow("avg", avg);
		cnt++;
	}
	return 0;
}
#endif

#ifdef ABSDIFF
int main() {
	VideoCapture capture("background.mp4");
	Mat background, image, gray, result, foregroundMask, foregroundImg;
	double fps = capture.get(CAP_PROP_FPS);

	//set the first frame as background
	capture >> background;
	cvtColor(background, background, CV_BGR2GRAY);

	while (waitKey(1000 / fps) != 27) {
		if (capture.grab() == 0) break;

		capture.retrieve(image);
		cvtColor(image, gray, CV_BGR2GRAY);

		absdiff(background, gray, foregroundMask);
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

#ifdef MOG2
int main() {
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
	Mat image, foregroundMask, backgroundImg, foregroundImg;
	VideoCapture cap("background.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> image;
		if (image.empty())
			break;

		// for decrease calculation
		resize(image, image, Size(640, 480));
		if (foregroundMask.empty())
			foregroundMask.create(image.size(), image.type());
		
		// perform background substraction
		// input: image, output: foregroundMask
		bg_model->apply(image, foregroundMask);
		// for obtain better mask
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY);
		// get foreground image using mask
		foregroundImg = Scalar::all(0);
		image.copyTo(foregroundImg, foregroundMask);
		// update background image automatically
		bg_model->getBackgroundImage(backgroundImg);

		imshow("foreground mask", foregroundMask);
		imshow("foreground image", foregroundImg);
		if (!backgroundImg.empty()) {
			imshow("mean background image", backgroundImg);
		}
	}
	return 0;
}
#endif

#ifdef COUNT
int main() {
	Mat gray = imread("contours.png", 0);
	Mat result;
	threshold(gray, result, 230, 255, THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	// input: result, output: contours
	findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	putText(result, format("contour count: %d", contours.size()), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(128), 4);
	imshow("contours", result);
	imshow("original", gray);
	waitKey(0);
}
#endif

#ifdef DRAW
int main() {
	Mat gray = imread("contours.png", 0);
	Mat original = imread("contours.png");
	Mat result;
	threshold(gray, result, 230, 255, THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy; // vector with 4 dimension
	findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	//defining bounding rectangle
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
		boundRect[i] = boundingRect(Mat(contours[i]));

	//draw rectangles on the contours
	for (int i = 0; i < contours.size(); i++)
		rectangle(original, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,0), 2, 8, 0);

	imshow("contours", result);
	imshow("original", original);
	waitKey(0);
}
#endif

#ifdef ABSDIFF_DRAW
int main() {
	VideoCapture capture("background.mp4");
	Mat background, image, gray, result, foregroundMask, foregroundImg;
	double fps = capture.get(CAP_PROP_FPS);

	//set the first frame as background
	capture >> background;
	cvtColor(background, background, CV_BGR2GRAY);

	while (waitKey(1000 / fps) != 27) {
		if (capture.grab() == 0) break;

		capture.retrieve(image);
		if (image.empty())
			break;
		cvtColor(image, gray, CV_BGR2GRAY);

		// get foreground mask by usng absolute difference
		absdiff(background, gray, foregroundMask);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);

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
			rectangle(image, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,255), 2, 8, 0);

		//foregroundMask.copyTo(foregroundImg);
		foregroundImg.setTo(Scalar(0));
		gray.copyTo(foregroundImg, foregroundMask);


		//imshow("foregroundImg", foregroundImg);
		//imshow("background", background);
		imshow("foregroundMask", foregroundMask);
		imshow("gray", gray);
		imshow("original with contours", image);
	}
	return 0;
}
#endif

#ifdef MOG2_DRAW
int main() {
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
	Mat image, foregroundMask, backgroundImg, foregroundImg;
	VideoCapture cap("background.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> image;
		if (image.empty())
			break;
		// for decrease calculation
		resize(image, image, Size(640, 480));
		if (foregroundMask.empty())
			foregroundMask.create(image.size(), image.type());

		// perform background substraction
		// input: image, output: foregroundMask
		bg_model->apply(image, foregroundMask);
		// for obtain better mask
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY);
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

		imshow("foreground mask", foregroundMask);
		imshow("foreground image", foregroundImg);
		imshow("original with contour", image);
		if (!backgroundImg.empty()) {
			imshow("mean background image", backgroundImg);
		}
	}
	return 0;
}
#endif