import cv2
import numpy as np

img = "C:/Users/Administrator/Desktop/OpencvTestImg/words.png"


# 二值化
def binarization_0_1(img):
    img = cv2.imread(img).astype(np.uint8)
    H, W, C = img.shape
    b = img[:, :, 0].copy()
    g = img[:, :, 1].copy()
    r = img[:, :, 2].copy()

    out = 0.2126 * r + 0.7152 * g + 0.0722 * b

    th = 128
    out[out < th] = 0
    out[out >= th] = 1

    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return out


# 细化算法
# 从左上角开始进行光栅扫描；
# 如果x(x,y)=0(黑色)，不处理。
# 如果x(x,y)=1，满足下面三个条件时，令x=0：
# 4近邻像素的取值有一个以上为0；
# x的4连接数为1；
# x的8近邻中有三个以上取值为1。
# 重复光栅扫描，直到步骤2中像素值改变次数为0。

# 细化算法
def refine(img):
    img = cv2.imread(img).astype(np.float32)
    H, W, C = img.shape
    out = np.zeros((H, W), dtype=np.int)

    # 二值化(0-255)->(0-1)
    out[img[..., 0] > 0] = 1

    count = 1
    while count > 0:
        count = 0
        # 复制一份进行判断
        tmp = out.copy()
        for y in range(H):
            for x in range(W):

                # 如果是黑色则跳过
                if out[y, x] == 0:
                    continue

                # 判断条件
                condition = 0  # 只针对当前像素

                # 4近邻像素的取值有一个以上为0(2,3,4添加越界判断)：上下左右
                if tmp[max(y - 1, 0), x] + tmp[min(y + 1, H - 1), x] + tmp[y, max(x - 1, 0)] + tmp[
                    y, min(x + 1, W - 1)] < 4:
                    condition += 1

                c = 0
                c += (tmp[y, min(x + 1, W - 1)] - tmp[y, min(x + 1, W - 1)] * tmp[max(y - 1, 0), min(x + 1, W - 1)] *
                      tmp[
                          max(y - 1, 0), x])
                c += (tmp[max(y - 1, 0), x] - tmp[max(y - 1, 0), x] * tmp[max(y - 1, 0), max(x - 1, 0)] * tmp[
                    y, max(x - 1, 0)])
                c += (tmp[y, max(x - 1, 0)] - tmp[y, max(x - 1, 0)] * tmp[min(y + 1, H - 1), max(x - 1, 0)] * tmp[
                    min(y + 1, H - 1), x])
                c += (tmp[min(y + 1, H - 1), x] - tmp[min(y + 1, H - 1), x] * tmp[
                    min(y + 1, H - 1), min(x + 1, W - 1)] *
                      tmp[y, min(x + 1, W - 1)])
                # x的4连接数为1；
                if c == 1:
                    condition += 1

                # x的8近邻中有三个以上取值为1。
                if np.sum(tmp[max(y - 1, 0): min(y + 2, H), max(x - 1, 0): min(x + 2, W)]) >= 4:
                    condition += 1

                if condition == 3:
                    out[y, x] = 0
                    count += 1

    # 扩张像素
    out = out.astype(np.uint8) * 255

    cv2.imshow("src", img)
    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    # binarization_0_1(img)
    refine(img)
