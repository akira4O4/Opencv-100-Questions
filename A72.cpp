#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_71_80.h"
using namespace cv;
//膨胀
Mat Dilate(Mat img, int n)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();

	Mat imgDilate = img.clone();
	Mat tempImg;//作为对比图
	for (int t = 0; t < n; ++t)
	{
		tempImg = imgDilate.clone();
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWidth; ++x)
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
				if ((x < imgWidth - 1) && (tempImg.at<uchar>(y, x + 1) == 255))
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
	return imgDilate;

}

//腐蚀
Mat Erode(Mat img, int n)
{
	int imgHeight = img.rows;
	int imgWidth = img.cols;
	int channel = img.channels();

	Mat imgErode = img.clone();
	Mat tempImg;//作为对比图

	for (int t = 0; t < n; ++t)
	{
		tempImg = imgErode.clone();
		for (int y = 0; y < imgHeight; ++y)
		{
			for (int x = 0; x < imgWidth; ++x)
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
				if ((x < imgWidth - 1) && (tempImg.at<uchar>(y, x + 1) == 0))
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
	return imgErode;
}

//开运算
Mat Morphology_Opening(Mat img,int n)
{
	Mat out = Erode(img, n);
	out = Dilate(out, n);
	return out;
}

//闭运算
Mat Morphology_Closing(Mat img, int n)
{
	Mat out = Dilate(img, n);
	out = Erode(out, n);
	return out;
}


void A72(Mat img)
{
	int imgHeight = img.rows;
	int imgWeight = img.cols;
	int channel = img.channels();
	Mat imgHSV = Mat::zeros(imgHeight, imgWeight, CV_32FC3);
	Mat imgRGB = Mat::zeros(imgHeight, imgWeight, CV_8UC3);

	float R, G, B;
	float H, S, V;
	double C, X, _H;
	float Cmax, Cmin, delta;

	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			//获取RGB
			R = (float)img.at<Vec3b>(y, x)[2] / 255;
			G = (float)img.at<Vec3b>(y, x)[1] / 255;
			B = (float)img.at<Vec3b>(y, x)[0] / 255;

			Cmax = fmax(R, fmax(G, B));
			Cmin = fmin(R, fmin(G, B));
			delta = Cmax - Cmin;

			if (delta == 0)
				H = 0;
			else if (Cmin == B)
				H = 60 * (G - R) / delta + 60;
			else if (Cmin == R)
				H = 60 * (B - G) / delta + 180;
			else if (Cmin == G)
				H = 60 * (R - B) / delta + 300;

			//计算S(0-1)
			if (Cmax == 0)
				S = 0;
			else
				S = delta;
			//S = delta/Cmax;效果不好

		//计算V(0-1)
			V = Cmax;

			imgHSV.at<Vec3f>(y, x)[0] = H;
			imgHSV.at<Vec3f>(y, x)[1] = S;
			imgHSV.at<Vec3f>(y, x)[2] = V;
		}
	}

	Mat bin = Mat::zeros(imgHeight, imgWeight, CV_8UC1);

	//蓝色范围180 - 260
	for (int y = 0; y < imgHeight; ++y)
	{
		for (int x = 0; x < imgWeight; ++x)
		{
			int h = imgHSV.at<Vec3f>(y, x)[0];
			if (h > 180 && h < 260)
				bin.at<uchar>(y, x) = 1;
			else
				bin.at<uchar>(y, x) = 0;
		}
	}

	Mat t = bin.clone();
	for (int y = 0; y < imgHeight; ++y)
		for (int x = 0; x < imgWeight; ++x)
			t.at<uchar>(y, x) *= 255;
	cv::imshow("t", t);

	int n = 5;

	bin = Morphology_Closing(bin, n);
	bin = Morphology_Opening(bin, n);
	
	t = bin.clone();
	for (int y = 0; y < imgHeight; ++y)
		for (int x = 0; x < imgWeight; ++x)
			t.at<uchar>(y, x) *= 255;
	cv::imshow("_t", t);

	Mat out = Mat::zeros(imgHeight, imgWeight, CV_8UC3);
	
	for (int y = 0; y < imgHeight; ++y)
		for (int x = 0; x < imgWeight; ++x)
			for (int c = 0; c < channel; ++c)
				out.at<Vec3b>(y, x)[c] = img.at<Vec3b>(y, x)[c] * (1 - bin.at<uchar>(y, x));

	cv::imshow("img", img);
	cv::imshow("out", out);

	cv::waitKey(0);
	cv::destroyAllWindows();
}
