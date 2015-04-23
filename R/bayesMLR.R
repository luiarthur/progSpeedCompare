dat <- as.matrix(read.table("../data/dat.txt"))

y <- dat[,1]
X <- dat[,-1]
k <- ncol(X)
n <- length(y)
colnames(X) <- paste0("b",0:9)
Xt <- t(X)
XXi <- solve(Xt%*%X)
s <- 100
#pairs(dat)
XXi%*%Xt%*%y
a <- 1
b <- 1
B <- 1e5
s2 <- 10

det <- function(x,log=F) as.numeric(determinant(x,log=log))[1]
#ll <- function(be,sig2) sum(dnorm(y,X%*%be,sqrt(sig2),log=T))
ll <- function(be,sig2) t(y-X%*%be)%*%(y-X%*%be)/(-2*sig2) - n/2*log(sig2)
lpb <- function(be) -t(be)%*%XXi%*%be/(s2*2)
lps <- function(sig2) (a-1)*log(sig2)-sig2/b
mvrnorm <- function(M,S,n=nrow(S)) M + t(chol(S)) %*% rnorm(n)

csb <- 4*XXi
css <- 1
acc.b <- 0
acc.s <- 0

b.hat <- matrix(0,B,k)
s2.hat <- rep(1,B)

r.time <- system.time(
for (i in 2:B) {
  b.hat[i,] <- b.hat[i-1,]
  s2.hat[i] <- s2.hat[i-1]

  # Update Beta
  cand <- mvrnorm(b.hat[i,],csb)
  q <- ll(cand,s2.hat[i])+lpb(cand)-ll(b.hat[i,],s2.hat[i])-lpb(b.hat[i,])
  if (q>log(runif(1))) {
    b.hat[i,] <- cand
    acc.b <- acc.b+1
  }

  # Update s2
  cand <- rnorm(1,s2.hat[i],css)
  if (cand>0) {
    q <- ll(b.hat[i,],cand)+lps(cand)-ll(b.hat[i,],s2.hat[i])-lps(s2.hat[i])
    if (q>log(runif(1))) {
      s2.hat[i] <- cand
      acc.s <- acc.s+1
    }
  }

  cat(paste0("\r",round(100*i/B),"%"))
}
)

cpp.time<-system.time(system("cd ../C++; ./mlr"))
scala.time <- 9.687
r.time <- r.time[3]
cpp.time <- cpp.time[3]
times <- round(c(cpp.time,scala.time,r.time)/cpp.time,3)

code.len <- c(155,126,60)

par(mfrow=c(3,1))
barplot(times,ylab="seconds",names.arg=c("C++","Scala","R"),
       legend.text=times,col=2:4, args.legend=list(x="topleft"),
       main="Bayesian Multiple Linear Regression Speed Race")
barplot(code.len,ylab="Lines of Code",names.arg=c("C++","Scala","R"),
       legend.text=code.len,col=2:4, args.legend=list(x="topright"),
       main="Bayesian Multiple Linear Regression Conciseness Test")
plot(code.len,times,type="l",col="grey30",lwd=5,
     main="Speed vs. Code Length Tradeoff",
     xlab="Lines of Code (Codeing Time or Coding Efficiency)",
     ylab="Execution Time")
points(code.len,times,col=2:4,pch=20,cex=3)
legend("topright",legend=c("BLQ: BEST","BRQ: fast but long",
                           "ULQ: Slow but short","URQ: slow and long (WORST)"))
par(mfrow=c(1,1))


#print(paste0(100*acc.b/B,"%"))
#print(paste0(100*acc.s/B,"%"))
#
#plot(s2.hat[90000:100000],type="l")
#print(mean(s2.hat[90000:100000]))
#print(apply(b.hat[90000:100000,],2,mean))
