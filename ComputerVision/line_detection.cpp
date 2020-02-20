#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define CIRCLES

#ifdef LINES
int main() {
	Mat image, edge, result;
	float rho, theta, a, b, x0, y0;
	Point p1, p2;
	vector<Vec2f> lines;
	image = imread("houghcircles.jpg");
	result = image.clone();
	cvtColor(image, image, CV_BGR2GRAY);
	Canny(image, edge, 50, 200, 3);
	//applying Hough Transform to find lines in the image
	//edge: input Mat, lines: output vector of lines
	//1: (rho) distance resolution of the accumulator in pixels
	//CV_PI/180: (theta) angle resolution of the accumulator in radians
	//150: (threshold) accumulator threshold parameter
	HoughLines(edge, lines, 1, CV_PI / 180, 70);
	for (int i = 0; i < lines.size(); i++) {
		rho = lines[i][0];
		theta = lines[i][1];
		a = cos(theta);
		b = sin(theta);
		x0 = a * rho;
		y0 = b * rho;
		p1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * a));
		p2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * a));

		line(result, p1, p2, Scalar(0, 0, 255), 3, 8);
	}
	imshow("Input image", image);
	imshow("edge", edge);
	imshow("Hough Transform", result);
	waitKey(0);
}
#endif

#ifdef LINESP
int main() {
	Mat image, edge, result;
	vector<Vec4i> lines;
	image = imread("houghcircles.jpg");
	result = image.clone();
	cvtColor(image, image, CV_BGR2GRAY);
	Canny(image, edge, 50, 200, 3);
	//edge: input Mat, lines: output vector of lines
	//1: (rho) distance resolution of the accumulator in pixels
	//CV_PI/180: (theta) angle resolution of the accumulator in radians
	//50: (threshold) accumulator threshold parameter
	//10: (minLineLength) minimum line length.
	//300: (maxLineGap) Maximum allowed gap between points on the same line to link them
	HoughLinesP(edge, lines, 1, CV_PI / 180, 70, 10, 300);
	for (int i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 8);
	}

	imshow("Input image", image);
	imshow("edge", edge);
	imshow("Hough Transform", result);
	waitKey(0);
}
#endif

#ifdef CIRCLES
int main() {
	Mat image, edge, result;
	Point p1, p2;
	vector<Vec3f> circles;
	image = imread("houghcircles.jpg");
	result = image.clone();
	cvtColor(image, image, CV_BGR2GRAY);
	Canny(image, edge, 50, 200, 3);

	HoughCircles(image, circles, HOUGH_GRADIENT, 1, 20, 50, 35);
	for (int i = 0; i < circles.size(); i++) {
		Vec3f c = circles[i];
		circle(result,Point(c[0],c[1]),c[2],Scalar(255,0,255),3,8);
	}

	imshow("Input image", image);
	imshow("edge", edge);
	imshow("Hough Transform", result);
	waitKey(0);
}
#endif