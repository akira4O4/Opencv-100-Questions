#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"
#include <math.h>

using namespace cv;

void A28(Mat img)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();
	//变换参数：仿射变换有6个自由度
	/*
	//矩阵乘法
	[a,b,tx][x] [_y]
	[c,d,ty][y]=[_x]
	[0,0,1] [1] [1]
	*/
	//决定旋转，相似变换，剪切变换
	double a = 1, b = 0, c = 0, d = 1;
	//决定平移位置
	double tx = 30, ty = -30;

	double det = a * d - b * c;

	//缩放后的宽高
	int resizeHeight = (int)(imgHeight * a);
	int resizeWidth = (int)(imgWidth * d);
	Mat imgOut = Mat::zeros(resizeHeight, resizeWidth, CV_8UC3);
	int xBefore, yBefore;
	double dx, dy;
	double	weightx = 0, weighty = 0;
	double weightSum = 0;
	double val = 0;
	int _x, _y;

	for (int y = 0; y < resizeHeight; ++y)
	{
		for (int x = 0; x < resizeWidth; ++x)
		{
			xBefore = (int)((d * x - b * y) / det - tx);
			if ((xBefore) < 0 || (xBefore >= imgWidth))
			{
				continue;
			}

			yBefore = (int)((-c * c + a * y) / det - ty);
			if ((yBefore) < 0 || (yBefore >= imgHeight))
			{
				continue;
			}
			for (int c = 0; c < channel; ++c)
			{
				imgOut.at<Vec3b>(y, x)[c] = img.at<Vec3b>(yBefore, xBefore)[c];
			}
		}
	}

	imshow("imgSrc", img);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}