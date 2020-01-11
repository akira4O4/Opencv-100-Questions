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

		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");
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

	void A3(int th)
	{
		printf_s("把图像进行二值化");
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");
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
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");
		//Mat API = imread("C:\\Users\\Administrator\\Desktop\\img1.jpg");

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
		printf_s("good k;%f\n", good_k);

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

	void A5(void)
	{
		Mat imgSrc = imread("C:\\Users\\Administrator\\Desktop\\img2.jpg");
		printf_s("RGB-->HSV");
		int imgHeight = imgSrc.rows;
		int imgWeight = imgSrc.cols;
		Mat imgOut = Mat::zeros(imgHeight, imgWeight, CV_32FC3);
		float R, G, B;
		float H, S, V;
		float Cmax, Cmin, delta;

		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWeight; ++x)
			{
				//获取RGB
				R = (float)imgSrc.at<Vec3b>(y, x)[2] / 255;
				G = (float)imgSrc.at<Vec3b>(y, x)[1] / 255;
				B = (float)imgSrc.at<Vec3b>(y, x)[0] / 255;

				Cmax = fmax(R, fmax(G, B));
				Cmin = fmin(R, fmin(G, B));
				delta = Cmax - Cmin;
				//计算	H(0-360)
				if (delta == 0)
				{
					H = 0;
				}
				else if (Cmin == B)
				{
					H = 0.6 * (((G - B) / delta) + 0);
					//H=60 * (G - R) / delta+60;
				}
				else if (Cmin == R)
				{
					H = 0.6 * (((B - R) / delta) + 2);
					//H = 60 * (B - G) / delta +180;
				}
				else if (Cmin == G)
				{
					H = 0.6 * (((R - G) / delta) + 4);
					//H = 60 * (R - B) / delta +300;
				}

				//计算S(0-1)
				if (Cmax == 0)
					S = 0;
				else
					S = delta / Cmax;

				//计算V(0-1)
				V = Cmax;

				imgOut.at<Vec3f>(y, x)[0] = H;
				imgOut.at<Vec3f>(y, x)[1] = S;
				imgOut.at<Vec3f>(y, x)[2] = V;
			}
		}
		imshow("imgSrc", imgSrc);
		imshow("imgOut", imgOut);
		waitKey(0);
		destroyAllWindows();
	}

	void A6(void)
	{
		/*原理：
		假设N是减色因子，将图像中每个像素的值除以NN(使用整数除法，不保留余数。实际上，该算法就是利用了整数除法的特性来实现减色的)。然后将结果乘以NN，得到NN的倍数，再加上N / 2N / 2，就得到相邻的NN的倍数之间的中间值。对所有8位通道值重复这个过程，就会得到(256 / N)∗(256 / N)∗(256 / N)(256 / N)∗(256 / N)∗(256 / N)种可能的颜色值。
		*/
		printf_s("减色处理");
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
					imgOut.at<Vec3b>(y, x)[c] = (uchar)(floor((double)imgSrc.at<Vec3b>(y, x)[c] / n) * n + n/2);
				}
			}
		}
		printf_s("");
		imshow("imgSrc", imgSrc);
		imshow("imgOut", imgOut);
		waitKey(0);
		destroyAllWindows();
	}
};

#endif // ! _Q_1_10_

