#include "cv.hpp"
#include <iostream>
#define PROBLEM 1

using namespace cv;
using namespace std;

#if PROBLEM==1

int main()
{
	VideoCapture cap("background.mp4");
	Mat image, sub, result;
	double fps = cap.get(CV_CAP_PROP_FPS);
	vector<Mat> Background_Queue;                   //Queue : First In First Out

	while (1)
	{

		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;

		cap >> image;
		result = image.clone();
		if (image.empty())
		{
			return -1;
		}

		Mat background = Mat::zeros(image.rows, image.cols, CV_8UC1);
		cvtColor(image, image, CV_BGR2GRAY);


		if (Background_Queue.size() < 10)
		{
			Background_Queue.insert(Background_Queue.begin(), image);
		}
		else
		{
			Background_Queue.pop_back();                                      //eliminate oldest
			Background_Queue.insert(Background_Queue.begin(), image);         //add new
		}

		for (int i = 0; i < Background_Queue.size(); i++)
		{
			add(Background_Queue[i] / (i + 1.0), (background * i) / (i + 1.0), background);     //As a result, it will be a mean of 10 frame
		}

		absdiff(background, image, sub);
		threshold(sub, sub, 20, 255, THRESH_BINARY);

		findContours(sub, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		vector<Rect> boundRect(contours.size());
		int rect_num = 0;

		for (int i = 0; i < contours.size(); i++)
		{
			boundRect[i] = boundingRect(contours[i]);                          //automatically find rectangle boundary Func
			if (boundRect[i].area() > 200)
			{
				rectangle(result, boundRect[i], Scalar(255, 255, 255), 2, 8);
				rect_num++;
			}
		}

		putText(result, format("# Rect: %d", rect_num), Point2f(10, 30), FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 255), 2);
		imshow("result", result);
		imshow("background", background);

		waitKey(1000 / fps);
	}
	return 0;
}
#endif
