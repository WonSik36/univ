#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define MOD 10

int main() {
	// variable for pedestrian detection
	Mat frame;
	vector<Rect> found;
	VideoCapture cap("Data/cv_live.mp4");
	double fps = cap.get(CAP_PROP_FPS);
	HOGDescriptor hog(Size(48, 96),Size(16, 16),Size(8, 8),Size(8, 8),9);
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	// variable for tracking
	Mat m_backproj, hsv;
	vector<Mat> m_model3d;
	vector<Rect> m_rc;
	const float hrange[] = { 0,180 };
	const float vrange[] = { 0,255 };
	const float srange[] = { 0,255 };
	const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
	const int channels[] = { 0, 1, 2 };
	const int hist_sizes[] = { 16, 16, 16 };
	bool tracking = false;
	long cnt = 0;

	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		tracking = true;

		if (cnt == 120) {
			cout << "cnt: " << cnt << endl;
		}

		// if first frame than detect pedestrian
		if (cnt%MOD == 0) {
			// detect pedestrain
			hog.detectMultiScale(frame,found,1.2,Size(8, 8),Size(32, 32),1.05,3);

			// clear roi vector
			m_rc.clear();
			m_model3d.clear();

			// set roi
			for (int i = 0; i < found.size(); i++) {
				Rect rc = found[i];
				Mat m_model3d_tmp;

				Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
				ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255);
				Mat roi(hsv, rc);
				calcHist(&roi, 1, channels, mask, m_model3d_tmp, 3, hist_sizes, ranges); // calculate histogram -> get feature

				m_rc.push_back(rc);
				m_model3d.push_back(m_model3d_tmp);
			}

			// draw the result
			for (int i = 0; i < found.size(); i++) {
				Point lt(found[i].x, found[i].y);
				Point rb(found[i].x + found[i].width, found[i].y + found[i].height);

				rectangle(frame, lt, rb, Scalar(0,0,255), 2, 4, 0);
			}

			tracking = false;
		}

		// if it is not first frame than tracking pedestrian by roi
		if (tracking) {
			for (int i = 0; i < found.size(); i++) {
				cout << "before i: " << (i + 1) << " x: " << m_rc[i].x << " y: " << m_rc[i].y << endl;
				calcBackProject(&hsv, 1, channels, m_model3d[i], m_backproj, ranges); // calculate back project to m_backproj with m_model3d
				//CamShift(m_backproj, m_rc[i], cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 1));
				meanShift(m_backproj, m_rc[i], TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
				rectangle(frame, m_rc[i], Scalar(0, 255, 0), 2, 4, 0);
				cout << "after i: " << (i + 1) << " x: " << m_rc[i].x << " y: " << m_rc[i].y << endl;
			}
		}

		// image display
		imshow("pedestrain detection with tracking", frame);

		// user input
		char ch = waitKey(1000 / fps);
		if (ch == 27) break; // ESC Key (exit)
		else if (ch == 32) { // SPACE Key (pause)
			while ((ch = waitKey(1000 / fps)) != 32 && ch != 27);
			if (ch == 27) break;
		}
		cnt++;
	}

}