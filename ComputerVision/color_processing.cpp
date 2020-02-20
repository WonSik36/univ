#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define BSM

#ifdef HSI
int main() {
	// Mat image = imread("colorful.jpg");
	Mat image = imread("lena.png");
	resize(image, image, Size(image.cols/2, image.rows/2), 0, 0, CV_INTER_LINEAR);


	Mat HSV, intensity_change, mask_out, change_color;
	vector<Mat> ic(3);	// intensity change
	vector<Mat> mo(3);	// mask out
	vector<Mat> cc(3);	// change color
	int rows = image.rows;
	int cols = image.cols;
	uchar* h;
	uchar* s;
	uchar* v;	// v is intensity
	cvtColor(image, HSV, CV_BGR2HSV);
	
	// split Mat to 3 channels
	split(HSV, ic);
	split(HSV, mo);
	split(HSV, cc);

	//eqaulizingthe histogram of I mat
	equalizeHist(ic[2], ic[2]);
	
	//masking out except orange
	for (int j = 0; j < rows; j++) {
		h = mo[0].ptr<uchar>(j);
		s = mo[1].ptr<uchar>(j);
		for (int i = 0; i < cols; i++) {
			// if color is orange than keep it
			if (h[i] > 9 && h[i] < 23) s[i] = s[i];
			// else set 0
			else s[i] = 0;
		}
	}
	
	//changing all colors
	for (int j = 0; j < rows; j++) {
		h = cc[0].ptr<uchar>(j);
		s = cc[1].ptr<uchar>(j);
		for (int i = 0; i < cols; i++) {
			if (h[i] + 45 > 179) h[i] = h[i] + 45 - 179;
			else h[i] += 45;
		}
	}

	// merge 3 channels to 1 image
	merge(ic, intensity_change);
	merge(mo, mask_out);
	merge(cc, change_color);
	// convert HSV to BGR
	cvtColor(intensity_change, intensity_change, CV_HSV2BGR);
	cvtColor(mask_out, mask_out, CV_HSV2BGR);
	cvtColor(change_color, change_color, CV_HSV2BGR);

	imshow("image", image);
	imshow("intensity change", intensity_change);
	imshow("mask out", mask_out);
	imshow("change color", change_color);
	waitKey(0);
	return 0;
}
#endif

#ifdef BSM
int main() {
	// Mat image = imread("colorful.jpg");
	Mat image1 = imread("google.png");
	Mat image2 = imread("salt_noise.jpg");
	//resize(image1, image1, Size(image1.cols * 2, image1.rows * 2), 0, 0, CV_INTER_LINEAR);
	
	Mat HSV, blurr, sharpen, median;
	Mat temp16S, blurred16S, unsharpMask16S, laplacian;
	vector<Mat> bl(3);	// intensity change
	vector<Mat> sh(3);	// mask out
	vector<Mat> md(3);	// change color
	int rows = image1.rows;
	int cols = image1.cols;
	uchar* h;
	uchar* s;
	uchar* v;	// v is intensity
	cvtColor(image1, HSV, CV_BGR2HSV);

	// split Mat to 3 channels
	split(HSV, bl);
	split(HSV, sh);

	//blur of I mat
	GaussianBlur(bl[2], bl[2], Size(7, 7), 0, 0, BORDER_DEFAULT);

	//sharpen blurred image by using unsharp mask
	//bl[2].convertTo(temp16S, CV_16S);
	//blur(temp16S, blurred16S, Size(5, 5));
	//subtract(temp16S, blurred16S, unsharpMask16S);
	//scaleAdd(unsharpMask16S, 2, temp16S, temp16S);
	//temp16S.convertTo(sh[2], CV_8U);

	//sharpen blurred image by using laplacian
	bl[2].convertTo(temp16S, CV_16S);
	Laplacian(bl[2], laplacian, CV_16S, 1, 1, 0);
	scaleAdd(laplacian, -50, temp16S, temp16S);
	temp16S.convertTo(sh[2], CV_8U);

	//median filter
	cvtColor(image2, HSV, CV_BGR2HSV);
	split(HSV, md);
	medianBlur(md[2], md[2], 5); //9*9

	// merge 3 channels to 1 image
	merge(bl, blurr);
	merge(sh, sharpen);
	merge(md, median);

	// convert HSV to BGR
	cvtColor(blurr, blurr, CV_HSV2BGR);
	cvtColor(sharpen, sharpen, CV_HSV2BGR);
	cvtColor(median, median, CV_HSV2BGR);
	
	imshow("image1", image1);
	imshow("blurred image1", blurr);
	imshow("sharpen image blur", sharpen);
	imshow("image2", image2);
	imshow("median filter image2", median);
	waitKey(0);
	return 0;
}
#endif

#ifdef PSEUDO
int main() {
	//Mat gray = imread("xray.jpg", 0);
	Mat gray = imread("lena.png", 0);
	Mat color;
	// Applies a colormap on a given image
	// gray: src, color: dst, COLORMAP_JET: the color map to apply
	applyColorMap(gray, color, COLORMAP_JET);
	imshow("gray", gray);
	imshow("image", color);
	waitKey(0);
	return 0;
}
#endif