#include "cv.hpp"
#include <iostream>

#define PROBLEM 1

using namespace cv;
using namespace std;

#if PROBLEM==1
struct MouseParams
{
	VideoCapture video1;
	VideoCapture video2;
	Mat img;
	vector<Point2f> in, out;
};

static void onMouse_imageTranform(int event, int x, int y, int, void* param);

int main()
{
	VideoCapture cap1("Contest.mp4");
	VideoCapture cap2("TimeSquare.mp4");
	Mat display;

	cap2 >> display;

	imshow("input", display);
	moveWindow("input", 0, 0);

	MouseParams mp;
	mp.in.push_back(Point2f(0, 0));
	mp.in.push_back(Point2f(cap1.get(CAP_PROP_FRAME_WIDTH), 0));
	mp.in.push_back(Point2f(cap1.get(CAP_PROP_FRAME_WIDTH), cap1.get(CAP_PROP_FRAME_HEIGHT)));
	mp.in.push_back(Point2f(0, cap1.get(CAP_PROP_FRAME_HEIGHT)));
	mp.video1 = cap1;
	mp.video2 = cap2;
	mp.img = display;

	setMouseCallback("input", onMouse_imageTranform, (void*)& mp);
	waitKey();
	return 0;
}

static void onMouse_imageTranform(int event, int x, int y, int, void* param)
{
	MouseParams* mp = (MouseParams*)param;
	Mat img_bg = mp->img;
	Mat input, timeSquare, result;
	Mat homo_mat;
	Mat mask_fg, mask_bg, img_fg, white;

	if (event == EVENT_LBUTTONDOWN)
	{
		mp->out.push_back(Point2f(x, y));
		if (mp->out.size() == 4)
		{
			homo_mat = getPerspectiveTransform(mp->in, mp->out);

			while (1) {
				mp->video1 >> input;
				mp->video2 >> timeSquare;
				if (input.empty()) break;

				white = Mat(input.rows, input.cols, CV_8U, 255);
				warpPerspective(white, mask_fg, homo_mat, Size(mp->img.cols, mp->img.rows));
				warpPerspective(input, img_fg, homo_mat, Size(mp->img.cols, mp->img.rows));

				threshold(mask_fg, mask_bg, 100, 255, THRESH_BINARY_INV);

				img_fg.copyTo(result, mask_fg);
				timeSquare.copyTo(result, mask_bg);

				imshow("output", result);
				waitKey(16);
			}
		}
		else
		{
			result = img_bg.clone();
			for (size_t i = 0; i < mp->out.size(); i++)
			{
				circle(result, mp->out[i], 3, Scalar(0, 0, 255), 5);
			}
			imshow("input", result);
		}
	}

	if (event == EVENT_RBUTTONDOWN)
	{
		mp->in.clear();
		imshow("input", img_bg);
	}
}

#endif


#if PROBLEM==2
int main()
{
	VideoCapture cap1("Contest.mp4");
	VideoCapture cap2("TimeSquare.mp4");

	vector<Point2f> points, points_trans;
	Point2f TL(2, 171), TR(183, 165), BL(2, 386), BR(190, 326);
	Mat input, timeSquare, result;
	Mat homo_mat;
	Mat mask_fg, mask_bg, img_fg, white;

	points.push_back(Point2f(0, 0));
	points.push_back(Point2f(cap1.get(CAP_PROP_FRAME_WIDTH), 0));
	points.push_back(Point2f(cap1.get(CAP_PROP_FRAME_WIDTH), cap1.get(CAP_PROP_FRAME_HEIGHT)));
	points.push_back(Point2f(0, cap1.get(CAP_PROP_FRAME_HEIGHT)));

	points_trans.push_back(TL);
	points_trans.push_back(TR);
	points_trans.push_back(BR);
	points_trans.push_back(BL);

	homo_mat = getPerspectiveTransform(points, points_trans);

	while (1) {
		cap1 >> input;
		cap2 >> timeSquare;
		if (input.empty() || timeSquare.empty()) break;

		white = Mat(input.rows, input.cols, CV_8U, 255);
		warpPerspective(white, mask_fg, homo_mat, Size(timeSquare.cols, timeSquare.rows));
		warpPerspective(input, img_fg, homo_mat, Size(timeSquare.cols, timeSquare.rows));

		threshold(mask_fg, mask_bg, 100, 255, THRESH_BINARY_INV);

		img_fg.copyTo(result, mask_fg);
		timeSquare.copyTo(result, mask_bg);

		imshow("output", result);
		waitKey(16);
	}
	return 0;
}

#endif
