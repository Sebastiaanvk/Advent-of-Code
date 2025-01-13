import itertools




def part1():
    #input = open("test14.txt").read().split("\n")
    #height,width = 7,11

    input = open("Day14.txt").read().split("\n")
    height,width = 103,101

    seconds = 100
    bots = []
    for ln in input:
        x = ln.split()
        x1 = x[0].split(",")
        x2 = x[1].split(",")
        bots.append([int(x1[0][2:]),int(x1[1]),int(x2[0][2:]),int(x2[1]) ])

    for sec in range(seconds):
        for i in range(len(bots)):
            bots[i][0] = (bots[i][0]+bots[i][2])%width
            bots[i][1] = (bots[i][1]+bots[i][3])%height

    quads = [0,0,0,0]

    xMiddle,yMiddle = width//2,height//2
    for bot in bots:
        x,y = bot[0],bot[1]
        if x!=xMiddle and y!=yMiddle:
            index= 0
            if x<xMiddle:
                index +=1
            if y<yMiddle:
                index += 2
            quads[index] += 1
    print("Day 14 part1: ",quads[0]*quads[1]*quads[2]*quads[3])


            

part1()

''''
def checkForTree(bots,width,height):
    minX,maxX = bots[0][0],bots[0][0]
    minY,maxY = bots[0][1],bots[0][0]
    
    for bot in bots:
        x,y=bot[0],bot[1]
        minX = min(minX,x) 
        maxX = max(maxX,x)
        minY = min(minY,y)
        maxY = max(maxY,y)

    if maxX-minX<50 and maxY-minY<50:
        return True

    return False
'''

def checkForTree(bots,width,height):
    s = set()
    totalNeighbors = 0
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    for bot in bots:
        x,y = bot[0],bot[1]
        s.add((bot[0],bot[1]))    
        for dx,dy in dirs:
            if (x+dx,y+dy) in s:
                totalNeighbors += 1
    print(totalNeighbors)

    return totalNeighbors>200

'''
def checkForTree(bots,width,height):
    top =0
    bottom = 0
    for bot in bots:
        y = bot[1]
        if y > height//2:
            bottom += 1
        else:
            top +=1
    return bottom>2.8*top
'''

def printArea(area,width,height):
    for y in range(height):
        string = "" 
        for x in range(width):
            string += str(area[y][x])
        print(string)
    print("\n\n")



def part2():
    #input = open("test14.txt").read().split("\n")
    #height,width = 7,11

    input = open("Day14.txt").read().split("\n")
    height,width = 103,101

    area = [[0 for i in range(width)] for j in range(height)]

    bots = []
    for ln in input:
        x = ln.split()
        x1 = x[0].split(",")
        x2 = x[1].split(",")
        bots.append([int(x1[0][2:]),int(x1[1]),int(x2[0][2:]),int(x2[1]) ])
        area[int(x1[1])][int(x1[0][2:])] += 1

    treeFound = False
    steps = 0
#    printArea(area,width,height)

    while not treeFound:
        for i in range(len(bots)):

            area[bots[i][1]][bots[i][0]] -= 1
            bots[i][0] = (bots[i][0]+bots[i][2])%width
            bots[i][1] = (bots[i][1]+bots[i][3])%height
            area[bots[i][1]][bots[i][0]] += 1
#        printArea(area,width,height)
        treeFound = checkForTree(bots,width,height)
        steps += 1
    printArea(area,width,height)

    print("Day 14 part2: ",steps)


            

part2()