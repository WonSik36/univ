#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

// size 7*7 or 9*9 is appropirate one
// more size, more time to calculate
int main() {
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
	Mat image, gray,foregroundMask, backgroundImg;
	Mat erosion_3_3_mask, erosion_33_33_mask, opening_3_3_mask, opening_33_33_mask;
	Mat erosion_3_3, erosion_33_33, opening_3_3, opening_33_33;
	Mat elementCRS_3_3 = getStructuringElement(MORPH_CROSS, Size(3, 3));
	Mat elementCRS_33_33 = getStructuringElement(MORPH_CROSS, Size(33, 33));

	VideoCapture cap("background.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps) != 27) {
		cap >> image;
		if (image.empty())
			break;
		cvtColor(image, gray, CV_BGR2GRAY);
		// for decrease calculation
		resize(gray, gray, Size(640, 480));
		if (foregroundMask.empty())
			foregroundMask.create(gray.size(), gray.type());

		// perform background substraction
		// input: gray, output: foregroundMask
		bg_model->apply(gray, foregroundMask);
		// for obtain better mask
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY);
		// update background image automatically
		bg_model->getBackgroundImage(backgroundImg);

		//update erosion and opening mask
		erode(foregroundMask, erosion_3_3_mask, elementCRS_3_3);
		erode(foregroundMask, erosion_33_33_mask, elementCRS_33_33);
		morphologyEx(foregroundMask, opening_3_3_mask, MORPH_OPEN, elementCRS_3_3);
		morphologyEx(foregroundMask, opening_33_33_mask, MORPH_OPEN, elementCRS_33_33);

		/*
		// update each image to 0
		erosion_3_3 = Scalar::all(0);
		erosion_33_33 = Scalar::all(0);
		opening_3_3 = Scalar::all(0);
		opening_33_33 = Scalar::all(0);

		// update each image by using each mask
		gray.copyTo(erosion_3_3, erosion_3_3_mask);
		gray.copyTo(erosion_33_33, erosion_33_33_mask);
		gray.copyTo(opening_3_3, opening_3_3_mask);
		gray.copyTo(opening_33_33, opening_33_33_mask);*/

		// update each image to original image
		gray.copyTo(erosion_3_3);
		gray.copyTo(erosion_33_33);
		gray.copyTo(opening_3_3);
		gray.copyTo(opening_33_33);

		// get contour from each foreground mask
		// and apply contours to each image
		{
			// erosion 3*3
			{
				vector<vector<Point>> contours;
				vector<Vec4i>hierarchy;
				findContours(erosion_3_3_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
				//defining bounding rectangle
				vector<Rect> boundRect(contours.size());
				for (int i = 0; i < contours.size(); i++)
					boundRect[i] = boundingRect(Mat(contours[i]));

				int cnt = 0;
				for (int i = 0; i < contours.size(); i++) {
					rectangle(erosion_3_3, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
					cnt++;
				}
				putText(erosion_3_3, format("contour count: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
			}

			// erosion 33*33
			{
				vector<vector<Point>> contours;
				vector<Vec4i>hierarchy;
				findContours(erosion_33_33_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
				//defining bounding rectangle
				vector<Rect> boundRect(contours.size());
				for (int i = 0; i < contours.size(); i++)
					boundRect[i] = boundingRect(Mat(contours[i]));

				int cnt = 0;
				for (int i = 0; i < contours.size(); i++) {
					rectangle(erosion_33_33, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
					cnt++;
				}
				putText(erosion_33_33, format("contour count: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
			}

			// opening 3*3
			{
				vector<vector<Point>> contours;
				vector<Vec4i>hierarchy;
				findContours(opening_3_3_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
				//defining bounding rectangle
				vector<Rect> boundRect(contours.size());
				for (int i = 0; i < contours.size(); i++)
					boundRect[i] = boundingRect(Mat(contours[i]));

				int cnt = 0;
				for (int i = 0; i < contours.size(); i++) {
					rectangle(opening_3_3, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
					cnt++;
				}
				putText(opening_3_3, format("contour count: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
			}

			// opening 33*33
			{
				vector<vector<Point>> contours;
				vector<Vec4i>hierarchy;
				findContours(opening_33_33_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
				//defining bounding rectangle
				vector<Rect> boundRect(contours.size());
				for (int i = 0; i < contours.size(); i++)
					boundRect[i] = boundingRect(Mat(contours[i]));

				int cnt = 0;
				for (int i = 0; i < contours.size(); i++) {
					rectangle(opening_33_33, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
					cnt++;
				}
				putText(opening_33_33, format("contour count: %d", cnt), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);
			}
		}

		//imshow("foreground mask", foregroundMask);
		imshow("erosion 3*3", erosion_3_3);
		imshow("erosion 33*33", erosion_33_33);
		imshow("opening 3*3", opening_3_3);
		imshow("opening 33*33", opening_33_33);
		/*imshow("erosion 3*3", erosion_3_3_mask);
		imshow("erosion 33*33", erosion_33_33_mask);
		imshow("opening 3*3", opening_3_3_mask);
		imshow("opening 33*33", opening_33_33_mask);*/
	}
	return 0;
}