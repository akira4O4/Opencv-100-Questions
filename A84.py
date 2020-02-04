import cv2
import numpy as np
import matplotlib.pyplot as plt
from glob import glob


# 减色处理
def dic_color(img):
    img //= 63
    img = img * 64 + 32
    return img


def get_db():
    train = glob("dataset/t_*.png")
    # print(train)
    # 对文件进行排序
    train.sort()

    # 构建矩阵
    db = np.zeros((len(train), 13), dtype=np.int32)
    print(db.shape)
    # enumerate:返回数据下标和数据
    for i, path in enumerate(train):
        # print(i,path)
        img = dic_color(cv2.imread(path))
        for j in range(4):
            db[i, j] = len(np.where(img[..., 0] == (64 * j + 32))[0])
            db[i, j + 4] = len(np.where(img[..., 1] == (64 * j + 32))[0])
            db[i, j + 8] = len(np.where(img[..., 2] == (64 * j + 32))[0])

        # 分类标签
        if 'cat' in path:
            cls = 0
        elif 'dog' in path:
            cls = 1

        db[i, -1] = cls

        img_h = img.copy() // 64
        img_h[..., 1] += 4
        img_h[..., 2] += 8
        plt.subplot(2, 5, i + 1)
        plt.hist(img_h.ravel(), bins=12, rwidth=0.8)
        plt.title(path)

    print(db)
    plt.show()


if __name__ == "__main__":
    get_db()
