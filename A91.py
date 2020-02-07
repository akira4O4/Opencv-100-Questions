import cv2
import numpy as np
import matplotlib.pyplot as plt
from glob import glob


# 从图像中随机选取K个RGB分量（这我们称作类别）。
# 将图像中的像素分别分到颜色距离最短的那个类别的索引中去，色彩距离按照下面的方法计算：
#  dis=sqrt{(R-R')^2+(G-G')^2+(B-B')^2}


def k_means(img, Class=5):
    img = cv2.imread(img).astype(np.float32)
    print(img.shape)
    H, W, C = img.shape

    # 随机种子
    np.random.seed(0)

    img = np.reshape(img, (H * W, -1))
    print(img.shape)

    # #numpy.random.choice(a, size=None, replace=True, p=None)
    # #从a(只要是ndarray都可以，但必须是一维的)中随机抽取数字，并组成指定大小(size)的数组
    # #replace:True表示可以取相同数字，False表示不可以取相同数字
    # #数组p：与数组a相对应，表示取数组a中每个元素的概率，默认为选取每个元素的概率相同。

    i = np.random.choice(np.arange(H * W), Class, replace=False)
    print(i)
    Cs = img[i].copy()
    print(Cs)

    clss = np.zeros((H * W), dtype=int)

    for i in range(H * W):
        # 计算距离
        dis = np.sqrt(np.sum((Cs - img[i]) ** 2, axis=1))
        # 求最小的距离
        clss[i] = np.argmin(dis)

    out = np.reshape(clss, (H, W)) * 50
    out = out.astype(np.uint8)

    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return out


if __name__ == "__main__":
    path = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    k_means(path)
