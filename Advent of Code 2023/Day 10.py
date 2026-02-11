import itertools
from collections import deque

def isPipe(loc,field):
    y,x = loc[0],loc[1]
    return 0<=y<len(field) and 0<=x<len(field[0]) and field[y][x] in ['-','|','L','F','7','J','S']

def possibleNextSteps(loc,field):
    y,x = loc[0],loc[1]
    char = field[y][x]
    if char == '-':
        return [(y,x-1),(y,x+1)]
    elif char == '|':
        return [(y-1,x),(y+1,x)]
    elif char == 'L':
        return [(y-1,x),(y,x+1)]
    elif char == '7':
        return [(y+1,x),(y,x-1)]
    elif char == 'J':
        return [(y-1,x),(y,x-1)]
    elif char == 'F':
        return [(y+1,x),(y,x+1)]

def getChar(field, loc):
    return field[loc[0]][loc[1]]
    
def checkLoop(startingLoc, direction, field):
    currentLoc = startingLoc
    candLoc = (startingLoc[0]+direction[0],startingLoc[1]+direction[1])
    inLoop = True
    steps = 0
    while inLoop:
        steps += 1
        if not isPipe(candLoc, field):
            return False, -1 
        if getChar(field, candLoc) == 'S':
            return True, steps
        adjFieldsCandidate = possibleNextSteps(candLoc, field)
        if not currentLoc in adjFieldsCandidate:
            return False, -1
        newCand = adjFieldsCandidate[0]
        if newCand == currentLoc:
            newCand = adjFieldsCandidate[1]
        currentLoc = candLoc
        candLoc = newCand

def checkLoopList(startingLoc, direction, field):
    currentLoc = startingLoc
    candLoc = (startingLoc[0]+direction[0],startingLoc[1]+direction[1])
    inLoop = True
    loop = []
    while inLoop:
        loop.append(currentLoc)
        if not isPipe(candLoc, field):
            return False, loop 
        if getChar(field, candLoc) == 'S':
            return True, loop
        adjFieldsCandidate = possibleNextSteps(candLoc, field)
        if not currentLoc in adjFieldsCandidate:
            return False, loop
        newCand = adjFieldsCandidate[0]
        if newCand == currentLoc:
            newCand = adjFieldsCandidate[1]
        currentLoc = candLoc
        candLoc = newCand

def part1():
    field = open("Day 10.txt").read().split("\n")
    height, width = len(field), len(field[0])
    startFound = False
    startingLoc = (0,0)
    while not startFound:
        for y,x in itertools.product(range(height),range(width)):
            if field[y][x] == "S":
                startFound = True
                startingLoc = (y,x)
    
    answer = 0 
    for dy,dx in [(1,0),(-1,0),(0,1),(0,-1)]:
        isLoop, totalSteps = checkLoop(startingLoc,(dy,dx),field)
        if isLoop:
            answer = totalSteps // 2                        
            break
    print("Day 10 part 1:",answer)

def addLocs(loc,diff):
    return (loc[0]+diff[0],loc[1]+diff[1])


def printFieldLoop(field, loop, leftOfPipe, rightOfPipe):

    newField = [['.']*len(line) for line in field]
    for loc in loop:
        newField[loc[0]][loc[1]] = '*'
    for loc in leftOfPipe:
        newField[loc[0]][loc[1]] = 'L'
    for loc in rightOfPipe:
        newField[loc[0]][loc[1]] = 'R'
    for x in newField:
        print( ''.join(x))
    
def part2():
    field = open("Day 10.txt").read().split("\n")
    height, width = len(field), len(field[0])
    startFound = False
    startingLoc = (0,0)
    while not startFound:
        for y,x in itertools.product(range(height),range(width)):
            if field[y][x] == "S":
                startFound = True
                startingLoc = (y,x)
    loop = []
    for dy,dx in [(1,0),(-1,0),(0,1),(0,-1)]:
        isLoop, loop = checkLoopList(startingLoc,(dy,dx),field)
        if isLoop:
            break
    loopSet = set(loop)
    leftOfPipe = set()
    rightOfPipe = set()
    dirs = [(1,0),(0,-1),(-1,0),(0,1)]
    for i in range(1,len(loop)):
    # We go from the incoming direction clockwise and add to the left side if we havent seen the outgoing direction
    # and add to the right side after seeing the outgoing direction
        p = 0
        currentLoc = loop[i]
        while addLocs(currentLoc,dirs[p])!=loop[i-1]:
            p += 1
        q = 0
        while addLocs(currentLoc,dirs[q])!=loop[(i+1)%len(loop)]:
            q += 1
        j = (p+1)%4
        while j!=q:
            neighbor = addLocs(currentLoc,dirs[j])
            if neighbor not in loopSet:
                leftOfPipe.add(neighbor)
            j = (j+1)%4
        j = (q+1)%4
        while j!=p:
            neighbor = addLocs(currentLoc,dirs[j])
            if neighbor not in loopSet:
                rightOfPipe.add(neighbor)
            j = (j+1)%4
    
    # change = True
    # while change:
    #     change = False
    #     # printFieldLoop(field,loop,leftOfPipe,rightOfPipe)
    #     newElts = []
    #     for loc in rightOfPipe:
    #         for dir in dirs:
    #             newLoc = addLocs(loc,dir)
    #             if newLoc not in loop and newLoc not in rightOfPipe:
    #                 newElts.append(newLoc)
    #                 change = True
    #     for x in newElts:
    #         rightOfPipe.add(x)
    queue = deque(rightOfPipe)
    while len(queue)>0:
        loc = queue.popleft()
        for dir in dirs:
            newLoc = addLocs(loc,dir)
            if newLoc not in loop and newLoc not in rightOfPipe:
                rightOfPipe.add(newLoc)
                queue.append(newLoc)


    print("Day 10 part 2:",len(rightOfPipe))
    







part1()
part2()