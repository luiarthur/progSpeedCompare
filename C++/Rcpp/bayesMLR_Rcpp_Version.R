#http://www.r-bloggers.com/for-faster-r-use-openblas-instead-better-than-atlas-trivial-to-switch-to-on-ubuntu/

#http://stackoverflow.com/questions/21730547/openblas-routine-used-from-r-rcpp-runs-only-on-a-single-core-in-linux

library(Rcpp)
Sys.setenv(PKG_CXXFLAGS="-std=c++11") # enable c++11, for RcppArmadillo

dat <- read.table("../../data/dat.txt",header=FALSE)
dat <- as.matrix(dat)

sourceCpp("bayesMLR_Rcpp_Version.cpp",verbose=TRUE,rebuild=TRUE)

system.time(x <- bayesMLR(dat))
