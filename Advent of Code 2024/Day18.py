from collections import deque


def part1():

    input = open("Day18.txt").read().split("\n")
    goalY,goalX = 70,70


    bytes = set()
    for i in range(1024):
        y,x = input[i].split(",")
        bytes.add((int(y),int(x)))

    fieldsVisited = set()

    dirs = [(0,1),(0,-1),(1,0),(-1,0)]

    queue = deque() 
    queue.append(((0,0),0))
    goalFound = False
    stepsNeeded = 0
    while(not goalFound):
        ((y,x),steps) = queue.popleft()
        if (y,x) == (goalY,goalX):
            goalFound = True
            stepsNeeded = steps
            break
        for dy,dx in dirs:
            newY,newX = y+dy, x+dx
            if 0<=newY<=goalY and 0<=newX<=goalX and (newY,newX) not in fieldsVisited and (newY,newX) not in bytes:
                queue.append(((newY,newX),steps+1))
                fieldsVisited.add((newY,newX))

    
    print("Day 18 part1: ", stepsNeeded)


part1()




def part2():

    input = open("Day18.txt").read().split("\n")
    goalY,goalX = 70,70

    dirs = [(0,1),(0,-1),(1,0),(-1,0)]

    iterationNoPath = 0

    for j in range(1024, len(input)-1):
        print(j)
        bytes = set()
        for i in range(j+1):
            y,x = input[i].split(",")
            bytes.add((int(y),int(x)))

        fieldsVisited = set()


        queue = deque() 
        queue.append((0,0))
        goalFound = False
        while(len(queue)):
            (y,x) = queue.popleft()
            if (y,x) == (goalY,goalX):
                goalFound = True
                break
            for dy,dx in dirs:
                newY,newX = y+dy, x+dx
                if 0<=newY<=goalY and 0<=newX<=goalX and (newY,newX) not in fieldsVisited and (newY,newX) not in bytes:
                    queue.append((newY,newX))
                    fieldsVisited.add((newY,newX))
        if not goalFound:
            iterationNoPath = j
            print("j:",j)
            break
    
    print("Day 18 part2: ", input[iterationNoPath])


part2()