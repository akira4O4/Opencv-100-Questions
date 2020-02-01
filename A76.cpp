#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
using namespace cv;

Mat GaussianPyramid(Mat img, float n)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();
	//缩放比例
	double rx;
	double ry;
	rx = ry = n;
	//缩放后的宽高
	int resizeHeight = (int)(imgHeight * ry);
	int resizeWidth = (int)(imgWidth * rx);
	Mat imgOut = Mat::zeros(resizeHeight, resizeWidth, CV_8UC1);
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
				val = (1. - dx) * (1. - dy) * img.at<uchar>(yBefore, xBefore) +
					dx * (1. - dy) * img.at<uchar>(yBefore, MIN(xBefore + 1, imgWidth - 1)) +
					(1. - dx) * dy * img.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore) +
					dx * dy * img.at<uchar>(MIN(yBefore + 1, imgHeight - 1), xBefore);
				imgOut.at<uchar>(y, x) = (uchar)val;
			}
		}
	}
	return imgOut;
}

void A76(Mat img)
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

	int n = 6;
	//使用vecto进行图片存储
	std::vector<Mat> out(n);
	char name[6][5] = { "out1","out2","out3","out4","out5","out6" };
	for (int i = 1; i < n + 1; i++)
	{
		Mat out = GaussianPyramid(imgGray, pow(0.5, i));
		imshow(name[i], out);
		/*out.push_back(out);*/
	}
	for (int i = 0; i < n; i++)
	{
		
		
	}


	imshow("imgGray", imgGray);
	waitKey(0);
	destroyAllWindows();
}