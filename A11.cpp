#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "A_11_20.h"

using namespace cv;


void A11(Mat img)
{
	/*
	原理：
	求卷积核范围内所有像素的均值，
	图片大小应该满足步长的整倍数
	*/

	Mat imgSrc = img;

	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);


	//卷积核大小
	const int kSize = 3;
	//卷积核半径
	int kRadius = floor((double)kSize / 2);
	Mat imgtemp = Mat::zeros(imgHeight + 2 * kRadius, imgWidth + 2 * kRadius, CV_8UC3);
	printf("kRadius:%d\n", kRadius);
	//卷积核矩阵
	int kArray[kSize * kSize];
	int count = 0;
	/*均值滤波卷积核
	[1,1,1]
	[1,1,1]
	[1,1,1]
	*/
	//设置卷积核,但是在下面计算中没有用到，为了快速计算，直接求sum/n;
	for (int i = 0; i < kSize * kSize; ++i)
	{
		kArray[i] = 1;
	}
	//复制一张原图，并且添加边框
	for (int y = 0; y < imgHeight; y++)
		for (int x = 0; x < imgWidth; x++)
			for (int c = 0; c < channel; c++)
				imgtemp.at<Vec3b>(y + kRadius, x + kRadius)[c] = imgSrc.at<Vec3b>(y, x)[c];

	for (int y = 0; y < imgHeight; y++)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			//printf_s("y=%d,x=%d\n", y, x);
			for (int c = 0; c < channel; c++)
			{
				count = 0;
				double val = 0;//存储卷积核半径内所有像素和
				for (int dy = -kRadius; dy < kRadius + 1; dy++) {
					for (int dx = -kRadius; dx < kRadius + 1; dx++) {
						if (((y + dy) >= 0) && ((x + dx) >= 0)) {
							//printf("%d+%d,%d+%d\n", y, dy, x, dx);
							val += (int)imgtemp.at<cv::Vec3b>(y + dy, x + dx)[c];
							//printf_s("yes\n");
						}
					}
				}
				//求均值
				val = val / (kSize * kSize);
				imgOut.at<Vec3b>(y, x)[c] = (uchar)val;
			}
		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}