#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob4
//prob1: display "lena.png" using oepnCV as color image, gray image
#ifdef prob1
int main(void) {
	Mat colorImage = imread("lena.png");
	Mat grayImage = imread("lena.png",0);

	if (colorImage.empty()||grayImage.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}

	imshow("lena_color", colorImage);
	imshow("lena_gray", grayImage);
	waitKey(0);
	return 0;
}
#endif

//prob2: display "background.mp4" video
#ifdef prob2
int main(void) {
	Mat frame;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("background.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);

	while (waitKey(1000 / fps)!=27) {
		cap >> frame;
		if (frame.empty())
			break;
		imshow("video", frame);
	}
	return 0;
}
#
#endif

//prob3: display "background.mp4" video two times faster and slower
#ifdef prob3
int main(void) {
	Mat frameFast, frameSlow;
	VideoCapture capFast,capSlow;
	// check if file exists. if none program ends
	if (capFast.open("background.mp4") == 0 || capSlow.open("background.mp4") == 0) {
		return -1;
	}
	double fps = capFast.get(CAP_PROP_FPS);
	
	long pos = 0;	//***
	while (waitKey(1000 / (2 * fps))!=27) {
		capFast >> frameFast;
		int curr_frame_fast = capFast.get(CAP_PROP_POS_FRAMES);
		if (pos % 4 == 0) {
			int curr_frame_slow = capSlow.get(CAP_PROP_POS_FRAMES);
			cout << "fast: " << curr_frame_fast << " slow: " <<curr_frame_slow << " " << pos << endl;
			capSlow >> frameSlow;
		}
		pos++;
		// if initially frameSlow is not assigned than it is empty
		if (frameSlow.empty())
			break;
		imshow("Faster", frameFast);
		imshow("Slower", frameSlow);
	}
	return 0;
}
#endif


//display 3-channel matrix with size is FHD
#ifdef prob4
int main(void) {
	int row = 1080, col = 1920;
	Mat image(row, col, CV_8UC3, Scalar(0,255,255));
	cout << "Size: " << image.size().height << ", " << image.size().width << endl;
	imshow("Mat", image);

	waitKey(0);
	return 0;
}
#endif