#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	CascadeClassifier face_clasifier;
	Mat frame, gray_frame;
	vector<Rect> faces;
	VideoCapture cap(0);
	double fps = cap.get(CAP_PROP_FPS);

	if (!cap.isOpened()) {
		cout << "Could not open the camera" << endl;
		return -1;
	}
	// configuration
	face_clasifier.load("haarcascade_frontalface_alt.xml");

	while (waitKey(1000 / fps) != 27) {
		cap >> frame;
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		face_clasifier.detectMultiScale(gray_frame, faces,
			1.1,		// increase search scale by 10% each pass
			3,			// merge groups of three detection
			0,			// not used for a new cascade
			Size(30, 30)// min size
		);

		// draw the result
		for (int i = 0; i < faces.size(); i++) {
			Point lt(faces[i].x, faces[i].y);
			Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

			rectangle(frame, lt, rb, Scalar(0, 255, 0), 3, 4, 0);
		}

		imshow("Face detection", frame);
	}

}