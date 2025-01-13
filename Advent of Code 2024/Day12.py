import itertools

dirs = [(1,0),(-1,0),(0,1),(0,-1)]



def fillNewArea(area,newArea,y,x,newValue,originalAreaValue,height,width):
    if newArea[y][x]!=0:
        return
    newArea[y][x] = newValue
    for dy,dx in dirs:
        if 0<=y+dy<height and 0<=x+dx<width and area[y+dy][x+dx]==originalAreaValue:
            fillNewArea(area,newArea,y+dy,x+dx,newValue, originalAreaValue, height, width)

def part1():
    area = open("Day12.txt").read().split("\n")
    #area = open("test12.txt").read().split("\n")

    height, width = len(area),len(area[0])

    areas = {}
    perimeters = {}

    newArea = [ [0 for i in range(width) ] for j in range(height)] 
    newValue = 1
    for y,x in  itertools.product(range(height),range(width)):
        if newArea[y][x]==0:
            fillNewArea(area,newArea,y,x,newValue,area[y][x],height,width)
            newValue += 1


    for y,x in itertools.product(range(height),range(width)):



        flower = newArea[y][x]
        areas[flower] = areas.get(flower,0) + 1
        for dy,dx in dirs:
            if y+dy<0 or y+dy>=height or x+dx<0 or x+dx>=width or newArea[y+dy][x+dx]!=flower:
                perimeters[flower] = perimeters.get(flower,0) + 1

    sum = 0     
    for key in areas:
#        print(key, areas[key],perimeters[key])
        sum += areas[key]*perimeters[key]

    print("Day 12 part1: ", sum)

part1()

"""
Explanation:
I only count the edges that dont extend further to the left or up.
So for example, if we have a horizontal edge, then we only count it if it doesn't have a horizontal edge
to the left the is part of the same region.
This way we make sure that for every line, we only count the leftmost or the highest edge


"""
def part2():
    area = open("Day12.txt").read().split("\n")
    #area = open("test12.txt").read().split("\n")

    height, width = len(area),len(area[0])

    areas = {}
    lines = {}

    newArea = [ [0 for i in range(width) ] for j in range(height)] 
    newValue = 1
    for y,x in  itertools.product(range(height),range(width)):
        if newArea[y][x]==0:
            fillNewArea(area,newArea,y,x,newValue,area[y][x],height,width)
            newValue += 1

    for y,x in itertools.product(range(height),range(width)):

        flower = newArea[y][x]
        areas[flower] = areas.get(flower,0) + 1
        
        for dy,dx in dirs:
            if dy==0:
                if x+dx<0 or x+dx>=width or newArea[y][x+dx]!=flower:
                    if y==0 or newArea[y-1][x]!=flower or (0<=x+dx<width and newArea[y-1][x+dx]==flower):
                        lines[flower] = lines.get(flower,0)+1
            else:
                if y+dy<0 or y+dy>=height or newArea[y+dy][x]!=flower:
                    if x==0 or newArea[y][x-1]!=flower or (0<=y+dy<height and newArea[y+dy][x-1]==flower):
                        lines[flower] = lines.get(flower,0)+1

    sum = 0     
    for key in areas:
#        print(key, areas[key],lines[key])
        sum += areas[key]*lines[key]

    print("Day 12 part2: ", sum)

part2()