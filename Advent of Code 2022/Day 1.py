print("Part 1:",max(sum( map(int,l.split() ) ) for l in open("Day 1.txt","r").read().split("\n\n") ) )
print("Part 2:",sum( sorted([ sum( map(int,l.split() ) ) for l in open("Day 1.txt","r").read().split("\n\n") ])[-3:] ) )