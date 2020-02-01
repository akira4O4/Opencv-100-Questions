#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_1_10.h"
#include "A_11_20.h"
#include "A_21_30.h"
#include "A_31_40.h"
#include "A_41_50.h"
#include "A_51_60.h"
#include "A_61_70.h"
#include "A_71_80.h"

using namespace std;
using namespace cv;

int main()
{
	Mat imgSrc32 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img32.png");

	Mat imgSrc128 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img128.png");
	Mat imgSrc128part = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img128_part.png");

	Mat imgSrc256 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img256.png");

	Mat imgSrc512 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img512.png");


	Mat img_dark = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img_dark.jpg");
	Mat img_gamma = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\gamma.jpg");
	Mat img_canny = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\canny2.png");

	Mat imori = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\imori.jpg");
	Mat imori_part = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\imori_part.jpg");


	Mat part1 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\color.png");
	Mat part2 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\blue1_part.png");

	Mat seg = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\seg.png");
	Mat img10 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img10.png");
	Mat words = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\words.png");
	//A1();
	//A2();
	//A3();
	//A4();
	//A5();
	//A6();
	//A7();
	//A8();
	//A9();
	//A10();
	//A11(imgSrc2);
	//A12(imgSrc1);
	//A13(imgSrc512);
	//A14(imgSrc512);
	//A15(imgSrc512);
	//A16(imgSrc512);
	//A17(imgSrc512);
	//A18(imgSrc512);
	//A19(imgSrc512);
	//A20(imgSrc512);
	//A21(img_dark);
	//A22(img_dark);
	//A23(img_dark);
	//A24(img_gamma);
	//A25(imgSrc512);
	//A26(imgSrc512);
	//A27(imgSrc512);
	//A28(imgSrc512);
	//A29(imgSrc512);
	//A30(imgSrc512);
	//A31(imgSrc128);
	//A32(imgSrc128);
	//A41(imgSrc512);
	//A42(imgSrc512);
	//A43(img_canny);
	//A44(img_canny);
	//A45(img_canny);
	//A47(imgSrc512);
	//A48(imgSrc512);
	//A49(imgSrc512);
	//A50(imgSrc512);
	//A51(imgSrc512);
	//A52(imgSrc512);
	//A53(imgSrc512);
	//A54(imgSrc128, imgSrc128part);
	//A55(imgSrc128, imgSrc128part);
	//A56(imgSrc128, imgSrc128part);
	//A57(imgSrc128, imgSrc128part);
	//A58(seg);
	//A59(seg);
	//A61(img10);
	//A62(img10);
	//A63(words);
	//A64(words);
	//A65(words);
	//A70(imori);
	//A71(imori);
	//A72(imori);
	//A73(imori);
	//A74(imori);
	//A75(imori);
	A76(imori);

}