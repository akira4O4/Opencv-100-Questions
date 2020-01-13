#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "A_11_20.h"

using namespace cv;


void A19(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgGray = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	Mat imgGaussianOut = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	Mat imgLoGOut = Mat::zeros(imgHeight, imgWidth, CV_8UC1);

	//先灰度化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			imgGray.at<uchar>(y, x) = 0.2126 * (float)imgSrc.at<cv::Vec3b>(y, x)[2] \
				+ 0.7152 * (float)img.at<cv::Vec3b>(y, x)[1] \
				+ 0.0722 * (float)img.at<cv::Vec3b>(y, x)[0];
		}
	}
	const int kSize = 3;
	//卷积半径
	int kRadius = floor((double)kSize / 2);//卷积半径
	double kernel[kSize][kSize];
	double kernel_sum = 0;
	double _x, _y;
	double sigma = 3;
	double PI = atan(1) * 4;

	//高斯滤波,计算算子
	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			_y = y - kRadius;
			_x = x - kRadius;
			kernel[y][x] = (_x * _x + _y * _y - sigma * sigma) / (2 * PI * pow(sigma, 6)) * exp(-(_x * _x + _y * _y) / (2 * sigma * sigma));
			kernel_sum += kernel[y][x];
		}
	}
	for (int y = 0; y < kSize; y++)
	{
		for (int x = 0; x < kSize; x++)
		{
			kernel[y][x] /= kernel_sum;
		}
	}

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			double val = 0;
			for (int dy = -kRadius; dy < kRadius + 1; dy++)
			{
				for (int dx = -kRadius; dx < kRadius + 1; dx++)
				{
					if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
					{
						val += imgGray.at<uchar>(y + dy, x + dx) * kernel[kRadius + dy][kRadius + dx];
					}

				}
			}
			imgGaussianOut.at<uchar>(y, x) = (uchar)val;

		}
	}
	//拉普拉斯算子
	double kLaplacian[kSize][kSize] = { {0, 1, 0}, {1, -4, 1}, {0, 1, 0} };
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			uchar val = 0;
			for (int dy = -kRadius; dy < kRadius + 1; dy++)
			{
				for (int dx = -kRadius; dx < kRadius + 1; dx++)
				{
					if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
					{
						val += imgGaussianOut.at<uchar>(y + dy, x + dx) * kLaplacian[kRadius + dy][kRadius + dx];
					}

				}
			}
			imgLoGOut.at<uchar>(y, x) = (uchar)val;
		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgGray", imgGray);
	imshow("imgGaussianOut", imgGaussianOut);
	imshow("imgLoGOut", imgLoGOut);
	waitKey(0);
	destroyAllWindows();

}