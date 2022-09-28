import itertools

input = list(map( lambda l: list(l.split(" ")) , open("Day 4.txt","r").read().split("\n")[:-1]))
print("Day 1: ", sum( (sum(x1==x2 for (x1,x2) in itertools.combinations(l,2)))==0  for l in input   ))
print("Day 2: ", sum( (sum( sorted(x1)==sorted(x2) for (x1,x2) in itertools.combinations(l,2)))==0  for l in input   ))


