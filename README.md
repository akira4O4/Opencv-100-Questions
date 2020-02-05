# Opencv的100道题目
## 1-10题的题目：
### 1-20需要引入头文件：A_1_10.h
- [通道交换](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A1.cpp "通道交换")
- [灰度化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A2.cpp "灰度化")
- [二值化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A3.cpp "二值化")
- [大津二值化算法](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A4.cpp "大津二值化算法")
- [RGB->HSV色域变换](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A5.cpp "RGB->HSV色域变换")
- [减色处理](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A6.cpp "减色处理")
- [平均池化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A7.cpp "平均池化")
- [最大池化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A8.cpp "最大池化")
- [高斯滤波](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A9.cpp "高斯滤波")
- [中值滤波](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A10.cpp "中值滤波")

## 1-10题重要算法解析：
### 一维高斯分布
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/一维高斯分布.png)
### 二维高斯分布
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/二维高斯分布.png)
### 最大类内方差
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/最大类内方差1.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/最大类内方差2.png)


## 11-10题的题目：
- [均值滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A11.cpp "均值滤波器")
- [Motion Filter](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A12.cpp "Motion Filter")
- [MAX-MIN滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A13.cpp "MAX-MIN滤波器")
- [差分滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A14.cpp "差分滤波器")
- [Sobel滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A15.cpp "Sobel滤波器")
- [Prewitt滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A16.cpp "Prewitt滤波器")
- [Laplacian滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A17.cpp "Laplacian滤波器")
- [Emboss滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A18.cpp "Emboss滤波器")
- [LoG滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A19.cpp "LoG滤波器")
- [直方图(C++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A20.cpp "直方图")
- [直方图(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A20.py "直方图")
### 11-20需要引入头文件：A_11_20.h
11-20题全是关于滤波器的题目
### 什么是边缘？
边缘一般是指图像中某一局部强度剧烈变化的区域。强度变化一般有2中情况，阶跃效应和屋顶效应。而边缘检测的任务就是找到具有阶跃变化或者屋顶变化的像素点的集合。
边缘检测基本原理：
- 对于阶跃效应：一阶微分的峰值为边缘点，二阶微分的零点为边缘点。
具体来说，从阶跃效应的那张图可以看到边缘处的斜率（一阶导）最大，所以一阶微分的峰值是边缘点，而斜率是先增大后减小的，即边缘点的二阶导为0处。
#### 阶跃效应
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/阶跃效应.png)

- 对于屋顶效应：一阶微分的零点为边缘点，二阶微分的峰值为边缘点。
#### 屋顶效应
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/屋顶效应.png)


## 11-20题重要算法解析：
### 均值滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/均值滤波卷积核.png)
### 运动滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/运动滤波器.png)
### MAX-MIN滤波器(效果图)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/max-min.png)
### 差分滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/垂直滤波器.png)

![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/水平滤波器.png)

### Sobel滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/Sobel卷积核.png)
### Prewitt滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/prewitt算子.png)
### Laplacian滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/4领域拉普拉斯算子.png)
### Emboss滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/Emboss算子.png)
### LoG滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/高斯拉普拉斯算子.png)
### 直方图
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/直方图.png)

## 21-30题的题目：
### 11-20需要引入头文件：A_21_30.h
- [直方图归一化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A21.cpp "直方图归一化")
- [方图操作](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A22.cpp "方图操作")
- [直方图均衡化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A23.cpp "直方图均衡化")
- [伽玛校正](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A24.cpp "伽玛校正")
- [最邻近插值](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A25.cpp "最邻近插值")
- [双线性插值](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A26.cpp "双线性插值")
- [双三次插值](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A27.cpp "双三次插值")
- [仿射变换-平行移动](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A28.cpp "仿射变换-平行移动")
- [仿射变换-放大缩小](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A29.cpp "仿射变换-放大缩小")
- [仿射变换-旋转](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A30.cpp "仿射变换-旋转")

