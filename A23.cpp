#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"

using namespace cv;

void A23(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	//S是总的像素数；Z_{ max }是像素点的最大取值（在这里是255）；
	//h(z)表示取值为z的累积分布函数： Z' = \frac{Z_{max}}{S} \ \sum\limits_{i=0}^z\ h(i) 

	double ZMax = 255;
	double hist[255];
	double S = imgHeight * imgWidth * channel;
	int val;
	double histSum = 0;

	//初始化
	for (int i = 0; i < 255; ++i)
		hist[i] = 0;

	//统计像素分布
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = imgSrc.at<Vec3b>(y, x)[c];
				hist[val]++;
			}
		}
	}
	//直方图均衡

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = imgSrc.at<Vec3b>(y, x)[c];
				histSum = 0;
				//根据0-val的所有像素个数的构建sum
				for (int l = 0; l < val; l++)
				{
					histSum += hist[l];
				}
				imgOut.at<Vec3b>(y, x)[c] = (uchar)(ZMax / S * histSum);
			}
		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}
