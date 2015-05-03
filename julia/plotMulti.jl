using Gadfly, DataFrames

y1(n) = 2n
y2(n) = n+2
y3(n) = sin(n)

N=10
x = repeat([1:N],outer=[3])
ys = vcat([y1(n) for n=1:N],
          [y2(n) for n=1:N], 
          [y3(n) for n=1:N])
z = repeat(["1","2","3"], inner=[N])

df = DataFrame(x=x,y=y,z=z)
plot(df, x="x", y="y",color="z", Geom.point, Geom.line)
