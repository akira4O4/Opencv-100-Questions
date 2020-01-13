#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include<math.h>
#include "A_11_20.h"

using namespace cv;


void A16(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgGray = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	Mat imgOutH = Mat::zeros(imgHeight, imgWidth, CV_8UC1);
	Mat imgOutV = Mat::zeros(imgHeight, imgWidth, CV_8UC1);

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

	const int kSize = 3;
	//卷积半径
	int kRadius = floor((double)kSize / 2);//卷积半径
	//卷积核
	/*
	[0,-1,0]
	[0,-1,1]
	[0,0,0]
	*/
	//设置卷积核:水平
	double kPrewittHorizontal[kSize][kSize] = { {-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1} };

	//设置卷积核:垂直
	double kPrewittVertical[kSize][kSize] = { {-1, -1, -1}, {0, 0, 0}, {1, 1, 1} };

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			uchar valH = 0;
			uchar valV = 0;
			for (int dy = -kRadius; dy < kRadius + 1; dy++)
			{
				for (int dx = -kRadius; dx < kRadius + 1; dx++)
				{
					if (((y + dy >= 0)) && (x + dx) >= 0 && ((y + dy) < imgHeight) && ((x + dx) < imgWidth))
					{
						valH += imgGray.at<uchar>(y + dy, x + dx) * kPrewittHorizontal[kRadius + dy][kRadius + dx];
						valV += imgGray.at<uchar>(y + dy, x + dx) * kPrewittVertical[kRadius + dy][kRadius + dx];
					}

				}
			}
			imgOutH.at<uchar>(y, x) = (uchar)valH;
			imgOutV.at<uchar>(y, x) = (uchar)valV;

		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgOutH", imgOutH);
	imshow("imgOutV", imgOutV);
	waitKey(0);
	destroyAllWindows();

}