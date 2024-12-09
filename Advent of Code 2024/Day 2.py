import itertools

print("Day 2 part 1:",sum([ l.count(1)+l.count(2)+l.count(3)==len(l) or l.count(-1)+l.count(-2)+l.count(-3)==len(l)   for l in list(map( lambda m: [ y-x for (x,y) in zip(m[0:-1],m[1:]) ] ,list(map(lambda k: list(map(int,k.split())) ,open("Day 2.txt").read().split('\n')[:-1] ))  ))]))

print("Day 2 part 2:",sum([ 0<sum([ k.count(1)+k.count(2)+k.count(3)==len(k) or k.count(-1)+k.count(-2)+k.count(-3)==len(k) for k in list(map( lambda m: [y-x for (x,y) in zip(m[0:-1],m[1:])]    ,[l]+[ l[:i]+l[i+1:] for i in range(len(l))])) ])  for l in list(map(lambda k: list(map(int,k.split())) ,open("Day 2.txt").read().split('\n')[:-1] ))]))