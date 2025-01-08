import itertools

def part1():
    area = open("Day6.txt").read().split("\n")
    height, width = len(area), len(area[0])

    dirs = [(0,1),(1,0),(0,-1),(-1,0)]
    dirInd = 3
    currentY, currentX  = 0,0
    for i,j in itertools.product(range(height),range(width)):
            if area[i][j] == "^":
                currentY,currentX = i,j
                break
    
    positions = {(currentY,currentX)}

    while 0<=currentY<height and 0<=currentX<=width:
        positions.add((currentY,currentX))
        nextY,nextX = currentY+dirs[dirInd][0],currentX+dirs[dirInd][1]
        while(0<=nextY<height and 0<=nextX<=width and area[nextY][nextX] == '#'):
            dirInd  = (dirInd+1 )%4
            nextY,nextX = currentY+dirs[dirInd][0],currentX+dirs[dirInd][1]
        currentY, currentX = nextY, nextX

    print("Day 6 part 1: ",len(positions))

part1()


def part2():
    area = open("Day6.txt").read().split("\n")
    height, width = len(area), len(area[0])

    dirs = [(0,1),(1,0),(0,-1),(-1,0)]
    startingInd = 3
    startingY, startingX  = 0,0
    for i,j in itertools.product(range(height),range(width)):
            if area[i][j] == "^":
                startingY,startingX = i,j
                break
    
    nbrPositions = 0
    for y,x in itertools.product(range(height),range(width)):
        print(y,x)
        if area[y][x] == '.':
            dirInd = startingInd 
            currentY, currentX  =  startingY,startingX

            positions = {(currentY,currentX,dirInd)}
            positions.clear()

            infiniteLoop = False

            while 0<=currentY<height and 0<=currentX<=width:
                if (currentY,currentX,dirInd) in positions:
                     infiniteLoop = True
                     break

                positions.add((currentY,currentX,dirInd))
                nextY,nextX = currentY+dirs[dirInd][0],currentX+dirs[dirInd][1]
                while(0<=nextY<height and 0<=nextX<width and (area[nextY][nextX] == '#' or  (y==nextY and x == nextX) )):
                    dirInd  = (dirInd+1 )%4
                    nextY,nextX = currentY+dirs[dirInd][0],currentX+dirs[dirInd][1]
                currentY, currentX = nextY, nextX

            if infiniteLoop:
                 nbrPositions += 1


    print("Day 6 part 2: ",nbrPositions)


part2()