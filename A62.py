import cv2
import numpy as np
import matplotlib.pyplot as plt

img = "C:/Users/Administrator/Desktop/OpencvTestImg/img128.png"


# connect 8
def connect_8(img):
    img = cv2.imread(img).astype(np.uint8)
    H, W, C = img.shape

    bin = np.zeros((H, W), dtype=np.uint8)

    bin[img[..., 0] > 0] = 1

    img8 = 1 - bin

    out = np.zeros((H, W, 3), dtype=np.uint8)

    # each pixel
    for y in range(H):
        for x in range(W):
            if bin[y, x] < 1:
                continue

            S = 0
            S += (img8[y, min(x + 1, W - 1)] - img8[y, min(x + 1, W - 1)] * img8[max(y - 1, 0), min(x + 1, W - 1)] * img8[
                max(y - 1, 0), x])
            S += (img8[max(y - 1, 0), x] - img8[max(y - 1, 0), x] * img8[max(y - 1, 0), max(x - 1, 0)] * img8[
                y, max(x - 1, 0)])
            S += (img8[y, max(x - 1, 0)] - img8[y, max(x - 1, 0)] * img8[min(y + 1, H - 1), max(x - 1, 0)] * img8[
                min(y + 1, H - 1), x])
            S += (img8[min(y + 1, H - 1), x] - img8[min(y + 1, H - 1), x] * img8[min(y + 1, H - 1), min(x + 1, W - 1)] *
                  img8[y, min(x + 1, W - 1)])

            if S == 0:
                out[y, x] = [0, 0, 255]#b
            elif S == 1:
                out[y, x] = [0, 255, 0]#g
            elif S == 2:
                out[y, x] = [255, 0, 0]#r
            elif S == 3:
                out[y, x] = [255, 255, 0]
            elif S == 4:
                out[y, x] = [255, 0, 255]

    cv2.imshow("result", out)
    cv2.imshow("src", img)
    cv2.imshow("img8", img8)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    connect_8(img)
