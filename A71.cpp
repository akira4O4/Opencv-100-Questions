#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
using namespace cv;


void A71(Mat img)
{
	int imgHeight = img.rows;
	int imgWeight = img.cols;

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

	Mat out = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	//蓝色范围180 - 260
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			int h = imgHSV.at<Vec3f>(y, x)[0];
			if (h > 180 && h < 260)
				out.at<uchar>(y, x) = 255;
			else
				out.at<uchar>(y, x) = 0;
		}
	}

	//HSV->RGB
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			H = imgHSV.at<Vec3f>(y, x)[0];
			S = imgHSV.at<Vec3f>(y, x)[1];
			V = imgHSV.at<Vec3f>(y, x)[2];

			C = S;
			_H = H / 60;
			X = C * (1 - abs(fmod((H / 60), 2) - 1));
			R = G = B = V - C;

			if (_H < 1)
			{
				R += C;
				G += X;
			}
			else if (_H < 2)
			{
				R += X;
				G += C;
			}
			else if (_H < 3)
			{
				G += C;
				B += X;
			}
			else if (_H < 4)
			{
				G += X;
				B += C;
			}
			else if (_H < 5)
			{
				R += X;
				B += C;
			}
			else if (_H < 6)
			{
				R += C;
				B += X;
			}

			imgRGB.at<cv::Vec3b>(y, x)[0] = (uchar)(B * 255);
			imgRGB.at<cv::Vec3b>(y, x)[1] = (uchar)(G * 255);
			imgRGB.at<cv::Vec3b>(y, x)[2] = (uchar)(R * 255);
		}
	}

	imshow("img", img);
	imshow("RGB-HSV", imgHSV);
	imshow("HSV-RGB", imgRGB);

	waitKey(0);
	destroyAllWindows();
}

