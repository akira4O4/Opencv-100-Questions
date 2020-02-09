import numpy as np


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


def train_nn(nn, train_x, train_t, iteration_N=5000):
    for i in range(5000):
        nn.forward(train_x)
        # update parameters
        nn.train(train_x, train_t)
    return nn


# test
def test_nn(nn, test_x, test_t):
    for j in range(len(test_x)):
        x = train_x[j]
        t = train_t[j]
        print("in:", x, "pred:", nn.forward(x))


if __name__ == "__main__":
    # 训练数据
    train_x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]], dtype=np.float32)

    # 训练标签
    train_t = np.array([[0], [1], [1], [0]], dtype=np.float32)

    nn = NN()

    nn = train_nn(nn, train_x, train_t, iteration_N=5000)

    test_nn(nn, train_x, train_t)
