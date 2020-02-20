#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define	prob1

#ifdef prob1
int main() {
	Mat image, image_at, image_data;
	int value_at, value_ptr, value_data;

	image = imread("lena.png");
	image_at = image.clone();
	image_data = image.clone();

	for (int i = 0; i < image_at.rows; i+=2) {
		for (int j = 0; j < image_at.cols; j++) {
			image_at.at<Vec3b>(i, j)[0] = 0;
			image_at.at<Vec3b>(i, j)[1] = 0;
			image_at.at<Vec3b>(i, j)[2] = 255;
		}
	}
	int channels = 3;
	uchar* data = (uchar*)image_data.data;
	for (int i = 0; i < image_data.rows; i += 2) {
		for (int j = 0; j < image_data.cols; j++) {
			data[(i * image.cols + j) * channels + 0] = 0;
			data[(i * image.cols + j) * channels + 1] = 0;
			data[(i * image.cols + j) * channels + 2] = 255;
		}
	}

	imshow("image_at", image_at);
	imshow("image_data", image_data);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat image = imread("lena.png");
	int value, value_B, value_G, value_R, channels;

	MatIterator_ <Vec3b> it3, end3;

	for (it3 = image.begin<Vec3b>(), end3 = image.end<Vec3b>(); it3 != end3; ++it3) {
		(*it3)[0] = 255;
	}
	imshow("iterator", image);
	waitKey(0);
	return 0;
}
#endif

#ifdef prob3
int main() {
	Mat image, image_gray;
	int value_at, value_ptr, value_data;

	image = imread("lena.png",0);
	value_at = image.at<uchar>(120, 100);
	int channels = 1;

	uchar* p = image.ptr<uchar>(120);
	value_ptr = p[100 * channels];

	uchar* data = (uchar*)image.data;
	value_data = data[(120 * image.cols + 100) * channels];

	uchar* ptr_at = &image.at<uchar>(120, 100);
	uchar* ptr_ptr = &p[100 * channels];
	uchar* ptr_data = &data[(120 * image.cols + 100) * channels];
	cout << "at " << value_at << " address: "<< (void*)ptr_at <<endl;
	cout << "ptr " << value_ptr << " address: " << (void*)ptr_ptr << endl;
	cout << "data " << value_data << " address: " << (void*)ptr_data << endl;
	//waitKey(0);
	return 0;
}
#endif

#ifdef prob4
int main() {
	Mat image = imread("lena.png");
	Mat gray = imread("lena.png", 0);
	int value, value_B, value_G, value_R, channels;

	// try both image & gray
	channels = gray.channels();
	MatIterator_ <uchar> it, end;
	MatIterator_ <Vec3b> it3, end3;

	it = gray.begin<uchar>();
	int count = 0;
	for (it3 = image.begin<Vec3b>(), end3 = image.end<Vec3b>(); it3 != end3; ++it3, count++) {
		int aver = ((*it3)[0] + (*it3)[1] + (*it3)[2]) / 3;
		int grayInt = *it;
		cout << "AVERAGE: " << aver << ", gray: " << grayInt << endl;
		if (count % 3 == 0)
			it++;
	}

	return 0;
}
#endif