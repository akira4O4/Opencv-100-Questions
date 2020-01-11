#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Q_1_10.h"
#include <math.h>
using namespace cv;

void A9(void)
{
	printf_s("高斯滤波\n");
	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img3.jpg");
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	/*高斯滤波器将中心像素周围的像素按照高斯分布加权平均进行平滑化。这样的（二维）权值通常被称为卷积核（kernel）或者滤波器（filter）。*/
	//当图片大小不是滤波器的整数倍时候，需要在周围补0

	int sigma = 1.3;//方差
	const int kernelSize = 3;//卷积核大小
	int kernelRadius = floor(kernelSize / 2);//卷积核半径
	float kernel[kernelSize][kernelSize];//卷积核矩阵
	double kernelSum = 0;
	int x_ = 0, y_ = 0;//半径内的坐标
	double PI = atan(1) * 4;

	//计算卷积核权值
	for (int y = 0; y < kernelSize; ++y)
	{
		for (int x = 0; x < kernelSize; ++x)
		{
			x_ = x - kernelRadius;
			y_ = y - kernelRadius;
			//二维高斯分布函数
			kernel[y][x] = 1 / (2 * PI * sigma * sigma) * exp(-(x_ * x_ + y_ * y_) / (2 * sigma * sigma));
			kernelSum += kernel[y][x];
		}
	}
	//------------打印卷积核------------
	printf_s("kernel-sum:%f\n", kernelSum);
	printf_s("未归一化的卷积核\n");
	for (int i = 0; i < kernelSize; ++i)
	{
		for (int j = 0; j < kernelSize; ++j)
		{
			printf_s("%f ", kernel[i][j]);
		}
		printf_s("\n");
	}

	double sum = 0;
	//归一化卷积核，使得所有权值之和为1
	for (int y = 0; y < kernelSize; y++) {
		for (int x = 0; x < kernelSize; x++) {
			kernel[y][x] = kernel[y][x]/ kernelSum;
			sum += kernel[y][x];
		}
	}

	//------------打印卷积核------------
	printf_s("kernel-sum:%f\n", sum);
	printf_s("归一化以后的卷积核\n");
	for (int i = 0; i < kernelSize; ++i)
	{
		for (int j = 0; j < kernelSize; ++j)
		{
			printf_s("%f ", kernel[i][j]);
		}
		printf_s("\n");
	}

	//使用卷积核对源图像进行高斯滤波
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				double val = 0;
				for (int dy = -kernelRadius; dy < kernelRadius + 1; dy++)
				{
					for (int dx = -kernelRadius; dx < kernelRadius + 1; dx++)
					{
						//防止越界
						if (((y + dy) >= 0) && ((x + dx) >= 0))
						{
							/*val += (double)imgSrc.at<Vec3b>(y + dy, x + dx)[c] * kernel[dy + kernelRadius][dx + kernelRadius];*/


						}
					}
				}
				imgOut.at<Vec3b>(y, x)[c] = val;
			}
		}
	}

	imshow("src", imgSrc);
	imshow("out", imgOut);

	waitKey(0);
	destroyAllWindows();
}

