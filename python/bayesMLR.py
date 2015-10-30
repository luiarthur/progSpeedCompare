f = open ( '../data/dat.txt' , 'r')
dat = [ map(float,line.split(' ')) for line in f if line.strip() != "" ]
