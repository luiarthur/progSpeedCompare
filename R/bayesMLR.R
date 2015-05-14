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
scala.time <- 7
r.time <- r.time[3]
cpp.time <- cpp.time[3]
julia.time <- 9
times <- round(c(cpp.time,scala.time,julia.time,r.time)/cpp.time,3)

code.len <- c(155,126,65,60)

#par(mfrow=c(3,1))
mc <- c("darkgoldenrod2","springgreen3","indianred1","cadetblue3")

mar <- par("mar")
par("mar"=c(3,1,4.1,1))
svg("speed.svg")
  barplot(times,names.arg=c("C++","Scala","Julia","R"),yaxt="n",col=mc,
         #legend.text=times,args.legend=list(x="topleft",bty="n"),
         main="Bayesian Multiple Linear Regression Speed (seconds)",border=NA)
  xt <- seq(0,par("usr")[2],len=9)[c(2,4,6,8)] + c(.07,.05,0,-.05)
  text(xt[1],times[1]-.5,times[1],col="white",cex=1.3)
  text(xt[2],times[2]-.5,times[2],col="white",cex=1.3)
  text(xt[3],times[3]-.5,times[3],col="white",cex=1.3)
  text(xt[4],times[4]-.5,times[4],col="white",cex=1.3)
dev.off()

svg("lines.svg")
  barplot(code.len,yaxt="n",names.arg=c("C++","Scala","Julia","R"),col=mc,
         #legend.text=code.len,args.legend=list(x="topright",bty="n"),
         main="Bayesian Multiple Linear Regression \n Lines of Code",border=NA)
  text(xt[1],code.len[1]-5,code.len[1],col="white",cex=1.6)
  text(xt[2],code.len[2]-5,code.len[2],col="white",cex=1.6)
  text(xt[3],code.len[3]-5,code.len[3],col="white",cex=1.6)
  text(xt[4],code.len[4]-5,code.len[4],col="white",cex=1.6)
  par("mar"=mar)
dev.off()

svg("vs2.svg",width=13.8,height=5)
  plot(code.len,times,col="grey",type="l",
       main="Speed vs. Code Length Tradeoff",
       xlab="Lines of Code (Codeing Time or Coding Efficiency)",
       ylab="Execution Time (seconds)",
       bty='n')
  points(code.len,times,col=mc,pch=20,cex=4)
dev.off()
legend("topright",legend=c("BLQ: BEST","BRQ: Fast but Long",
                           "ULQ: Slow but Short","URQ: Slow and Long (WORST)"))
#par(mfrow=c(1,1))


#print(paste0(100*acc.b/B,"%"))
#print(paste0(100*acc.s/B,"%"))
#
#plot(s2.hat[90000:100000],type="l")
#print(mean(s2.hat[90000:100000]))
#print(apply(b.hat[90000:100000,],2,mean))
