#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define PROBLEM 3

#if PROBLEM==1
int main() {
	Mat image;
	image = imread("lena.png", 0);
	blur(image, image, Size(7, 7));
	threshold(image, image, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

	imshow("result", image);
	waitKey(0);
	return 0;
}
#endif

#if PROBLEM==2
int main() {
	Mat image = imread("balancing.jpg");
	Mat HSV, HSVtoBGR;
	vector<Mat> splitHSV(3), splitBGR(3);
	cvtColor(image, HSV, CV_BGR2HSV);
	split(HSV, splitHSV);
	equalizeHist(splitHSV[2], splitHSV[2]);
	merge(splitHSV, HSV);
	cvtColor(HSV, HSVtoBGR, CV_HSV2BGR);

	split(HSVtoBGR, splitBGR);
	double imgNormHist[8] = { 0, };

	for (int i = 0; i < splitBGR[2].rows; i++) {
		for (int j = 0; j < splitBGR[2].cols; j++) {
			imgNormHist[(splitBGR[2].at<uchar>(i, j) / 32)] += 1.0f;
		}
	}
	for (int i = 0; i < 8; i++) {
		imgNormHist[i] = imgNormHist[i] / ((double)splitBGR[2].rows * splitBGR[2].cols);
	}
	cout << "Normalized Histogram of Result R-channel" << endl;
	for (int i = 0; i < 8; i++) {
		cout << imgNormHist[i] << " ";
	}
	cout << endl << endl;

	//imshow("original", image);
	imshow("Intensity equalization", HSVtoBGR);
	waitKey(0);
	return 0;
}
#endif

#if PROBLEM==3
int main() {
	VideoCapture cap("background.mp4");
	Mat image, sub, background;
	bool flag = false;
	double fps = cap.get(CV_CAP_PROP_FPS);
	vector<Mat> Background_Queue;           
	Mat elementCRS = getStructuringElement(MORPH_CROSS, Size(5, 5));

	while (waitKey(1000 / fps) != 27)
	{

		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;

		cap >> image;
		if (image.empty())
		{
			return -1;
		}

		cvtColor(image, image, CV_BGR2GRAY);

		
		if (!flag) {
			background = Mat::zeros(image.rows, image.cols, CV_8UC1);
			if (Background_Queue.size() < 10)
			{
				Background_Queue.insert(Background_Queue.begin(), image);
			}
			for (int i = 0; i < Background_Queue.size(); i++)
			{
				add(Background_Queue[i] / (i + 1.0), (background * i) / (i + 1.0), background);
			}
			if (Background_Queue.size() == 10)
				flag = true;
			cout << "backgorund updated" << endl;
		}

		absdiff(background, image, sub);
		threshold(sub, sub, 40, 255, THRESH_BINARY);
		morphologyEx(sub, sub, MORPH_CLOSE, elementCRS);

		//imshow("original image", image);
		imshow("binary image", sub);
	}
	return 0;
}
#endif