import cv2
import numpy as np


# rgb到hsv色域变换
def rgb_hsv(imgsrc):
    imgsrc = cv2.imread(imgsrc).astype(np.float32)
    img = imgsrc.copy() / 255

    hsv = np.zeros_like(img, dtype=np.float32)

    max_v = np.max(img, axis=2).copy()
    min_v = np.min(img, axis=2).copy()
    
    # numpy.argmin表示最小值在数组中所在的位置
    min_arg = np.argmin(img, axis=2)

    # 以下源自rgb->hsv转换公式

    # H
    hsv[..., 0][np.where(max_v == min_v)] = 0

    # if min == B
    ind = np.where(min_arg == 0)
    hsv[..., 0][ind] = 60 * (img[..., 1][ind] - img[..., 2][ind]) / (max_v[ind] - min_v[ind]) + 60
    # if min == G
    ind = np.where(min_arg == 1)
    hsv[..., 0][ind] = 60 * (img[..., 2][ind] - img[..., 0][ind]) / (max_v[ind] - min_v[ind]) + 300
    # if min == R
    ind = np.where(min_arg == 2)
    hsv[..., 0][ind] = 60 * (img[..., 0][ind] - img[..., 1][ind]) / (max_v[ind] - min_v[ind]) + 180

    # S
    hsv[..., 1] = max_v.copy() - min_v.copy()

    # V
    hsv[..., 2] = max_v.copy()

    mask = np.zeros_like(hsv[..., 0])
    # 确定颜色在色相（H）中取值，
    # np.logical_and/or/not (逻辑与/或/非)
    mask[np.logical_and((hsv[..., 0] > 180), (hsv[..., 0] < 260))] = 255

    imgsrc = imgsrc.astype(np.uint8)
    hsv = hsv.astype(np.uint8)
    mask = mask.astype(np.uint8)

    cv2.imshow("img", img)
    cv2.imshow("hsv", hsv)
    cv2.imshow("mask", mask)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    img = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    rgb_hsv(img)
