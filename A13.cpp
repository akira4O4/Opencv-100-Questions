#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "A_11_20.h"

using namespace cv;


void A13(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	Mat imgGray = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC1);

	//先灰度化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			imgGray.at<uchar>(y, x) = 0.2126 * (float)imgSrc.at<cv::Vec3b>(y, x)[2] \
				+ 0.7152 * (float)img.at<cv::Vec3b>(y, x)[1] \
				+ 0.0722 * (float)img.at<cv::Vec3b>(y, x)[0];
		}
	}
	int kSize = 3;//卷积核大小
	int kRadius = floor((double)kSize / 2);//卷积半径
	
	//max-min:对每一个卷积半径内的元素取最大最小值，取差值做目标值
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			double MAX = 0;
			double MIN = 999;
			double val = 0;
			for (int dy = -kRadius; dy < kRadius + 1; dy++)
			{
				for (int dx = -kRadius; dx < kRadius + 1; dx++)
				{
					//printf_s("%d %d\n",y,x);
					if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
					{
						val = (double)imgGray.at<uchar>(y + dy, x + dx);
						MAX = fmax(val, MAX);
						MIN = fmin(val, MIN);
					}
				}
			}
			imgOut.at<uchar>(y, x) = (uchar)(MAX - MIN);
		}
	}


	imshow("imgSrc", imgSrc);
	imshow("imgGray", imgGray);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}
