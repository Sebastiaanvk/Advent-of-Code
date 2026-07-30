

def part1():
    inp = open("day-20.txt").read().split("\n")[:-1]
    intervals = []
    for s in inp:
        sSplit = s.split("-")
        intervals.append((int(sSplit[0]),int(sSplit[1])))
    intervals.sort(key=lambda x:x[0])  
    minAllowed = 0
    index = 0
    while(intervals[index][0]<=minAllowed):
        minAllowed = max(minAllowed,intervals[index][1]+1)
        index += 1
    print("Part 1: ", minAllowed)
part1()

def part2():
    inp = open("day-20.txt").read().split("\n")[:-1]
    intervals = []
    for s in inp:
        sSplit = s.split("-")
        intervals.append((int(sSplit[0]),int(sSplit[1])))
    intervals.sort(key=lambda x:x[0])  
    allowedIntervals = [(0,4294967295)]
    for (x,y) in intervals:
        allowedIntervalsCopy = []
        for (l,r) in allowedIntervals:
            if r<x or l>y:
                allowedIntervalsCopy.append((l,r))
            else:
                if l<x:
                    allowedIntervalsCopy.append((l,x-1))
                if r>y:
                    allowedIntervalsCopy.append((y+1,r))
        allowedIntervals = allowedIntervalsCopy
    totalAllowed = 0
    for (x,y) in allowedIntervals:
        totalAllowed += 1+y-x
    print("Part 2: ", totalAllowed)
part2()