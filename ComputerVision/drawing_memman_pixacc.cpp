#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define	COPY

#ifdef RECTANGLE
int main() {
	Mat image = imread("lena.png");
	Point p(300, 300);
	Rect rect = Rect(10, 10, 100, 100); // LT position, width, height
	
	circle(image, p, 100, Scalar(255, 0, 0), 4, CV_AA, 0);
	rectangle(image, rect, Scalar(255, 0, 0), 4, CV_AA, 0);
	imshow("image", image);

	waitKey(0);
	return 0;
}
#endif

#ifdef LINE
int main() {
	Mat image = imread("lena.png");
	Point p1(25, 25), p2(50, 50), p3(75, 75);
	line(image, p1, p2, Scalar(255, 0, 0), 10, 8, 0);
	line(image, p2, p3, Scalar(0, 255, 0), 10, CV_AA, 0);
	imshow("image", image);
	waitKey(0);

	return 0;
}
#endif

#ifdef POLYGON
int main() {
	Mat image = Mat::zeros(512, 512, CV_8UC3);	// black image
	int w = 400;
	Point trapezoid[2][4];
	trapezoid[0][0] = Point(w * 2 / 6, w / 4);			// 0 1
	trapezoid[0][1] = Point(w * 4 / 6, w / 4);			// 3 2
	trapezoid[0][2] = Point(w * 5 / 6, w * 3 / 4);
	trapezoid[0][3] = Point(w / 6, w * 3 / 4);

	trapezoid[1][0] = Point(300,200);			// 0 1
	trapezoid[1][1] = Point(400,100);			// 3 2
	trapezoid[1][2] = Point(400,200);

	const Point* ppt[2] = { trapezoid[0], trapezoid[1] };
	int npt[2] = { 4 ,3};
	// Mat& img: image, , const Point** pts: ppt, const int* npts: npt,int ncontours: 2
	fillPoly(image, ppt, npt, 2, Scalar(255, 255, 255), 8);	
	imshow("image", image);
	waitKey(0);

	return 0;
}
#endif

#ifdef TEXT
int main() {
	// Create black empty images
	Mat image = Mat::zeros(400, 600, CV_8UC3);
	int w = image.cols;
	int h = image.rows;
	putText(image, format("width: %d, height: %d", w,h),Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4, CV_AA);
	imshow("image", image);
	waitKey(0);
	return(0);
}
#endif

#ifdef COPY
int main() {
	Mat m1 = (Mat_ < double >(3, 3)<<1, 2, 3, 4, 5, 6, 7, 8, 9);
	Mat m_shallow = m1;
	Mat m_deep = m1.clone();
	//Mat copy2 = Mat(Size(3,3), 6); // m1.type() is 6
	Mat copy2 = (Mat_ < double >(3, 3) << 0, 0, 0, 0, 0, 0, 0, 0, 0);

	m1.copyTo(copy2);
	
	cout<<m1.type()<<endl;
	cout << "m1 =\n" << m1 << endl << endl;	// 1 2 3 4 5 6 7 8 9
	cout << "m_shallow=\n" << m_shallow << endl << endl; // 1 2 3 4 5 6 7 8 9
	cout << "m_deep =\n" << m_deep << endl << endl; // 1 2 3 4 5 6 7 8 9
	cout << "copyTo =\n" << copy2 << endl << endl; // 1 2 3 4 5 6 7 8 9
		
	cout << "********** After Update **********" << endl << endl;
	
	// Update m1
	m1.at < double >(0, 0) = 100;
	cout << "m1 =\n" << m1 << endl << endl;	// 100 2 3 4 5 6 7 8 9
	cout << "m_shallow=\n" << m_shallow << endl << endl; // 100 2 3 4 5 6 7 8 9
	cout << "m_deep =\n" << m_deep << endl << endl; // 1 2 3 4 5 6 7 8 9
	cout << "copyTo =\n" << copy2 << endl << endl; // 1 2 3 4 5 6 7 8 9

	//waitKey(0);
	return 0;
}
#endif

#ifdef ACCESS
int main() {
	Mat image, image_gray;
	int value, value_B, value_G, value_R, channels;
	
	image = imread("lena.png");
	image_gray = imread("lena.png", 0);
	//try both image & image_gray
	channels = image_gray.channels();
	//channels = image.channels();
	//At operator
	switch (channels) {
		case 1:
			value = image_gray.at<uchar>(50, 100);
			cout << "value: " << value << endl;
			break;
		case 3:
			value_B = image.at<Vec3b>(50, 100)[0];
			value_G = image.at<Vec3b>(50, 100)[1];
			value_R = image.at<Vec3b>(50, 100)[2];
			cout << "value at (100,50): " << value_B << " " << value_G << " " << value_R << endl;
			break;
	}
	//waitKey(0);
	return 0;
}
#endif

#ifdef POINTER
int main() {
	Mat image = imread("lena.png");
	int value, value_B, value_G, value_R, channels;
	channels = image.channels();
	//Pointer
	uchar* p = image.ptr<uchar>(50);
	value_B = p[100 * channels + 0];
	value_G = p[100 * channels + 1];
	value_R = p[100 * channels + 2];
	cout << "value at (100,50): " << value_B << " " << value_G << " " << value_R << endl;

	return 0;
}
#endif

#ifdef DATA
int main() {
	Mat image;
	int value, value_B, value_G, value_R, channels;
	image = imread("lena.png");
	channels = image.channels();
			
	//Data member function
	uchar* data = (uchar*)image.data;
	value_B = data[(50 * image.cols + 100) * channels + 0];
	value_G = data[(50 * image.cols + 100) * channels + 1];
	value_R = data[(50 * image.cols + 100) * channels + 2];
	
	cout << "value at (100,50): " << value_B << " " << value_G << " " << value_R << endl;

	return 0;
}
#endif

#ifdef ITERATOR
int main() {
	Mat image = imread("lena.png");
	Mat gray = imread("lena.png", 0);
	int value, value_B, value_G, value_R, channels;
		
	// try both image & gray
	channels = gray.channels();
	MatIterator_ <uchar> it, end;
	MatIterator_ <Vec3b> it3, end3;
	
	switch (channels) {
		case 1:
			for (it=gray.begin<uchar>(), end=gray.end<uchar>(); it != end; ++it){
					value = *it;
					cout << "value: " << value << endl;
			}
			break;
		case 3:
			for (it3 = image.begin<Vec3b>(), end3 = image.end<Vec3b>(); it3 != end3; ++it3){
				value_B = (*it3)[0];
				value_G = (*it3)[1];
				value_R = (*it3)[2];
				cout << "B: " << value_B << ", G: " << value_G << ", R: " << value_R << endl;
			}
			break;
	}
	
	return 0;
}
#endif

#ifdef COMPARE
int main() {
	Mat image, image_gray;
	int value_at, value_ptr, value_data;

	image = imread("lena.png", 0);
	value_at = image.at<uchar>(120, 100);
	int channels = 1;

	uchar* p = image.ptr<uchar>(120);
	value_ptr = p[100 * channels];

	uchar* data = (uchar*)image.data;
	value_data = data[(120 * image.cols + 100) * channels];

	uchar* ptr_at = &image.at<uchar>(120, 100);
	uchar* ptr_ptr = &p[100 * channels];
	uchar* ptr_data = &data[(120 * image.cols + 100) * channels];
	cout << "at " << value_at << " address: " << (void*)ptr_at << endl;
	cout << "ptr " << value_ptr << " address: " << (void*)ptr_ptr << endl;
	cout << "data " << value_data << " address: " << (void*)ptr_data << endl;
	//waitKey(0);
	return 0;
}
#endif