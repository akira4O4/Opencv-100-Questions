#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"
#include <math.h>

using namespace cv;

//计算权重：Bicubic function
double Bicubic(double x)
{
	double a = -1;
	if (fabs(x) < 1)
	{
		return (a + 2) * pow(fabs(x), 3) - (a + 3) * pow(fabs(x), 2) + 1;
	}
	else if (fabs(x) <= 2)
	{
		return a * pow(fabs(x), 3) - 5 * a * pow(fabs(x), 2) + 8 * a * fabs(x) - 4 * a;
	}
	return 0;
}
// [*, *] -> [min, max]
int ValueClip(int a, int min, int max)
{
	return fmin(fmin(a, min), max);
}

void A27(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();

	//缩放比例
	double rx = 1.2;
	double ry = 1.2;

	//缩放后的宽高
	int resizeHeight = (int)(imgHeight * ry);
	int resizeWidth = (int)(imgWidth * rx);
	Mat imgOut = Mat::zeros(resizeHeight, resizeWidth, CV_8UC3);

	int xBefore, yBefore;
	double dx, dy;
	double	weightx = 0, weighty = 0;
	double weightSum=0;
	double val=0;
	int _x, _y;

	for (int y = 0; y < resizeHeight; ++y)
	{
		dy = y / ry;
		yBefore = (int)floor(dy);
		for (int x = 0; x < resizeWidth; ++x)
		{
			dx = x / rx;
			xBefore = (int)floor(dx);
			for (int c = 0; c < channel; ++c)
			{
				weightSum = 0;
				val = 0;
				//求出目标目标像素周围16个像素的权重
				for (int j = -1; j < 3; j++)
				{
					_y = ValueClip(yBefore+j, 0, imgHeight - 1);
					weighty = Bicubic(fabs(dy - _y));

					for (int i = -1; i < 3; i++)
					{
						_x = ValueClip(xBefore+i, 0, imgWidth - 1);
						weightx = Bicubic(fabs(dx - _x));
						weightSum += (weightx + weighty);
						val += (double)img.at<Vec3b>(_y, _x)[c] * weightx * weighty;
					}
				}
				//val /= weightSum;
				val = ValueClip(val, 0, 255);
				imgOut.at<Vec3b>(y, x)[c] = (uchar)val;
			}
		}
	}
	imshow("imgSrc", img);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}