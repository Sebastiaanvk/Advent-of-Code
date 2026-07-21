from collections import deque


def containsWall(loc):
    x,y = loc
    if x<0 or y<0:
        return True
    number = 1364
    n = x*x + 3*x + 2*x*y + y + y*y + number
    nr1Bits = 0
    while n>0:
        if n%2==1:
            nr1Bits+=1
        n = n>>1
    return nr1Bits%2==1

nbs = [(1,0),(-1,0),(0,1),(0,-1)]

def part1():
    Q = deque()
    Q.append((1,1,0))
    seen = set()
    seen.add((1,1))
    while len(Q)>0:
        x,y,steps = Q[0]
        Q.popleft()
        for dx,dy in nbs:
            newLoc = (x+dx,y+dy)
            if newLoc == (31,39):
                print("Part 1: ",steps+1)
                return
            if newLoc not in seen and not containsWall(newLoc):
                Q.append((x+dx,y+dy,steps+1))
                seen.add(newLoc)

part1()

def part2():
    Q = deque()
    Q.append((1,1,0))
    seen = set()
    seen.add((1,1))
    while len(Q)>0:
        x,y,steps = Q[0]
        Q.popleft()
        for dx,dy in nbs:
            newLoc = (x+dx,y+dy)
            if newLoc not in seen and not containsWall(newLoc):
                if steps<49:
                    Q.append((x+dx,y+dy,steps+1))
                seen.add(newLoc)
    print("Part 2:", len(seen))

part2()