## 21-30题重要算法解析：
### 均值方差均方差
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/均值方差标准差.jpg)
### 伽马矫正
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/伽马矫正.png)
### 最邻近插值
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/最邻近插值.png)
### 双线性插值
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双线性插值1.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双线性插值2.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双线性插值4.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双线性插值3.png)
### BiCubic函数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/BiCubic函数.png)
### 双三次插值
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双三次插值2.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双三次插值1.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/双三次插值5.png)
### 齐次坐标系到笛卡尔坐标系转换
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/齐次到笛卡尔坐标.png)
### 放射变换
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/仿射变换1.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/仿射变换2.png)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/仿射变换3.png)
#### 平移量为0的仿射变换
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/平移量为0的仿射变换.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/仿射变换4.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/放射变换5.png)
## 31-40题的题目：
# 暂无
### 11-20需要引入头文件：A_31_40.h

## 41-50题的题目：
### 41-50需要引入头文件：A_41_50.h
- [Canny边缘检测：边缘强度](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A41.cpp "Canny边缘检测：边缘强度")
- [Canny边缘检测：边缘细化](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A42.cpp "Canny边缘检测：边缘细化")
- [Canny 边缘检测：滞后阈值](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A43.cpp "Canny 边缘检测：滞后阈值")
- [霍夫变换：直线检测](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A44.cpp "霍夫变换：直线检测")
- [霍夫变换：直线检测-NMS](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A45.cpp "霍夫变换：直线检测-NMS")
- [霍夫变换：直线检测-霍夫逆变换](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A46.cpp "霍夫变换：直线检测-霍夫逆变换")
- [膨胀（Dilate）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A47.cpp "膨胀（Dilate）")
- [腐蚀（Erode）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A48.cpp "腐蚀（Erode）")
- [开运算（Opening Operation）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A49.cpp "开运算（Opening Operation）")
- [闭运算（Closing Operation）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A50.cpp "闭运算（Closing Operation）")
## 41-50题重要算法解析：
### Canny边缘检测-高斯核
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/canny1.png)
### Canny边缘检测-Sobel核（垂直和水平）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/canny2.png)
### Canny边缘检测-求梯度
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/canny3.png)
### 霍夫变换
#### 笛卡尔坐标系下直线
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换1.png)  
#### 霍夫变换下坐标方程
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换2.png)  
#### 笛卡尔坐标系->霍夫坐标系（直线）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换3.png)  
#### 笛卡尔坐标系->霍夫坐标系（点）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换4.png)  
#### 笛卡尔坐标系->霍夫坐标系（两点）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换5.png)  
#### 笛卡尔坐标系->霍夫坐标系（三点）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换6.png)  
#### 笛卡尔坐标系->霍夫坐标系（多点）
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换7.png)  
#### 通过霍夫坐标系下找最好共线点
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换8.png)  
#### 极坐标系
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换9.png)  
#### 极坐标系->霍夫坐标系
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换10.png)  
#### 伪代码
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/霍夫变换11.png)  

## 51-60题的题目：
### 51-60题需要引入头文件：A_51_60.h
- [形态学梯度（Morphology Gradient）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A51.cpp "形态学梯度（Morphology Gradient）")
- [顶帽（Top Hat）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A52.cpp "顶帽（Top Hat）")
- [黑帽（Black Hat）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A53.cpp "黑帽（Black Hat）")
- [误差平方和](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A54.cpp "误差平方和")
- [绝对值差和](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A55.cpp "绝对值差和")
- [归一化交叉相关](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A56.cpp "归一化交叉相关")
- [零均值归一化交叉相关](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A57.cpp "零均值归一化交叉相关")
- [4邻域连通域标记](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A58.cpp "4邻域连通域标记")
- [8邻域连通域标记](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A59.cpp "8邻域连通域标记")
- [透明混合（Alpha Blending）(py)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A60.py "透明混合（Alpha Blending）")
## 51-60题重要算法解析：
### 形态学梯度
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/形态学梯度.png)
### 模式匹配-误差平方和(SSD)
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/误差平方和(SSD).png)

### 模式匹配-绝对值差和
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/绝对值差和.png)
### 模式匹配-归一化交叉相关
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/归一化交叉相关.png)
### 模式匹配-零均归一化
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/零均归一化.png)
### 模式匹配-ncc zncc
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/ncc_zncc.png)

