#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
#include <math.h>
using namespace cv;

int k_Radius = 0;

Mat _GetGobar(float Angle)
{
	float kSum = 0;
	int px = 0, py = 0;//半径内的坐标

	int sigma = 10;//方差
	int gamma = 1.2;//伽马
	const int kSize = 111;//卷积核大小
	k_Radius = floor(kSize / 2);//卷积核半径
	float kernel[kSize][kSize];//卷积核矩阵
	float theta = 0;
	float angle = Angle;
	float Lambda = 10;
	float Psi = 0;

	float max = 0;
	float min = 999;
	Mat gabor = Mat::zeros(kSize, kSize, CV_8UC1);
	//计算卷积核权值
	for (int y = 0; y < kSize; ++y)
	{
		for (int x = 0; x < kSize; ++x)
		{
			px = x - k_Radius;
			py = y - k_Radius;

			theta = angle / 180. * PI;

			float _x = cos(theta) * px + sin(theta) * py;
			float _y = sin(theta) * px + cos(theta) * py;

			kernel[y][x] = exp(-(pow(_x, 2) + pow(gamma, 2) * pow(_y, 2)) / (2 * pow(sigma, 2))) * cos(2 * PI * _x / Lambda + Psi);

			kSum += abs(kernel[y][x]);
			max = MAX(max, kernel[y][x]);
			min = MIN(min, kernel[y][x]);

		}
	}
	printf_s("%f,%f\n", max, min);

	//for (int y = 0; y < kSize; y++)
	//{
	//	for (int x = 0; x < kSize; x++)
	//	{
	//		gabor.at<uchar>(y, x) = kernel[y][x] / kSum;
	//		gabor.at<uchar>(y, x) -= min;
	//		gabor.at<uchar>(y, x) /= max;
	//		gabor.at<uchar>(y, x) *= 255;
	//	}
	//}
	return gabor;
}

void A80(Mat img)
{
	//灰度化
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();
	Mat imgGray = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	//灰度化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			imgGray.at<uchar>(y, x) = 0.2126 * (float)img.at<Vec3b>(y, x)[2] \
				+ 0.7152 * (float)img.at<Vec3b>(y, x)[1] \
				+ 0.0722 * (float)img.at<Vec3b>(y, x)[0];
		}
	}
	float angleA[] = { 0,45,90,135 };
	char name[4][5] = { "out1","out2","out3","out4" };

	Mat gaborOut[4];
	Mat imgOut[4];

	for (int i = 0; i < 4; ++i)
		gaborOut[i] = _GetGobar(angleA[i]);

	Mat out = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	printf_s("%d\n", k_Radius);
	for (int t = 0; t < 4; ++t)
	{
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWidth; ++x)
			{
				int val = 0;
				for (int dy = -k_Radius; dy < k_Radius + 1; ++dy)
				{
					for (int dx = -k_Radius; dx < k_Radius + 1; ++dx)
					{
						if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
						{
							val += imgGray.at<uchar>(y + dy, x + dx) * gaborOut[t].at<uchar>(k_Radius + dy, k_Radius + dx);

						}
					}
				}
				out.at<uchar>(y, x) = (uchar)val;
			}
		}
		imgOut[t] = out;
	}
	Mat OUT = Mat::zeros(imgHeight,imgWidth,CV_8UC1);
	for (int i = 0; i < 4; ++i)
		for (int y = 0; y < imgHeight; ++y)
			for (int x = 0; x < imgWidth; ++x)
				OUT.at<uchar>(y, x) += imgOut[i].at<uchar>(y, x)*255;
	imshow("OUT",OUT);
	waitKey(0);
	destroyAllWindows();
}