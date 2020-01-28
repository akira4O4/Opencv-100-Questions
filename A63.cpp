#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_61_70.h"
#include <math.h>

void A63(Mat img)
{
	int H = img.rows;
	int W = img.cols;
	int channel = img.channels();
	int val = 0;
	//灰度二值化（0-1）
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
			//在这里进行翻转0-255
			if (imgGray.at<uchar>(y, x) > good_k)
				imgBin.at<uchar>(y, x) = 1;
			else
				imgBin.at<uchar>(y, x) = 0;
		}
	}

	Mat out = imgBin.clone();
	Mat temp;
	int count = 1;
	int countl = -1;
	int k = 5;
	while (true)
	{
		//k--;
		printf_s("count:%d\n", count);
		if (count == countl)
			break;
		else
			countl = count;

		count = 0;
		temp = out.clone();
		for (int y = 0; y < H; ++y)
		{
			for (int x = 0; x < W; ++x)
			{
				if (imgBin.at<uchar>(y, x) == 0)
					continue;

				int condition = 0;
				//# 4近邻像素的取值有一个以上为0(2, 3, 4添加越界判断)：上下左右
				if (temp.at<uchar>(MAX(y - 1, 0), x) + temp.at<uchar>(MIN(y + 1, H - 1), x) + temp.at<uchar>(y, MAX(x - 1, 0) + temp.at<uchar>(y, MIN(x + 1, W - 1)) < 4))
				{
					condition++;
				}
				//# 4近邻像素的取值有一个以上为0；
				int c = 0;
				c += (temp.at<uchar>(y, MIN(x + 1, W - 1)) - temp.at<uchar>(y, MIN(x + 1, W - 1)) * temp.at<uchar>(MAX(y - 1, 0), MIN(x + 1, W - 1)) *
					temp.at<uchar>(MAX(y - 1, 0), x));

				c += (temp.at<uchar>(MAX(y - 1, 0), x) - temp.at<uchar>(MAX(y - 1, 0), x) * temp.at<uchar>(MAX(y - 1, 0), MAX(x - 1, 0)) * temp.at<uchar>(
					y, MAX(x - 1, 0)));

				c += (temp.at<uchar>(y, MAX(x - 1, 0)) - temp.at<uchar>(y, MAX(x - 1, 0)) * temp.at<uchar>(MIN(y + 1, H - 1), MAX(x - 1, 0)) * temp.at<uchar>(MIN(y + 1, H - 1), x));

				c += (temp.at<uchar>(MIN(y + 1, H - 1), x) - temp.at<uchar>(MIN(y + 1, H - 1), x) * temp.at<uchar>(MIN(y + 1, H - 1), MIN(x + 1, W - 1)) *
					temp.at<uchar>(y, MIN(x + 1, W - 1)));

				if (c == 1)
					condition++;
				//x的8近邻中有三个以上取值为1。
				int sum = 0;
				for (int _y = -1; _y < 2; ++_y)
				{
					for (int _x = -1; _x < 2; ++_x)
					{
						if (_y == 0 && _x == 0)
							continue;
						sum += temp.at<uchar>(y + _y, x + _x);
					}
				}
				if (sum >= 4)
					condition++;

				if (condition == 3)
				{
					out.at<uchar>(y, x) = 0;
					count++;
				}
			}
		}
	}
	//扩张像素
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			if (out.at<uchar>(y, x) == 0)
				continue;
			out.at<uchar>(y, x)=out.at<uchar>(y, x) * 255;
		}
	}
	cv::imshow("img", img);
	cv::imshow("out", out);
	cv::waitKey(0);
	cv::destroyAllWindows();

}