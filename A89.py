import cv2
import numpy as np
import matplotlib.pyplot as plt
from glob import glob


# 减色处理
def dic_color(img):
    img //= 63
    img = img * 64 + 32
    return img


# 获取数据
def get_db():
    train = glob("dataset/t_*.png")
    train.sort()

    db = np.zeros((len(train), 13), dtype=np.int32)
    pdb = []

    for i, data in enumerate(train):
        img = dic_color(cv2.imread(data))
        for j in range(4):
            db[i, j] = len(np.where(img[..., 0] == (64 * j + 32))[0])
            db[i, j + 4] = len(np.where(img[..., 1] == (64 * j + 32))[0])
            db[i, j + 8] = len(np.where(img[..., 2] == (64 * j + 32))[0])
        if 'cat' in data:
            cls = 0
        elif 'dog' in data:
            cls = 1

        db[i, -1] = cls

        pdb.append(data)

    return db, pdb


# 这里需要大量的数据，数据越少，准确率越低
def k_means(db, pdb, Class=2):
    feats = db.copy()
    # 随机种子
    np.random.seed(1)

    # 随机分配类别
    for i in range(len(feats)):
        if np.random.random() < 0.5:
            feats[i, -1] = 0
        else:
            feats[i, -1] = 1

    # 循环迭代计算质心，直到质心变换量小于阈值
    while True:
        gs = np.zeros((Class, 12), dtype=np.float32)
        change_count = 0

        # 分别计算类别0和类别1的特征量的质心
        for i in range(Class):
            gs[i] = np.mean(feats[np.where(feats[..., -1] == i)[0], :12], axis=0)

        for i in range(len(feats)):
            # 计算样本到每个质心的距离
            dis = np.sqrt(np.sum(np.square(np.abs(gs - feats[i, :12])), axis=1))
            pred = np.argmin(dis, axis=0)

            if int(feats[i, -1]) != pred:
                change_count += 1
                feats[i, -1] = pred

        # 如果不再变化，则说明质心稳定，分类结束
        if change_count < 1:
            break

    for i in range(db.shape[0]):
        print(pdb[i], " Pred:", feats[i, -1])


if __name__ == "__main__":
    db, pdb = get_db()
    k_means(db, pdb)
