import cv2
import numpy as np


# 灰度化
def rgb2gray(img):
    gray = 0.2126 * img[..., 2] + 0.7152 * img[..., 1] + 0.0722 * img[..., 0]
    gray = gray.astype(np.uint8)
    return gray


# sobel滤波
def sobel(img):
    H, W = img.shape
    sobel_x = np.array(((1, 0, -1),
                        (2, 0, -2),
                        (1, 0, -1)), dtype=np.float32)

    sobel_y = np.array(((1, 2, 1),
                        (0, 0, 0),
                        (-1, -2, -1)), dtype=np.float32)
    # 添加边缘
    tmp = np.pad(img, (1, 1), 'edge')
    Ix = np.zeros_like(img, dtype=np.float32)
    Iy = np.zeros_like(img, dtype=np.float32)

    for y in range(H):
        for x in range(W):
            Ix[y, x] = np.mean(tmp[y:y + 3, x:x + 3] * sobel_x)
            Iy[y, x] = np.mean(tmp[y:y + 3, x:x + 3] * sobel_y)

    Ix2 = Ix ** 2
    Iy2 = Iy ** 2
    Ixy = Ix * Iy
    return Ix2, Iy2, Ixy


# 角检测
def corner_detect(img, Ix2, Iy2, Ixy):
    H, W = img.shape
    out = np.array((img, img, img))
    # x,y,z=0,1,2
    # transpose:调换维度
    out = np.transpose(out, (1, 2, 0))

    hes = np.zeros((H, W))
    for y in range(H):
        for x in range(W):
            hes[y, x] = Ix2[y, x] * Iy2[y, x] * Ixy[y, x] ** 2

    for y in range(H):
        for x in range(W):
            # 在y,x8邻域内为最大值并且大于max(det(H))*0.1$的点。
            if hes[y, x] == np.max(hes[max(y - 1, 0): min(y + 2, H), max(x - 1, 0): min(x + 2, W)]) and hes[
                y, x] > np.max(hes) * 0.1:
                out[y, x] = [0, 0, 255]#着色
    return out


def hessian(img):
    img = cv2.imread(img).astype(np.float32)
    # 灰度化
    gray = rgb2gray(img)

    Ix2, Iy2, Ixy = sobel(gray)

    out = corner_detect(gray, Ix2, Iy2, Ixy)

    out = out.astype(np.uint8)
    # sobel检测

    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


img = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
if __name__ == "__main__":
    hessian(img)
