set.seed(1)

n <- 1000
k <- 9
X <- cbind(1,matrix(rnorm(n*k,5,3),n,k))

b <- (k+1):1

y <- X%*%b + rnorm(n)

write.table(cbind(y,X),file="dat.txt",append=F,quote=F,row.names=F,col.names=F)
