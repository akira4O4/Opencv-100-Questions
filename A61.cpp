#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_61_70.h"
#include <math.h>

void A61(Mat img)
{
	printf_s("---");
	int H = img.rows;
	int W = img.cols;
	int channel = img.channels();
	int val = 0;
	//灰度二值化
	Mat imgGray = Mat::zeros(H, W, CV_8UC1);
	Mat imgBin = Mat::zeros(H, W, CV_8UC1);

	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
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
	int pixelSum = H * W;//总像素值

	//统计图片中各个灰度值的个数
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
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
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			if (imgGray.at<uchar>(y, x) > good_k)
				imgBin.at<uchar>(y, x) = 255;
			else
				imgBin.at<uchar>(y, x) = 0;
		}
	}

	Mat imgOut = Mat::zeros(H, W, CV_8UC3);
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			printf_s("y:%d x:%d\n",y,x);
			//如果是黑色则跳过
			if (imgBin.at<uchar>(y, x) == 1)
				continue;
			int s = 0;
			//右上
			s += imgBin.at<uchar>(y, MIN(x + 1, W - 1)) - imgBin.at<uchar>(y, MIN(x + 1, W - 1)) * imgBin.at<uchar>(MAX(y - 1, 0), MIN(x + 1, W - 1)) * imgBin.at<uchar>(MAX(y - 1, 0), x);

			//左上
			s += imgBin.at<uchar>(MAX(y - 1, 0), x) - imgBin.at<uchar>(MAX(y - 1, 0), x) * imgBin.at<uchar>(MAX(y - 1, 0), MAX(x - 1, 0)) * imgBin.at<uchar>(y, MAX(x - 1, 0));

			//左下
			s += imgBin.at<uchar>(y, MAX(x - 1, 0)) - imgBin.at<uchar>(y, MAX(x - 1, 0)) * imgBin.at<uchar>(MIN(y + 1, H - 1), MAX(x - 1, 0)) * imgBin.at<uchar>(MIN(y + 1, H - 1), x);

			//右下
			s += imgBin.at<uchar>(MIN(y + 1, H - 1), x) - imgBin.at<uchar>(MIN(y + 1, H - 1), x) * imgBin.at<uchar>(MIN(y + 1, H - 1), MIN(x + 1, W - 1)) * imgBin.at<uchar>(y, MIN(x + 1, W - 1));

			if (s == 0)
			{
				imgOut.at<Vec3b>(y, x)[0] = 0;
				imgOut.at<Vec3b>(y, x)[1] = 0;
				imgOut.at<Vec3b>(y, x)[2] = 255;
			}
			else if (s == 1)
			{
				imgOut.at<Vec3b>(y, x)[0] = 0;
				imgOut.at<Vec3b>(y, x)[1] = 255;
				imgOut.at<Vec3b>(y, x)[2] = 0;
			}
			else if (s == 2)
			{
				imgOut.at<Vec3b>(y, x)[0] = 255;
				imgOut.at<Vec3b>(y, x)[1] = 0;
				imgOut.at<Vec3b>(y, x)[2] = 0;
			}
			else if (s == 3)
			{
				imgOut.at<Vec3b>(y, x)[0] = 255;
				imgOut.at<Vec3b>(y, x)[1] = 255;
				imgOut.at<Vec3b>(y, x)[2] = 0;
			}
			else if (s == 4)
			{
				imgOut.at<Vec3b>(y, x)[0] = 255;
				imgOut.at<Vec3b>(y, x)[1] = 0;
				imgOut.at<Vec3b>(y, x)[2] = 255;
			}

		}
	}

	cv::imshow("img", img);
	cv::imshow("imgBin", imgBin);
	cv::imshow("imgOut", imgOut);
	cv::waitKey(0);
	cv::destroyAllWindows();
}