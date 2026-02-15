def calcLoadPart1(field):
    sum = 0
    for col in range(len(field[0])):
        rocks = 0
        for row in range(len(field)-1,-1,-1):
            if field[row][col]=='O':
                rocks += 1
            elif field[row][col]=='#':
                for j in range(row+1,row+rocks+1):
                    sum += len(field)-j
                rocks = 0
        for j in range(rocks):
            sum += len(field)-j
    return sum


def part1():
    with open("Day 14.txt") as f:
        field = f.read().split('\n')
        print("Day 14 part 1:",calcLoadPart1(field))

def moveNorth(field):
    for col in range(len(field[0])):
        rocks = 0
        for row in range(len(field)-1,-1,-1):
            if field[row][col]=='O':
                field[row][col] = '.'
                rocks+=1
            elif field[row][col]=='#':
                for j in range(row+1,row+rocks+1):
                    field[j][col] = 'O'
                rocks = 0
        for j in range(rocks):
            field[j][col] = 'O'

def moveWest(field):
    for row in range(len(field)):
        rocks = 0
        for col in range(len(field[0])-1,-1,-1):
            if field[row][col]=='O':
                field[row][col] = '.'
                rocks += 1
            elif field[row][col]=='#':
                for j in range(col+1,col+rocks+1):
                    field[row][j] = 'O'
                rocks = 0
        for j in range(rocks):
            field[row][j] = 'O'

def moveSouth(field):
    for col in range(len(field[0])):
        rocks = 0
        for row in range(0,len(field)):
            if field[row][col]=='O':
                field[row][col] = '.'
                rocks += 1
            elif field[row][col]=='#':
                for j in range(row-1,row-1-rocks,-1):
                    field[j][col] = 'O'
                rocks = 0
        for j in range(rocks):
            field[len(field)-1-j][col] = 'O'

def moveEast(field):
    for row in range(len(field)):
        rocks = 0
        for col in range(len(field[0])):
            if field[row][col]=='O':
                field[row][col] = '.'
                rocks += 1
            elif field[row][col]=='#':
                for j in range(col-rocks,col):
                    field[row][j] = 'O'
                rocks = 0
        for j in range(rocks):
            field[row][len(field)-1-j] = 'O'

# def rotatedField(field):
#     newField = []
#     for i in range(len(field[0])):
#         newField.append([field[row][i] for row in range(len(field)-1,-1,-1 )])
#     return newField

def calcLoad(field):
    sum = 0
    for row in range(len(field)):
        for col in range(len(field[0])):
            if field[row][col]=='O':
                sum += len(field)-row

    return sum



def part2():
    with open("Day 14.txt") as f:
        fieldStr = f.read().split('\n')
        field = []
        for line in fieldStr:
            field.append([c for c in line])
        
        seqCheckLength = 5  
        valList = []
        for i in range(200):
            moveNorth(field)
            moveWest(field)
            moveSouth(field)
            moveEast(field)
            valList.append(calcLoad(field))
            # for j in range(4):
            #     moveNorth(field)
            #     field = rotatedField(field)
        # print(valList)
        seqLength = 1
        overlap = False
        while not overlap:
            seqLength += 1
            if valList[len(valList)-seqLength-5:len(valList)-seqLength] == valList[len(valList)-5:len(valList)]:
                overlap=True
        # print(seqLength)
        print("Day 14 part 2:",valList[len(valList)-1-seqLength + (1000000000-200)%seqLength])
            



part1()
part2()