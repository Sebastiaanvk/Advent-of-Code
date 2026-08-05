from collections import deque
from itertools import permutations

nbs = [(-1,0),(1,0),(0,-1),(0,1)]

def part1():
    inp = open("day-24.txt").read().split('\n')[:-1]
    walls = set()
    interests = {}
    for y in range(len(inp)):
        for x in range(len(inp[0])):
            if inp[y][x]=='#':
                walls.add((y,x))
            elif inp[y][x]!='.':
                interests[inp[y][x]] = (y,x)
    dists = {}
    for src in interests:
        seen = set()
        Q = deque()
        Q.append((interests[src],0))
        seen.add(interests[src])
        while len(Q):
            loc,dist = Q.popleft()
            y,x = loc
            for dy,dx in nbs:
                newLoc = (y+dy,x+dx)
                char = inp[newLoc[0]][newLoc[1]]
                if newLoc not in seen and char != '#':
                    Q.append((newLoc,dist+1))
                    seen.add(newLoc)
                    if  char != '.':
                        dists[(src,char)] = dist + 1
                        
    # print(dists)
    minDist = 10000000
    chars = []
    for x in interests:
        if x != '0':
            chars.append(x)
    for ls in permutations(chars):
        dist = dists[('0',ls[0])]
        for i in range(0,len(ls)-1):
            dist += dists[(ls[i],ls[i+1])]
        minDist = min(minDist,dist)
    print("Part 1: ",minDist)

    minDist = 10000000
    chars = []
    for x in interests:
        if x != '0':
            chars.append(x)
    for ls in permutations(chars):
        dist = dists[('0',ls[0])]
        for i in range(0,len(ls)-1):
            dist += dists[(ls[i],ls[i+1])]
        dist += dists[ls[-1],'0']
        minDist = min(minDist,dist)
    print("Part 2: ",minDist)





part1()