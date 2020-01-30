import cv2
import numpy as np


# BGR -> HSV
def BGR2HSV(imgsrc):
    img = cv2.imread(imgsrc).astype(np.float32)
    img = img.copy() / 255.

    hsv = np.zeros_like(img, dtype=np.float32)

    # get max and min
    max_v = np.max(img, axis=2).copy()
    min_v = np.min(img, axis=2).copy()
    min_arg = np.argmin(img, axis=2)

    # H
    hsv[..., 0][np.where(max_v == min_v)] = 0
    ## if min == B
    ind = np.where(min_arg == 0)
    hsv[..., 0][ind] = 60 * (img[..., 1][ind] - img[..., 2][ind]) / (max_v[ind] - min_v[ind]) + 60
    ## if min == R
    ind = np.where(min_arg == 2)
    hsv[..., 0][ind] = 60 * (img[..., 0][ind] - img[..., 1][ind]) / (max_v[ind] - min_v[ind]) + 180
    ## if min == G
    ind = np.where(min_arg == 1)
    hsv[..., 0][ind] = 60 * (img[..., 2][ind] - img[..., 0][ind]) / (max_v[ind] - min_v[ind]) + 300

    # S
    hsv[..., 1] = max_v.copy() - min_v.copy()

    # V
    hsv[..., 2] = max_v.copy()

    mask = np.zeros_like(hsv[..., 0])
    # 蓝色范围180-260
    mask[np.logical_and((hsv[..., 0] > 180), (hsv[..., 0] < 260))] = 255

    out = mask.astype(np.uint8)
    img = img.astype(np.uint8)

    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    img = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    BGR2HSV(img)
