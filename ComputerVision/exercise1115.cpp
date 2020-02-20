#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define prob2

#ifdef prob1
int main() {
	Mat frame;
	vector<Rect> found;
	int i;
	char ch;
	// openthevideofile
	VideoCapture cap("pedestrian_detection2.mp4");
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

		// draw results(bounding boxes)
		for (i = 0; i < (int)found.size(); i++)
			rectangle(frame, found[i], Scalar(0, 255, 0), 2);

		// put text on frame
		putText(frame, format("pedestrian: %d", found.size()), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1,Scalar(0,255,0),2);

		// display
		imshow("Pedestrian Detection", frame);
		ch = waitKey(10);
		if (ch == 27) break;// ESC Key
		else if (ch == 32) { // SPACE Key
			while ((ch = waitKey(10)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}

	return 0;
}
#endif

#ifdef prob2
int main() {
	Mat frame;
	vector<Rect> found, old_found;
	vector<vector<Rect>> found_queue;
	int i;
	char ch;
	// openthevideofile
	VideoCapture cap("pedestrian_detection2.mp4");
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
			1.05,
			2);

		if (found_queue.size() < 15){
			found_queue.insert(found_queue.begin(), found);

			// draw results(bounding boxes)
			for (i = 0; i < (int)found.size(); i++)
				rectangle(frame, found[i], Scalar(0, 255, 0), 1);
		}else{
			old_found = found_queue.back();

			found_queue.pop_back();                                      //eliminate oldest
			found_queue.insert(found_queue.begin(), found);         //add new

			// draw rectangle which is stopping
			for (i = 0; i < (int)found.size(); i++) {
				bool flag = false;
				for (int j = 0; j < old_found.size(); j++) {
					if (abs(found[i].x - old_found[j].x) < 10 && abs(found[i].y - old_found[j].y) < 10) {
						flag = true;
						break;
					}
				}

				if (flag)
					rectangle(frame, found[i], Scalar(0, 0, 255), -1);
				else 
					rectangle(frame, found[i], Scalar(0, 255, 0), 1);
			}
		}

		// put text on frame
		putText(frame, format("pedestrian: %d", found.size()), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

		// display
		imshow("Pedestrian Detection", frame);
		ch = waitKey(10);
		if (ch == 27) break;// ESC Key
		else if (ch == 32) { // SPACE Key
			while ((ch = waitKey(10)) != 32 && ch != 27);
			if (ch == 27) break;
		}
	}

	return 0;
}
#endif