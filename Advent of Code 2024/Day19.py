from collections import deque


def part1():
    input = open("Day19.txt").read().split("\n\n")
    patternSet = set(input[0].split(", "))
    goalPatterns = input[1].split("\n")

    maxLength = 0 
    for pattern in patternSet:
        maxLength = max(maxLength,len(pattern))
    
    nrPatternsPossible = 0
    for goalPattern in goalPatterns:
        indicesReached = set()
        queue = deque()
        queue.append(0)
        endReached= False
        while not endReached and len(queue)>0:
            nextIndex = queue.popleft()
            if nextIndex == len(goalPattern):
                endReached = True
                break
            for i in range(nextIndex,min(nextIndex+maxLength,len(goalPattern))):
                if i+1 not in indicesReached and goalPattern[nextIndex:i+1] in patternSet:
                    if i+1==len(goalPattern):
                        endReached = True
                    indicesReached.add(i+1)
                    queue.append(i+1)

        if endReached:
            nrPatternsPossible += 1

        
    print("Day 19 part1: ",nrPatternsPossible)
    
part1()


def part2():
    input = open("Day19.txt").read().split("\n\n")
    goalPatterns = input[1].split("\n")
    patternSet = set(input[0].split(", "))

    maxLength = 0 
    for pattern in patternSet:
        maxLength = max(maxLength,len(pattern))

    totalNrTowels = 0
    
    for goalPattern in goalPatterns:
        nrTowels = [0 for i in range(len(goalPattern) + 1)]
        nrTowels[0] = 1
        for i in range(len(goalPattern)):
            for j in range(i, min(len(goalPattern), i+maxLength)+1):
                if goalPattern[i:j] in patternSet:
                    nrTowels[j] += nrTowels[i]
        totalNrTowels += nrTowels[len(goalPattern)]
    print("Day 19 part2:",totalNrTowels)





part2()