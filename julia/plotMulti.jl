using Gadfly, DataFrames

N=10
x = [1:N]
y = [x,x*2,x*3]
xs = repeat([1:N],outer=[3])
z = repeat(["1","2","3"], inner=[N])

df = DataFrame(x=xs,y=y,z=z)
plot(df, x="x", y="y",color="z", Geom.point, Geom.line)


