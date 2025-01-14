import heapq
import itertools


dirs = [(0,1),(1,0),(0,-1),(-1,0)]


def part1():
    field = open("Day16.txt").read().split("\n")

    #field = open("test16.txt").read().split("\n")
    height,width = len(field), len(field[0])
    goalFound = False
    steps = 0
    startY,startX = 0,0
    goalY,goalX = 0,0
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x]=="S":
            startY,startX = y,x
        if field[y][x]=="E":
            goalY,goalX = y,x

    minDist = {}
    prioQueue = []
    # dist, coordinates, direction
    heapq.heappush(prioQueue, (0,startY,startX,0) )

    while not goalFound:
        dist, y, x, dir = heapq.heappop(prioQueue)  
#        print(dist,y,x,dir)
        if (y,x)==(goalY,goalX):
            goalFound = True
            steps = dist
        elif not (y,x,dir) in minDist:
            minDist[(y,x,dir)] = dist
            dy,dx = dirs[dir]
            if field[y+dy][x+dx] == "." or field[y+dy][x+dx] == "E":
                if (y+dy,x+dx,dir) not in minDist or minDist[(y+dy,x+dx,dir)]>dist+1:
                    heapq.heappush(prioQueue, (dist+1,y+dy,x+dx,dir)) 




            for i in range(1,4):
                newDir = (dir+i)%4
                dy,dx = dirs[newDir] 
                newY,newX = y+dy,x+dx
                if field[newY][newX] == "." or field[newY][newX]=="E":
                    newDist = dist
                    if i==1 or i==3:
                        newDist += 1000
                    elif i==2:
                        newDist += 2000
                    if (y,x,newDir) not in minDist or minDist[(y,x,newDir)]>newDist:
                        heapq.heappush(prioQueue, (newDist,y,x,newDir)) 






    print("Day16 part1: ",steps)




part1()


def part2():
    field = open("Day16.txt").read().split("\n")

    #field = open("test16.txt").read().split("\n")
    height,width = len(field), len(field[0])
    goalFound = False
    steps = 0
    startY,startX = 0,0
    goalY,goalX = 0,0
    for y,x in itertools.product(range(height),range(width)):
        if field[y][x]=="S":
            startY,startX = y,x
        if field[y][x]=="E":
            goalY,goalX = y,x

    minDist = {}
    prioQueue = []
    # dist, coordinates, direction
    heapq.heappush(prioQueue, (0,startY,startX,0) )

    while not goalFound:
        dist, y, x, dir = heapq.heappop(prioQueue)  
#        print(dist,y,x,dir)
        if (y,x)==(goalY,goalX):
            goalFound = True
            steps = dist
        elif not (y,x,dir) in minDist:
            minDist[(y,x,dir)] = dist
            dy,dx = dirs[dir]
            if field[y+dy][x+dx] == "." or field[y+dy][x+dx] == "E":
                if (y+dy,x+dx,dir) not in minDist or minDist[(y+dy,x+dx,dir)]>dist+1:
                    heapq.heappush(prioQueue, (dist+1,y+dy,x+dx,dir)) 




            for i in range(1,4):
                newDir = (dir+i)%4
                dy,dx = dirs[newDir] 
                newY,newX = y+dy,x+dx
                if field[newY][newX] == "." or field[newY][newX]=="E":
                    newDist = dist
                    if i==1 or i==3:
                        newDist += 1000
                    elif i==2:
                        newDist += 2000
                    if (y,x,newDir) not in minDist or minDist[(y,x,newDir)]>newDist:
                        heapq.heappush(prioQueue, (newDist,y,x,newDir)) 

    
    setGoodSquaresDirs = set()
    for i in range(4):
        setGoodSquaresDirs.add((steps, goalY,goalX,i))

    goodSquareAdded = True


    
    while goodSquareAdded:
        goodSquareAdded = False
        for (y,x,dir) in minDist:
            dist = minDist[(y,x,dir)]
            if (dist,y,x,dir) not in setGoodSquaresDirs:
                dy,dx = dirs[dir]
                if field[y+dy][x+dx] != "#":
                    if (dist+1,y+dy,x+dx,dir) in setGoodSquaresDirs:
                        setGoodSquaresDirs.add((dist,y,x,dir))
                        goodSquareAdded = True
                for i in range(1,4):
                    extra = 1000
                    if i==2:
                        extra =2000
                    if (dist+extra,y,x,(dir+i)%4) in setGoodSquaresDirs:
                        setGoodSquaresDirs.add((dist,y,x,dir))
                        goodSquareAdded = True

    setGoodSquares = set()

    newField = [[ c for c in ln] for ln in field]

    for (dist,y,x,dir) in setGoodSquaresDirs:
        setGoodSquares.add((y,x))
        newField[y][x] = "O"
    
#    for ln in newField:
#        print(ln)



    print("Day16 part2: ",len(setGoodSquares))




part2()