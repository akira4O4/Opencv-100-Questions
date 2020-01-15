#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"

using namespace cv;

void A21(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);
	int val = 0;
	//初始像素点取值范围(start,end)
	int start = 999;
	int end = 0;
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				//遍历取所有像素，取最大最小值
				val = (float)imgSrc.at<Vec3b>(y, x)[c];
				start = fmin(start, val);
				end = fmax(end, val);
			}
		}
	}
	//新的像素范围(0-255)
	int newStart = 0;
	int newEnd = 255;

	//判定赋值
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = imgSrc.at<Vec3b>(y, x)[c];
				if (val < newStart)
					imgOut.at<Vec3b>(y, x)[c] = (uchar)newStart;
				else if(val<=newEnd)
					imgOut.at<Vec3b>(y, x)[c] = (uchar)((newEnd-newStart)/(end-start)*(val-start)+newStart);
				else
					imgOut.at<Vec3b>(y, x)[c] = (uchar)newEnd;
			}
		}
	}

	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}