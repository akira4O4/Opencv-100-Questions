#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "Q_1_10.h"
#include <math.h>
using namespace cv;

void A10()
{
	printf_s("中值滤波\n");
	Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img3.jpg");
	int imgHeight = imgSrc.rows;
	int imgWidth = imgSrc.cols;
	int channel = imgSrc.channels();
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC3);

	const int kernelSize = 3;//卷积核大小
	int kernelRadius = floor(kernelSize / 2);//卷积核半径
	float kernelArray[kernelSize * kernelSize];//卷积核矩阵,排序矩阵
	int count = 0;//计数器

	for (int y = 0; y < imgHeight; ++y)
	{
		for(int x=0;x<imgWidth;++x)
		{
			for (int c = 0; c < channel; ++c)
			{
				//防止倒序
				for (int i = 0; i < kernelSize * kernelSize; i++) {
					kernelArray[i] = 999;
				}

				//在卷积核范围内取值
				for (int dy = -kernelRadius; dy < kernelRadius + 1; dy++)
				{
					for (int dx = -kernelRadius; dx < kernelRadius+1; dx++)
					{ 
						if (((y + dy) >= 0) && ((x + dx) >= 0))
						{
							kernelArray[count++] = (int)imgSrc.at<Vec3b>(y + dy, x + dx)[c];
						}
					}
				}

				//对元素进行排序
				std::sort(kernelArray,kernelArray+(kernelSize*kernelSize));
				//取中值
				int val = kernelArray[int(floor(count/2))+1];
				imgOut.at<Vec3b>(y, x)[c] = (uchar)val;
			}
		}
	}

	imshow("src", imgSrc);
	imshow("out", imgOut);
	waitKey(0);
	destroyAllWindows();
}