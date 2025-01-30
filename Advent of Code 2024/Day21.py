import itertools

dirMap = {
    '^':(-1,0),
    'v':(1,0),
    '>': (0,1),
    '<': (0,-1)
}

def createWalkLists(pad):
    walkLists = {}
    for sourceLoc, destLoc in itertools.product(itertools.product(range(len(pad)),range(len(pad[0]))),itertools.product(range(len(pad)),range(len(pad[0])))):
        source = pad[sourceLoc[0]][sourceLoc[1]]
        dest = pad[destLoc[0]][destLoc[1]]
        if -1 not in {source,dest}:
            dy,dx = destLoc[0]-sourceLoc[0],destLoc[1]-sourceLoc[1]
            if dy>=0:
                vert = 'v'
            else:
                vert = '^'
            if dx>=0:
                hor = '>'
            else:
                hor = '<'
            moves = [vert] * abs(dy) + [hor] * abs(dx)
            perms = itertools.permutations(moves)
            walkLists[(source,dest)] = set()
            for route in perms:
                currentY,currentX = sourceLoc[0],sourceLoc[1]
                routeAllowed = True
                for step in route:
                    currentY += dirMap[step][0]
                    currentX += dirMap[step][1]
                    if pad[currentY][currentX] == -1:
                        routeAllowed = False
                if routeAllowed:
                    walkLists[(source,dest)].add(route)
    return walkLists


def part1():
    input = open("Day21.txt").read().split("\n")
    keypad = [['7','8','9'],['4','5','6'],['1','2','3'],[-1,'0','A']]
    arrowPad = [[-1,'^','A'],['<','v','>']]
    walkListsNumpad = createWalkLists(keypad)
    walkListsArrows = createWalkLists(arrowPad)

    minStepsFirst = {}
    for (source,dest) in walkListsArrows:
        if source == dest:
            minStepsFirst[(source,dest)] = 1 
        else:
            minStepsFirst[(source,dest)] = len(next(iter(walkListsArrows[(source,dest)])))+1

    minStepsSecond = {}
    for (source,dest) in walkListsArrows:
        if source == dest:
            minStepsSecond[(source,dest)] = 1
        else:
            minSteps = 1000000
            for route in walkListsArrows[(source,dest)]:
                steps = minStepsFirst[('A',route[0])]
                for i in range(len(route)-1):
                    steps += minStepsFirst[(route[i],route[i+1])]
                steps += minStepsFirst[(route[len(route)-1],'A')]
                minSteps = min(minSteps,steps)
            minStepsSecond[(source,dest)] = minSteps

    minStepsNumpad = {}
    for (source,dest) in walkListsNumpad:
        if source == dest:
            minStepsNumpad[(source,dest)] = 1
        else:
            minSteps = 1000000
            for route in walkListsNumpad[(source,dest)]:
                steps = 0
                steps += minStepsSecond[('A',route[0])]
                for i in range(len(route)-1):
                    steps += minStepsSecond[(route[i],route[i+1])]
                steps += minStepsSecond[(route[len(route)-1],'A')]
                minSteps = min(minSteps,steps)
            minStepsNumpad[(source,dest)] = minSteps
    sum = 0
    for line in input:
        stepsNeeded = minStepsNumpad[('A',line[0])]
        for i in range(len(line)-1):
            stepsNeeded += minStepsNumpad[(line[i],line[i+1])]
        numb = int(line[:-1])
        sum += stepsNeeded*numb
    print("Day 21 part1: ",sum)


part1()


def part2():
    input = open("Day21.txt").read().split("\n")
    nrArrowPadRobots = 25
    keypad = [['7','8','9'],['4','5','6'],['1','2','3'],[-1,'0','A']]
    arrowPad = [[-1,'^','A'],['<','v','>']]
    walkListsNumpad = createWalkLists(keypad)
    walkListsArrows = createWalkLists(arrowPad)

    minStepsArrow = {}
    minStepsArrow[0] = {}
    for (source,dest) in walkListsArrows:
        if source == dest:
            minStepsArrow[0][(source,dest)] = 1 
        else:
            minStepsArrow[0][(source,dest)] = len(next(iter(walkListsArrows[(source,dest)])))+1

    for i in range(1,nrArrowPadRobots):
        minStepsArrow[i] = {}
        for (source,dest) in walkListsArrows:
            if source == dest:
                minStepsArrow[i][(source,dest)] = 1
            else:
                minSteps = 1000000000000000000
                for route in walkListsArrows[(source,dest)]:
                    steps = minStepsArrow[i-1][('A',route[0])]
                    for j in range(len(route)-1):
                        steps += minStepsArrow[i-1][(route[j],route[j+1])]
                    steps += minStepsArrow[i-1][(route[len(route)-1],'A')]
                    minSteps = min(minSteps,steps)
                minStepsArrow[i][(source,dest)] = minSteps

    minStepsNumpad = {}
    for (source,dest) in walkListsNumpad:
        if source == dest:
            minStepsNumpad[(source,dest)] = 1
        else:
            minSteps = 1000000000000000000
            for route in walkListsNumpad[(source,dest)]:
                steps = 0
                steps += minStepsArrow[nrArrowPadRobots-1][('A',route[0])]
                for j in range(len(route)-1):
                    steps += minStepsArrow[nrArrowPadRobots-1][(route[j],route[j+1])]
                steps += minStepsArrow[nrArrowPadRobots-1][(route[len(route)-1],'A')]
                minSteps = min(minSteps,steps)
            minStepsNumpad[(source,dest)] = minSteps
    sum = 0
    for line in input:
        stepsNeeded = minStepsNumpad[('A',line[0])]
        for i in range(len(line)-1):
            stepsNeeded += minStepsNumpad[(line[i],line[i+1])]
        numb = int(line[:-1])
        sum += stepsNeeded*numb
    print("Day 21 part2: ",sum)


part2()