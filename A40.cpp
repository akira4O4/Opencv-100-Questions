#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_31_40.h"
#include <math.h>

using namespace cv;
//将图像从RGB色彩空间变换到YCbCr色彩空间；
//对YCbCr做DCT；
//DCT之后做量化；
//量化之后应用IDCT；
//IDCT之后从YCbCr色彩空间变换到RGB色彩空间。
void A40(Mat img)
{
	if (img.rows != 128 || img.cols != 128)
	{
		printf_s("图片不符合规格");
		return;
	}
	const int height = 128;
	const int width = 128;

	Mat YCbCr = Mat::zeros(height, width, CV_32FC3);
	Mat out = Mat::zeros(height, width, CV_8UC3);

	//RGB->YCrCb
	for (int y = 0; y < height; y++)
	{
		printf_s("y:%d\n", y);
		for (int x = 0; x < width; x++)
		{
			// Y
			YCbCr.at<Vec3f>(y, x)[0] = (int)((float)img.at<Vec3b>(y, x)[0] * 0.114 + (float)img.at<Vec3b>(y, x)[1] * 0.5870 + (float)img.at<Vec3b>(y, x)[2] * 0.299);

			// Cb
			YCbCr.at<Vec3f>(y, x)[1] = (int)((float)img.at<Vec3b>(y, x)[0] * 0.5 + (float)img.at<Vec3b>(y, x)[1] * (-0.3323) + (float)img.at<Vec3b>(y, x)[2] * (-0.1687) + 128);

			// Cr
			YCbCr.at<Vec3f>(y, x)[2] = (int)((float)img.at<Vec3b>(y, x)[0] * (-0.0813) + (float)img.at<Vec3b>(y, x)[1] * (-0.4187) + (float)img.at<Vec3b>(y, x)[2] * 0.5 + 128);
		}
	}
	const int T = 8;
	int K = 4;
	const int channel = 3;
	double coef[height][width][channel];

	//离散余弦变换
	double I;
	double F;
	double Cu, Cv;
	//DCT
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
								I = (double)YCbCr.at<Vec3f>(ys + y, xs + x)[c];
								F += 2. / T * Cu * Cv * I * cos((2. * x + 1) * u * PI / 2. / T) * cos((2. * y + 1) * v * PI / 2. / T);
							}
						}
						coef[ys + v][xs + u][c] = F;
					}
				}
			}
		}
	}
	//量化
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
	//IDCT
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
						YCbCr.at<Vec3f>(ys + y, xs + x)[c] = (uchar)f;
					}
				}
			}
		}
	}

	//YCrCb->RGB
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// R
			out.at<Vec3b>(y, x)[2] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] + (YCbCr.at<Vec3f>(y, x)[2] - 128) * 1.4102);

			// G
			out.at<Vec3b>(y, x)[1] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] - (YCbCr.at<Vec3f>(y, x)[1] - 128) * 0.3441 - (YCbCr.at<Vec3f>(y, x)[2] - 128) * 0.7139);

			// B
			out.at<Vec3b>(y, x)[0] = (uchar)(YCbCr.at<Vec3f>(y, x)[0] + (YCbCr.at<Vec3f>(y, x)[1] - 128) * 1.7718);
		}
	}

	imshow("img", img);
	imshow("out", out);
	waitKey(0);
	destroyAllWindows();
}