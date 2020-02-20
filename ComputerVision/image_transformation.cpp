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
		mp->in.push_back(Point2f(x, y));
		if (mp->in.size() == 4)
		{
			//Compute Homographyfrom 4 matching pairs
			Mat homo_mat = getPerspectiveTransform(mp->in, mp->out);
			//Imagewarping
			warpPerspective(img, result, homo_mat, Size(200, 200));
			imshow("output", result);
		}
		else
		{
			result = img.clone();
			for (size_t i = 0; i < mp->in.size(); i++)
			{
				circle(result, mp->in[i], 3, Scalar(0, 0, 255), 5);
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
	Mat imput = imread("perspective.png");
	imshow("input", imput);
	MouseParams mp;
	mp.out.push_back(Point2f(0, 0));
	mp.out.push_back(Point2f(200, 0));
	mp.out.push_back(Point2f(200, 200));
	mp.out.push_back(Point2f(0, 200));
	mp.img = imput;
	setMouseCallback("input", onMouse, (void*)& mp);
	waitKey();
	return 0;
}
