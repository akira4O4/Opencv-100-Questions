#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_31_40.h"
#include <math.h>

using namespace cv;

void A36(Mat img)
{
	int T = 8;
	int K = 4;
	const int height = 128, width = 128, channel = 3;
	double coef[height][width][channel];

	//¿Î…¢”‡œ“±‰ªª
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
	//¿Î…¢”‡œ“ƒÊ±‰ªª
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

	imshow("imgSrc", img);
	imshow("out", out);
	waitKey(0);
	destroyAllWindows();
}