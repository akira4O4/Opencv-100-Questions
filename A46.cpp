#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "A_41_50.h"
#include <math.h>
#include <time.h>

using namespace cv;

// 霍夫变换
const int ANGLE_T = 180;//角度
const int RHO_MAX = 127;

// 霍夫表
struct HoughTable {
    int table[RHO_MAX * 2][ANGLE_T];
};

//霍夫变换：投票
HoughTable _HoughVote(HoughTable hough_table, Mat img)
{
    int height = img.rows;
    int width = img.cols;
    int rho = 0;
    double angle = 0;
    //遍历整个图片
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf_s("y:%d,x:%d\n", y, x);
            // 如果整个像素不是边，则直接跳过
            if (img.at<uchar>(y, x) != 255)
                continue;
            // 0 <= 角度 < 180
            for (int t = 0; t < ANGLE_T; t++) {
                angle = PI / 180 * t;
                //r = xcosθ + ysinθ
                rho = (int)(x * cos(angle) + y * sin(angle));
                //进行投票
                hough_table.table[rho + RHO_MAX][t] ++;
            }
        }
    }
    return hough_table;
}

//霍夫变换：非极大值抑制
HoughTable _HoughNMS(HoughTable hough_table)
{
    // 输出表
    HoughTable output_hough_table;

    // 初始化霍夫表
    for (int rho = 0; rho < RHO_MAX * 2; rho++) {
        for (int t = 0; t < ANGLE_T; t++)
        {
            output_hough_table.table[rho][t] = 0;
        }
    }

    // top N x, y
    const int N = 30;
    int top_N_rho[N], top_N_t[N], top_N_vote[N];
    int tmp_rho, tmp_t, tmp_vote, tmp_rho2, tmp_t2, tmp_vote2;
    int rho, t;

    for (int n = 0; n < N; n++)
    {
        top_N_rho[n] = -1;
        top_N_t[n] = -1;
        top_N_vote[n] = -1;
    }

    for (int rho = 0; rho < RHO_MAX * 2; rho++) {
        for (int t = 0; t < ANGLE_T; t++) {
            if (hough_table.table[rho][t] == 0)
                continue;

            // 对比左上
            if (((t - 1) >= 0) && ((rho - 1) >= 0))
                if (hough_table.table[rho][t] < hough_table.table[rho - 1][t - 1])
                    continue;

            // 对比上面
            if ((rho - 1) >= 0) {
                if (hough_table.table[rho][t] < hough_table.table[rho - 1][t]) {
                    continue;
                }
            }

            // 对比右上
            if (((t + 1) < ANGLE_T) && ((rho - 1) >= 0))
                if (hough_table.table[rho][t] < hough_table.table[rho - 1][t + 1])
                    continue;

            //对比左边
            if ((t - 1) >= 0)
                if (hough_table.table[rho][t] < hough_table.table[rho][t - 1])
                    continue;

            // 对比右边
            if ((t + 1) < ANGLE_T)
                if (hough_table.table[rho][t] < hough_table.table[rho][t + 1])
                    continue;

            // 对比左下
            if (((t - 1) >= 0) && ((rho + 1) < RHO_MAX * 2))
                if (hough_table.table[rho][t] < hough_table.table[rho + 1][t - 1])
                    continue;

            // 对比下面
            if ((rho + 1) < RHO_MAX * 2)
                if (hough_table.table[rho][t] < hough_table.table[rho + 1][t])
                    continue;

            // 对比右下
            if (((t + 1) < ANGLE_T) && ((rho + 1) < RHO_MAX * 2))
                if (hough_table.table[rho][t] < hough_table.table[rho + 1][t + 1])
                    continue;

            // 选择前N票
            for (int n = 0; n < N; n++) {
                if (top_N_vote[n] <= hough_table.table[rho][t]) {
                    tmp_vote = top_N_vote[n];
                    tmp_rho = top_N_rho[n];
                    tmp_t = top_N_t[n];
                    top_N_vote[n] = hough_table.table[rho][t];
                    top_N_rho[n] = rho;
                    top_N_t[n] = t;

                    for (int m = n + 1; m < N - 1; m++) {
                        tmp_vote2 = top_N_vote[m];
                        tmp_rho2 = top_N_rho[m];
                        tmp_t2 = top_N_t[m];
                        top_N_vote[m] = tmp_vote;
                        top_N_rho[m] = tmp_rho;
                        top_N_t[m] = tmp_t;
                        tmp_vote = tmp_vote2;
                        tmp_rho = tmp_rho2;
                        tmp_t = tmp_t2;
                    }

                    top_N_vote[N - 1] = tmp_vote;
                    top_N_rho[N - 1] = tmp_rho;
                    top_N_t[N - 1] = tmp_t;
                    break;
                }
            }
        }
    }

    // 获得前N名投票的像素
    for (int n = 0; n < N; n++) {
        if (top_N_rho[n] == -1)
            break;
        rho = top_N_rho[n];
        t = top_N_t[n];
        output_hough_table.table[rho][t] = hough_table.table[rho][t];
    }

    return output_hough_table;
}

//霍夫逆变换
Mat HoughInverse(HoughTable hough_table, Mat img) {
    int height = img.rows;
    int width = img.cols;

    double _cos, _sin;
    int y, x;

    for (int rho = 0; rho < RHO_MAX * 2; rho++) {
        for (int t = 0; t < ANGLE_T; t++) {
            // if not vote, skip
            if (hough_table.table[rho][t] < 1) {
                continue;
            }

            _cos = cos(t * PI / 180);
            _sin = sin(t * PI / 180);

            if ((_sin == 0) || (_cos == 0)) {
                continue;
            }

            for (int x = 0; x < width; x++) {
                y = (int)(-_cos / _sin * x + (rho - RHO_MAX) / _sin);

                if ((y >= 0) && (y < height)) {
                    img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);
                }
            }

            for (int y = 0; y < height; y++) {
                x = (int)(-_sin / _cos * y + (rho - RHO_MAX) / _cos);

                if ((x >= 0) && (x < width)) {
                    img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);
                }
            }
        }
    }

    return img;
}
void A46(Mat img)
{
    //Canny
    Mat gray = ImgGray(img);
    Mat gaussian = GaussianFilter(gray, 1.4);
    Mat fy = SobelFilterV(gaussian);
    Mat fx = SobelFilterH(gaussian);
    Mat edge = GetEdge(fx, fy);
    Mat angle = GetAngel(fx, fy);
    edge = NMS(angle, edge);
    edge = Histerisis(edge, 100, 30);
    imshow("canny", edge);

    HoughTable hough_table;
    //投票
    hough_table = _HoughVote(hough_table, edge);
    //非极大值抑制
    hough_table = _HoughNMS(hough_table);
    //霍夫逆变换
    Mat imgHough = HoughInverse(hough_table, img);
    imshow("imgHough", imgHough);
    waitKey(0);
    destroyAllWindows();
}