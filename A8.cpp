#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "Q_1_10.h"

using namespace cv;

void A8(void)
{
	printf_s("将图片按照固定大小网格分割，网格内的像素值取网格内所有像素的最大值");
	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img3.jpg");
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);
	int step = 8;//步数
	int r = 8;//池化范围
	for (int y = 0; y < imgHeight; y += step)
	{
		for (int x = 0; x < imgWidth; x += step)
		{
			for (int c = 0; c < channel; c++)
			{
				//统计在r范围内的所有像素最大值
				int val = 0;
				for (int dy = 0; dy < r; dy++)
				{
					for (int dx = 0; dx < r; ++dx)
					{
						val = fmax(imgSrc.at<Vec3b>(y + dy, x + dx)[c],val);
					}
				}
				printf_s("%d", val);
				//在r范围内所统一赋值
				for (int dy = 0; dy < r; dy++)
				{
					for (int dx = 0; dx < r; ++dx)
					{
						imgOut.at<Vec3b>(y + dy, x + dx)[c] = (uchar)val;
					}
				}
			}
		}
	}

	imshow("src", imgSrc);
	imshow("out", imgOut);
	waitKey(0);
	destroyAllWindows();
}