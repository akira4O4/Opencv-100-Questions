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


# 对进过sobel滤波的图像进行高斯滤波
def gausian(i, k_size, sigma):
    H, W = i.shape

    I_tmp = np.pad(i, (k_size // 2, k_size // 2), 'edge')

    # 滤波器
    k = np.zeros((k_size, k_size), dtype=np.float)

    for x in range(k_size):
        for y in range(k_size):
            _x = x - k_size // 2
            _y = y - k_size // 2
            # 二维高斯滤波器函数
            k[y, x] = np.exp(-(_x ** 2 + _y ** 2) / (2 * (sigma ** 2)))
    k /= (sigma * np.sqrt(2 * np.pi))
    k /= k.sum()

    for y in range(H):
        for x in range(W):
            i[y, x] = np.sum(I_tmp[y: y + k_size, x: x + k_size] * k)

    return i


# 角检测
def corner_detect(img, Ix2, Iy2, Ixy, k=0.04, th=0.1):
    out = np.array((img, img, img))
    out = np.transpose(out, (1, 2, 0))

    R = (Ix2 * Iy2 - Ixy ** 2) - k * ((Ix2 + Iy2) ** 2)

    out[R >= np.max(R) * th] = [0, 0, 255]

    out = out.astype(np.uint8)

    return out


def harris(img):
    img = cv2.imread(img).astype(np.float32)
    # 灰度化
    gray = rgb2gray(img)

    Ix2, Iy2, Ixy = sobel(gray)

    Ix2 = gausian(Ix2, 3, 3)
    Iy2 = gausian(Iy2, 3, 3)
    Ixy = gausian(Ixy, 3, 3)

    out = corner_detect(gray, Ix2, Iy2, Ixy)
    out = out.astype(np.uint8)

    # Ix2 = Ix2.astype(np.uint8)
    # Iy2 = Iy2.astype(np.uint8)
    # Ixy = Ixy.astype(np.uint8)

    cv2.imshow("Ix2", Ix2)
    cv2.imshow("Iy2", Iy2)
    cv2.imshow("Ixy", Ixy)
    cv2.imshow("out", out)

    cv2.waitKey(0)
    cv2.destroyAllWindows()


img = "C:/Users/Administrator/Desktop/OpencvTestImg/thorino.jpg"
if __name__ == "__main__":
    harris(img)
