/*
	prototype 0 : background segmentation

	background segmentation with first 10 frame accumulation  
	and update background when brightness changed dynamically

*/


#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int getBrightness(Mat frame);
void getBackground(vector<Mat> backgrounds, Mat& output);
void insertBackgroundQueue(vector<Mat>& backgrounds, Mat frame);
void throwError(string from, string e);
void deepCopy(Mat src, Mat& dst);

int main() {
	VideoCapture capture("Data/cv_live.mp4");
	Mat background, frame, gray, result, foregroundMask, foregroundImg;
	vector<Mat> background_queue;
	double fps = capture.get(CAP_PROP_FPS);
	int brightness, prev_brightness;
	int cnt = 0;
	bool initialization = true, completeBack = false;

	/**************************************** initialization ****************************************/
	{
		//set the first frame as background
		capture >> background;
		cvtColor(background, background, CV_BGR2GRAY);
		Mat tmp;
		deepCopy(background, tmp);
		background_queue.insert(background_queue.begin(), tmp);
		brightness = getBrightness(background);
		cnt++;
		prev_brightness = brightness;
		initialization = false;

		// check if file load is succeeded
		if (!capture.isOpened()) {
			cout << "can't open video file" << endl;
			return 0;
		}
	}


	/**************************************** play video ****************************************/
	while (true) {
		cout << "cnt: " << cnt << endl;


		// assertion
		{
			if (background_queue.size() == 0)
				throwError("assertion error", "background queue size is 0");
			if (background_queue.size() > 10)
				throwError("assertion error", "background queue size is bigger than 10");
		}

		// get current frame
		capture >> frame;
		if (frame.empty()) break;
		cvtColor(frame, gray, CV_BGR2GRAY);

		// check brightness of current frame and compare to previous one
		brightness = getBrightness(gray);
		cout << "brightness at frame[" << cnt << "]: " << brightness << endl;
		int gap = abs(brightness - prev_brightness);
		if (gap > 20) {
			initialization = true;
		}

		// initialize 
		if (initialization) {
			background_queue.clear();
			Mat tmp;
			deepCopy(gray, tmp);
			background_queue.insert(background_queue.begin(), tmp);
			cnt++;
			prev_brightness = brightness;
			initialization = false;
			completeBack = false;
			continue;
		}
	
		// check if background is complete 
		// else than update background
		if (!completeBack) {
			getBackground(background_queue, background);

			/*  insert current frame to background queue
				if size of queue is smaller than 10 */
			if (background_queue.size() <= 10) {
				Mat tmp;
				deepCopy(gray, tmp);
				background_queue.insert(background_queue.begin(), tmp);
			}
			else {
				throwError("whie loop in main", "background queue' size is bigger than 10");
			}

			if (background_queue.size() == 10)
				completeBack = true;
		}

		// get foreground mask by usng absolute difference
		absdiff(background, gray, foregroundMask);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);

		foregroundImg.setTo(Scalar(0));
		frame.copyTo(foregroundImg, foregroundMask);

		// get contour from foreground mask
		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;
		findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//defining bounding rectangle
		vector<Rect> boundRect(contours.size());
		for (int i = 0; i < contours.size(); i++)
			boundRect[i] = boundingRect(Mat(contours[i]));

		//draw rectangles to frame on the contours
		for (int i = 0; i < contours.size(); i++)
			rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 255), 2, 8, 0);

		/**************************************** imshow and waitkey ****************************************/
		imshow("foregroundImg", foregroundImg);
		imshow("background", background);
		imshow("foregroundMask", foregroundMask);
		imshow("gray", gray);
		imshow("original with contours", frame);

		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(10)) != 32 && ch != 27);
			if (ch == 27) break;
		}
		cnt++;
		prev_brightness = brightness;
	}
	return 0;
}

int getBrightness(Mat frame) {
	if (frame.type() != 0)
		throwError("getBrightness", "parameter type is not CV_8UC1");
	
	int sum = 0;

	for (int i = 0; i < frame.rows; i++) {
		for (int j = 0; j < frame.cols; j++) {
			sum += frame.at<uchar>(i, j);
		}
	}
	int res = sum / (frame.rows * frame.cols);
	return res;
}

void getBackground(vector<Mat> backgrounds, Mat &output) {
	output = Mat::zeros(backgrounds[0].size(), backgrounds[0].type());

	for (int i = 0; i < backgrounds.size(); i++){
		add(backgrounds[i] / (i + 1.0), (output * i) / (i + 1.0), output);     //As a result, it will be a mean of 10 frame
	}
}

void insertBackgroundQueue(vector<Mat> &backgrounds, Mat frame) {
	Mat tmp;
	deepCopy(frame, tmp);
	backgrounds.insert(backgrounds.begin(), tmp);
}

void throwError(string from,string e) {
	cout << "Error from: " << from << endl;
	cout << "error message: " << e << endl;
	exit(1);
}

void deepCopy(Mat src, Mat &dst) {
	dst = Mat(src.size(), src.type());

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	}
}