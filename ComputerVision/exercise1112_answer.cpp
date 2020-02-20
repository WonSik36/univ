#include "cv.hpp"
#include <iostream>

#define PROBLEM 1
using namespace cv;
using namespace std;

#if PROBLEM == 1
int main() {
	CascadeClassifier face_classifier;
	Mat frame, grayframe;
	vector<Rect> faces;

	VideoCapture cap("face.mp4");
	float h = cap.get(CAP_PROP_FRAME_HEIGHT), w = cap.get(CAP_PROP_FRAME_WIDTH);
	float resize_factor = 1.0 / 2.0;
	int max_size, face_size;
	Rect max_face;

	if (!cap.isOpened()) {
		cout << "Could not open camera" << endl;
		return -1;
	}

	face_classifier.load("haarcascade_frontalface_alt.xml");

	while (true) {
		cap >> frame;
		if (frame.empty()) break;

		resize(frame, frame, Size(w * resize_factor, h * resize_factor));
		cvtColor(frame, grayframe, COLOR_BGR2GRAY);

		face_classifier.detectMultiScale(grayframe,
			faces,
			1.1,
			3,
			0,
			Size(30, 30)
		);

		max_size = 0;

		for (int i = 0; i < faces.size(); i++) {
			face_size = faces[i].size().width * faces[i].size().height;
			if (face_size > max_size) {
				max_size = face_size;
				max_face = faces[i];
			}
		}

		Point lb(max_face.x + max_face.width, max_face.y + max_face.height);
		Point tr(max_face.x, max_face.y);
		rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);

		imshow("Face Detection", frame);
		if (waitKey(33) == 27) break;
	}

}
#endif

#if PROBLEM == 2

int main() {
	Mat image = imread("lena.png", 0);

	Mat integral_img(Size(image.cols + 1, image.rows + 1), CV_32S, Scalar::all(0));
	int sum_pixels = 0;
	Point2f LT(100, 100), BR(300, 300);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			integral_img.at<int>(i + 1, j + 1) = integral_img.at<int>(i + 1, j) +
				integral_img.at<int>(i, j + 1) -
				integral_img.at<int>(i, j) +
				image.at<uchar>(i, j);
		}
	}

	sum_pixels = integral_img.at<int>(BR.y + 1, BR.x + 1) -
		integral_img.at<int>(BR.y + 1, LT.x) -
		integral_img.at<int>(LT.y, BR.x + 1) +
		integral_img.at<int>(LT);

	cout << sum_pixels << endl;

	return 0;
}

#endif
