import cv2
import numpy as np
import matplotlib.pyplot as plt
from glob import glob


def k_means(img, Class=5):
    img = cv2.imread(img).astype(np.float32)
    H, W, C = img.shape
    print("shape:", img.shape)
    np.random.seed(0)

    # 摊平
    img = np.reshape(img, (H * W, -1))
    print("shape:", img.shape)

    # 随机像素RGB
    i = np.random.choice(np.arange(H * W), Class, replace=False)
    random_rgb = img[i].copy()
    print("随机像素:", random_rgb)

    while True:
        class_label = np.zeros((H * W), dtype=int)
        for i in range(H * W):
            # 计算距离
            dis = np.sqrt(np.sum((random_rgb - img[i]) ** 2, axis=1))
            # 求分量中最小距离
            class_label[i] = np.argmin(dis)

        class_label_tmp = np.zeros((Class, 3))

        for i in range(Class):
            class_label_tmp[i] = np.mean(img[class_label == i], axis=0)

        if (random_rgb == class_label_tmp).all():
            break
        else:
            random_rgb = class_label_tmp.copy()

    out = np.zeros((H * W, 3), dtype=np.float32)

    # 分配像素
    for i in range(Class):
        out[class_label == i] = random_rgb[i]

    # 归一化到0-255
    out = np.clip(out, 0, 255)

    out = np.reshape(out, (H, W, 3))
    out = out.astype(np.uint8)

    cv2.imshow("out", out)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    path = "C:/Users/Administrator/Desktop/OpencvTestImg/imori.jpg"
    k_means(path)
