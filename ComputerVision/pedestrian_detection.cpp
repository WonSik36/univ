#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat frame;
	vector<Rect> found;
	int i;
	char ch;
	// openthevideofile
	//VideoCapture cap("pedestrian_detection2.mp4");
	VideoCapture cap("Data/cv_live.mp4");
	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}
	// detector(48x96 template)
	HOGDescriptor hog(
		Size(48, 96),
		Size(16, 16),
		Size(8, 8),
		Size(8, 8),
		9);
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
	while (1) {
		// inputimage
		cap >> frame;
		
		if (frame.empty()) break;
		
		//resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));

		// detect
		hog.detectMultiScale(
			frame,
			found,
			1.0,
			Size(8, 8),
			Size(32, 32),
			1.1,
			2);
		
		// drawresults(boundingboxes)
		for (i = 0; i < (int)found.size(); i++)
			rectangle(frame, found[i], Scalar(0, 255, 0), 2);

		// display
		imshow("Pedestrian Detection", frame);
		ch = waitKey(10);
		if (ch == 27) break;// ESC Key
		else if(ch == 32){ // SPACE Key
			while ((ch = waitKey(10)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}

	return 0;
}