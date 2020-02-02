#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
#include <math.h>
using namespace cv;


void A77(Mat)
{
	int sigma = 10;//方差
	int gamma = 1.2;//伽马
	const int kSize = 111;//卷积核大小
	int kRadius = floor(kSize / 2);//卷积核半径
	float kernel[kSize][kSize];//卷积核矩阵
	double kSum = 0;
	int x_ = 0, y_ = 0;//半径内的坐标
	float theta = 0;
	float angle = 0;
	float Lambda = 10;
	float Psi = 0;
	int max = 0;
	int min=999;
	Mat gabor = Mat::zeros(kSize, kSize, CV_8UC1);
	//计算卷积核权值
	for (int y = 0; y < kSize; ++y)
	{
		for (int x = 0; x < kSize; ++x)
		{
			x_ = x - kRadius;
			y_ = y - kRadius;
			theta = angle / 180. * PI;
			float _x = cos(theta) * x_ + sin(theta) * y_;
			float _y = sin(theta) * x_ + cos(theta) * y_;

			kernel[y][x] = exp(-(pow(_x, 2) + pow(gamma, 2) * pow(_y, 2)) / (2 * pow(sigma, 2))) * cos(2 * PI * _x / Lambda + Psi);
			max = MAX(max, kernel[y][x]);
			min = MIN(min, kernel[y][x]);
			kSum += std::abs(kernel[y][x]);
		}
	}
	printf_s("%d,%d\n",max,min);
	for (int y = 0; y < kSize; y++) {
		for (int x = 0; x < kSize; x++) {
			gabor.at<uchar>(y, x) = kernel[y][x] / kSum ;
		}
	}

	for (int y = 0; y < kSize; y++) {
		for (int x = 0; x < kSize; x++) {
			kernel[y][x] -= min;
			kernel[y][x] /= max;
			gabor.at<uchar>(y, x) = kernel[y][x] / kSum * 255;
		}
	}

	imshow("gabor", gabor);
	waitKey(0);
	destroyAllWindows();
}