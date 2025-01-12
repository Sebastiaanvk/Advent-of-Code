import itertools

dirs = [(0,1),(1,0),(0,-1),(-1,0)]

nrPaths = 0
height,width = 0,0
area = open("Day10.txt").read().split("\n")
#area = open("test10.txt").read().split("\n")

def dfs(currentY, currentX, value,endSet):
    if value==9:
        endSet.add((currentY,currentX))
        return
    for dy,dx in dirs:
        newY,newX = currentY+dy,currentX+dx
        if 0<=newY<height and 0<=newX<width and int(area[newY][newX])==value+1:
            dfs(newY,newX, int(area[newY][newX]),endSet)

def part1():
    nrPaths = 0
    global height, width
    height = len(area)
    width = len(area[0])

    for (y,x) in itertools.product(range(height),range(width)):
        if area[y][x] == '0':
            endSet = set()
            dfs(y,x,0,endSet)
            nrPaths += len(endSet)

    print("Day10 part1: ", nrPaths)

part1()

def dfs2(currentY, currentX, value):
    if value==9:
        global nrPaths
        nrPaths += 1
        return
    for dy,dx in dirs:
        newY,newX = currentY+dy,currentX+dx
        if 0<=newY<height and 0<=newX<width and int(area[newY][newX])==value+1:
            dfs2(newY,newX, int(area[newY][newX]))

def part2():
    global nrPaths
    nrPaths = 0
    global height, width
    height = len(area)
    width = len(area[0])

    for (y,x) in itertools.product(range(height),range(width)):
        if area[y][x] == '0':
            dfs2(y,x,0)

    print("Day10 part2: ", nrPaths)

part2()
