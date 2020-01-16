#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"
#include <math.h>

using namespace cv;

#define PI acos(-1)//圆周率

void A30(Mat img)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();
	//变换参数：仿射变换有6个自由度
	/*
	//矩阵乘法(theta=0)
	[a,b,tx][x] [_y]
	[c,d,ty][y]=[_x]
	[0,0,1] [1] [1]
	*/
	//决定旋转，相似变换，剪切变换
	double a = 1, b = 0, c = 0, d = 1;
	//决定平移位置
	double tx = 0, ty = 0;
	double theta = -30;//旋转角度(默认逆时针)
	double det = a * d - b * c;

	//计算旋转参数
	if (theta != 0)
	{
		double rad = theta / 180.0 * PI;
		a = std::cos(rad);
		b = -std::sin(rad);
		c = std::sin(rad);
		d = std::cos(rad);
		tx = 0;
		ty = 0;

		double det = a * d - b * c;

		//计算平移参数：tx,ty
		//因为旋转是绕左下角旋转，如果需要对图片中心旋转需要图片进行移动
		double cx = imgWidth / 2;
		double cy = imgHeight / 2;
		double cxNew = (d * cx - b * cy) / det;
		double cyNew = (-c * cx + a * cy) / det;
		tx = cxNew - cx;
		ty = cyNew - cy;
	}

	int resizeHeight = (int)(imgHeight * d);
	int resizeWidth = (int)(imgWidth * a);

	//重新设定输出图片尺寸
	if (theta!=0)
	{
		resizeHeight = (int)(imgHeight);
		resizeWidth = (int)(imgWidth);
	}

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
				continue; 

			yBefore = (int)((-c * x + a * y) / det - ty);
			if ((yBefore) < 0 || (yBefore >= imgHeight))
				continue;

			for (int c = 0; c < channel; ++c)
				imgOut.at<Vec3b>(y, x)[c] = img.at<Vec3b>(yBefore, xBefore)[c];
		}
	}
	imshow("imgSrc", img);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}