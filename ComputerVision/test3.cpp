#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define PROBLEM 2

/*
	edge detection
	line detection
	face detection
	pedestrian detection
	tracking
	image transformation
*/


// face.mp4 get middle person detection
// width, height /2
#if PROBLEM==1
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
		if (frame.empty()) break;
		
		//resize
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

		// face detection
		face_clasifier.detectMultiScale(gray_frame, faces,
			1.1,		// increase search scale by 10% each pass
			3,			// merge groups of three detection
			0			// not used for a new cascade
		);

		// draw the result
		for (int i = 0; i < faces.size(); i++) {
			Point lt(faces[i].x, faces[i].y);
			Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			int size = (rb.x - lt.x) * (rb.y - lt.y);
			
			cout << "size of " << i << " " << size << endl;

			// filter by size
			if(size < 500 && size >400)
				rectangle(frame, lt, rb, Scalar(0, 255, 0), 3, 4, 0);
		}

		imshow("Face detection", frame);
	}

}
#endif


// rail way get edge detection with roi
// image transformation
// houghlinesp
#if PROBLEM==2
int main() {
	Mat img = imread("railway.jpg");
	Mat imgLeft, imgRight, edgeLeft, edgeRight;
	Rect leftRect(250, 300, 150, 200);
	Rect rightRect(450, 300, 150, 200);
	vector<Vec4i> linesLeft, linesRight;
	if (img.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}

	// get copy of image
	Mat clone(img.size(), img.type());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			clone.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
		}
	}
	

	/************************************ line detection *****************************************/
	imgLeft = img(leftRect);
	imgRight = img(rightRect);
	Canny(imgLeft, edgeLeft, 50, 200, 3);
	Canny(imgRight, edgeRight, 50, 200, 3);
	HoughLinesP(edgeLeft, linesLeft, 1, CV_PI / 180, 70, 10, 300);
	HoughLinesP(edgeRight, linesRight, 1, CV_PI / 180, 70, 10, 300);

	Vec4i l = linesLeft[0];
	line(imgLeft, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, 8);
	l = linesRight[0];
	line(imgRight, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, 8);


	/************************************ image transformation *****************************************/
	l = linesLeft[0];
	cout << "top " << l[2]+250 << " " << l[3]+300 << endl;
	cout << "bot " << l[0]+250 << " " << l[1]+300<<endl;
	l = linesRight[0];
	cout << "top " << l[0]+450 << " " << l[1]+300 << endl;
	cout << "bot " << l[2]+450 << " " << l[3]+300 << endl;

	Mat transformResult;
	vector<Point2f> in, out;

	l = linesLeft[0];
	in.push_back(Point2f(l[2]+250, l[3]+300));
	l = linesRight[0];
	in.push_back(Point2f(l[0]+450, l[1]+300));
	in.push_back(Point2f(l[2]+450, l[3]+300));
	l = linesLeft[0];
	in.push_back(Point2f(l[0]+250, l[1]+300));
	
	out.push_back(Point2f(0, 0));
	out.push_back(Point2f(200, 0));
	out.push_back(Point2f(200, 200));
	out.push_back(Point2f(0, 200));

	Mat homo_mat = getPerspectiveTransform(in,out);
	warpPerspective(clone, transformResult, homo_mat, Size(200, 200));

	imshow("line detection", img);
	imshow("transfrom result", transformResult);
	/*imshow("left", imgLeft);
	imshow("right", imgRight);
	imshow("left edge", edgeLeft);
	imshow("right edge", edgeRight);*/
	waitKey(0);
}
#endif