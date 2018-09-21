from sklearn.datasets.samples_generator import make_blobs
from sklearn.datasets import make_circles
from sklearn.datasets import make_gaussian_quantiles
import numpy as np
import random, math

import matplotlib.pyplot as plt

X, y = make_blobs(n_samples=1000000, n_features=5, centers=10, cluster_std=0.4, random_state=0)

with open("large.dat", "w") as f:
# with open("dataset.dat", "w") as f:

    for x in X:
        for dim in x:
            f.writelines(str(dim) + " ")
        f.writelines("\n")
    f.close()

plt.figure(figsize=(7, 7))
plt.scatter(X[:,0], X[:,1],0.2)
# plt.plot(X)
plt.show()
