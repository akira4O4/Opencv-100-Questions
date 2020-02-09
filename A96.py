import numpy as np
import cv2


# HOG
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


def hog(img):
    gray = rbg2gray(img)

    gx, gy = get_gradXY(gray)

    magnitude, gradient = get_MagGrad(gx, gy)

    gradient_quantized = quantization(gradient)

    histogram = gradient_histogram(gradient_quantized, magnitude)

    histogram = normalization(histogram)

    return histogram


# 激活函数
def sigmoid(x):
    return 1. / (1. + np.exp(-x))


class NN:
    # 初始化
    # 高斯分布：均值：0，标准差：1 ->标准正态分布
    def __init__(self, ind=2, w=64, w2=64, outd=1, leaning_rate=0.1):
        # 权重1
        self.w1 = np.random.normal(0, 1, [ind, w])
        # 偏置1
        self.b1 = np.random.normal(0, 1, [w])
        # 权重2
        self.w2 = np.random.normal(0, 1, [w, w2])
        # 偏置2
        self.b2 = np.random.normal(0, 1, [w2])
        # 输出层权重
        self.wout = np.random.normal(0, 1, [w2, outd])
        # 输出层偏置
        self.bout = np.random.normal(0, 1, [outd])
        # 学习效率
        self.leaning_rate = leaning_rate

    def forward(self, x):
        self.z1 = x

        # np.dot：矩阵乘法
        self.z2 = sigmoid(np.dot(self.z1, self.w1) + self.b1)
        self.z3 = sigmoid(np.dot(self.z2, self.w2) + self.b2)
        self.out = sigmoid(np.dot(self.z3, self.wout) + self.bout)

        return self.out

    # 训练
    def train(self, x, t):
        # En = t * np.log(self.out) + (1-t) * np.log(1-self.out)
        En = (self.out - t) * self.out * (1 - self.out)

        # 计算梯度
        grad_wout = np.dot(self.z3.T, En)
        grad_bout = np.dot(np.ones([En.shape[0]]), En)
        # 更新参数
        self.wout -= self.leaning_rate * grad_wout
        self.bout -= self.leaning_rate * grad_bout

        grad_u2 = np.dot(En, self.wout.T) * self.z3 * (1 - self.z3)
        grad_w2 = np.dot(self.z2.T, grad_u2)
        grad_b2 = np.dot(np.ones([grad_u2.shape[0]]), grad_u2)

        self.w2 -= self.leaning_rate * grad_w2
        self.b2 -= self.leaning_rate * grad_b2

        grad_u1 = np.dot(grad_u2, self.w2.T) * self.z2 * (1 - self.z2)
        grad_w1 = np.dot(self.z1.T, grad_u1)
        grad_b1 = np.dot(np.ones([grad_u1.shape[0]]), grad_u1)

        self.w1 -= self.leaning_rate * grad_w1
        self.b1 -= self.leaning_rate * grad_b1


def train_nn(nn, train_x, train_t, iteration_N=10000):
    for i in range(iteration_N):
        nn.forward(train_x)

        nn.train(train_x, train_t)

    return nn


# test
def test_nn(nn, test_x, test_t, pred_th=0.5):
    accuracy_N = 0.

    for data, t in zip(test_x, test_t):

        prob = nn.forward(data)

        pred = 1 if prob >= pred_th else 0
        if t == pred:
            accuracy_N += 1

    accuracy = accuracy_N / len(db)

    print("准确率 ： {} ({} / {})".format(accuracy, accuracy_N, len(db)))


def make_dataset(img, gt, Crop_N=200, L=60, th=0.5, H_size=32):
    img = cv2.imread(img).astype(np.float32)
    H, W, _ = img.shape

    HOG_feature_N = ((H_size // 8) ** 2) * 9

    db = np.zeros([Crop_N, HOG_feature_N + 1])

    for i in range(Crop_N):

        x1 = np.random.randint(W - L)

        y1 = np.random.randint(H - L)

        x2 = x1 + L

        y2 = y1 + L

        crop = np.array((x1, y1, x2, y2))

        _iou = np.zeros((3,))
        _iou[0] = iou(gt, crop)

        if _iou.max() >= th:
            cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255), 1)
            label = 1
        else:
            cv2.rectangle(img, (x1, y1), (x2, y2), (255, 0, 0), 1)
            label = 0

        crop_area = img[y1:y2, x1:x2]

        crop_area = resize(crop_area, H_size, H_size)

        _hog = hog(crop_area)

        db[i, :HOG_feature_N] = _hog.ravel()
        db[i, -1] = label

    return db


if __name__ == "__main__":
    path = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    img = cv2.imread(path).astype(np.float32)
    histogram = hog(img)

    gt = np.array((47, 41, 129, 103), dtype=np.float32)

    db = make_dataset(path, gt)

    input_dim = db.shape[1] - 1

    train_x = db[:, :input_dim]

    train_t = db[:, -1][..., None]

    nn = NN(ind=input_dim, leaning_rate=0.01)

    nn = train_nn(nn, train_x, train_t, iteration_N=10000)

    test_nn(nn, train_x, train_t)
