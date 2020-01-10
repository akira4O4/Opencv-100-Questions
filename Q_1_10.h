#pragma once

#ifndef  _Q_1_10_
#define _Q_1_10_

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

class Q_1_10
{

private:

	int imgWidth = 0;
	int imgHeight = 0;

public:
	void A1(void)
	{
		//图形宽高

		printf_s("//读取图像，然后将{RGB}通道替换成{BGR}通道\n");

		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\nanasai1.jpg");
		imgWidth = imgSrc.cols;
		imgHeight = imgSrc.rows;

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

		printf_s("imgWidth:%d\n", imgWidth);
		printf_s("imgHeight:%d\n", imgHeight);

		imshow("imgSrc(RGB)", imgSrc);
		imshow("imgOut(BGR)", imgOut);
		waitKey(0);
		destroyWindow("imgSrc");
	}
	void A2(void)
	{
		printf_s("计算图片灰度");
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\nanasai1.jpg");
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

	void A3(int th)
	{
		printf_s("把图像进行二值化");
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\nanasai1.jpg");
		int imgHeight = imgSrc.rows;
		int imgWeight = imgSrc.cols;
		Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
		//先进性灰度化
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				imgOut.at<uchar>(y, x) = 0.114 * (float)imgSrc.at<Vec3b>(y, x)[2]
					+ 0.587 * (float)imgSrc.at<Vec3b>(y, x)[1]
					+ 0.299 * (float)imgSrc.at<Vec3b>(y, x)[0];
			}
		}
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				if (imgOut.at<uchar>(y, x) > th)
				{
					imgOut.at<uchar>(y, x) = 255;//白色
				}
				else
				{
					imgOut.at<uchar>(y, x) = 0;//黑色
				}

			}
		}
		imshow("imgSrc", imgSrc);
		imshow("imgOut", imgOut);
		waitKey(0);
		destroyAllWindows();
	}

	void A4(void)
	{
		printf_s("大津二值化算法");
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\nanasai1.jpg");
		//Mat API = imread("C:\\Users\\Administrator\\Desktop\\nanasai1.jpg");

		int imgHeight = imgSrc.rows;
		int imgWeight = imgSrc.cols;

		Mat imgGray = Mat::zeros(imgHeight, imgWeight, CV_8UC1);
		Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_8UC1);

		//灰度化
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				imgGray.at<uchar>(y, x) = 0.114 * (float)imgSrc.at<Vec3b>(y, x)[2]
					+ 0.587 * (float)imgSrc.at<Vec3b>(y, x)[1]
					+ 0.299 * (float)imgSrc.at<Vec3b>(y, x)[0];
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
		printf_s("good k;%f\n",good_k);

		//取得最好的k值，以k值作为阈值进行二值化
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				if (imgGray.at<uchar>(y, x) > good_k)
					imgOut.at<uchar>(y, x) = 255;
				else
					imgOut.at<uchar>(y, x) = 0;
			}
		}
		imshow("imgSrc", imgSrc);
		imshow("imgGray", imgGray);
		imshow("ostu", imgOut);
		//imshow("API", API);
		waitKey(0);
		destroyAllWindows();
	}
};

#endif // ! _Q_1_10_

