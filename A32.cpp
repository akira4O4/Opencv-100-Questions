#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_31_40.h"
#include <math.h>
#include <time.h>

using namespace cv;

//计时
clock_t start, stop;
double duration;

Mat Gray(Mat img)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	Mat imgGray = Mat::zeros(imgHeight, imgWidth, CV_8UC1);

	//灰度化
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWidth; ++x)
		{
			imgGray.at<uchar>(y, x) = 0.2126 * (float)img.at<Vec3b>(y, x)[2] \
				+ 0.7152 * (float)img.at<Vec3b>(y, x)[1] \
				+ 0.0722 * (float)img.at<Vec3b>(y, x)[0];
		}
	}
	return imgGray;
}

const int height = 128, width = 128;
//虚数矩阵
std::complex<double> coef[height][width];

void A32(Mat img)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();

	//灰度化
	start = clock();//开始计时
	Mat imgGray = Gray(img);
	Mat imgOut = Mat::zeros(imgHeight, imgWidth, CV_8UC1);

	//DFT:离散傅里叶变换
	std::complex<double> i;//虚数:a+bi
	double val;//像素值
	double theta;
	//在对于二维图片，需要进行两个方向上的傅里叶变换
	for (int y = 0; y < imgHeight; ++y)
	{
		printf_s("傅里叶变换第y:%d行\n", y);
		for (int x = 0; x < imgWidth; ++x)
		{
			i.real(0);
			i.imag(0);
			/*printf_s("y:%d,x:%d\n",y,x);*/
			for (int _y = 0; _y < imgHeight; ++_y)
			{
				for (int _x = 0; _x < imgWidth; ++_x)
				{
					//获取图像的值(采样信号):x(n)
					val = (double)imgGray.at<uchar>(_y, _x);
					//θ=(2πkn)/N
					theta = -2 * PI * ((double)x * (double)_x / (double)imgWidth + (double)y * (double)_y / (double)imgHeight);
					//变换后的数据：X(k)=Σ(N-1)(n=0)[x(n)cos(θ)+jsin(θ)];
					i += std::complex<double>(cos(theta), sin(theta)) * val;
				}
			}
			i /= sqrt(imgHeight * imgWidth);
			coef[y][x] = i;
		}
	}

	printf_s("傅里叶变换计算完成\n");
	double g;
	std::complex<double> G;

	//IDFT 离散傅里叶逆变换
	for (int y = 0; y < imgHeight; ++y)
	{
		printf_s("傅里叶逆变换第y:%d行\n", y);
		for (int x = 0; x < imgWidth; ++x)
		{
			i.real(0);
			i.imag(0);

			for (int _y = 0; _y < imgHeight; ++_y)
			{
				for (int _x = 0; _x < imgWidth; ++_x)
				{
					//获取傅里叶变换过后的数据
					G = coef[_y][_x];
					//θ=(2πkn)/N
					theta = 2 * PI * ((double)_x * (double)x / (double)imgWidth + (double)_y * (double)y / (double)imgHeight);
					//变换后的数据：X(k)=Σ(N-1)(n=0)[x(n)cos(θ)+jsin(θ)];
					i += std::complex<double>(cos(theta), sin(theta)) * G;
				}
			}
			g = std::abs(i) / sqrt(height * width);
			imgOut.at<uchar>(y, x) = (uchar)g;
		}
	}
	/* 结束计时 */
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	printf("运行时间：%f\n", duration);
	printf_s("傅里叶逆变换计算完成\n");
	imshow("imgSrc", img);
	imshow("imgGray", imgGray);
	imshow("imgOut", imgOut);
	waitKey(0);
	destroyAllWindows();
}