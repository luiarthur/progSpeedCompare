#= Install Packages if needed:
  Pkg.add("Distributions")
  Pkg.add("DataFrames")
=#
#ta = 1:size(X,2); (ta .!= 3) & (ta .!= 5)
#blas_set_num_thread(8)

using DataFrames
using Distributions

const dat = readdlm("../data/dat.txt")
const n,k = size(dat); k = k-1

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
function mvrnorm(M,S,n=size(S,2)) M+chol(S)'randn(n) end

csb = 4*XXi
css = 1
accb = 0
accs = 0

bb = zeros(B,k)
ss = ones(B)

bcur = bb[1,:]'
scur = ss[i]
r = log(rand(B*2))

for i in 1:B
  bb[i,] = bcur
  ss[i]  = scur

  # Update β̂: 
  candb = mvrnorm(bcur,csb)
  q = ll(candb,scur)+lpb(candb) -ll(bcur,scur)-lpb(bcur)
  if q>r[i] 
    bcur = candb
    accb += 1
  end

  # Update ŝ²:
  cands = rand(Normal(scur,sqrt(css)))
  if cands>0
    q = ll(bcur,cands)+lps(cands) -ll(bcur,scur)-lpb(scur)
    if q>r[i+B]
      scur = cands
      accs += 1
    end
  end

  #print("\r",round(100i/B),"%")
end
