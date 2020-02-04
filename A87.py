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

    path_db = []

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

        path_db.append(path)

    return db, path_db


def test_DB(db, pdb, N):
    test = glob("testset/test_*.png")
    test.sort()

    success_num = 0.
    accuracy_N = 0.
    # each image
    for path in test:

        img = dic_color(cv2.imread(path))

        hist = np.zeros(12, dtype=np.int32)
        for j in range(4):
            hist[j] = len(np.where(img[..., 0] == (64 * j + 32))[0])
            hist[j + 4] = len(np.where(img[..., 1] == (64 * j + 32))[0])
            hist[j + 8] = len(np.where(img[..., 2] == (64 * j + 32))[0])

        # 求差
        difs = np.abs(db[:, :12] - hist)
        difs = np.sum(difs, axis=1)

        pred_i = np.argsort(difs)[:N]
        pred = db[pred_i, -1]

        if len(pred[pred == 0]) > len(pred[pred == 1]):
            pl = "cat"
        else:
            pl = "dog"
        print(path, "像 : ", end='')
        for i in pred_i:
            print(pdb[i], end=', ')
        print("|猜测是 ：", pl)

        gt = "cat" if "cat" in path else "dog"
        if gt == pl:
            accuracy_N += 1.

    accuracy = accuracy_N / len(test)
    print("准确率 ：", accuracy, "({}/{})".format(int(accuracy_N), len(test)))


if __name__ == "__main__":
    db, pdb = get_db()
    test_DB(db, pdb, 3)
