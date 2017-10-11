# mcmc.py
import numpy as np

def logit(p):
    return np.log(p / (1.0 - p))

def invlogit(x):
    return 1.0 / (1.0 + np.exp(-x))

def logDensityLogXTwoParam(lf):
    return lambda logx, a, b: lf(np.exp(logx), a, b) + logx

def lpIG(x, a, b):
    return -(a+1) * np.log(x) - b / x

lpLogIG = logDensityLogXTwoParam(lpIG)

def gibbs(init, update, B, burn, printEvery):
    out = [init] * B

    for i in range(B + burn):
        if i <= burn:
            out[0] = update(out[0])
        else:
            out[i-burn] = update(out[i-burn-1])

        if printEvery > 0 and (i+1) % printEvery == 0:
            print "Progress: ", i+1, "/", B + burn

    return out

def metropolis(curr, ll, lp, cs):
    cand = np.random.randn() * cs + curr
    u = np.random.rand()

    if ll(cand) + lp(cand) - ll(curr) - lp(curr) > np.log(u):
        new_state = cand
    else:
        new_state = curr
        
    return new_state

def metropolis_MV(curr, ll, lp, CS):
    cand = np.random.multivariate_normal(curr, CS)
    u = np.random.rand()

    if ll(cand) + lp(cand) - ll(curr) - lp(curr) > np.log(u):
        new_state = cand
    else:
        new_state = curr
        
    return new_state

def metLogit(curr, ll, lp, cs):
    def lp_logit(logit_p):
        p = invlogit(logit_p)
        logJ = -logit_p + 2.0*log(1-p)
        return lp(p) + logJ
  
    def ll_logit(logit_p):
        return ll(invlogit(logit_p))

    return invlogit(metropolis(logit(curr), ll_logit, lp_logit, cs))


