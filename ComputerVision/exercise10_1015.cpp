#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void localThreshold(Point lt, Point rb, Mat src, Mat* dst, int c);
void getHistLocalMat(int* cnt, int bucket, Point lt, Point rb, Mat img);
int getCntUnderThreshold(int* arr, int len, int th);
int getCntOverThreshold(int* arr, int len, int th);
double getMeanFromArr(int* arr, int from, int to);
double getVarianceFromArr(int* arr, int from, int to, double mean);
int getThresholdLocalMatIntraClass(int* cnt, int totalPix);
int getThresholdLocalMatInterClass(int* cnt, int totalPix);
void applyThresholdLocalMat(Point lt, Point rb, Mat src, Mat* dst, int th);

#define prob3_2

#ifdef prob1
int main() {
	Mat image, result;
	image = imread("Finger.png", 0);
	threshold(image, result, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("Input image", image);
	imshow("result", result);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat image, result;
	image = imread("adaptive_1.jpg", 0);
	adaptiveThreshold(image, result, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 51, 20);
	imshow("Input image", image);
	imshow("result", result);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob3_1
int main() {
	Mat image, result;
	image = imread("adaptive.png", 0);
	adaptiveThreshold(image, result, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 13, 25);
	imshow("Input image", image);
	imshow("result", result);
	waitKey(0);
	return 0;
	// column으로 나눠서 풀어보기
}
#endif

#ifdef prob3_2
int main() {
	Mat image, result, global;
	image = imread("adaptive.png", 0);
	result = image.clone();

	threshold(image, global, 110, 255, THRESH_BINARY);

	int sec = image.cols;

	for (int i = 0; i < sec; i++) {
		/*cout << "left top x: " << i * image.cols / sec << " y: " << 0 << endl;
		cout << "right bottom x: " << (i + 1) * image.cols / sec - 1 << " y: " << image.rows - 1 << endl;*/
		localThreshold(Point(i * image.cols / sec, 0), Point((i + 1) * image.cols / sec - 1, image.rows - 1), result, &result, 0);
	}

	imshow("Input image", image);
	imshow("result", result);
	imshow("global", global);
	waitKey(0);
	return 0;
}
#endif

/*
	local threshold function
	input: Point of left top, Point of right bottom, source Mat, destination Mat
	output: void
*/
void localThreshold(Point lt, Point rb, Mat src, Mat* dst, int c) {

	// step1: get histrogram of src mat
	int bucket = 256;
	int totalPix = (rb.x-lt.x+1)*(rb.y - lt.y +1);
	int* cnt = (int*)malloc(sizeof(int)*bucket);
	getHistLocalMat(cnt, bucket, lt, rb, src);
	
	// step2: get threshold by applying otsu method
	int th = getThresholdLocalMatInterClass(cnt, totalPix);

	//cout << "threshold: " << th << endl;
	// step3: apply threshold to locally
	applyThresholdLocalMat(lt, rb, src, dst, th-c);
	
	free(cnt);
}

void applyThresholdLocalMat(Point lt, Point rb, Mat src, Mat* dst, int th) {
	*dst = src.clone();

	for (int i = lt.y; i <= rb.y; i++) {
		for (int j = lt.x; j <= rb.x; j++) {
			if ((*dst).at<uchar>(i, j) < th) {
				(*dst).at<uchar>(i, j) = 0;
			}
			else {
				(*dst).at<uchar>(i, j) = 255;
			}
		}
	}
}

int getThresholdLocalMatIntraClass(int* cnt, int totalPix) {
	// apply intra-class variance
	double minRes = 1000000000;
	int minResTh = 0;

	for (int th = 1; th < 256; th++) {
		int underTh = getCntUnderThreshold(cnt, 256, th);
		int overTh = getCntOverThreshold(cnt, 256, th);

		if(underTh + overTh != totalPix)
			throw invalid_argument("total pixel is not matched");

		double m1 = getMeanFromArr(cnt, 0, th - 1);
		double v1 = getVarianceFromArr(cnt, 0, th - 1, m1);
		double m2 = getMeanFromArr(cnt, th, 255);
		double v2 = getVarianceFromArr(cnt, th, 255, m2);
		if (m1 == 0 || m2 == 0)
			continue;

		double res = m1 * v1 + m2 * v2;

		if (minRes > res) {
			minRes = res;
			minResTh = th;
		}
	}

		return minResTh;
}

int getThresholdLocalMatInterClass(int* cnt, int totalPix) {
	// apply inter-class variance
	double maxRes = 0;
	int maxResTh = 0;

	for (int th = 1; th < 256; th++) {
		int underTh = getCntUnderThreshold(cnt, 256, th);
		int overTh = getCntOverThreshold(cnt, 256, th);

		if (underTh + overTh != totalPix)
			throw invalid_argument("total pixel is not matched");

		double alpha = underTh / (double)totalPix;
		double beta = overTh / (double)totalPix;
		double m1 = getMeanFromArr(cnt, 0, th - 1);
		double m2 = getMeanFromArr(cnt, th, 255);
		
		if (m1 == 0 || m2 == 0)
			continue;

		double res = alpha * beta * (m1 - m2) * (m1 - m2);

		if (maxRes < res) {
			maxRes = res;
			maxResTh = th;
		}
	}

	return maxResTh;
}

void getHistLocalMat(int * cnt, int bucket, Point lt, Point rb, Mat img) {
	for (int i = 0; i < bucket; i++) {
		*(cnt + i) = 0;
	}

	for (int i = lt.y; i <= rb.y; i++) {
		for (int j = lt.x; j <= rb.x; j++) {
			int idx = img.at<uchar>(i, j) / (256/bucket);
			*(cnt+idx) = *(cnt + idx) + 1;
		}
	}
	return;
}

int getCntUnderThreshold(int* arr, int len, int th) {
	int sum = 0;
	for (int i = 0; i < th && i < len; i++) {
		sum += arr[i];
	}

	return sum;
}

int getCntOverThreshold(int* arr, int len, int th) {
	int sum = 0;
	for (int i = th; i < len; i++) {
		sum += arr[i];
	}

	return sum;
}

double getVarianceFromArr(int* arr, int from, int to, double mean) {
	double sum = 0;
	int cnt = 0;
	double var;

	for (int i = from; i <= to; i++) {
		sum += arr[i] * (i-mean) * (i - mean);
		cnt += arr[i];
	}
	if (cnt != 0)
		var = sum / cnt;
	else
		var = 0;

	//cout << "sum: " << sum << " cnt: " << cnt << endl;
	//cout << "Variance: " << var << endl;
	
	return var;
}

double getMeanFromArr(int* arr, int from, int to) {
	int sum = 0;
	int cnt = 0;
	double mean;

	for (int i = from; i <= to; i++) {
		sum += arr[i] * i;
		cnt += arr[i];
	}
	if (cnt != 0)
		mean = (double)sum / cnt;
	else
		mean = 0;
	//cout << "sum: " << sum << " cnt: " << cnt << endl;
	//cout << "Mean: " << res << endl;

	return mean;
}