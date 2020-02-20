#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void) {
	Mat color = imread("lena.png", IMREAD_COLOR);

	if (color.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}

	Mat gray;

	cvtColor(color, gray, COLOR_BGR2GRAY);
	imwrite("gray_lena.png", gray);

	imshow("BGR", color);
	waitKey(0);

	destroyWindow("BGR");
	imshow("GRAY", gray);
	waitKey(0);

	return 0;
}