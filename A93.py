import numpy as np


def iou():
    a = np.array((50, 50, 150, 150), dtype=np.float32)
    b = np.array((60, 60, 170, 160), dtype=np.float32)
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


if __name__ == "__main__":
    iou()
