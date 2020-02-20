#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define video
#ifdef video
int main(void) {
	Mat frame;
	VideoCapture cap;
	// check if file exists. if none program ends
	if (cap.open("background.mp4") == 0) {
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	double time_in_msec = 0;
	int curr_frame = 0;
	int total_frame = cap.get(CAP_PROP_FRAME_COUNT);

	while (time_in_msec < 5000) {
		cap >> frame;
		if (frame.empty())
			break;
		time_in_msec = cap.get(CAP_PROP_POS_MSEC);
		curr_frame = cap.get(CAP_PROP_POS_FRAMES);
		cout << "frames: " << curr_frame << "/" << total_frame << endl;

		imshow("video", frame);
		waitKey(1000/fps);
	}
}
#endif
#ifdef webcam
int main(void) {
	Mat frame;
	VideoCapture cap(0);

	while (waitKey(16)!=27) {
		cap >> frame;
		imshow("video", frame);
	}
}
#endif