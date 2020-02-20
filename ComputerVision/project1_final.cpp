#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int getBrightness(Mat frame);
void getBackground(vector<Mat> backgrounds, Mat& output);
void insertBackgroundQueue(vector<Mat>& backgrounds, Mat frame); // deprecated
void throwError(string from, string e);
void deepCopy(Mat src, Mat& dst);

int main() {
	/* variable for playing video */
	VideoCapture capture("Data/cv_live.mp4");
	if (!capture.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	double fps = capture.get(CAP_PROP_FPS);
	Mat frame;
	Mat gray;
	int cnt = 0;
	int brightness, prev_brightness;
	/*VideoWriter writer;
	Size vSize = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
	writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, vSize, true);*/

	/* variable for background segmentation */
	Mat background, foregroundMask, foregroundImg, element;
	vector<Mat> background_queue;
	bool initialization = true;

	/* variable for pedestrian detection */
	vector<Rect> found;
	HOGDescriptor hog(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

	//set the first frame as background
	capture >> background;
	cvtColor(background, background, CV_BGR2GRAY);
	Mat tmp;
	deepCopy(background, tmp);
	background_queue.insert(background_queue.begin(), tmp);
	prev_brightness = getBrightness(background);
	element = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
	cnt++;
	initialization = false;

	/**************************************** play video ****************************************/
	while (true) {

		/* assertion */
		{
			if (background_queue.size() == 0)
				throwError("assertion error", "background queue size is 0");
			if (background_queue.size() > 10)
				throwError("assertion error", "background queue size is bigger than 10");
		}

		/* get current frame */
		capture >> frame;
		if (frame.empty()) break;
		cvtColor(frame, gray, CV_BGR2GRAY);

		/* check brightness of current frame and compare to previous one */
		brightness = getBrightness(gray);
		int gap = abs(brightness - prev_brightness);
		// if gap is bigger than 20, than it needs to update background queue
		if (gap > 20) {
			initialization = true;
		}

		/* initialize background by using current frame */
		if (initialization) {
			background_queue.clear();
			Mat tmp;
			deepCopy(gray, tmp);
			background_queue.insert(background_queue.begin(), tmp);
			cnt++;
			prev_brightness = brightness;
			initialization = false;
		}

		/*************** update background and background queue ***************/

		getBackground(background_queue, background);

		/*  insert current frame to background queue
			if queue has more than 10 frames than pop out */

		if (background_queue.size() > 10)
			throwError("main function", "background queue' size is bigger than 10");
		Mat tmp;
		deepCopy(gray, tmp);
		background_queue.insert(background_queue.begin(), tmp);
		if (background_queue.size() > 10)
			background_queue.pop_back();


		/*************** background segmentation ***************/

		/* get foreground mask by usng absolute difference */
		absdiff(background, gray, foregroundMask);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);
		morphologyEx(foregroundMask, foregroundMask, MORPH_OPEN, element);

		/* get foreground img by usng foreground mask */
		foregroundImg.setTo(Scalar(0));
		frame.copyTo(foregroundImg, foregroundMask);


		/*************** pedestrain detection ***************/
		if (background_queue.size() < 10) {
			/* detect pedestrain */
			hog.detectMultiScale(frame, found, 1.2, Size(8, 8), Size(32, 32), 1.05, 3);

			/* draw results(bounding boxes) */
			for (int i = 0; i < (int)found.size(); i++)
				rectangle(frame, found[i], Scalar(0, 0, 255), 2);

			putText(frame, format("number of moving object: %d", found.size()), Point(10, 10), FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 255), 2);

		} else {

		/*************** background segmentation ***************/

			/* get foreground mask by usng absolute difference */
			absdiff(background, gray, foregroundMask);
			GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
			threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);

			/* get contour from foreground mask */
			vector<vector<Point>> contours;
			vector<Vec4i>hierarchy;
			findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			/* defining bounding rectangle */
			vector<Rect> boundRect(contours.size());
			for (int i = 0; i < contours.size(); i++)
				boundRect[i] = boundingRect(Mat(contours[i]));

			/* draw rectangles to image on the contours */
			int objectCnt = 0;
			for (int i = 0; i < contours.size(); i++) {
				if (boundRect[i].width * boundRect[i].height > 2000) {
					rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
					objectCnt++;
				}
			}
			putText(frame, format("number of moving object: %d", objectCnt), Point(10, 10), FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 255), 2);
		}

		/*************** imshow and waitkey ***************/
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
		
		//writer.write(frame);
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

void getBackground(vector<Mat> backgrounds, Mat& output) {
	output = Mat::zeros(backgrounds[0].size(), backgrounds[0].type());

	for (int i = 0; i < backgrounds.size(); i++) {
		add(backgrounds[i] / (i + 1.0), (output * i) / (i + 1.0), output);     //As a result, it will be a mean of 10 frame
	}
}

void insertBackgroundQueue(vector<Mat>& backgrounds, Mat frame) {
	Mat tmp;
	deepCopy(frame, tmp);
	backgrounds.insert(backgrounds.begin(), tmp);
}

void throwError(string from, string e) {
	cout << "Error from: " << from << endl;
	cout << "error message: " << e << endl;
	exit(1);
}

void deepCopy(Mat src, Mat& dst) {
	if (src.type() != CV_8UC1)
		throwError("deepCopy", "src type is not CV_8UC1");

	dst = Mat(src.size(), src.type());

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<uchar>(i, j) = src.at<uchar>(i, j);
		}
	}
}