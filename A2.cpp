#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_1_10.h"
using namespace cv;
void A2(void)
{
	printf_s("º∆À„Õº∆¨ª“∂»");
	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");
	int imgWeight = imgSrc.cols;
	int imgHeight = imgSrc.rows;
	Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; x++)
		{
			//GRAY=b0.114 + g0.587 + r0.299 
			imgOut.at<uchar>(y, x) = 0.114 * (float)imgSrc.at<Vec3b>(y, x)[2]
				+ 0.587 * (float)imgSrc.at<Vec3b>(y, x)[1]
				+ 0.299 * (float)imgSrc.at<Vec3b>(y, x)[0];
		}
	}
	imshow("imgSrc", imgSrc);
	imshow("imgGray", imgOut);
	waitKey(0);
	destroyAllWindows();
}