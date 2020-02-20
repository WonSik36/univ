#include <iostream>
#include "cv.hpp"
#include "ml.hpp" // for gaussian mixture model

using namespace cv::ml;
using namespace std;
using namespace cv;


int main(int argc, const char* argv[]) {

	////// Car Detection ///////////////
	CascadeClassifier car_classifier;
	Mat frame, grayFrame;
	vector<Rect> cars;

	// open the web cam
	VideoCapture cap("Data/Go_1.mp4");

	// check if we succeeded
	if (!cap.isOpened()) {
		cout << "Could not open camera" << endl;
		return -1;
	}

	// face detection configuration - training result
	car_classifier.load("cars.xml");

	while (true) {
		// get a new frame from webcam
		cap >> frame;
		if (frame.empty()) break;

		// convert captured frame to gray scale & equalize
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		equalizeHist(grayFrame, grayFrame);

		//Size
		Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
		car_classifier.detectMultiScale(
			grayFrame,
			cars,
			1.05, // increase search scale by 10% each pass
			5, // merge groups of three detections - if more than three detection
			0, // not used for a new cascade
			Size(0, 0),
			frameSize// min size - if face size is smaller than Size(30,30) it will not be detected
			//, Size() // max size
		);

		// draw the results
		for (int i = 0; i < cars.size(); i++) {
			Point lb(cars[i].x + cars[i].width, cars[i].y + cars[i].height);
			Point tr(cars[i].x, cars[i].y);
			rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
		}

		// print the ouptut
		imshow("Car Detection", frame);
		if (waitKey(33) == 27) break;

	}



	return 0;

}





