dat <- as.matrix(read.table("../data/dat.txt"))

y <- dat[,1]
X <- dat[,-1]
k <- ncol(X)
colnames(X) <- paste0("b",0:9)
Xt <- t(X)
XXi <- solve(t(X)%*%X)
s <- 100
#pairs(dat)
#solve(t(X)%*%X,t(X)%*%y)
a <- 1
b <- 1
d <- a-1-1/b
B <- 1e3
s2 <- 10

det <- function(x,log=F) as.numeric(determinant(x,log=log))[1]
ll <- function(be,sig2) sum(dnorm(y,X%*%be,sqrt(sig2),log=T))
lpb <- function(be) -5*t(be)%*%XXi%*%be
lps <- function(sig2) d*sig2
mvrnorm <- function(M,S,n=nrow(S)) M + t(chol(S)) %*% rnorm(n)

csb <- diag(1,k)
css <- 3
acc.b <- 0
acc.s <- 0

b.hat <- matrix(0,B,k)
s2.hat <- rep(1,B)

for (i in 2:B) {
  b.hat[i,] <- b.hat[i-1,]
  s2.hat[i] <- s2.hat[i-1]

  # Update Beta
  cand <- mvrnorm(b.hat[i,],XXi*s2)
  q <- ll(cand,s2.hat[i])+lpb(cand)-ll(b.hat[i,],s2.hat[i])-lpb(b.hat[i,])
  if (q>log(runif(1))) {
    b.hat[i,] <- cand
    acc.b <- acc.b+1
  }

  cand <- rnorm(1,s2.hat[i],css)
  if (cand>0) {
    q <- ll(b.hat[i,],cand)-ll(b.hat[i,],s2.hat[i])+lps(cand)-lps(s2.hat[i])
    if (q>log(runif(1))) {
      s2.hat[i] <- cand
      acc.s <- acc.s+1
    }
  }

  cat(paste0("\r",round(100*i/B),"%"))
}
