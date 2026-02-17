from collections import deque



def part1():
    dirs = [(0,1),(1,0),(0,-1),(-1,0)]
    RIGHT,DOWN,LEFT,UP = 0,1,2,3

    with open("Day 16.txt") as f:
        field = f.read().split("\n")
        height,width = len(field),len(field[0])
        queue = deque()
        queue.append((0,0,0))
        seenSquares = set([(0,0)])
        seenSquaresDirs = set([(0,0,0)])
        while len(queue)>0:
            y,x,dirIndex = queue[0]
            queue.popleft()
            char = field[y][x]
            nextSteps = []
            if char == '.' or (char=='|' and dirIndex in [UP,DOWN]) or (char=='-' and dirIndex in [LEFT,RIGHT]):
                nextSteps.append((y+dirs[dirIndex][0],x+dirs[dirIndex][1],dirIndex))
            elif char == '|':
                nextSteps = [(y-1,x,UP),(y+1,x,DOWN)]
            elif char == '-':
                nextSteps = [(y,x-1,LEFT),(y,x+1,RIGHT)]
            elif (char == '\\' and dirIndex==RIGHT) or (char == '/' and dirIndex==LEFT):
                nextSteps = [(y+1,x,DOWN)]
            elif (char == '\\' and dirIndex==UP) or (char == '/' and dirIndex==DOWN):
                nextSteps = [(y,x-1,LEFT)]
            elif (char == '\\' and dirIndex==LEFT) or (char == '/' and dirIndex==RIGHT):
                nextSteps = [(y-1,x,UP)]
            elif (char == '\\' and dirIndex==DOWN) or (char == '/' and dirIndex==UP):
                nextSteps = [(y,x+1,RIGHT)]

            for (y2,x2,dir2) in nextSteps:
                if 0<=y2<height and 0<=x2<width:
                    seenSquares.add((y2,x2))
                    if (y2,x2,dir2) not in seenSquaresDirs:
                        queue.append((y2,x2,dir2))
                        seenSquaresDirs.add((y2,x2,dir2))
        print("Day 16 part 1:", len(seenSquares))

def calcLights(field,startingSquare,startingDir):
    dirs = [(0,1),(1,0),(0,-1),(-1,0)]
    RIGHT,DOWN,LEFT,UP = 0,1,2,3

    height,width = len(field),len(field[0])
    queue = deque()
    beginSqDir = (startingSquare[0],startingSquare[1],startingDir)
    queue.append(beginSqDir)
    seenSquares = set([startingSquare])
    seenSquaresDirs = set([beginSqDir])
    while len(queue)>0:
        y,x,dirIndex = queue[0]
        queue.popleft()
        char = field[y][x]
        nextSteps = []
        if char == '.' or (char=='|' and dirIndex in [UP,DOWN]) or (char=='-' and dirIndex in [LEFT,RIGHT]):
            nextSteps.append((y+dirs[dirIndex][0],x+dirs[dirIndex][1],dirIndex))
        elif char == '|':
            nextSteps = [(y-1,x,UP),(y+1,x,DOWN)]
        elif char == '-':
            nextSteps = [(y,x-1,LEFT),(y,x+1,RIGHT)]
        elif (char == '\\' and dirIndex==RIGHT) or (char == '/' and dirIndex==LEFT):
            nextSteps = [(y+1,x,DOWN)]
        elif (char == '\\' and dirIndex==UP) or (char == '/' and dirIndex==DOWN):
            nextSteps = [(y,x-1,LEFT)]
        elif (char == '\\' and dirIndex==LEFT) or (char == '/' and dirIndex==RIGHT):
            nextSteps = [(y-1,x,UP)]
        elif (char == '\\' and dirIndex==DOWN) or (char == '/' and dirIndex==UP):
            nextSteps = [(y,x+1,RIGHT)]

        for (y2,x2,dir2) in nextSteps:
            if 0<=y2<height and 0<=x2<width:
                seenSquares.add((y2,x2))
                if (y2,x2,dir2) not in seenSquaresDirs:
                    queue.append((y2,x2,dir2))
                    seenSquaresDirs.add((y2,x2,dir2))
    return len(seenSquares)

def part2():

        with open("Day 16.txt") as f:
            field = f.read().split('\n')
            maxLights = 0
            RIGHT,DOWN,LEFT,UP = 0,1,2,3
            for x in range(len(field[0])):
                maxLights = max(maxLights,calcLights(field,(0,x),DOWN))
                maxLights = max(maxLights,calcLights(field,(len(field)-1,x),UP))
            for y in range(len(field)):
                maxLights = max(maxLights,calcLights(field,(y,0),RIGHT))
                maxLights = max(maxLights,calcLights(field,(y,len(field[0])-1),LEFT))

        print("Day 16 part 2:", maxLights )

part1()
part2()