#= Install Packages if needed:
  Pkg.add("Distributions")
  Pkg.add("DataFrames")
=#
#ta = 1:size(X,2); (ta .!= 3) & (ta .!= 5)
#blas_set_num_thread(8)

println("Loading packages...")
using DataFrames
using Distributions
using Gadfly
println("Finished loading packages...")

const dat = readdlm("../data/dat.txt")
n,k1 = size(dat)
const k = k1-1

const y =dat[:,1]
const X = dat[:,2:end]

const XXi = inv(X'X)
const s = 100
const mle = XXi*X'y

a = 1
b = 1
B = 100000
s2=10
csb = 4*XXi
css = 1
accb = 0
accs = 0
S = chol(csb)'

function ll(be::Array{Float64,1},sig2::Float64) 
  c = y-X*be
  c'c/(-2sig2)-n*log(sig2)/2 
end

lpb(be::Array{Float64,1}) = -be'XXi*be/2s2
lps(sig2::Float64) = (a-1)*log(s2)-s2/b 
mvrnorm(M::Array{Float64,1}) = M+S*randn(k)


bb = Array(Float64,(k,B))
ss = Array(Float64,B)

bcur = bb[:,1]
scur = 1.0
r = log(rand(B*2))
rnorm = randn(B)
println("Starting Metropolis...")
#@time @fastmath for i in 1:B
@time for i in 1:B

  # Update β̂: 
  candb = mvrnorm(bcur)
  q = ll(candb,scur)+lpb(candb) -ll(bcur,scur)-lpb(bcur)
  if q[1]>r[i] 
    bcur = candb
    accb += 1
  end

  # Update ŝ²:
  #cands = rand(Normal(scur,sqrt(css)))
  cands = rnorm[i]*sqrt(css)+scur
  if cands>0
    q = ll(bcur,cands)+lps(cands) -ll(bcur,scur)-lps(scur)
    if q[1]>r[i+B]
      scur = cands
      accs += 1
    end
  end

  @inbounds bb[:,i] = bcur
  @inbounds ss[i]  = scur

  if i%(B/10)==0 print("\r",round(100*i/B),"%") end
end
println("End of Metropolis.\n\n")

println("β̂:", mean(bb[:,90000:100000],2),"\n")
println("ŝ²:", mean(ss[90000:100000]),"\n")

println("Acceptance rate for β̂: ",accb/B)
println("Acceptance rate for ŝ²:",accs/B)

plot(1:10001,ss[90000:100000])
p1 = linspace(0,2*pi,1000); p2 = sin(3*p1 + 4*cos(2*p1))
plot(p1, p2, color="red", linewidth=2.0, linestyle="--")
