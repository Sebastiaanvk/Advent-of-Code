from collections import defaultdict
from itertools import product

def listInSet(y,x,offsets,set):
    for offset in offsets:
        if (y+offset[0],x+offset[1]) in set:
            return True
    return False


dirCheckOffsets = [
    [(-1,-1),(-1,0),(-1,1)],
    [(1,-1),(1,0),(1,1)],
    [(-1,-1),(0,-1),(1,-1)],
    [(-1,1),(0,1),(1,1)],
]

dirSteps = [(-1,0),(1,0),(0,-1),(0,1)]
    

def nextLoc(loc, elfLocs,startIndex):
    y,x = loc
    for i in range(4):
        dirIndex = (i+startIndex)%4
        if not listInSet(y,x,dirCheckOffsets[dirIndex],elfLocs):
            return (y+dirSteps[dirIndex][0],x+dirSteps[dirIndex][1])

    return loc

def printField(elfLocs):
    left = min([x for y,x in elfLocs])
    right = max([x for y,x in elfLocs])+1
    up = min([y for y,x in elfLocs])
    down = max([y for y,x in elfLocs])+1
    field = [['.' for j in range(right-left) ] for i in range(down-up)]
    for (y,x) in elfLocs:
        field[y-up][x-left] = '#'
    for line in field:
        print(''.join(line))
    print(' ')

def noNeighbours(elfLoc, elfLocs):
    for dy,dx in product(range(-1,2),range(-1,2)):
        if dy!=0 or dx!=0:
            if (elfLoc[0]+dy,elfLoc[1]+dx) in elfLocs:
                return False
    return True


def part1():
    field = open("Day 23.txt").read().split('\n')
    height,width = len(field),len(field[0])
    elfLocs = set()
    for y,x in product(range(height),range(width)):
        if field[y][x] == '#':
            elfLocs.add((y,x))
    for i in range(10):
        # printField(elfLocs)
        candSteps = defaultdict(list)
        for elf in elfLocs:
            if noNeighbours(elf,elfLocs):
                candSteps[elf].append(elf)            
            else:
                candSteps[nextLoc(elf,elfLocs,i%4)].append(elf)
        # print(candSteps)
        elfLocs = set()
        for targetLoc in candSteps:
            sources = candSteps[targetLoc]
            if len(sources)==1:
                elfLocs.add(targetLoc)
            else:
                for source in sources:
                    elfLocs.add(source)
    # printField(elfLocs)

    left = min([x for y,x in elfLocs])
    right = max([x for y,x in elfLocs])+1
    up = min([y for y,x in elfLocs])
    down = max([y for y,x in elfLocs])+1
    print("Day 23 part 1:",(right-left)*(down-up)-len(elfLocs))


def part2():
    field = open("Day 23.txt").read().split('\n')
    height,width = len(field),len(field[0])
    elfLocs = set()
    for y,x in product(range(height),range(width)):
        if field[y][x] == '#':
            elfLocs.add((y,x))
    elfMoved = True
    i=0
    while elfMoved:
        # printField(elfLocs)
        candSteps = defaultdict(list)
        elfMoved = False
        for elf in elfLocs:
            if noNeighbours(elf,elfLocs):
                candSteps[elf].append(elf)            
            else:
                elfMoved = True
                candSteps[nextLoc(elf,elfLocs,i%4)].append(elf)
        # print(candSteps)
        elfLocs = set()
        for targetLoc in candSteps:
            sources = candSteps[targetLoc]
            if len(sources)==1:
                elfLocs.add(targetLoc)
            else:
                for source in sources:
                    elfLocs.add(source)
        i+=1
    # printField(elfLocs)

    print("Day 23 part 2:",i)




part1()
part2()