#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_51_60.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <map>

using namespace cv;

void A59(Mat img)
{
	int imgHeight = img.rows;
	int imgWeight = img.cols;
	int channel = img.channels();
	int val = 0;
	//灰度二值化
	Mat imgGray = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
	Mat imgBin = Mat::zeros(imgHeight, imgWeight, CV_8UC1);

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

	int label = 0;
	uchar up = 0, left = 0, leftup = 0, rightup = 0;

	int** labelSet;

	//开辟空间:行=y
	labelSet = new int* [imgHeight];

	//开辟空间：列=x
	for (int i = 0; i < imgHeight; ++i)
		labelSet[i] = new int[imgWeight];

	for (int i = 0; i < imgHeight; i++)
		for (int j = 0; j < imgWeight; j++)
			labelSet[i][j] = 0;

	//bgr
	Scalar white(255, 255, 255);

	Scalar blue(255, 0, 0);
	Scalar greed(0, 255, 0);
	Scalar red(0, 0, 255);
	Scalar yellow(0, 255, 255);
	Scalar pink(128, 0, 255);
	Scalar purple(255, 0, 128);
	Scalar origin(0, 128, 255);

	Scalar colorSet[] = { white, blue ,greed ,red ,yellow,pink,purple ,origin };
	Scalar drawColor;
	int k = 0;
	Mat temp = img.clone();
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			val = (int)imgBin.at<uchar>(y, x);
			//如果是白色：255
			if (val == 255)
			{
				Point p(x, y);
				circle(temp, p, 0, red);
				cv::imshow("temp", temp);
				cv::waitKey(5);

				if (y >= 1 && x >= 1)
				{
					//右下角
					if (x == imgWeight - 1 && y == imgHeight - 1)
					{
						up = (int)imgBin.at<uchar>(y - 1, x);
						left = (int)imgBin.at<uchar>(y, x - 1);
						leftup = (int)imgBin.at<uchar>(y - 1, x - 1);
						rightup = 0;
					}
					up = (int)imgBin.at<uchar>(y - 1, x);
					leftup = (int)imgBin.at<uchar>(y - 1, x - 1);
					left = (int)imgBin.at<uchar>(y, x - 1);
					rightup = (int)imgBin.at<uchar>(y - 1, x + 1);
				}
				//第一列
				else if (x == 0 && y >= 1)
				{
					up = (int)imgBin.at<uchar>(y - 1, x);
					leftup = 0;
					left = 0;
					rightup = (int)imgBin.at<uchar>(y, x + 1);
				}
				//第一行
				else if (x >= 1 && y == 0)
				{
					up = 0;
					leftup = 0;
					left = (int)imgBin.at<uchar>(y, x - 1);
					rightup = 0;
				}
				//左上角
				else
				{
					up = 0;
					leftup = 0;
					left = 0;
					rightup = 0;
				}
				printf_s("y:%d x:%d left:%d leftup:%d up:%d rightup:%d\n", y, x, left, leftup, up, rightup);
				//邻域内像素值为0，添加新lable
				if (up == 0 && left == 0 && leftup == 0 && rightup == 0)
				{
					label++;
					imgBin.at<uchar>(y, x) = label;
					printf_s("label:%d\n", label);
					drawColor = colorSet[label];

					//画点
					Point p(x, y);
					circle(temp, p, 0, drawColor);
					cv::imshow("temp", temp);
					cv::waitKey(5);
					continue;
				}
				if (left > 0 && rightup > 0)
				{
					int min = MIN(rightup, left);
					if (rightup == 0)
						min = left;
					if (left == 0)
						min = rightup;
					left = rightup = min;
					imgBin.at<uchar>(y, x) = min;

					drawColor = colorSet[min];
					Point p(x, y);
					circle(temp, p, 0, drawColor);
					cv::imshow("temp", temp);
					cv::waitKey(5);
				}
				if (leftup > 0 && rightup > 0)
				{
					int min = MIN(rightup, leftup);
					if (rightup == 0)
						min = leftup;
					if (leftup == 0)
						min = rightup;
					leftup = rightup = min;
					imgBin.at<uchar>(y, x) = min;

					drawColor = colorSet[min];
					Point p(x, y);
					circle(temp, p, 0, drawColor);
					cv::imshow("temp", temp);
					cv::waitKey(5);
				}
				//如果其中一个不为0(黑)，选择最小的label为新像素label
				else
				{
					int min = MIN(MIN(MIN(up, left), leftup), rightup);

					if (rightup == 0)
						min =left;
					imgBin.at<uchar>(y, x) = min;

					drawColor = colorSet[min];
					Point p(x, y);
					circle(temp, p, 0, drawColor);
					cv::imshow("temp", temp);
					cv::waitKey(5);
				}
			}
			//如果是非白色则遍历下一个像素
			else
				continue;

		}
	}
	printf_s("扫描完成,label:%d\n", label);

	cv::imshow("img", img);
	cv::imshow("imgBin", imgBin);
	cv::waitKey(0);
	cv::destroyAllWindows();
}