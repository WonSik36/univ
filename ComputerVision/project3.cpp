#include "cv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void loadForeground(Mat foregrounds[]);
void overlayImage(const Mat& background, const Mat& foreground, Mat& output, Point lt, Point rb);
void deepCopy(const Mat& src, Mat& dst);

#define FOREGROUND_NUM 3
string foreground_filename[FOREGROUND_NUM] = { "apeach.png", "lion.png", "muji.png" };

int main(int argc, char* argv[]) {
	Mat background, foregrounds[FOREGROUND_NUM], output, gray, check;
	CascadeClassifier face_clasifier;
	vector<Rect> faces;

	// 1. get img file name
	string filename;
	cout << "type image: ";
	cin >> filename;

	background = imread(filename);
	
	loadForeground(foregrounds);
	if (background.empty()) {
		cerr << "there is no such file" << endl;
		exit(1);
	}
	cvtColor(background, gray, COLOR_BGR2GRAY);

	// 2. face detection
	face_clasifier.load("haarcascade_frontalface_alt.xml");
	face_clasifier.detectMultiScale(gray, faces,
		1.1,		// increase search scale by 10% each pass
		3,			// merge groups of three detection
		0,			// not used for a new cascade
		Size(30, 30)// min size
	);

	// if no faces in image return it
	if (faces.size() == 0) {
		cout << "No faces were detected" << endl;
		return 0;
	}

	// 3. check whether user want to overlay img to face 
	cout << "detected faces: " << faces.size() << endl;
	deepCopy(background, output);
	bool flag = false;
	int cnt = 0;
	for (int i = 0; i < faces.size(); i++) {
		Point lt(faces[i].x, faces[i].y);
		Point rb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);

		cout << "number of current face: " << (i + 1) << endl;
		cout << "lt x: " << lt.x << ", y: " << lt.y << endl;
		cout << "rb x: " << rb.x << ", y: " << rb.y << endl;

		deepCopy(background, check);
		rectangle(check, lt, rb, Scalar(0, 255, 0), 3, 4, 0);
		imshow("If you want to overlay press y, else n", check);

		char in = waitKey(0);

		// 4. if yes, than overlay img to face
		if (in == 'y' || in == 'Y') {
			overlayImage(background, foregrounds[cnt++%FOREGROUND_NUM], output, lt, rb);
			deepCopy(output, background);
			flag = true;
		// else check next one
		} else if (in == 'n' || in == 'N') {
			continue;
		// other input than retry
		} else {
			i--;
		}
	}
	
	// if no faces were chosen, than return it
	if (!flag) {
		cout << "no faces were chosen" << endl;
		return 0;
	}

	// 5. show output image
	destroyAllWindows();
	imshow("result", output);
	waitKey(0);
	destroyAllWindows();

	// 6. get output img file name and save it
	cout << "type save image name: ";
	cin >> filename;
	imwrite(filename, output);

	return 0;
}

void loadForeground(Mat foregrounds[]) {
	for (int i = 0; i < FOREGROUND_NUM; i++) {
		foregrounds[i] = imread(foreground_filename[i], IMREAD_UNCHANGED);
		if (foregrounds[i].empty()) {
			cerr << "foreground image load failed" << endl;
			exit(1);
		}
	}
}

// reference: http://jepsonsblog.blogspot.com/2012/10/overlay-transparent-image-in-opencv.html
void overlayImage(const Mat& background, const Mat& foreground, Mat& output, Point lt, Point rb) {
	if (foreground.type() != 24) {
		cout << "foreground image must be BGRA(png.gif)" << endl;
		exit(1);
	}

	Mat resized_foreground;
	Point center((lt.x + rb.x) / 2, (lt.y + rb.y) / 2);
	int width = (rb.x - lt.x);
	int height = (rb.y - lt.y);

	// calculate width, height
	if (width > height) {
		double ratio = (double)height / foreground.rows;
		width = ratio * foreground.cols;
		lt.x = center.x - width / 2;
		rb.x = center.x + width / 2;
	} else {
		double ratio = (double)width / foreground.cols;
		height = ratio * foreground.rows;
		lt.y = center.y - height / 2;
		rb.y = center.y + height / 2;
	}

	// resize foreground image
	resize(foreground, resized_foreground, Size(width, height));

	// copy to output
	deepCopy(background, output);

	for (int i = 0; i < resized_foreground.rows; i++) {
		for (int j = 0; j < resized_foreground.cols; j++) {
			double opacity = resized_foreground.at<Vec4b>(i, j)[3] / 255.0;
			if (opacity > 0) {
				output.at<Vec3b>(i+lt.y,j+lt.x)[0] = resized_foreground.at<Vec4b>(i, j)[0];
				output.at<Vec3b>(i+lt.y,j+lt.x)[1] = resized_foreground.at<Vec4b>(i, j)[1];
				output.at<Vec3b>(i+lt.y,j+lt.x)[2] = resized_foreground.at<Vec4b>(i, j)[2];
			}
		}
	}
}

void deepCopy(const Mat& src, Mat& dst) {
	dst = Mat(src.size(), src.type());

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
	}
}