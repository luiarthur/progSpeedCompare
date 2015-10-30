import numpy as np
from numpy.linalg import *

dat = np.genfromtxt('../data/dat.txt',delimiter=' ')

y = dat[:,0]
X = dat[:,1:11]
k = X.shape[1]
n = y.shape[0]
Xt = X.transpose()
XXi = inv(np.dot(Xt,X))
b_mle = np.dot( np.dot(XXi, Xt), y )

a = 1
b = 1
B = 1e5
s2 = 10

def ll(be, sig2):
    y_min_Xb = y - np.dot(X, be)
    return np.dot( y_min_Xb.transpose(), y_min_Xb) / (-2*sig2) - n/2 * np.log(sig2)

def lpb(be):
    return -np.dot( be.transpose(), np.dot(XXi, be) ) / (s2*2)

def lps(sig2):
    return (a-1) * np.log(sig2) - sig2 / b

def mvrnorm(M,S,n=S.shape): # STOPPED HERE
    return 0

#ll(b_mle, s2) # test
#lpb(b_mle) # test
# lps(s2) # test
