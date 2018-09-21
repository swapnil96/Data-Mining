from sklearn.datasets.samples_generator import make_blobs
from sklearn.datasets import make_circles
from sklearn.datasets import make_gaussian_quantiles
import numpy as np
import random, math

import matplotlib.pyplot as plt

# X, y = make_blobs(n_samples=150000, n_features=5, centers=10, cluster_std=0.4, random_state=0)
X = np.ones(shape=(500, 2))
idx = 0
while (idx < 100):
    # radius of the circle
    circle_r = 5
    # center of the circle (x, y)
    circle_x = 10
    circle_y = 10

    # random angle
    alpha = 2 * math.pi * random.random()
    # random radius
    r = circle_r * math.sqrt(random.random())
    # calculating coordinates
    x = r * math.cos(alpha) + circle_x
    y = r * math.sin(alpha) + circle_y

    # print("Random point", (x, y))
    X[idx] = [x,y]
    idx += 1

while (idx < 500):
    # radius of the circle
    circle_r = .7
    # center of the circle (x, y)
    circle_x = 10
    circle_y = 10

    # random angle
    alpha = 2 * math.pi * random.random()
    # random radius
    r = circle_r * math.sqrt(random.random())
    # calculating coordinates
    x = r * math.cos(alpha) + circle_x
    y = r * math.sin(alpha) + circle_y

    # print("Random point", (x, y))
    X[idx] = [x, y]
    idx += 1


# X1, y1 = make_blobs(n_samples=40000, n_features=2, centers=1, cluster_std=0.01, center_box=(2, 3), random_state=0)

# X2, y2 = make_blobs(n_samples=5000, n_features=2, centers=1, cluster_std=0.1, center_box=(3, 4), random_state=0)

X2, y2 = make_circles(n_samples=95000, factor=0.6)
X2 = X2*5

# print (X1.shape, X2.shape)
# X = np.vstack((X, X2))
# X = X2
# print(X.shape)

# with open("temp.dat", "w") as f:
with open("dataset.dat", "w") as f:

    for x in X:
        for dim in x:
            f.writelines(str(dim) + " ")
        f.writelines("\n")
    f.close()

plt.figure(figsize=(7, 7))
plt.scatter(X[:,0], X[:,1],0.2)
# plt.plot(X)
plt.show()
