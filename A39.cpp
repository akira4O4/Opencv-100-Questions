#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_31_40.h"
#include <math.h>

using namespace cv;

void A39(Mat img)
{
	int height = img.rows;
	int width = img.cols;
	printf_s("height:%d,width:%d\n", height, width);
	Mat YCbCr = Mat::zeros(height, width, CV_32FC3);
	Mat out = Mat::zeros(height, width, CV_8UC3);

	//RGB->YCrCb
	for (int y = 0; y < height; y++) 
	{
		printf_s("y:%d\n", y);
		for (int x = 0; x < width; x++) 
		{
			//printf_s("y:%d,x:%d\n", y, x);
			// Y
			YCbCr.at<Vec3f>(y, x)[0] = (int)((float)img.at<Vec3b>(y, x)[0] * 0.114 + (float)img.at<Vec3b>(y, x)[1] * 0.5870 + (float)img.at<Vec3b>(y, x)[2] * 0.299);

			// Cb
			YCbCr.at<Vec3f>(y, x)[1] = (int)((float)img.at<Vec3b>(y, x)[0] * 0.5 + (float)img.at<Vec3b>(y, x)[1] * (-0.3323) + (float)img.at<Vec3b>(y, x)[2] * (-0.1687) + 128);

			// Cr
			YCbCr.at<Vec3f>(y, x)[2] = (int)((float)img.at<Vec3b>(y, x)[0] * (-0.0813) + (float)img.at<Vec3b>(y, x)[1] * (-0.4187) + (float)img.at<Vec3b>(y, x)[2] * 0.5 + 128);
		}
	}
	
	//ºı¡¡∂»
	for (int y = 0; y < height; y++) 
		for (int x = 0; x < width; x++) 
			YCbCr.at<Vec3f>(y, x)[0] *= 0.7;
	printf_s("ºı¡¡∂»\n");
	
	//YCrCb->RGB
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			// R
			out.at<Vec3b>(y, x)[2] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] + (YCbCr.at<Vec3f>(y, x)[2] - 128) * 1.4102);

			// G
			out.at<Vec3b>(y, x)[1] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] - (YCbCr.at<Vec3f>(y, x)[1] - 128) * 0.3441 - (YCbCr.at<Vec3f>(y, x)[2] - 128) * 0.7139);

			// B
			out.at<Vec3b>(y, x)[0] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] + (YCbCr.at<Vec3f>(y, x)[1] - 128) * 1.7718);
		}
	}

	imshow("img", img);
	imshow("out", out);
	waitKey(0);
	destroyAllWindows();

}