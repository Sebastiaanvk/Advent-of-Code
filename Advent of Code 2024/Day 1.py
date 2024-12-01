import itertools


print("Part 1: ", sum([abs(x-y) for (x,y) in zip( sorted(list(map( lambda s: int(s.split()[0]), open("Day 1.txt").read().split('\n')[:-1]))), sorted(list(map( lambda s: int(s.split()[1]), open("Day 1.txt").read().split('\n')[:-1])))    )]))

print("Part 2: ", sum([ x * list(map( lambda s: int(s.split()[1]), open("Day 1.txt").read().split('\n')[:-1])).count(x)   for x in list(map( lambda s: int(s.split()[0]), open("Day 1.txt").read().split('\n')[:-1])) ]))

