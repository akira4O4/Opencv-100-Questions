#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_31_40.h"
#include <math.h>

using namespace cv;

void A38(Mat img)
{
	if (img.rows != 128 || img.cols != 128)
	{
		printf_s("图片不符合规格");
		return;
	}

	const int T = 8;
	int K = 4;
	const int height = 128, width = 128, channel = 3;
	double coef[height][width][channel];

	//离散余弦变换
	double I;
	double F;
	double Cu, Cv;

	Mat out = Mat::zeros(height, width, CV_8UC3);

	for (int ys = 0; ys < height; ys += T)
	{
		for (int xs = 0; xs < width; xs += T)
		{
			for (int c = 0; c < channel; c++)
			{
				for (int v = 0; v < T; v++)
				{
					for (int u = 0; u < T; u++)
					{
						F = 0;

						if (u == 0)
							Cu = 1. / sqrt(2);
						else
							Cu = 1;

						if (v == 0)
							Cv = 1. / sqrt(2);
						else
							Cv = 1;

						for (int y = 0; y < T; y++)
						{
							for (int x = 0; x < T; x++)
							{
								I = (double)img.at<cv::Vec3b>(ys + y, xs + x)[c];
								F += 2. / T * Cu * Cv * I * cos((2. * x + 1) * u * PI / 2. / T) * cos((2. * y + 1) * v * PI / 2. / T);
							}
						}
						coef[ys + v][xs + u][c] = F;
					}
				}
			}
		}
	}
	
	double Q[T][T] = { {16, 11, 10, 16, 24, 40, 51, 61},
				  {12, 12, 14, 19, 26, 58, 60, 55},
				  {12, 12, 14, 19, 26, 58, 60, 55},
				  {14, 17, 22, 29, 51, 87, 80, 62},
				  {18, 22, 37, 56, 68, 109, 103, 77},
				  {24, 35, 55, 64, 81, 104, 113, 92},
				  {49, 64, 78, 87, 103, 121, 120, 101},
				  {72, 92, 95, 98, 112, 100, 103, 99}
	};

	for (int ys = 0; ys < height; ys += T)
		for (int xs = 0; xs < width; xs += T)
			for (int c = 0; c < channel; c++)
				for (int y = 0; y < T; y++)
					for (int x = 0; x < T; x++)
						coef[ys + y][xs + x][c] = round(coef[ys + y][xs + x][c] / Q[y][x]) * Q[y][x];


	//离散余弦逆变换
	double f;
	for (int ys = 0; ys < height; ys += T)
	{
		for (int xs = 0; xs < width; xs += T)
		{
			for (int c = 0; c < channel; c++)
			{
				for (int y = 0; y < T; y++)
				{
					for (int x = 0; x < T; x++)
					{
						f = 0;

						for (int v = 0; v < K; v++)
						{
							for (int u = 0; u < K; u++)
							{
								if (u == 0)
									Cu = 1. / sqrt(2);

								else
									Cu = 1;


								if (v == 0)
									Cv = 1. / sqrt(2);

								else
									Cv = 1;


								f += 2. / T * Cu * Cv * coef[ys + v][xs + u][c] * cos((2. * x + 1) * u * PI / 2. / T) * cos((2. * y + 1) * v * PI / 2. / T);
							}
						}

						f = fmin(fmax(f, 0), 255);
						out.at<cv::Vec3b>(ys + y, xs + x)[c] = (uchar)f;
					}
				}
			}
		}
	}

	//均方误差
	double MSE = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int c = 0; c < channel; c++)
			{
				MSE += pow(((double)img.at<cv::Vec3b>(y, x)[c] -
					(double)out.at<cv::Vec3b>(y, x)[c]), 2);
			}
		}
	}

	//峰值信噪比
	double v_max = 255;
	double PSNR = 10 * log10(v_max * v_max / MSE);

	double bitrate = T * K * K / T * T;

	printf_s("MSE:%f\n", MSE);
	printf_s("PSNR:%f\n", PSNR);
	printf_s("bitrate:%f\n", bitrate);

	imshow("imgSrc", img);
	imshow("out", out);
	waitKey(0);
	destroyAllWindows();
}