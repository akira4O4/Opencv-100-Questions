#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_51_60.h"
#include <math.h>
#include <time.h>
using namespace cv;

void A52(Mat img)
{
	int imgHeight = img.rows;
	int imgWeight = img.cols;
	//灰度，二值
	Mat imgGray = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	Mat imgBin = Mat::zeros(imgHeight, imgWeight, CV_8UC1);

	//灰度化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			imgGray.at<uchar>(y, x) = 0.114 * (float)img.at<Vec3b>(y, x)[2]
				+ 0.587 * (float)img.at<Vec3b>(y, x)[1]
				+ 0.299 * (float)img.at<Vec3b>(y, x)[0];
		}
	}


	const int grayScale = 256;//灰度值

	int pixelCount[grayScale] = { 0 };//灰度直方图
	float pixelPro[grayScale] = { 0 };//各个灰度值占总体的比例

	double w0, w1;//背景/前景像素占比
	double u0, u1;//前景/背景平均灰度值
	double p0, p1;
	double g = 0;//类间方差

	double max_g = 0;//最大类间方差
	double good_k = 0;//最优阈值
	int pixelSum = imgHeight * imgWeight;//总像素值

	//统计图片中各个灰度值的个数
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			int val = imgGray.at<uchar>(y, x);
			pixelCount[val]++;
		}
	}

	//统计图片中各个灰度值所占的比例
	for (int i = 0; i < grayScale; ++i)
	{
		pixelPro[i] = 1.0 * pixelCount[i] / pixelSum;
	}

	//k:暂定阈值(0-255)
	for (int k = 0; k < grayScale; ++k)
	{
		w0 = w1 = u0 = u1 = g = 0;
		p0 = p1 = 0;
		//前景，背景区分 [0-k][k+1-255]
		for (int i = 0; i < grayScale; ++i)
		{
			//如果当前像素值小于阈值k则属于背景，反之属于前景
			if (i <= k)
			{
				//计算背景像素占比
				w0 += pixelPro[i];
				//计算当前灰度值发生的概率:灰度值*灰度值发生的概率
				p0 += (i * pixelPro[i]);

			}
			else
			{
				//计算背景像素占比
				w1 += pixelPro[i];
				p1 += (i * pixelPro[i]);
			}
		}
		//计算平均灰度值：p0/w0
		u0 = p0 / w0;
		u1 = p1 / w1;
		//计算类内方差
		g = (float)(w0 * w1 * pow((u0 - u1), 2));
		if (g > max_g)
		{
			max_g = g;
			good_k = k;

		}
	}

	printf_s("good k;%f\n", good_k);

	//取得最好的k值，以k值作为阈值进行二值化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			if (imgGray.at<uchar>(y, x) > good_k)
				imgBin.at<uchar>(y, x) = 255;
			else
				imgBin.at<uchar>(y, x) = 0;
		}
	}

	//开运算：腐蚀->膨胀

	//腐蚀
	Mat tempImg;//作为对比图
	Mat imgErode = imgBin.clone();
	int time = 3;//执行次数
	for (int t = 0; t < time; ++t)
	{
		tempImg = imgErode.clone();
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				//对于待操作的像素(x,y)=0，(x, y-1)，(x-1, y)，(x+1, y)，(x, y+1)中不论哪一个不为255，令(x,y)=0。
				if ((x > 0) && (tempImg.at<uchar>(y, x - 1) == 0))
				{
					imgErode.at<uchar>(y, x) = 0;
					continue;
				}
				if ((y > 0) && (tempImg.at<uchar>(y - 1, x) == 0))
				{
					imgErode.at<uchar>(y, x) = 0;
					continue;
				}
				if ((x < imgWeight - 1) && (tempImg.at<uchar>(y, x + 1) == 0))
				{
					imgErode.at<uchar>(y, x) = 0;
					continue;
				}
				if ((y < imgHeight - 1) && (tempImg.at<uchar>(y + 1, x) == 0))
				{
					imgErode.at<uchar>(y, x) = 0;
					continue;
				}
			}
		}
	}

	//膨胀
	Mat imgDilate = imgErode.clone();
	time = 3;
	for (int t = 0; t < time; ++t)
	{
		tempImg = imgDilate.clone();
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				//对于待操作的像素(x,y)=0，(x, y-1)，(x-1, y)，(x+1, y)，(x, y+1)中不论哪一个为255，令(x,y)=255。
				if ((x > 0) && (tempImg.at<uchar>(y, x - 1) == 255))
				{
					imgDilate.at<uchar>(y, x) = 255;
					continue;
				}
				if ((y > 0) && (tempImg.at<uchar>(y - 1, x) == 255))
				{
					imgDilate.at<uchar>(y, x) = 255;
					continue;
				}
				if ((x < imgWeight - 1) && (tempImg.at<uchar>(y, x + 1) == 255))
				{
					imgDilate.at<uchar>(y, x) = 255;
					continue;
				}
				if ((y < imgHeight - 1) && (tempImg.at<uchar>(y + 1, x) == 255))
				{
					imgDilate.at<uchar>(y, x) = 255;
					continue;
				}
			}
		}
	}

	//顶帽:二值-开运算
	Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			imgOut.at<uchar>(y, x) = imgBin.at<uchar>(y, x) - imgDilate.at<uchar>(y, x);
		}
	}

	cv::imshow("imgOut", imgOut);
	cv::waitKey(0);
	cv::destroyAllWindows();
}