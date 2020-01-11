#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Q_1_10.h"
using namespace cv;
void A6(void)
{
	/*原理：
	假设N是减色因子，将图像中每个像素的值除以N(使用整数除法，不保留余数。实际上，该算法就是利用了整数除法的特性来实现减色的)。然后将结果乘以N，得到N的倍数，再加上N/ 2，就得到相邻的N的倍数之间的中间值。对所有8位通道值重复这个过程，就会得到(256 / N)∗(256 / N)∗(256 / N)种可能的颜色值。
	*/

	printf_s("减色处理\n");
	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img2.jpg");
	int imgHeight = imgSrc.rows;
	int imgWeight = imgSrc.cols;
	int channel = imgSrc.channels();//色彩通道
	Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC3);
	int n = 64;//减色因子

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			//取每个通道的1/n
			for (int c = 0; c < channel; ++c)
			{
				//floor:向下取整
				imgOut.at<Vec3b>(y, x)[c] = (uchar)(floor((double)imgSrc.at<Vec3b>(y, x)[c] / n) * n + n / 2);
			}
		}
	}

	Mat imgPrt = Mat::zeros(imgHeight, imgWeight, CV_8UC3);
	//使用指针操作
	for (int y = 0; y < imgHeight; ++y)
	{
		uchar* data = imgSrc.ptr<uchar>(y);//获取源图像的每行
		uchar* imgPrtData = imgPrt.ptr<uchar>(y);//获取输出图像的每行
		for (int x = 0; x < imgWeight * channel; x++)
		{
			imgPrtData[x] = floor((double)data[x] / n) * n + n / 2;
			//for (int i=0;i<3;++i)
			//{
			//	printf_s("%d ", data[x+i]);
			//}
			//printf_s("\t");
		}
	}
	imshow("imgSrc", imgSrc);

	imshow("imgOut", imgOut);
	imshow("imgPrtOut", imgPrt);
	waitKey(0);
	destroyAllWindows();
}