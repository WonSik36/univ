#include "cv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat image = imread("lena.png");

	if (image.empty()) {
		cerr << "read fail" << endl;
		exit(-1);
	}

	imshow("image", image);

	cout << "before wait key" << endl;
	waitKey(0);
	cout << "after wait key" << endl;
	return 0;
}