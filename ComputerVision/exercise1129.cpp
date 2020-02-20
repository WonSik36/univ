#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct MouseParams
{
	Mat img;
	vector<Point2f> in, out;
};

static void onMouse(int event, int x, int y, int, void* param)
{
	MouseParams* mp = (MouseParams*)param;
	Mat img = mp->img;
	if (event == EVENT_LBUTTONDOWN) // left button
	{
		Mat result;
		//InsertpositionfromLT.Directionisclock-wise
		mp->out.push_back(Point2f(x, y));
		if (mp->out.size() == 4)
		{
			VideoCapture background("TimeSquare.mp4");
			VideoCapture foreground("Contest.mp4");
			Mat frame1, frame2 , homo_mat;
			Mat warped, gray, mask;
			double fps = background.get(CAP_PROP_FPS);
			
			// close input window
			destroyAllWindows();

			//Compute Homographyfrom 4 matching pairs
			homo_mat = getPerspectiveTransform(mp->in, mp->out);

			while (true) {
				background >> frame1;
				foreground >> frame2;

				if (frame1.empty() || frame2.empty()) 
					break;

				//Image warping
				warpPerspective(frame2, warped, homo_mat, frame1.size());

				// get mask
				cvtColor(warped, gray, CV_BGR2GRAY);
				threshold(gray, mask, 5, 255, THRESH_BINARY);

				// copy to frame2 -> make fram1 + frame2
				warped.copyTo(frame1, mask);
				imshow("output",frame1);
				imshow("mask", mask);

				char ch = waitKey(1000 / fps);
				if (ch == 27) break; // ESC Key (exit)
				else if (ch == 32) { // SPACE Key (pause)
					while ((ch = waitKey(10)) != 32 && ch != 27);
					if (ch == 27) break;
				}
			}
		}
		else
		{
			result = img.clone();
			for (size_t i = 0; i < mp->out.size(); i++)
			{
				circle(result, mp->out[i], 3, Scalar(0, 0, 255), 5);
			}
			imshow("input", result);
		}
	}
	//Resetpositions
	if (event == EVENT_RBUTTONDOWN)
	{
		mp->in.clear();
		imshow("input", img);
	}
}
int main()
{
	VideoCapture background("TimeSquare.mp4");
	VideoCapture foreground("Contest.mp4");
	Mat frame1, frame2;
	if (!background.isOpened() || !foreground.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	background >> frame1;
	foreground >> frame2;

	MouseParams mp;
	mp.in.push_back(Point2f(0,0));
	mp.in.push_back(Point2f(frame2.cols, 0));
	mp.in.push_back(Point2f(frame2.cols, frame2.rows));
	mp.in.push_back(Point2f(0, frame2.rows));
	mp.img = frame1;

	imshow("input", frame1);
	setMouseCallback("input", onMouse, (void*)& mp);

	waitKey(0);
	return 0;
}
