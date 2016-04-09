library(Rcpp)
Sys.setenv(PKG_CXXFLAGS="-std=c++11") # enable c++11, for RcppArmadillo

dat <- read.table("../../data/dat.txt",header=FALSE)
dat <- as.matrix(dat)

sourceCpp("bayesMLR_Rcpp_Version.cpp",verbose=TRUE,rebuild=TRUE)

system.time(x <- bayesMLR(dat))
