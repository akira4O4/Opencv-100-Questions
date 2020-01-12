#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_1_10.h"
using namespace cv;

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

