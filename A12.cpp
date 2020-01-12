#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "A_11_20.h"

using namespace cv;


void A12(Mat img)
{
	Mat imgSrc = img;

	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);
	//卷积核大小
	const int kSize = 3;
	//卷积核半径
	int kRadius = floor((double)kSize / 2);
	double kArray[kSize][kSize];
	//设置卷积核
	/*
	[1/3,0,0]
	[0,1/3,0]
	[0,0,1/3]
	*/
	printf_s("卷积核\n");
	for (int i = 0; i < kSize; ++i)
	{
		for (int j = 0; j < kSize; ++j)
		{
			if (i - j == 0)
			{
				kArray[i][j] = 1.0 / kSize;
			}
			else
			{
				kArray[i][j] = 0;
			}
			printf_s("%f1 ", kArray[i][j]);
		}
		printf_s("\n");
	}
	//添加边框,如果进行图片宽高判断则不需要使用边框，反之需要为图片添加边框
	Mat imgtemp = Mat::zeros(imgHeight + 2 * kRadius, imgWidth + 2 * kRadius, CV_8UC3);
	for (int y = 0; y < imgHeight; y++)
		for (int x = 0; x < imgWidth; x++)
			for (int c = 0; c < channel; c++)
				imgtemp.at<Vec3b>(y + kRadius, x + kRadius)[c] = imgSrc.at<Vec3b>(y, x)[c];

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				double val = 0;
				for (int dy = -kRadius; dy < kRadius + 1; dy++)
					for (int dx = -kRadius; dx < kRadius + 1; dx++)

						/*if (((y + dy >= 0)) && (x + dx) >= 0 )
							val += (double)imgtemp.at<Vec3b>(y + dy, x + dx)[c] * kArray[dy + kRadius][dx + kRadius];*/

						if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
							val += (double)imgSrc.at<Vec3b>(y + dy, x + dx)[c] * kArray[dy + kRadius][dx + kRadius];

				imgOut.at<Vec3b>(y, x)[c] = (uchar)val;
			}
		}

	}
	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}