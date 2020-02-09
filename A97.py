import cv2
import numpy as np


def hog(img):
    gray = rgb2gray(img)

    gx, gy = get_gradXY(gray)

    magnitude, gradient = get_MagGrad(gx, gy)

    gradient_quantized = quantization(gradient)

    histogram = gradient_histogram(gradient_quantized, magnitude)

    histogram = normalization(histogram)

    return histogram


def rbg2gray(img):
    # img = cv2.imread(img).astype(np.float32)
    gray = 0.2126 * img[..., 2] + 0.7152 * img[..., 1] + 0.0722 * img[..., 0]
    return gray


def get_gradXY(gray):
    H, W = gray.shape

    # 填充边框
    gray = np.pad(gray, (1, 1), 'edge')

    gx = gray[1:H + 1, 2:] - gray[1:H + 1, :W]
    gy = gray[2:, 1:W + 1] - gray[:H, 1:W + 1]

    # 防止计算错误
    gx[gx == 0] = 1e-6

    return gx, gy


def get_MagGrad(gx, gy):
    magnitude = np.sqrt(gx ** 2 + gy ** 2)
    gradient = np.arctan(gy / gx)

    gradient[gradient < 0] = np.pi / 2 + gradient[gradient < 0] + np.pi / 2

    return magnitude, gradient


# 数据量化
def quantization(gradient):
    gradient_quantized = np.zeros_like(gradient, dtype=np.int)

    d = np.pi / 9

    for i in range(9):
        gradient_quantized[np.where((gradient >= d * i) & (gradient <= d * (i + 1)))] = i

    return gradient_quantized


def gradient_histogram(gradient_quantized, magnitude, N=8):
    H, W = magnitude.shape

    cell_N_H = H // N
    cell_N_W = W // N
    histogram = np.zeros((cell_N_H, cell_N_W, 9), dtype=np.float32)

    for y in range(cell_N_H):
        for x in range(cell_N_W):
            for j in range(N):
                for i in range(N):
                    histogram[y, x, gradient_quantized[y * 4 + j, x * 4 + i]] += magnitude[y * 4 + j, x * 4 + i]

    return histogram


def normalization(histogram, C=3, epsilon=1):
    cell_N_H, cell_N_W, _ = histogram.shape
    for y in range(cell_N_H):
        for x in range(cell_N_W):
            histogram[y, x] /= np.sqrt(np.sum(histogram[max(y - 1, 0): min(y + 2, cell_N_H),
                                              max(x - 1, 0): min(x + 2, cell_N_W)] ** 2) + epsilon)

    return histogram


def iou(a, b):
    # a = np.array((50, 50, 150, 150), dtype=np.float32)
    # b = np.array((60, 60, 170, 160), dtype=np.float32)
    print(a)
    print(b)

    # 面积
    area_a = (a[2] - a[0]) * (a[3] - a[1])
    area_b = (b[2] - b[0]) * (b[3] - b[1])
    print("a的面积", area_a, 'b的面积：', area_b)

    # 左上角，左下角，右上角，右下角
    x1 = np.maximum(a[0], b[0])
    y1 = np.maximum(a[1], b[1])
    x2 = np.minimum(a[2], b[2])
    y2 = np.minimum(a[3], b[3])

    width = x2 - x1
    height = y2 - y1
    print("width", width)
    print("height", height)

    # 检测结果：DetectionResult
    # 基本事实：Ground Truth
    dr = width * height
    gt = area_a + area_b - dr
    iou = dr / gt

    print("dr", dr)
    print("gt", gt)
    print("iou", iou)
    return iou


def resize(img, h, w):
    _h, _w, _c = img.shape

    ah = 1. * h / _h
    aw = 1. * w / _w

    y = np.arange(h).repeat(w).reshape(w, -1)
    x = np.tile(np.arange(w), (h, 1))

    y = (y / ah)
    x = (x / aw)

    ix = np.floor(x).astype(np.int32)
    iy = np.floor(y).astype(np.int32)

    ix = np.minimum(ix, _w - 2)
    iy = np.minimum(iy, _h - 2)

    dx = x - ix
    dy = y - iy

    dx = np.tile(dx, [_c, 1, 1]).transpose(1, 2, 0)
    dy = np.tile(dy, [_c, 1, 1]).transpose(1, 2, 0)

    out = (1 - dx) * (1 - dy) * img[iy, ix] + dx * (1 - dy) * img[iy, ix + 1] + (1 - dx) * dy * img[
        iy + 1, ix] + dx * dy * img[iy + 1, ix + 1]
    out[out > 255] = 255

    return out


# 滑动窗口

def sliding_window(img, H_size=32):
    H, W, _ = img.shape

    recs = np.array(((42, 42), (56, 56), (70, 70)), dtype=np.float32)

    for y in range(0, H, 4):
        for x in range(0, W, 4):
            for rec in recs:
                dh = int(rec[0] // 2)
                dw = int(rec[1] // 2)

                x1 = max(x - dw, 0)
                x2 = min(x + dw, W)
                y1 = max(y - dh, 0)
                y2 = min(y + dh, H)

                region = img[max(y - dh, 0): min(y + dh, H), max(x - dw, 0): min(x + dw, W)]

                region = resize(region, H_size, H_size)

                region_hog = hog(region).ravel()


if __name__ == "__main__":
    path = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    img = cv2.imread(path).astype(np.float32)
    sliding_window(img)
