#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void){
	Mat color = imread("lena.png", IMREAD_COLOR);

	if (color.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}

	Mat gray;

	cvtColor(color, gray, COLOR_BGR2GRAY);
	imwrite("gray_lena.png", gray);

	namedWindow("BGR", WINDOW_AUTOSIZE);
	imshow("BGR", color);

	namedWindow("GRAY", WINDOW_AUTOSIZE);
	imshow("GRAY", gray);

	while (waitKey(0)!=27) {
	}

	return 0;
}