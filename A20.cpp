#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_11_20.h"

using namespace cv;

void A20(Mat img)
{
	printf_s("灰度直方图\n");
	Mat imgSrc = img;
	int imgWeight = imgSrc.cols;
	int imgHeight = imgSrc.rows;

	const int grayScale = 256;//灰度值
	int pixelCount[grayScale] = { 0 };//灰度直方图
	float pixelPro[grayScale] = { 0 };//各个灰度值占总体的比例
	int pixelSum = imgHeight * imgWeight;//总像素值

	Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	
	//计算灰度
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; x++)
		{
			//GRAY=b0.114 + g0.587 + r0.299 
			imgOut.at<uchar>(y, x) = 0.114 * (float)imgSrc.at<Vec3b>(y, x)[2]
				+ 0.587 * (float)imgSrc.at<Vec3b>(y, x)[1]
				+ 0.299 * (float)imgSrc.at<Vec3b>(y, x)[0];
		}

	}

	for (int y=0;y<grayScale;++y)
	{
		for (int x = 0; x < grayScale; ++x)
		{
			int val = imgOut.at<uchar>(y,x);
			pixelCount[val]++;
		}
	}

	for (int i=0;i<grayScale;++i)
	{
		pixelPro[i] = (pixelCount[i]*1.0) / pixelSum;
	}
	for (int i = 0; i < grayScale; ++i)
	{
		printf_s("%d-->%f\n",i,pixelPro[i]*1000);
	}
}