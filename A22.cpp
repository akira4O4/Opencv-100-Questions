#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"

using namespace cv;

void A22(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	//目标值
	int m0= 128;
	int s0= 52;

	double m, s;
	//和，平方和
	double sum = 0.0,squaredSum=0.0;
	double val;

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = (double)imgSrc.at<Vec3b>(y, x)[c];
				sum += val;
				squaredSum += (val * val);
			}
		}
	}
	//计算平均值，标准差
	m = sum / (imgHeight * imgWidth * channel);
	s = sqrt(squaredSum / (imgHeight * imgWidth * channel) - (m * m));

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = imgSrc.at<Vec3b>(y,x)[c];
				imgOut.at<Vec3b>(y,x)[c]=(uchar)(s0 / s * (val - m) + m0);
			}
		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}
