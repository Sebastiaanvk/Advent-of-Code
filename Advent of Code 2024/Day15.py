import itertools



def part1():
#    input = open("test15.txt").read().split("\n\n")
    input = open("Day15.txt").read().split("\n\n")

    field = [[c for c in ln] for ln in input[0].split("\n")]
    height,width = len(field),len(field[0])
    currentY,currentX = 0,0

    for y,x in itertools.product(range(height),range(width)):
        if field[y][x] == "@":
            currentY, currentX = y,x
    
    for c in input[1]:
        dy,dx = 0,0
        if c == "^":
            dy = -1
        elif c == ">":
            dx = 1
        elif c == "<":
            dx = -1
        elif c == "v":
            dy = 1
        else:
            continue
        endPushY, endPushX = currentY+dy, currentX+dx
        while field[endPushY][endPushX] == "O":
            endPushY += dy
            endPushX += dx

        if field[endPushY][endPushX] != "#":
            field[currentY][currentX] = "."
            currentY += dy
            currentX += dx
            field[endPushY][endPushX] = "O"
            field[currentY][currentX] = "@"
    sum = 0
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x]=="O":
            sum += y*100+x
    print("Day 15 part 1: ", sum)

part1()



def part2():
#    input = open("test15.txt").read().split("\n\n")
    input = open("Day15.txt").read().split("\n\n")
    field = []
    for ln in input[0].split("\n"):
        fieldLine = []
        for c in ln:
            if c=="#":
                fieldLine.append("#")
                fieldLine.append("#")
            elif c=="O":
                fieldLine.append("[")
                fieldLine.append("]")
            elif c==".":
                fieldLine.append(".")
                fieldLine.append(".")
            elif c=="@":
                fieldLine.append("@")
                fieldLine.append(".")
        field.append(fieldLine)
    
    #for ln in field:
        #print(ln)

    height,width = len(field),len(field[0])

    currentY,currentX = 0,0

    for y,x in itertools.product(range(height),range(width)):
        if field[y][x] == "@":
            currentY, currentX = y,x

    for c in input[1]:
        dy,dx = 0,0
        if c == "^":
            dy = -1
        elif c == ">":
            dx = 1
        elif c == "<":
            dx = -1
        elif c == "v":
            dy = 1
        else:
            continue
        nextY,nextX = currentY+dy,currentX+dx
        if field[nextY][nextX]==".":
            field[currentY][currentX] = "."
            currentX += dx
            currentY += dy
            field[currentY][currentX] = "@"
        elif dy==0:
            while field[currentY][nextX] == "[" or field[currentY][nextX] == "]":
                nextX += 2*dx
            if field[currentY][nextX]==".":
                field[currentY][currentX]="."
                currentX += dx
                field[currentY][currentX] = "@"
                i=1
                if dx==1:
                    while field[currentY][currentX+i*dx] == "]":
                        field[currentY][currentX+i*dx] = "["
                        field[currentY][currentX+i*dx+1] = "]"
                        i +=2
                else:
                    while field[currentY][currentX+i*dx] == "[":
                        field[currentY][currentX+i*dx] = "]"
                        field[currentY][currentX+i*dx-1] = "["
                        i +=2
        else:
            allowedToPush = True
            contLooking = True
            consideredRow = currentY+dy
            boxPosPerRow = {} 
            boxPosPerRow[consideredRow] = set()
            if field[consideredRow][currentX]=="]":
                boxPosPerRow[consideredRow].add(currentX-1)
            elif field[consideredRow][currentX]=="[":
                boxPosPerRow[consideredRow].add(currentX)
            else:
                allowedToPush = False
                contLooking = False

            while contLooking and allowedToPush:
                contLooking = False
                boxPosPerRow[consideredRow+dy] = set()
                for box in boxPosPerRow[consideredRow]:
                    x = box
                    nextItem = field[consideredRow+dy][x]
                    if nextItem=="[":
                        boxPosPerRow[consideredRow+dy].add(x)
                        contLooking = True
                    elif nextItem=="]":
                        boxPosPerRow[consideredRow+dy].add(x-1)
                        contLooking = True
                    elif nextItem == "#":
                        allowedToPush = False
                    x = box+1
                    nextItem = field[consideredRow+dy][x]
                    if nextItem=="[":
                        boxPosPerRow[consideredRow+dy].add(x)
                        contLooking = True
                    elif nextItem=="]":
                        boxPosPerRow[consideredRow+dy].add(x-1)
                        contLooking = True
                    elif nextItem == "#":
                        allowedToPush = False
                consideredRow += dy
            if allowedToPush:
                while consideredRow!=currentY:
                    for box in boxPosPerRow[consideredRow]:
                        field[consideredRow+dy][box]="["
                        field[consideredRow+dy][box+1]="]"
                        field[consideredRow][box]="."
                        field[consideredRow][box+1]="."
                    consideredRow -= dy
                field[currentY][currentX] = "."
                currentY += dy
                field[currentY][currentX] = "@"


    sum = 0
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x]=="[":
            sum += y*100+x
    print("Day 15 part 2: ", sum)

part2()