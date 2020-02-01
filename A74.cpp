#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
using namespace cv;

void A74(Mat img)
{
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

	//缩放比例
	double rx;
	double ry;
	rx = ry = 0.5;
	//缩放后的宽高
	int resizeHeight = (int)(imgHeight * ry);
	int resizeWidth = (int)(imgWidth * rx);
	Mat imgOut1 = Mat::zeros(resizeHeight, resizeWidth, CV_8UC1);
	//计算值
	int xBefore, yBefore;
	double dy, dx;
	double val;
	for (int y = 0; y < resizeHeight; ++y)
	{
		yBefore = (int)floor(y / ry);
		yBefore = fmin(yBefore, imgHeight - 1);
		dy = y / ry - yBefore;

		for (int x = 0; x < resizeWidth; ++x)
		{
			xBefore = (int)floor(x / rx);
			xBefore = fmin(xBefore, imgWidth - 1);
			dx = x / rx - xBefore;

			for (int c = 0; c < channel; ++c)
			{
				val = (1. - dx) * (1. - dy) * imgGray.at<uchar>(yBefore, xBefore) +
					dx * (1. - dy) * imgGray.at<uchar>(yBefore, MIN(xBefore + 1, imgWidth - 1)) +
					(1. - dx) * dy * imgGray.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore) +
					dx * dy * imgGray.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore);
				imgOut1.at<uchar>(y, x) = (uchar)val;
			}
		}
	}
	//放大两倍
	imgHeight = imgOut1.rows;
	imgWidth = imgOut1.cols;
	rx = ry = 2;
	resizeHeight = (int)(imgHeight * ry);
	resizeWidth = (int)(imgWidth * rx);
	Mat imgOut2 = Mat::zeros(resizeHeight, resizeWidth, CV_8UC1);
	xBefore = yBefore = 0;
	dy = dx = 0;
	val = 0;
	for (int y = 0; y < resizeHeight; ++y)
	{
		yBefore = (int)floor(y / ry);
		yBefore = fmin(yBefore, imgHeight - 1);
		dy = y / ry - yBefore;

		for (int x = 0; x < resizeWidth; ++x)
		{
			xBefore = (int)floor(x / rx);
			xBefore = fmin(xBefore, imgWidth - 1);
			dx = x / rx - xBefore;

			val = (1. - dx) * (1. - dy) * imgOut1.at<uchar>(yBefore, xBefore) +
				dx * (1. - dy) * imgOut1.at<uchar>(yBefore, MIN(xBefore + 1, imgWidth - 1)) +
				(1. - dx) * dy * imgOut1.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore) +
				dx * dy * imgOut1.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore);
			imgOut2.at<uchar>(y, x) = (uchar)val;
		}
	}
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			imgOut2.at<uchar>(y, x) = std::abs(imgOut2.at<uchar>(y, x) - imgGray.at<uchar>(y, x));
		}
	}

	printf_s("%d %d\n", imgGray.rows, imgGray.cols);
	printf_s("%d %d\n", imgOut2.rows, imgOut2.cols);
	printf_s("%d %d\n", imgOut1.rows, imgOut1.cols);

	imshow("imgOut1", imgOut1);
	imshow("imgOut2", imgOut2);
	imshow("imgSrc", img);
	waitKey(0);
	destroyAllWindows();
}