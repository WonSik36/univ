#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
Mat drawHistogram(Mat src);
#define prob2

#ifdef prob1
int main() {
	Mat image;
	Mat hist_graph;

	image = imread("lena.png", 0);
	if (!image.data) exit(1); //Check image


	hist_graph = drawHistogram(image);

	imshow("Input Image", image);
	imshow("Hist Graph", hist_graph);

	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat img = imread("apple.jpg");
	Rect rect(160, 140, 180, 230);
	Mat rect_roi = img(rect);
	
	double imgNormHist[8] = { 0, };
	double roiNormHist[8] = { 0, };

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			imgNormHist[((img.at<Vec3b>(i,j)[2]) / 32)]+=1.0f;
		}
	}
	for (int i = 0; i < 8; i++) {
		imgNormHist[i] = imgNormHist[i] / ((double)img.rows * img.cols);
	}
	cout << "Normalized Histogram of image" << endl;
	for (int i = 0; i < 8; i++) {
		cout << imgNormHist[i] << " ";
	}
	cout << endl<<endl;

	for (int i = 0; i < rect_roi.rows; i++) {
		for (int j = 0; j < rect_roi.cols; j++) {
			roiNormHist[((rect_roi.at<Vec3b>(i,j)[2]) / 32)]+= 1.0f;
		}
	}
	for (int i = 0; i < 8; i++) {
		roiNormHist[i] = roiNormHist[i] / ((double)rect_roi.rows * rect_roi.cols);
	}
	cout << "Normalized Histogram of ROI" << endl;
	for (int i = 0; i < 8; i++) {
		cout << roiNormHist[i] << " ";
	}
	cout << endl;
	return 0;
}
#endif

Mat drawHistogram(Mat src) {
	Mat hist, histImage;
	// establish the number of bins
	int i, hist_w, hist_h, bin_w, histSize;
	float range[] = { 0, 256 };	// range of input
	const float* histRange = { range };
	hist_w = 512;
	hist_h = 400;
	histSize = 16; // number of bins ex) 8 bins -> 8
	bin_w = cvRound((double)hist_w / histSize); 
	// compute the histograms
	// &src: input image, 1: #of srcimage, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask
	// hist: output histogram, 1: histogram dimension, &histSize: array of histogram size,  &histRange: array of histogram¡¯s boundaries
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	//draw the histogram
	histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
	// normalize the result to [0, histImage.rows]
	// hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary
	// NORM_MINMAX: normalization type, -1: when negative, the ouputarray has the same type as src, Mat(): optional mask
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (i = 0; i < histSize; i++)
	{
		rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i + 32 / histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1, CV_AA, 0);
	}
	return histImage;
}