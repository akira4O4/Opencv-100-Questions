#pragma once
#include <opencv2/opencv.hpp>
#ifndef _A_41_50_
#define _A_41_50_

#define PI  atan(1) * 4

using namespace cv;

//Canny Function
//灰度化
Mat ImgGray(Mat img);
float Clip(float value, float min, float max);
//高斯滤波
Mat GaussianFilter(Mat img, double Sigma);
//Sobel垂直
Mat SobelFilterV(Mat img);
//Sobel水平
Mat SobelFilterH(Mat img);
Mat GetEdge(Mat imgX, Mat imgY);
Mat GetAngel(Mat imgX, Mat imgY);
//非极大值抑制：NMS
Mat NMS(Mat angle, Mat edge);
//连接边
Mat Histerisis(Mat edge, int HT, int LT);


void A41(Mat img);
void A42(Mat img);
void A43(Mat img);
void A44(Mat img);
void A45(Mat img);
void A46(Mat img);
void A47(Mat img);
void A48(Mat img);
void A49(Mat img);
void A50(Mat img);


#endif // !_A_41_50_