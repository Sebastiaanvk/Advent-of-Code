
dirs = [(0,1),(1,0),(0,-1),(-1,0)]

def calcNextLoc(loc,dirIndex,rangesRows,rangesCols):
    y,x = loc
    if dirIndex==0 and x==rangesRows[y][1]:
        return (y,rangesRows[y][0])
    elif dirIndex==2 and x==rangesRows[y][0]:
        return (y,rangesRows[y][1])
    elif dirIndex==1 and y==rangesCols[x][1]:
        return (rangesCols[x][0],x)
    elif dirIndex==3 and y==rangesCols[x][0]:
        return (rangesCols[x][1],x)
    return (y+dirs[dirIndex][0],x+dirs[dirIndex][1])


def part1():
    inp = open("Day 22.txt").read().split("\n\n")
    field = inp[0].split('\n')
    rangesRows = [] # Inclusive interval for the indices on the field
    for line in field:
        i = 0
        while line[i]==' ':
            i += 1
        rangesRows.append((i,len(line)-1))
    width = max([w[1] for w in rangesRows])+1
    rangesCols = []
    for col in range(width):
        topRow = 0
        while col<rangesRows[topRow][0] or rangesRows[topRow][1]<col:
            topRow += 1
        bottomRow = len(field)-1
        while col<rangesRows[bottomRow][0] or rangesRows[bottomRow][1]<col:
            bottomRow -= 1
        rangesCols.append((topRow,bottomRow))

    instructions = []
    i = 0
    while i < len(inp[1]):
        if inp[1][i]=='R' or inp[1][i]=='L':
            instructions.append(inp[1][i])
            i+=1
        else:
            j=i+1
            while j<len(inp[1]) and inp[1][j]!='R' and inp[1][j]!='L':
                j+=1
            instructions.append(inp[1][i:j])
            i=j
    # print(instructions)
    loc = (0,rangesRows[0][0])
    print(loc)
    dir = 0
    for x in instructions:
        if x=='L':
            dir = (dir-1)%4
        elif x=='R':
            dir = (dir+1)%4
        else:
            steps = int(x)
            i=0
            cont=True
            while i<steps and cont:
                newLoc = calcNextLoc(loc,dir,rangesRows,rangesCols)
                if field[newLoc[0]][newLoc[1]]=='#':
                    cont = False
                else:
                    loc = newLoc
                i += 1
            # print(loc)
    print("Day 22 part 1:",1000*(loc[0]+1)+4*(loc[1]+1)+dir)

RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3

    
def calcNextLoc2(loc,dirIndex):
    y,x = loc
    newDir = dirIndex

    if x==50 and 0<=y<50 and dirIndex==LEFT:#a
        # print("a")
        newX = 0
        newY = 149-y
        newDir = RIGHT
    elif y==0 and 50<=x<100 and dirIndex == UP:#b
        # print("b")
        newX = 0
        newY = 100+x
        newDir = RIGHT
    elif y==0 and 100<=x<150 and dirIndex == UP:#c
        # print("c")
        newY=199
        newX=x-100
        newDir = UP
    elif x==149 and 0<=y<50 and dirIndex == RIGHT:#d
        # print("d")
        newX = 99
        newY = 149-y
        newDir = LEFT
    elif y==49 and 100<=x<150 and dirIndex == DOWN:#e
        # print("e")
        newX = 99
        newY = x-50
        newDir = LEFT
    elif x==99 and 50<=y<100 and dirIndex == RIGHT:#f
        # print("f")
        newX = y+50
        newY=49
        newDir = UP
    elif x==50 and 50<=y<100 and dirIndex==LEFT:#g
        # print("g")
        newX = y-50
        newY = 100
        newDir = DOWN
    elif y==100 and 0<=x<50 and dirIndex==UP:#h
        # print("h")
        newX = 50
        newY = 50+x
        newDir = RIGHT
    elif x==0 and 100<=y<150 and dirIndex==LEFT:#i
        # print("i")
        newX = 50
        newY = 149-y
        newDir = RIGHT
    elif x==99 and 100<=y<150 and dirIndex==RIGHT:#j
        # print("j")
        newX = 149
        newY = 149-y
        newDir = LEFT
    elif x==0 and 150<=y<200 and dirIndex==LEFT:#k
        # print("k")
        newY=0
        newX = y-100
        newDir = DOWN
    elif x==49 and 150<=y<200 and dirIndex==RIGHT: #l
        # print("l")
        newX = y - 100
        newY = 149
        newDir = UP
    elif y==149 and 50<=x<100 and dirIndex == DOWN: #m
        # print("m")
        newX = 49
        newY = x+100
        newDir = LEFT
    elif y==199 and 0<=x<50 and dirIndex == DOWN: #n
        # print("a")
        newY=0
        newX = x + 100
        newDir = DOWN
    else:
        # print("No edge hit")
        newY,newX = y+dirs[dirIndex][0],x+dirs[dirIndex][1]

    return (newY,newX), newDir

def part2():
    inp = open("Day 22.txt").read().split("\n\n")
    field = inp[0].split('\n')

    instructions = []
    i = 0
    while i < len(inp[1]):
        if inp[1][i]=='R' or inp[1][i]=='L':
            instructions.append(inp[1][i])
            i+=1
        else:
            j=i+1
            while j<len(inp[1]) and inp[1][j]!='R' and inp[1][j]!='L':
                j+=1
            instructions.append(inp[1][i:j])
            i=j
    xStart = 0
    while field[0][xStart] == ' ':
        xStart += 1

    loc = (0,xStart)
    dir = 0

    for x in instructions:
        # print(x)
        if x=='L':
            dir = (dir-1)%4
        elif x=='R':
            dir = (dir+1)%4
        else:
            steps = int(x)
            i=0
            cont=True
            while i<steps and cont:

                newLoc,newDir = calcNextLoc2(loc,dir)
                # print(newLoc)
                if field[newLoc[0]][newLoc[1]]=='#':
                    cont = False
                else:
                    loc = newLoc
                    dir = newDir
                i += 1
    print("Day 22 part 2:",1000*(loc[0]+1)+4*(loc[1]+1)+dir)


part1()
part2()