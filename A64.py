import cv2
import numpy as np

img = "C:/Users/Administrator/Desktop/OpencvTestImg/words.png"


# 从左上角开始进行光栅扫描；
# x_0(x,y)=0的话、不进行处理。x_0(x,y)=1的话，下面五个条件都满足的时候令x_0=-1：
# 当前像素的4-近邻中有一个以上0；
# x_0的8-连接数为1；
# x_1至x_8的绝对值之和大于2；
# 8-近邻像素的取值有一个以上为1；
# 对所有x_n(n in [1,8])以下任一项成立：
# x_n不是-1；
# 当x_n为0时，x_0的8连接数为1。
# 将每个像素的-1更改为0；
# 重复进行光栅扫描，直到某一次光栅扫描中步骤3的变化数变为0。

def hilditch(img):
    img = cv2.imread(img).astype(np.float32)
    H, W, C = img.shape
    out = np.zeros((H, W), dtype=np.int)

    # 二值化(0-255)->(0-1)
    out[img[..., 0] > 0] = 1

    tmp1 = out.copy()
    _tmp1 = 1 - tmp1

    count = 1

    while count > 0:
        count = 0
        tmp1 = out.copy()
        tmp2 = out.copy()
        _tmp1 = 1 - tmp1
        _tmp2 = 1 - tmp2
        for y in range(H):
            for x in range(W):
                if out[y, x] == 0:
                    continue

                condition = 0
                # 当前像素的4-近邻中有一个以上0；
                if (tmp1[y, min(x + 1, W - 1)] * tmp1[max(y - 1, 0), x] * tmp1[y, max(x - 1, 0)] * tmp1[
                    min(y + 1, H - 1), x]) == 0:
                    condition += 1

                # x_0的8-连接数为1；
                c = 0
                c += (_tmp1[y, min(x + 1, W - 1)] - _tmp1[y, min(x + 1, W - 1)] * _tmp1[
                    max(y - 1, 0), min(x + 1, W - 1)] *
                      _tmp1[max(y - 1, 0), x])
                c += (_tmp1[max(y - 1, 0), x] - _tmp1[max(y - 1, 0), x] * _tmp1[max(y - 1, 0), max(x - 1, 0)] * _tmp1[
                    y, max(x - 1, 0)])
                c += (_tmp1[y, max(x - 1, 0)] - _tmp1[y, max(x - 1, 0)] * _tmp1[min(y + 1, H - 1), max(x - 1, 0)] *
                      _tmp1[
                          min(y + 1, H - 1), x])
                c += (_tmp1[min(y + 1, H - 1), x] - _tmp1[min(y + 1, H - 1), x] * _tmp1[
                    min(y + 1, H - 1), min(x + 1, W - 1)] * _tmp1[y, min(x + 1, W - 1)])
                if c == 1:
                    condition += 1

                # x_1至x_8的绝对值之和大于2；
                sum = 0
                for _y in range(-1, 2):
                    for _x in range(-1, 2):
                        sum += tmp1[y + _y, x + _x]
                if sum > 2:
                    condition += 1

                # 8-近邻像素的取值有一个以上为1；
                sum = 0
                for _y in range(-1, 2):
                    for _x in range(-1, 2):
                        if _y == 0 and _x == 0:
                            continue
                        sum += tmp1[y + _y, x + _x]
                if sum > 1:
                    condition += 1

                _tmp2 = 1 - out

                c = 0
                c += (_tmp2[y, min(x + 1, W - 1)] - _tmp2[y, min(x + 1, W - 1)] * _tmp2[
                    max(y - 1, 0), min(x + 1, W - 1)] * _tmp2[max(y - 1, 0), x])
                c += (_tmp2[max(y - 1, 0), x] - _tmp2[max(y - 1, 0), x] * (1 - tmp1[max(y - 1, 0), max(x - 1, 0)]) *
                      _tmp2[y, max(x - 1, 0)])
                c += (_tmp2[y, max(x - 1, 0)] - _tmp2[y, max(x - 1, 0)] * _tmp2[min(y + 1, H - 1), max(x - 1, 0)] *
                      _tmp2[min(y + 1, H - 1), x])
                c += (_tmp2[min(y + 1, H - 1), x] - _tmp2[min(y + 1, H - 1), x] * _tmp2[
                    min(y + 1, H - 1), min(x + 1, W - 1)] * _tmp2[y, min(x + 1, W - 1)])
                if c == 1 or (out[max(y - 1, 0), max(x - 1, 0)] != tmp1[max(y - 1, 0), max(x - 1, 0)]):
                    condition += 1

                c = 0
                c += (_tmp2[y, min(x + 1, W - 1)] - _tmp2[y, min(x + 1, W - 1)] * _tmp2[
                    max(y - 1, 0), min(x + 1, W - 1)] * (1 - tmp1[max(y - 1, 0), x]))
                c += ((1 - tmp1[max(y - 1, 0), x]) - (1 - tmp1[max(y - 1, 0), x]) * _tmp2[max(y - 1, 0), max(x - 1, 0)] *
                      _tmp2[y, max(x - 1, 0)])
                c += (_tmp2[y, max(x - 1, 0)] - _tmp2[y, max(x - 1, 0)] * _tmp2[min(y + 1, H - 1), max(x - 1, 0)] *
                      _tmp2[min(y + 1, H - 1), x])
                c += (_tmp2[min(y + 1, H - 1), x] - _tmp2[min(y + 1, H - 1), x] * _tmp2[
                    min(y + 1, H - 1), min(x + 1, W - 1)] * _tmp2[y, min(x + 1, W - 1)])
                if c == 1 or (out[max(y - 1, 0), x] != tmp1[max(y - 1, 0), x]):
                    condition += 1

                c = 0
                c += (_tmp2[y, min(x + 1, W - 1)] - _tmp2[y, min(x + 1, W - 1)] * (
                            1 - tmp1[max(y - 1, 0), min(x + 1, W - 1)]) * _tmp2[max(y - 1, 0), x])
                c += (_tmp2[max(y - 1, 0), x] - _tmp2[max(y - 1, 0), x] * _tmp2[max(y - 1, 0), max(x - 1, 0)] * _tmp2[
                    y, max(x - 1, 0)])
                c += (_tmp2[y, max(x - 1, 0)] - _tmp2[y, max(x - 1, 0)] * _tmp2[min(y + 1, H - 1), max(x - 1, 0)] *
                      _tmp2[min(y + 1, H - 1), x])
                c += (_tmp2[min(y + 1, H - 1), x] - _tmp2[min(y + 1, H - 1), x] * _tmp2[
                    min(y + 1, H - 1), min(x + 1, W - 1)] * _tmp2[y, min(x + 1, W - 1)])
                if c == 1 or (out[max(y - 1, 0), min(x + 1, W - 1)] != tmp1[max(y - 1, 0), min(x + 1, W - 1)]):
                    condition += 1

                c = 0
                c += (_tmp2[y, min(x + 1, W - 1)] - _tmp2[y, min(x + 1, W - 1)] * _tmp2[
                    max(y - 1, 0), min(x + 1, W - 1)] * _tmp2[max(y - 1, 0), x])
                c += (_tmp2[max(y - 1, 0), x] - _tmp2[max(y - 1, 0), x] * _tmp2[max(y - 1, 0), max(x - 1, 0)] * (
                            1 - tmp1[y, max(x - 1, 0)]))
                c += ((1 - tmp1[y, max(x - 1, 0)]) - (1 - tmp1[y, max(x - 1, 0)]) * _tmp2[
                    min(y + 1, H - 1), max(x - 1, 0)] * _tmp2[min(y + 1, H - 1), x])
                c += (_tmp2[min(y + 1, H - 1), x] - _tmp2[min(y + 1, H - 1), x] * _tmp2[
                    min(y + 1, H - 1), min(x + 1, W - 1)] * _tmp2[y, min(x + 1, W - 1)])
                if c == 1 or (out[y, max(x - 1, 0)] != tmp1[y, max(x - 1, 0)]):
                    condition += 1

                if condition >= 8:
                    out[y, x] = 0
                    count += 1

    # 扩张像素
    out = out.astype(np.uint8) * 255
    cv2.imshow("src", img)
    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    hilditch(img)
