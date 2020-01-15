#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_1_10.h"
#include "A_11_20.h"
#include "A_21_30.h"

using namespace std;
using namespace cv;

int main()
{
	Mat imgSrc1 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img3.jpg");
	Mat imgSrc512 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img512.png");
	Mat imgSrc32 = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img32.png");
	Mat img_dark = imread("C:\\Users\\Administrator\\Desktop\\OpencvTestImg\\img_dark.jpg");
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
	A21(img_dark);

	return 0;
}