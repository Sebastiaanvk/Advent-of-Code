import itertools
from collections import deque

dirs = [(1,0),(0,-1),(-1,0),(0,1)]

def part1():
    field = open("Day20.txt").read().split("\n")
    start,end = (0,0),(0,0)
    height,width = len(field),len(field[0])
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x] == "S":
            start = (y,x)
        if field[y][x] == "E":
            end = (y,x)
    distFromStart = {}
    queue = deque([start])
    distFromStart[start] = 0
    while len(queue) !=0:
        (y,x) = queue.popleft() 
        for dy,dx in dirs:
            newY,newX = y+dy,x+dx
            if field[newY][newX] != "#" and (newY,newX) not in distFromStart:
                distFromStart[(newY,newX)] = distFromStart[(y,x)]+1
                queue.append((newY,newX))

    distFromEnd = {}
    queue = deque([end])
    distFromEnd[end] = 0
    while len(queue) !=0:
        (y,x) = queue.popleft() 
        for dy,dx in dirs:
            newY,newX = y+dy,x+dx
            if field[newY][newX] != "#" and (newY,newX) not in distFromEnd:
                distFromEnd[(newY,newX)] = distFromEnd[(y,x)]+1
                queue.append((newY,newX))

    normalStepsNeeded = distFromStart[end] 
    goodShortcuts = 0
    for y,x in itertools.product(range(height),range(width)):
        if (y,x) in distFromStart: 
            for dy,dx in dirs:
                if 0<=y+2*dy<height and 0<=x+2*dx<width:
                    if field[y+dy][x+dx] == "#" and field[y+2*dy][x+2*dx] != "#" and (y+2*dy,x+2*dx) in distFromEnd:
                        stepsNeeded = distFromStart[(y,x)] + distFromEnd[(y+2*dy,x+2*dx)] + 2
                        if normalStepsNeeded-stepsNeeded>=100:
                            goodShortcuts += 1
    print("Day 20 part1:",goodShortcuts)

part1()



def part2():
    field = open("Day20.txt").read().split("\n")
    start,end = (0,0),(0,0)
    height,width = len(field),len(field[0])
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x] == "S":
            start = (y,x)
        if field[y][x] == "E":
            end = (y,x)
    distFromStart = {}
    queue = deque([start])
    distFromStart[start] = 0
    while len(queue) !=0:
        (y,x) = queue.popleft() 
        for dy,dx in dirs:
            newY,newX = y+dy,x+dx
            if field[newY][newX] != "#" and (newY,newX) not in distFromStart:
                distFromStart[(newY,newX)] = distFromStart[(y,x)]+1
                queue.append((newY,newX))

    distFromEnd = {}
    queue = deque([end])
    distFromEnd[end] = 0
    while len(queue) !=0:
        (y,x) = queue.popleft() 
        for dy,dx in dirs:
            newY,newX = y+dy,x+dx
            if field[newY][newX] != "#" and (newY,newX) not in distFromEnd:
                distFromEnd[(newY,newX)] = distFromEnd[(y,x)]+1
                queue.append((newY,newX))

    normalStepsNeeded = distFromStart[end] 
    goodShortcuts = 0
    for y,x in itertools.product(range(height),range(width)):
        if (y,x) in distFromStart: 
            for dx in range(-20,21):
                absDy = 20 - abs(dx)
                for dy in range(-absDy,absDy+1):
                    if 0<=y+dy<height and 0<=x+dx<width:
                        if field[y+dy][x+dx] != "#" and (y+dy,x+dx) in distFromEnd:
                            stepsNeeded = distFromStart[(y,x)] + distFromEnd[(y+dy,x+dx)] + abs(dx)+ abs(dy)  
                            if normalStepsNeeded-stepsNeeded>=100:
                                goodShortcuts += 1
    print("Day 20 part2:",goodShortcuts)

part2()