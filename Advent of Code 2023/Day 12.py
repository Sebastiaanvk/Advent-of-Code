def minRemainingLength(contiguousGroups,j):
    return sum(contiguousGroups[j:]) + len(contiguousGroups)-1-j

def canFit(line, contiguousGroups,i,j):
    if i+contiguousGroups[j]>len(line):
        return False
    for k in range(i,i+contiguousGroups[j]):
        if line[k]=='.':
            return False
    if i+contiguousGroups[j] < len(line) and line[i+contiguousGroups[j]]=='#':
        return False
    return True


def calcPoss(line, contiguousGroups,i,j):
    if j==len(contiguousGroups):
        for k in range(i,len(line)):
            if line[k]=='#':
                return 0
        return 1
    if minRemainingLength(contiguousGroups,j) > len(line)-i:
        return 0
    if line[i]=='.':
        return calcPoss(line,contiguousGroups,i+1,j)
    elif line[i]=='#':
        if canFit(line,contiguousGroups,i,j):
            return calcPoss(line,contiguousGroups,i+contiguousGroups[j]+1,j+1)    
        else:
            return 0
    else:
        if canFit(line,contiguousGroups,i,j):
            return calcPoss(line,contiguousGroups,i+contiguousGroups[j]+1,j+1) +calcPoss(line,contiguousGroups,i+1,j)
        else:
            return calcPoss(line,contiguousGroups,i+1,j)

def part1():
    totalPoss = 0
    with open("Day 12.txt") as f:
        for line in f.read().split('\n'):
            l = line.split(" ")
            totalPoss += calcPoss(l[0],list(map(int,l[1].split(','))),0,0)
            # print(calcPoss(l[0],list(map(int,l[1].split(','))),0,0))
    print("Day 12 part 1:",totalPoss)



def calcPossFiveRec(calcDict, line, contiguousGroups, i, j):
    # print(i,j)
    if (i,j) in calcDict:
        return calcDict[(i,j)]
    result = 0
    # print(len(line),len(contiguousGroups), i, j)
    if i>=len(line):
        if j<len(contiguousGroups):
            result = 0
        else:
            result = 1
    elif j==len(contiguousGroups):
        if line[i] != '#':
            result = calcPossFiveRec(calcDict, line, contiguousGroups, i+1,j)
        else:
            result = 0
    elif minRemainingLength(contiguousGroups,j) > len(line)-i:
        # print("niet genoeg plek")
        result = 0
    elif line[i]=='.':
        result = calcPossFiveRec(calcDict,line,contiguousGroups,i+1,j)
    elif line[i]=='#':
        if canFit(line,contiguousGroups,i,j):
            result = calcPossFiveRec(calcDict, line,contiguousGroups,i+contiguousGroups[j]+1,j+1)    
        else:
            result = 0
    else:
        if canFit(line,contiguousGroups,i,j):
            result = calcPossFiveRec(calcDict,line,contiguousGroups,i+contiguousGroups[j]+1,j+1) +calcPossFiveRec(calcDict,line,contiguousGroups,i+1,j)
        else:
            result = calcPossFiveRec( calcDict,line,contiguousGroups,i+1,j)

    calcDict[(i,j)] = result
    return result



def calcPossFive(line, contiguousGroups):
    fullString = line
    fullGroups = contiguousGroups.copy()
    for i in range(4):
        fullString += "?" + line
        fullGroups += contiguousGroups
    # print(fullString, fullGroups)
    
    calcDict = {}
    calcDict[(len(fullString),len(fullGroups))] = 1

    answer =  calcPossFiveRec(calcDict,fullString,fullGroups,0,0)
    # print(calcDict)
    return answer



def part2():
    totalPoss = 0
    with open("Day 12.txt") as f:
        for line in f.read().split('\n'):
            l = line.split(" ")
            totalPoss += calcPossFive(l[0],list(map(int,l[1].split(','))))
            # print(calcPossFive(l[0],list(map(int,l[1].split(',')))))
            # break
            # dict = {}
            # print(calcPossFiveRec(dict,l[0],list(map(int,l[1].split(','))),0,0))
    print("Day 12 part 2:",totalPoss)


part1()
part2()