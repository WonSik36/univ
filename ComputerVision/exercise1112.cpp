#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int integralSum(Mat integral, Point lt, Point rb);

#define prob1

#ifdef prob1
int main() {
	CascadeClassifier face_clasifier;
	Mat frame, gray_frame;
	vector<Rect> faces;
	VideoCapture cap("face.mp4");
	double fps = cap.get(CAP_PROP_FPS);

	if (!cap.isOpened()) {
		cout << "Could not open the camera" << endl;
		return -1;
	}
	// configuration
	face_clasifier.load("haarcascade_frontalface_alt.xml");

	while (waitKey(1000 / fps) != 27) {
		cap >> frame;

		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		face_clasifier.detectMultiScale(gray_frame, faces,
			1.2,		// increase search scale by 10% each pass
			3,			// merge groups of three detection
			0			// not used for a new cascade
			//Size(1, 1)// min size
		);

		// draw the result
		for (int i = 0; i < faces.size(); i++) {
			Point lt(faces[i].x, faces[i].y);
			Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

			rectangle(frame, lt, rb, Scalar(0, 255, 0), 1, 4, 0);
		}

		imshow("Face detection", frame);
	}

}
#endif

#ifdef prob2
int main() {
	Mat img = imread("lena.png", 0);
	if (img.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}

	Mat integral = Mat::zeros(Size(img.cols+1,img.rows+1), CV_32S);
	int sum = 0;
	for (int i = 1; i <= img.rows; i++) {
		for (int j = 1; j <= img.cols; j++) {
			integral.at<int>(i, j) += img.at<uchar>(i-1, j-1);
			integral.at<int>(i, j) += integral.at<int>(i-1, j);
			integral.at<int>(i, j) += integral.at<int>(i, j-1);
			integral.at<int>(i, j) -= integral.at<int>(i-1, j-1);
			//cout << integral.at<int>(i, j) << " ";

			sum+= (int)img.at<uchar>(i - 1, j - 1);
		}
		//cout << endl;
	}

	int maxX = integral.rows;
	int maxY = integral.cols;

	cout << "sum: " << (int)sum << endl;
	cout << "Integral (" << maxX << "," << maxY << "): " << integral.at<int>(maxX - 1, maxY - 1) << endl;
	// 101~200 in integral -> 100~199 in img
	cout << "lt(100,100)~rb(200,200): " << integralSum(integral,Point(100,100),Point(200,200)) << endl;
	cout << "lt(150,150)~rb(170,170): " << integralSum(integral, Point(150, 150), Point(170, 170)) << endl;
	cout << "lt(200,200)~rb(210,210): " << integralSum(integral, Point(200, 200), Point(210, 210)) << endl;

	return 0;
}
#endif

int integralSum(Mat integral, Point lt, Point rb) {
	int ltx = lt.x;
	int lty = lt.y;
	int rbx = rb.x;
	int rby = rb.y;

	return integral.at<int>(rbx, rby) - integral.at<int>(rbx, lty) - integral.at<int>(ltx, rby) + integral.at<int>(ltx, lty);
}