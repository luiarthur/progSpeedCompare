using Gadfly, DataFrames
function myplot (x,y)
  n,k = size(y)
  xs = repeat(x,outer=[3])
  ys = squeeze(reshape(y,n*k,1)',1)
  zs = repeat([1:k],inner=[n])
  df = DataFrame(x=xs,y=ys,z=zs)
  plot(df,x="x",y="y",color="z",Geom.point,Geom.line)
end
#= Example:
x = [1:10]
y = [x x*2 x*3]
myplot(x,y)
=#
