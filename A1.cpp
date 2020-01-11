#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Q_1_10.h"

using namespace cv;
void A1(void)
{
	//图形宽高
	printf_s("//读取图像，然后将{RGB}通道替换成{BGR}通道\n");

	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");
	int imgWidth = imgSrc.cols;
	int imgHeight = imgSrc.rows;

	//构建图片矩阵,CV_8UC3:uchar 8bit depth:3
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	//遍历图片：从左到右，从上到下
	for (int y = 0; y < imgHeight; y++)
	{
		for (int x = 0; x < imgWidth; x++)
		{
			//Mat.at:用于获取图像矩阵某点的值或改变某点的值。[0][1][2]三个通道
			//typedef Vec<uchar,3> Vec3b;0-255
			// R -> B
			imgOut.at<Vec3b>(y, x)[0] = imgSrc.at<Vec3b>(y, x)[2];
			// G -> G
			imgOut.at<Vec3b>(y, x)[1] = imgSrc.at<Vec3b>(y, x)[1];
			// B -> R
			imgOut.at<Vec3b>(y, x)[2] = imgSrc.at<Vec3b>(y, x)[0];
		}
	}
	/*printf_s("imgWidth:%d\n", imgWidth);
	printf_s("imgHeight:%d\n", imgHeight);*/

	imshow("imgSrc(RGB)", imgSrc);
	imshow("imgOut(BGR)", imgOut);
	waitKey(0);
	destroyWindow("imgSrc");
}