using Gadfly, DataFrames

y1(n) = 2n
y2(n) = n+2
y3(n) = sin(n)

N=10
x = repeat([1:N],outer=[3])
y = vcat([y1(n) for n=1:N],
         [y2(n) for n=1:N], 
         [y3(n) for n=1:N])
col = repeat(["1","2","3"], inner=[N])

df = DataFrames.DataFrame(d1=x,d2=y,d3=col)
plot(df, x="d1", y="d2", color="d3", Geom.point, Geom.line)
