#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
using namespace cv;


void A71(Mat img)
{
	int imgHeight = img.rows;
	int imgWeight = img.cols;
	int channel = img.channels();
	Mat imgHSV = Mat::zeros(imgHeight, imgWeight, CV_32FC3);
	Mat imgRGB = Mat::zeros(imgHeight, imgWeight, CV_8UC3);

	float R, G, B;
	float H, S, V;
	double C, X, _H;
	float Cmax, Cmin, delta;

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			//获取RGB
			R = (float)img.at<Vec3b>(y, x)[2] / 255;
			G = (float)img.at<Vec3b>(y, x)[1] / 255;
			B = (float)img.at<Vec3b>(y, x)[0] / 255;

			Cmax = fmax(R, fmax(G, B));
			Cmin = fmin(R, fmin(G, B));
			delta = Cmax - Cmin;

			if (delta == 0)
				H = 0;
			else if (Cmin == B)
				H = 60 * (G - R) / delta + 60;
			else if (Cmin == R)
				H = 60 * (B - G) / delta + 180;
			else if (Cmin == G)
				H = 60 * (R - B) / delta + 300;

			//计算S(0-1)
			if (Cmax == 0)
				S = 0;
			else
				S = delta;
			//S = delta/Cmax;效果不好

		//计算V(0-1)
			V = Cmax;

			imgHSV.at<Vec3f>(y, x)[0] = H;
			imgHSV.at<Vec3f>(y, x)[1] = S;
			imgHSV.at<Vec3f>(y, x)[2] = V;
		}
	}

	Mat bin = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	//蓝色范围180 - 260
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			int h = imgHSV.at<Vec3f>(y, x)[0];
			if (h > 180 && h < 260)
				bin.at<uchar>(y, x) = 0;
			else
				bin.at<uchar>(y, x) = 1;
		}
	}
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			bin.at<uchar>(y, x) *= 255;
		}
	}
	cv::imshow("_bin", bin);
	Mat out = Mat::zeros(imgHeight, imgWeight, CV_8UC3);
	//out*imgsrc
	for (int y = 0; y < imgHeight; ++y)
		for (int x = 0; x < imgWeight; ++x)
			for (int c = 0; c < channel; ++c)
				out.at<Vec3b>(y, x)[c] = img.at<Vec3b>(y, x)[c] * bin.at<uchar>(y, x);


	imshow("img", img);
	imshow("out", out);

	waitKey(0);
	destroyAllWindows();
}