## 61-70题的题目：
### 61-70需要引入头文件：A_61_70.h
- [4连接数(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A61.cpp "4连接数")
- [4连接数(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A61.py "4连接数")
- [8连接数(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A62.cpp "8连接数")
- [8连接数(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A62.py "8连接数")
- [细化处理(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A63.cpp "细化处理")
- [细化处理(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A63.py "细化处理")
- [Hilditch 细化算法(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A64.cpp "Hilditch 细化算法")
- [Hilditch 细化算法(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A64.py "Hilditch 细化算法")
- [Zhang-Suen细化算法(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A65.cpp "Zhang-Suen细化算法")
- [Zhang-Suen细化算法(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A65.py "Zhang-Suen细化算法")
- [HOG-梯度幅值・梯度方向(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A66.py "HOG-梯度幅值・梯度方向")
- [HOG-梯度直方图(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A67.py "HOG-梯度直方图")
- [HOG-直方图归一化(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A68.py "HOG-直方图归一化")
- [HOG-可视化特征量(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A69.py "HOG-可视化特征量")
- [色彩追踪（Color Tracking）(python)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A70.py "色彩追踪（Color Tracking）")
- [色彩追踪（Color Tracking）(c++)](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A70.cpp "色彩追踪（Color Tracking）")
## 61-70题重要算法解析：
### 4连通
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/4连通.png) 
### 8连通
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/8连通.png)  
### HOG
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/HOG1.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/图像梯度1.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/图像梯度2.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/9bin.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/block.png)  

## 71-80题的题目：
### 71-80题需要引入头文件：A_71_80.h
- [掩膜（Masking）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A71.cpp "掩膜（Masking）")
- [掩膜（色彩追踪（Color Tracking）+形态学处理）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A72.cpp "掩膜（色彩追踪（Color Tracking）+形态学处理）")
- [缩小和放大](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A73.cpp "缩小和放大")
- [使用差分金字塔提取高频成分](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A74.cpp "使用差分金字塔提取高频成分")
- [高斯金字塔（Gaussian Pyramid）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A75.cpp "高斯金字塔（Gaussian Pyramid）")
- [显著图（Saliency Map）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A76.cpp "显著图（Saliency Map）")
- [Gabor 滤波器（Gabor Filter）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A77.cpp "Gabor 滤波器（Gabor Filter）")
- [旋转Gabor滤波器](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A78.cpp "旋转Gabor滤波器")
- [使用Gabor滤波器进行边缘检测](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A79.cpp "使用Gabor滤波器进行边缘检测")
- [使用Gabor滤波器进行特征提取](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A80.py "使用Gabor滤波器进行特征提取")  
## 71-80题重要算法解析：
#### 三角函数+高斯分布
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/三角函数_高斯分布.png)   
### gabor滤波器
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor滤波器.png)  
### gabor实数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor实数.png)  
### gabor虚数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor虚数.png)  
### gabor复数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor复数.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor1.png)  
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/gabor3.png)  

## 81-90题的题目：
- [Hessian角点检测](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A81.cpp "Hessian角点检测")
- [Harris角点检测第一步：Sobel + Gausian）](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A82.cpp "Harris角点检测第一步：Sobel + Gausian")
- [Harris角点检测第二步：角点检测](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A83.cpp "Harris角点检测第二步：角点检测")
- [简单图像识别第一步：减色化+柱状图^3](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A84.cpp "简单图像识别第一步：减色化+柱状图^3")
- [简单图像识别第二步：判别类别](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A85.cpp "简单图像识别第二步：判别类别")
- [简单图像识别第三步：评估](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A86.cpp "简单图像识别第三步：评估")
- [简单图像识别第四步：k-NN](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A87.cpp "简单图像识别第四步：k-NN")
- [k-平均聚类算法 第一步：生成质心](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A88.cpp "k-平均聚类算法第一步：生成质心")
- [k-平均聚类算法 第二步：聚类](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A89.cpp "k-平均聚类算法第二步：聚类")
- [k-平均聚类算法 第三步：调整初期类别](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/A90.py "k-平均聚类算法 第三步：调整初期类别")  
## 81-90题重要算法解析：
#### Hessian矩阵
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/Hessian矩阵.png)   
### 高斯滤波+Hessian矩阵
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/高斯滤波_Hessian矩阵.png)  
### 图像一阶导数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/图像一阶导数.png)  
### 图像二阶导数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/图像二阶导数.png)  
### result
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/结果.png)  
### 距离函数
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/距离函数.png)  
### KNN
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/KNN.png)  
### kmeans_dis
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/kmeans_dis.png) 
### 质心
![GitHub set up](https://github.com/omega-Lee/Opencv-100-Questions/blob/master/images/质心.png) 
