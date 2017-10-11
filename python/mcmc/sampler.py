#from numba import jit
import numpy as np
import mcmc

#@jit
def sampler(y, X, cs_sig2, CS_beta, init, B, burn, printEvery, a=2, b=1, s2=100):
    n = len(y)

    def lps(log_sig2):
        return mcmc.lpLogIG(log_sig2, a, b)

    def lpb(beta):
        return -np.dot(beta.T, np.dot(XXi, beta)) / (s2 * 2)

    def ll(curr):
        beta = curr['beta']
        sig2 = curr['sig2']
        err = y - np.dot(X, beta)
        return np.dot(err.T, err) / -(2 * sig2) - n / 2 * np.log(sig2)

    def update(curr):
        newState = curr

        def ll_b(beta):
            state = newState
            state['beta'] = beta
            return ll(state)
        newBeta = mcmc.metropolis_MV(newState['beta'], ll_b, lpb, CS_beta)
        newState['beta'] = newBeta

        def ll_ls(log_sig2):
            state = newState
            state['sig2'] = np.exp(log_sig2)
            return ll(state)
        newSig2 = np.exp(mcmc.metropolis(np.log(newState['sig2']), ll_ls, lps, cs_sig2))
        newState['sig2'] = newSig2

        return newState
    
    return mcmc.gibbs(init, update, B, burn, printEvery)


### MAIN ###
dat = np.genfromtxt('../../data/dat.txt', delimiter=' ')
y = dat[:, 0]
X = dat[:, 1:11]
XXi = np.linalg.inv(np.dot(X.T,X))
K = X.shape[1]

CS = np.eye(K)
K = X.shape[1]
init = {'beta':np.zeros(K), 'sig2':1}

out = sampler(y, X, 1, CS, init, B=100000, burn=0, printEvery=1000, a=2, b=1)

post_beta = np.array([o['beta'] for o in out])
post_sig2 = np.array([o['sig2'] for o in out])

post_beta.mean(0)
post_sig2.mean()
