from itertools import product
from collections import deque

doors = set()
compass = {'N':-1j,'S':1j,'E':1,'W':-1}

def stepThroughList(st, dir):
    setCopy = set()
    for x in st:
        doors.add(x+compass[dir])
        setCopy.add(x+2*compass[dir])
    return setCopy


def walkThroughMap(s,startIndex,initialPositions):
    currentPositions= initialPositions.copy()
    endPositions = set()
    currentIndex = startIndex
    c = s[currentIndex]
    while c not in [')','$']:
        # print(currentIndex)
        if c == '(':
            currentPositions, currentIndex = walkThroughMap(s, currentIndex+1, currentPositions)
        elif c == '|':
            endPositions |= currentPositions
            currentPositions = initialPositions.copy()
            currentIndex += 1
        else:
            currentPositions = stepThroughList(currentPositions,c)
            currentIndex +=1
        c = s[currentIndex]
    endPositions |= currentPositions
    return endPositions,currentIndex+1

def part1():
    inp = open("day-20.txt").read().split('\n')[0]
    # inp = "^ENWWW(NEEE|SSE(EE|N))$"
    # inp = "^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$"
    doors.clear() 
    initPos = set()
    initPos.add(0)
    walkThroughMap(inp,1,initPos)

    seen = set()
    Q = deque()
    Q.append((0,0))
    seen.add(0)
    largestDist = 0
    nrFarDoors = 0
    while len(Q):
        current,dist = Q.pop()
        for dir in [-1j,1j,-1,1]:
            if current+dir in doors and current+2*dir not in seen:
                seen.add(current+2*dir)
                Q.append((current+2*dir,dist+1))
                largestDist = max(largestDist,dist+1)
                if dist+1>=1000:
                    nrFarDoors += 1

    print("Part 1: ",largestDist)
    print("Part 2:", nrFarDoors)






part1()