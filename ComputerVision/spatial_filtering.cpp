#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define AVERAGE_FILTER

#ifdef AVERAGE_FILTER
int main() {
	Mat image, AvgImg, GaussianImg15, GaussianImg30;
	image = imread("lena.png");
	// Blurs an image using the normalized box filter
	// image: input image, AvgImg: output image, Size(5, 5): blurring kernel size
	blur(image, AvgImg, Size(5, 5));
	// Blurs an image using a Gaussian filter
	// image: input image, GaussianImg: output image, Size(5, 5): Gaussian kernel size
	// 1.5: Gaussian kernel standard deviation in X direction
	GaussianBlur(image, GaussianImg15, Size(5, 5), 1.5);
	GaussianBlur(image, GaussianImg30, Size(5, 5), 3.0); //more standard deviation more similar weight to each pixel
	imshow("Input image", image);
	imshow("Average image", AvgImg);
	imshow("Gaussian blurred image 1.5", GaussianImg15);
	imshow("Gaussian blurred image 5.0", GaussianImg30);
	waitKey(0);
	return 0;
}
#endif

#ifdef SHARPEN_2ND
int main() {
	Mat image, laplacian, abs_laplacian, sharpening, image16S, result;
	image = imread("Moon.png", 0);
	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);
	// calculates the Laplacian of an image
	// image: src, laplacian: dst, CV_16S: desire depth of dst, 
	// 1: aperture size used to compute second-derivative (optional)
	// 1: optional scale factor for the computed Laplacian values
	// 0: optional delta value that is added to the result
	image.convertTo(image16S, CV_16S);
	Laplacian(image, laplacian, CV_16S, 1, 1, 0);
	
	//convertScaleAbs(laplacian, abs_laplacian); // CV_16S -> CV8_U and absolute operation because laplacian can cause minus number
	//sharpening = abs_laplacian + image1;
	
	//sharpening = laplacian + image16S;
	scaleAdd(laplacian, -1, image16S, sharpening);

	sharpening.convertTo(result, CV_8U);
	imshow("Input image", image);
	imshow("Laplacian", laplacian);
	//imshow("abs_Laplacian", abs_laplacian);
	imshow("Sharpening", result);
	waitKey(0);
}

#endif

#ifdef MEDIAN_FILTER
int main() {
	Mat image = imread("saltnpepper.png", 0);
	imshow("SaltAndPepper", image);
	Mat mf1, mf2;
	// Blurs an image using the median filter
	// image: src, mf1: dst, 3: aperture size(must be odd and greater than 1)
	medianBlur(image, mf1, 3); //3*3
	imshow("MedianFiltered1", mf1);
	medianBlur(image, mf2, 9); //9*9
	imshow("MedianFiltered2", mf2);
	waitKey(0);
	return 0;
}
#endif

#ifdef UNSHARP_MASK
int main() {
	Mat image = imread("Moon.png", 0);
	Mat img16S, BlurredImg16S, unsharpMask16S, sharpenImg16S;
	Mat result;
	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);

	image.convertTo(img16S, CV_16S);
	blur(img16S, BlurredImg16S, Size(5, 5));
	subtract(img16S, BlurredImg16S, unsharpMask16S);
	scaleAdd(unsharpMask16S, 0.5, img16S, sharpenImg16S);
	sharpenImg16S.convertTo(result, CV_8U);

	imshow("original", image);
	imshow("result", result);

	waitKey(0);
	return 0;
}
#endif