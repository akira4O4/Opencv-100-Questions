#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_21_30.h"

using namespace cv;

void A24(Mat img)
{
	Mat imgSrc = img;
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);
	double val;
	double gammaC= 1;//常数
	double gammaG= 2.2;//伽马变量
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				val = (double)imgSrc.at<Vec3b>(y,x)[c]/255;
				imgOut.at<Vec3b>(y, x)[c] = (uchar)(pow(val / gammaC, 1 / gammaG) * 255);

			}
		}

	}
	imshow("imgSrc", imgSrc);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}