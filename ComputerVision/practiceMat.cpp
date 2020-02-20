#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define IN_RANGE

#ifdef define_mat
int main(void) {
	int row = 100, col = 150;
	Mat image(row, col, CV_8UC1, Scalar(255));
	cout << "Size: " << image.size().height << ", "<<image.size().width << endl;
	imshow("Mat", image);

	waitKey(0);
	return 0;
}
#endif

#ifdef color_space_conversion
int main() {
	Mat image, image_YUV, dst;
	Mat YUV_channel[3];

	image = imread("lena.png");

	cvtColor(image, image_YUV, CV_BGR2YUV);
	split(image_YUV, YUV_channel);

	merge(YUV_channel,3,dst); //merge(YUV_channel,3,dst);

	imshow("input image", image);
	imshow("Y", YUV_channel[0]);
	imshow("U", YUV_channel[1]);
	imshow("V", YUV_channel[2]);
	imshow("YUV image", dst);

	waitKey(0);
	return 0;
}
#endif

#ifdef ROI
int main() {
	Mat image = imread("lena.png");
	// point (100,3) width: 250 height: 300
	Rect rect(100, 30, 250, 300);
	Mat rect_roi = image(rect);
	imshow("rect ROI", rect_roi);

	waitKey(0);
}
#endif

#ifdef ROI_poly
int main() {
	Mat image = imread("lena.png");
	Mat poly_roi;
	Mat poly_mask = Mat::zeros(image.size(),image.type());
	Point poly[1][4];
	poly[0][0] = Point(226, 100);
	poly[0][1] = Point(286, 100);
	poly[0][2] = Point(316, 300);
	poly[0][3] = Point(196, 300);
	const Point* ppt[1] = { poly[0]};
	int npt[] = { 4 };
	
	fillPoly(poly_mask, ppt, npt, 1, Scalar(255, 255, 255), 8);
	image.copyTo(poly_roi, poly_mask);
	imshow("Poly ROI", poly_roi);
	imshow("Poly Mask", poly_mask);

	waitKey(0);
}
#endif

#ifdef convert
int main() {
	Mat image = imread("lena.png");
	Mat after_converTo, after_convertScaleAbs;
	imshow("original", image);
	
	image.convertTo(after_converTo, CV_16SC1);	// gray screen //can choose type
	imshow("after convert to", after_converTo);	// if i want to use imshow than i should convert type?

	convertScaleAbs(image, after_convertScaleAbs, 2, 3);	//brighter screen //cannot choose type only unsinged 8bits
	imshow("after convert scale abs", after_convertScaleAbs);

	image.setTo(Scalar(0));
	imshow("after SetTo", image);
	waitKey(0);
}
#endif

#ifdef addition
int main() {
	Mat img1 = imread("lena.png");
	Mat img2 = imread("lena.png");
	Mat dst;

	add(img1, img2, dst);
	imshow("addition", dst);
	waitKey(0);
}
#endif

#ifdef Threshold
int main() {
	Mat img = imread("lena.png",0);
	Mat thresh_binary, thresh_binary_inv, thresh_trunc, thresh_2_zero, thresh_2_zero_inv;
	threshold(img, thresh_binary, 100, 255, THRESH_BINARY);
	threshold(img, thresh_binary_inv, 100, 255, THRESH_BINARY_INV);
	threshold(img, thresh_trunc, 100, 255, THRESH_TRUNC);
	threshold(img, thresh_2_zero, 100, 255, THRESH_TOZERO);
	threshold(img, thresh_2_zero_inv, 100, 255, THRESH_TOZERO_INV);

	imshow("original", img);
	imshow("threshold_binary", thresh_binary);
	imshow("threshold_binary_inv", thresh_binary_inv);
	imshow("threshold_trunc", thresh_trunc);
	imshow("threshold_tozero", thresh_2_zero);
	imshow("threshold_tozer_inv", thresh_2_zero_inv);

	waitKey(0);
	return 0;
}
#endif

#ifdef ADAPTIVE_THRESHOLD
int main() {
	Mat img = imread("lena.png", 0);
	Mat mean, gaussian;

	adaptiveThreshold(img, mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);
	adaptiveThreshold(img, gaussian, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 10);

	imshow("original", img);
	imshow("mean", mean);
	imshow("gaussian", gaussian);

	waitKey(0);
	return 0;
}
#endif

#ifdef IN_RANGE
int main() {
	Mat img = imread("hand.png");
	Mat dst;

	cvtColor(img, img, CV_BGR2YCrCb);
	inRange(img, Scalar(0, 133, 77), Scalar(255, 173, 127), dst);

	imshow("original", img);
	imshow("in range", dst);

	waitKey(0);
	return 0;
}
#endif