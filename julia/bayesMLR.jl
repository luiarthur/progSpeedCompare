#= Install Packages if needed:
  Pkg.add("Distributions")
  Pkg.add("DataFrames")
=#

#blas_set_num_thread(8)

using DataFrames
using Distributions

dat = readdlm("../data/dat.txt")
n,k = size(dat); k = k-1


