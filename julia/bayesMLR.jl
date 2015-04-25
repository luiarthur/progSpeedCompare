#= Install Packages if needed:
  Pkg.add("Distributions")
  Pkg.add("DataFrames")
=#
#ta = 1:size(X,2); (ta .!= 3) & (ta .!= 5)
#blas_set_num_thread(8)

println("Loading packages...")
using DataFrames
using Distributions
println("Finished loading packages...")

const dat = readdlm("../data/dat.txt")
n,k = size(dat); k = k-1

const y =dat[:,1]
const X = dat[:,2:end]

const XXi = inv(X'X)
const s = 100
const mle = XXi*X'y

a = 1
b = 1
B = 100000
s2=10

function ll(be,sig2) c = y-X*be; c'c/(-2sig2) - n*log(sig2)/2 end
function lpb(be) -be'XXi*be/2s2 end
function lps(sig2) +(a-1)*log(s2)-s2/b end
function mvrnorm(M,S) M+chol(S)'randn(k) end

csb = 4*XXi
css = 1
accb = 0
accs = 0

bb = zeros(k,B)
ss = ones(B)

bcur = bb[:,1]
scur = ss[1]
r = log(rand(B*2))

@time for i in 1:B
  bb[:,i] = bcur
  ss[i]  = scur

  # Update β̂: 
  candb = mvrnorm(bcur,csb)
  q = ll(candb,scur)+lpb(candb) -ll(bcur,scur)-lpb(bcur)
  if q[1]>r[i] 
    bcur = candb
    accb += 1
  end

  # Update ŝ²:
  #cands = rand(Normal(scur,sqrt(css)))
  cands = randn()*sqrt(css)+scur
  if cands>0
    q = ll(bcur,cands)+lps(cands) -ll(bcur,scur)-lps(scur)
    if q[1]>r[i+B]
      scur = cands
      accs += 1
    end
  end

  print("\r",round(100i/B),"%")
end

