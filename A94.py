import numpy as np
import cv2


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


def cut_bbox(img, gt, num=200, size=60, th=0.5):
    img = cv2.imread(img).astype(np.float32)
    _img = img.copy()
    H, W, C = img.shape

    # 真实区域
    cv2.rectangle(img, (gt[0], gt[1]), (gt[2], gt[3]), (0, 255, 0), 1)
    cv2.rectangle(_img, (gt[0], gt[1]), (gt[2], gt[3]), (0, 255, 0), 1)

    # 裁剪图片
    # 从图像中随机切出200个60*60的矩形。
    for i in range(num):
        # random.randint(a, b)：a <= n <= b。
        x1 = np.random.randint(W - size)
        y1 = np.random.randint(H - size)
        x2 = x1 + size
        y2 = y1 + size

        box = np.array((x1, y1, x2, y2))

        _iou = iou(gt, box)

        if _iou >= th:
            cv2.rectangle(_img, (x1, y1), (x2, y2), (0, 0, 255), 1)
            label = 1
        else:
            cv2.rectangle(_img, (x1, y1), (x2, y2), (255, 0, 0), 1)
            label = 0

    img = img.astype(np.uint8)
    _img = _img.astype(np.uint8)

    cv2.imshow("dt", img)
    cv2.imshow("iou", _img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    path = "C:/Users/Administrator/Desktop/OpencvTestImg/imori_1.jpg"
    gt = np.array((47, 41, 129, 103), dtype=np.float32)
    cut_bbox(path, gt)
