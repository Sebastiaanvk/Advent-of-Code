from itertools import product
from collections import defaultdict


def updateBlizzards(blizzards,height,width):
    newBlizzards = defaultdict(list)
    for (y,x) in blizzards:
        for (dy,dx) in blizzards[(y,x)]:
            newY,newX = y+dy,x+dx
            if newY == -1:
                newY=height-1
            elif newY == height:
                newY =0
            elif newX == -1:
                newX =  width-1
            elif newX == width:
                newX = 0
            newBlizzards[(newY,newX)].append((dy,dx))
    return newBlizzards

def printField(blizzards,height,width):
    field = [[0]*width for _ in range(height)]
    for (y,x) in blizzards:
        field[y][x] = len(blizzards[(y,x)])
    for line in field:
        print (line)
    print()

def inRange(y,x,height,width):
    return 0<=y<height and 0<=x<width

def part1():
    inp = open("Day 24.txt").read().split('\n')
    blizzards = defaultdict(list)
    width = len(inp[0])-2
    height = len(inp)-2
    dirsSymbDict = {'v':(1,0),'>':(0,1),'^':(-1,0),'<':(0,-1)}
    for (y,x) in product(range(height),range(width)):
        char = inp[y+1][x+1]
        if char != '.':
            blizzards[(y,x)].append(dirsSymbDict[char])
    
    locs = set([(-1,0)])
    exitFound = False
    step = 0
    while not exitFound:
        step += 1
        blizzards = updateBlizzards(blizzards,height,width)
        newLocs = set([(-1,0)])
        for loc in locs:
            if loc == (height-1,width-1):
                exitFound = True
                break
            for dy,dx in [(1,0),(0,1),(-1,0),(0,-1),(0,0)]:
                newY,newX = loc[0]+dy,loc[1]+dx
                if inRange(newY,newX,height,width) and (newY,newX) not in blizzards:
                    newLocs.add((newY,newX))
            locs = newLocs
            
    
    print("Day 24 part 1:",step)


def part2():
    inp = open("Day 24.txt").read().split('\n')
    blizzards = defaultdict(list)
    width = len(inp[0])-2
    height = len(inp)-2
    dirsSymbDict = {'v':(1,0),'>':(0,1),'^':(-1,0),'<':(0,-1)}
    for (y,x) in product(range(height),range(width)):
        char = inp[y+1][x+1]
        if char != '.':
            blizzards[(y,x)].append(dirsSymbDict[char])
    
    locs = set([(-1,0)])
    exitFound = False
    step = 0
    while not exitFound:
        step += 1
        blizzards = updateBlizzards(blizzards,height,width)
        newLocs = set([(-1,0)])
        for loc in locs:
            if loc == (height-1,width-1):
                exitFound = True
                break
            for dy,dx in [(1,0),(0,1),(-1,0),(0,-1),(0,0)]:
                newY,newX = loc[0]+dy,loc[1]+dx
                if inRange(newY,newX,height,width) and (newY,newX) not in blizzards:
                    newLocs.add((newY,newX))
            locs = newLocs

    locs = set([(height,width-1)])
    exitFound = False
    # blizzards = updateBlizzards(blizzards,height,width)
    while not exitFound:
        step += 1
        blizzards = updateBlizzards(blizzards,height,width)
        newLocs = set([(height,width-1)])
        for loc in locs:
            if loc == (0,0):
                exitFound = True
                break
            for dy,dx in [(1,0),(0,1),(-1,0),(0,-1),(0,0)]:
                newY,newX = loc[0]+dy,loc[1]+dx
                if inRange(newY,newX,height,width) and (newY,newX) not in blizzards:
                    newLocs.add((newY,newX))
            locs = newLocs

    locs = set([(-1,0)])
    exitFound = False
    # blizzards = updateBlizzards(blizzards,height,width)
    while not exitFound:
        step += 1
        blizzards = updateBlizzards(blizzards,height,width)
        newLocs = set([(-1,0)])
        for loc in locs:
            if loc == (height-1,width-1):
                exitFound = True
                break
            for dy,dx in [(1,0),(0,1),(-1,0),(0,-1),(0,0)]:
                newY,newX = loc[0]+dy,loc[1]+dx
                if inRange(newY,newX,height,width) and (newY,newX) not in blizzards:
                    newLocs.add((newY,newX))
            locs = newLocs
            
    
    print("Day 24 part 2:",step)


part1()
part2()