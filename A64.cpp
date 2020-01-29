#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_61_70.h"
#include <math.h>

using namespace cv;

int Calculate8Connections(Mat img8, int y, int x, int H, int W)
{
	int s = 0;
	s += (img8.at<uchar>(y, MIN(x + 1, W - 1)) - img8.at<uchar>(y, MIN(x + 1, W - 1)) * img8.at<uchar>(MAX(y - 1, 0), MIN(x + 1, W - 1)) * img8.at<uchar>(MAX(y - 1, 0), x));
	s += (img8.at<uchar>(MAX(y - 1, 0), x) - img8.at<uchar>(MAX(y - 1, 0), x) * img8.at<uchar>(MAX(y - 1, 0), MAX(x - 1, 0)) * img8.at<uchar>(y, MAX(x - 1, 0)));
	s += (img8.at<uchar>(y, MAX(x - 1, 0)) - img8.at<uchar>(y, MAX(x - 1, 0)) * img8.at<uchar>(MIN(y + 1, H - 1), MAX(x - 1, 0)) * img8.at<uchar>(MIN(y + 1, H - 1), x));
	s += (img8.at<uchar>(MIN(y + 1, H - 1), x) - img8.at<uchar>(MIN(y + 1, H - 1), x) * img8.at<uchar>(MIN(y + 1, H - 1), MIN(x + 1, W - 1)) * img8.at<uchar>(y, MIN(x + 1, W - 1)));
	return s;
}

void A64(Mat img)
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

	Mat img8 = Mat::zeros(H, W, CV_8UC1);

	//取得最好的k值，以k值作为阈值进行二值化
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			//8连接数：在这里进行翻转0-255
			if (imgGray.at<uchar>(y, x) > good_k)
			{
				imgBin.at<uchar>(y, x) = 1;
				img8.at<uchar>(y, x) = 0;
			}
			else
			{
				imgBin.at<uchar>(y, x) = 0;
				img8.at<uchar>(y, x) = 1;
			}

		}
	}
	//被删除像素应该满足6个条件
	//1.p的灰度值为255，即p不是背景；
	//	2.x0、x2、x4、x6不全为255；（不然删除p，会造成图像空心）
	//	3.x0 - x7至少有2个255；（若只有一个255，则p为图像的某个端点，不能删除否则影响图像性质，若没有255，则p为孤立点，也不能删除）
	//	4.p的8联通区域连接数为1，即Nc（p） = 1，此时p称为可删除点；
	//	5.假设x2被标记删除，x2 = 0时，p的联通连接数为1；
	//	6.假设x4被标记删除，x4 = 0时，p的联通连接数为1。

	Mat out = imgBin.clone();
	Mat tmp;
	bool flag = true;

	while (flag)
	{
		flag = false;
		tmp = out.clone();
		for (int y = 0; y < H; ++y)
		{
			for (int x = 0; x < W; ++x)
			{
				if (out.at<uchar>(y, x) == 0)
					img8.at<uchar>(y, x) = 1;
				else
					img8.at<uchar>(y, x) = 0;
			}
		}

		for (int y = 0; y < H; ++y)
		{
			for (int x = 0; x < W; ++x)
			{
				//黑色则跳过
				if (tmp.at<uchar>(y, x) == 0)
					continue;

				//4邻域内至少有一个0
				if (tmp.at<uchar>(MAX(y - 1, 0), x) * tmp.at<uchar>(MIN(y + 1, H - 1), x)* tmp.at<uchar>(y, MAX(x - 1, 0) * tmp.at<uchar>(y, MIN(x + 1, W - 1)) !=0))
					continue;
				
				//x1-x8 中，至少有2个为1
				int sum = 0;
				for (int _y = -1; _y < 2; ++_y)
				{
					for (int _x = -1; _x < 2; ++_x)
					{
						if (_y == 0 && _x == 0)
							continue;
						sum += tmp.at<uchar>(y + _y, x + _x);
					}
				}
				if (sum <= 1)
					continue;

				//p的8连通联结数为1；
				//计算（y,x）的8连接数
				int s = Calculate8Connections(img8, y, x, H, W);
				if (s != 1)
					continue;

				// 条件5: 假设p2已标记删除（1），则令p2为背景（1），p的联结数=1 
				//在img8中 0是前景，1是背景
				img8.at<uchar>(y - 1, x) = 1;
				s = Calculate8Connections(img8, y, x, H, W);
				img8.at<uchar>(y - 1, x) = 0;
				if (s != 1)
					continue;
				
				// 条件6: 假设p4已标记删除，则令p4为背景，p的联结数=1 
				img8.at<uchar>(y, x - 1) = 1;
				s = Calculate8Connections(img8, y, x, H, W);
				img8.at<uchar>(y, x - 1) = 0;

				if (s != 1)
					continue;

				printf_s("执行\n");
				out.at<uchar>(y, x) = 0;//满足以上条件则删除标记
				flag = true;
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
			out.at<uchar>(y, x) = out.at<uchar>(y, x) * 255;
		}
	}
	cv::imshow("img", img);
	cv::imshow("out", out);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

