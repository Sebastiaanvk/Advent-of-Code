print("Part 1:",sum( l[0]*10+l[-1]  for l in map(lambda x: [c for c in x if x.isdigit()],open("Day 1.txt","r").read().split("\n") )) )
