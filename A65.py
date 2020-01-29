import cv2
import numpy as np

img = "C:/Users/Administrator/Desktop/OpencvTestImg/words.png"


def zhangs_suen(img):
    img = cv2.imread(img).astype(np.float32)
    H, W, C = img.shape
    out = np.zeros((H, W), dtype=np.uint8)

    # 翻转像素0->1,1->0
    out[img[..., 0] > 0] = 1
    out = 1 - out

    find = True
    while find:
        find = False
        for y in range(1, H - 1):
            for x in range(1, W - 1):
                # 排除白色
                if out[y, x] == 1:
                    continue
                flag = 0
                if (out[y - 1, x + 1] - out[y - 1, x]) == 1:
                    flag += 1
                if (out[y, x + 1] - out[y - 1, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x + 1] - out[y, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x] - out[y + 1, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x - 1] - out[y + 1, x]) == 1:
                    flag += 1
                if (out[y, x - 1] - out[y + 1, x - 1]) == 1:
                    flag += 1
                if (out[y - 1, x - 1] - out[y, x - 1]) == 1:
                    flag += 1
                if (out[y - 1, x] - out[y - 1, x - 1]) == 1:
                    flag += 1
                if flag != 1:
                    continue

                sum = 0
                for _y in range(-1, 2):
                    for _x in range(-1, 2):
                        if _y == 0 and _x == 0:
                            continue
                        sum += out[y + _y, x + _x]
                if sum < 2 or sum > 6:
                    continue

                # 右半圈
                if out[y - 1, x] + out[y, x + 1] + out[y + 1, x] < 1:
                    continue
                # 左半圈
                if out[y, x + 1] + out[y + 1, x] + out[y, x - 1] < 1:
                    continue

                #
                out[y, x] = 1
                find = True
                # step1.append([y,x])
        for y in range(1, H - 1):
            for x in range(1, W - 1):
                # 排除白色
                if out[y, x] == 1:
                    continue
                flag = 0
                if (out[y - 1, x + 1] - out[y - 1, x]) == 1:
                    flag += 1
                if (out[y, x + 1] - out[y - 1, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x + 1] - out[y, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x] - out[y + 1, x + 1]) == 1:
                    flag += 1
                if (out[y + 1, x - 1] - out[y + 1, x]) == 1:
                    flag += 1
                if (out[y, x - 1] - out[y + 1, x - 1]) == 1:
                    flag += 1
                if (out[y - 1, x - 1] - out[y, x - 1]) == 1:
                    flag += 1
                if (out[y - 1, x] - out[y - 1, x - 1]) == 1:
                    flag += 1
                if flag != 1:
                    continue

                sum = 0
                for _y in range(-1, 2):
                    for _x in range(-1, 2):
                        if _y == 0 and _x == 0:
                            continue
                        sum += out[y + _y, x + _x]
                if sum < 2 or sum > 6:
                    continue
                # 上半圈
                if out[y - 1, x] + out[y, x + 1] + out[y, x - 1] < 1:
                    continue

                # 下半圈
                if out[y - 1, x] + out[y + 1, x] + out[y, x - 1] < 1:
                    continue
                out[y, x] = 1
                find = True

    # 翻转像素
    out = 1 - out
    # 扩张像素
    out = out * 255


if __name__ == "__main__":
    zhangs_suen(img)
