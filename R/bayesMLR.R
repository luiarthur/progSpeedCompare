dat <- as.matrix(read.table("../data/dat.txt"))

y <- dat[,1]
X <- dat[,-1]
colnames(X) <- paste0("b",0:9)

#pairs(dat)
#solve(t(X)%*%X,t(X)%*%y)
