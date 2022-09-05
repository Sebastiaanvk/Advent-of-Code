import itertools

input = list(map( lambda x: list(map(int,x.split())), open("Day 2.txt","r").read().split('\n')[:-1]))
print("Part 1:", sum( (max(x) - min(x)) for x in input) )
print("Part 2:", sum( next( max(x//d,d//x) for x,d in itertools.combinations(a,2) if x//d*d==x or d//x*x==d) for a in input) )