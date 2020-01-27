import cv2
import numpy as np
import matplotlib.pyplot as plt

img = "C:/Users/Administrator/Desktop/OpencvTestImg/img10.png"


def connect_4(img):
    img = cv2.imread(img).astype(np.float32)
    H, W, C = img.shape
    tmp = np.zeros((H, W), dtype=np.int)
    img_out = np.zeros((H, W, 3), dtype=np.uint8)

    # 二值化
    tmp[img[..., 0] > 0] = 1

    for y in range(H):
        for x in range(W):
            if tmp[y, x] < 1:
                continue
            S = 0
            S += (tmp[y, min(x + 1, W - 1)] - tmp[y, min(x + 1, W - 1)] * tmp[max(y - 1, 0), min(x + 1, W - 1)] * tmp[
                max(y - 1, 0), x])

            S += (tmp[max(y - 1, 0), x] - tmp[max(y - 1, 0), x] * tmp[max(y - 1, 0), max(x - 1, 0)] * tmp[
                y, max(x - 1, 0)])

            S += (tmp[y, max(x - 1, 0)] - tmp[y, max(x - 1, 0)] * tmp[min(y + 1, H - 1), max(x - 1, 0)] * tmp[
                min(y + 1, H - 1), x])

            S += (tmp[min(y + 1, H - 1), x] - tmp[min(y + 1, H - 1), x] * tmp[min(y + 1, H - 1), min(x + 1, W - 1)] *
                  tmp[y, min(x + 1, W - 1)])

            if S == 0:
                img_out[y, x] = [0, 0, 255]
            elif S == 1:
                img_out[y, x] = [0, 255, 0]
            elif S == 2:
                img_out[y, x] = [255, 0, 0]
            elif S == 3:
                img_out[y, x] = [255, 255, 0]
            elif S == 4:
                img_out[y, x] = [255, 0, 255]

    img_out = img_out.astype(np.uint8)
    img = img.astype(np.uint8)

    cv2.imshow("src", img)
    cv2.imshow("tmp", tmp)
    cv2.imshow("img_out", img_out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    connect_4(img)
