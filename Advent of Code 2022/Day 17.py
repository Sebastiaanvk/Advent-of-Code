shapes = [
    [(0,0),(0,1),(0,2),(0,3)],
    [(0,1),(1,1),(1,0),(2,1),(1,2)],
    [(0,0),(0,1),(0,2),(1,2),(2,2)],
    [(0,0),(1,0),(2,0),(3,0)],
    [(0,0),(0,1),(1,0),(1,1)]
]

def canPlace(shapeIndex, newY, newX, placedRocks):
    for (dy,dx) in shapes[shapeIndex]:
        if (newY+dy,newX+dx) in placedRocks:
            return False
        if  not (0<=newX+dx<7):
            return False
    return True

def part1():
    input = open("Day 17.txt","r").read()
    shapeIndex = 0
    placedRocks = {(-1,0),(-1,1),(-1,2),(-1,3),(-1,4),(-1,5),(-1,6)}
    highestRock = -1
    inputIndex = 0

    for rock in range(2022):
        currentY = highestRock+4
        currentX = 2
        hitRock = False
        while not hitRock:
            c = input[inputIndex]
            dx = -1 if  c=='<' else 1
            inputIndex = (inputIndex + 1) % len(input)
            if canPlace(shapeIndex, currentY, currentX+dx, placedRocks):
                currentX += dx
            if canPlace(shapeIndex, currentY-1, currentX, placedRocks):
                currentY -= 1 
            else:
                hitRock = True
                for (dy,dx) in shapes[shapeIndex]:
                    placedRocks.add((currentY+dy,currentX+dx))
                    highestRock = max(highestRock,currentY+dy)
        shapeIndex = (shapeIndex+1)%5
    print("Day 17 part 1: ",highestRock+1)

def checkPatternLength(diffs, l):
    for i in range(l):
        if diffs[-l+i] != diffs[-2*l+i]:
            return False
    return True

def findPattern(diffs):
    patternLength = 30
    patternFound = False
    while not patternFound:
        if checkPatternLength(diffs,patternLength):
            return patternLength
        patternLength += 1


def part2():
    input = open("Day 17.txt","r").read()
    shapeIndex = 0
    placedRocks = {(-1,0),(-1,1),(-1,2),(-1,3),(-1,4),(-1,5),(-1,6)}
    highestRock = -1
    inputIndex = 0

    diffs = []

    for rock in range(100000):
        currentY = highestRock+4
        currentX = 2
        hitRock = False
        while not hitRock:
            c = input[inputIndex]
            dx = -1 if  c=='<' else 1
            inputIndex = (inputIndex + 1) % len(input)
            if canPlace(shapeIndex, currentY, currentX+dx, placedRocks):
                currentX += dx
            if canPlace(shapeIndex, currentY-1, currentX, placedRocks):
                currentY -= 1 
            else:
                hitRock = True
                newHighestRock = highestRock
                for (dy,dx) in shapes[shapeIndex]:
                    placedRocks.add((currentY+dy,currentX+dx))
                    newHighestRock = max(newHighestRock,currentY+dy)
                diffs.append(newHighestRock-highestRock)
                highestRock = newHighestRock
        shapeIndex = (shapeIndex+1)%5

    patternLength = findPattern(diffs)
    print("The pattern length =",patternLength)

    patternHeight = 0
    for i in range(patternLength):
        patternHeight += diffs[-1-i]
    
    nrExtraPatterns = (1000000000000 - len(diffs) ) // patternLength
    extraSteps = (1000000000000 - len(diffs) ) % patternLength



    totalHeight = highestRock+1 + nrExtraPatterns * patternHeight
    for i in range(extraSteps):
        totalHeight += diffs[-patternLength + i]

    print("Day 17 part 2:", totalHeight)



part1()
part2()