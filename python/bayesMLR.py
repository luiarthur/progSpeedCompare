import numpy as np
dat = np.genfromtxt('../data/dat.txt',delimiter=' ')

y = dat[:,0]
X = dat[:,1:11]

k = X.shape[1]
n = y.shape[0]

Xt = X.transpose()
XXi = 
