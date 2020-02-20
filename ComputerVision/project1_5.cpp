/*
	prototype 3 : background segmentation and pedestrain detection

	background segmentation with first frame
	and update background when brightness changed dynamically

	update foreground image with foreground mask
	use foreground image to pedestrain detection
*/

#include "cv.hpp"
#include <iostream>

#define GAP 30

using namespace cv;
using namespace std;

/**************************************** functions ****************************************/
int getBrightness(Mat frame);
void getBackground(vector<Mat> backgrounds, Mat& output);
void insertBackgroundQueue(vector<Mat>& backgrounds, Mat frame); // deprecated
void throwError(string from, string e);
void deepCopy(Mat src, Mat& dst);

Mat adjustIntensity(Mat mat, int brightness);
int getMatAverage(Mat image);
double getGamma(Mat image, int brightness);
double _getGamma(Mat image, double left, double right, int brightness);
double getLogAver(double a, double b);

int main() {
	/**************************************** variable ****************************************/
	/* variable for play video */
	VideoCapture capture("Data/cv_live.mp4");
	double fps = capture.get(CAP_PROP_FPS);
	Mat frame, gray;
	int cnt = 0;
	int brightness, prev_brightness;

	/* variable for background segmentation */
	Mat background, foregroundMask, foregroundImg;
	bool initialization = true;

	/* variable for pedestrian detection */
	vector<Rect> found;
	HOGDescriptor hog(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

	/**************************************** initialization ****************************************/
	{
		//set the first frame as background
		capture >> background;
		cvtColor(background, background, CV_BGR2GRAY);
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

		/* assertion */
		{
		}

		/* get current frame */
		capture >> frame;
		if (frame.empty()) break;
		cvtColor(frame, gray, CV_BGR2GRAY);

		/* check brightness of current frame and compare to previous one */
		brightness = getBrightness(gray);
		cout << "brightness at frame[" << cnt << "]: " << brightness << endl;
		int gap = abs(brightness - prev_brightness);
		// if gap is bigger than 10, than update background
		if (gap > 10) {
			initialization = true;
		}

		/* initialize background by using current frame */
		if (initialization) {
			cnt++;
			prev_brightness = brightness;
			background = adjustIntensity(background, brightness);
			initialization = false;
			continue;
		}

		/*************** background segmentation ***************/

		/* get foreground mask by usng absolute difference */
		absdiff(background, gray, foregroundMask);
		GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
		threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);
		/* get foreground img by usng foreground mask */
		foregroundImg.setTo(Scalar(0));
		frame.copyTo(foregroundImg, foregroundMask);

		/*************** pedestrain detection ***************/

		/* detect pedestrain */
		hog.detectMultiScale(frame, found, 1.2, Size(8, 8), Size(32, 32), 1.05, 3);

		/* draw results(bounding boxes) */
		for (int i = 0; i < (int)found.size(); i++)
			rectangle(frame, found[i], Scalar(0, 0, 255), 2);

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
	dst = Mat(src.size(), src.type());

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	}
}

Mat adjustIntensity(Mat mat, int brightness) {
	Mat HSV, ret;
	vector<Mat> splitHSV(3);

	cvtColor(mat, HSV, CV_BGR2HSV);
	split(HSV, splitHSV);

	// calculate correct gamma
	float gamma = getGamma(splitHSV[2], brightness);
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

double getGamma(Mat image, int brightness) {
	Mat clone = image.clone();
	return _getGamma(clone, 0.00001f, 100000.0f,brightness);
}

double _getGamma(Mat image, double left, double right, int brightness) {
	double gamma = getLogAver(left, right);
	int leftTh = brightness-GAP, rightTh = brightness+GAP;
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
		return _getGamma(image, left, gamma,brightness);
	}
	else {
		return _getGamma(image, gamma, right,brightness);
	}
}

double getLogAver(double a, double b) {
	return pow(10, (log10(a) + log10(b)) / 2);
}