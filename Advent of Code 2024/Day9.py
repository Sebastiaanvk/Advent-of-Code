

def part1():
    input = open("Day9.txt").read()
    memory = []
    isData = True
    dataInd = 0
    
    for c in input:
        digit = int(c)
        if isData:
            for i in range(digit):
                memory.append(dataInd)
            dataInd += 1
        else:
            for i in range(digit):
                memory.append('.')
        isData = not isData
    i, j = int(input[0]), len(memory)-1
    while i<j:
        memory[i],memory[j] = memory[j],memory[i]
        while memory[i]!='.':
            i += 1
        while memory[j]=='.':
            j -= 1
    sum = 0
    i = 0
    while(memory[i]!='.'):
        sum += i*memory[i]
        i += 1
    print("2024 Day 9 part 1: ", sum)



part1()

def part2():
    input = open("Day9.txt").read()
    memory = []
    isData = True
    dataInd = -1
    
    for c in input:
        digit = int(c)
        if isData:
            dataInd += 1
            for i in range(digit):
                memory.append(dataInd)
        else:
            for i in range(digit):
                memory.append('.')
        isData = not isData

    j = len(memory)-1

    while dataInd>=0:
        print(dataInd)
        while(memory[j]!=dataInd):
            j -= 1
        dataSize = 1
        while(j>0 and memory[j-1]==dataInd):
            j -= 1
            dataSize += 1
        
        i = 0
        placeFree = False
        while i< j :
            while memory[i]!='.' and i<j:
                i += 1
            if i>=j:
                break
            space = 1
            while memory[i+space]=='.':
                space += 1
            if space>=dataSize:
                placeFree = True
                break
            i = i+space
        if placeFree:
            for k in range(dataSize):
                memory[i+k] = dataInd
                memory[j+k] = '.'
        dataInd -= 1
    sum = 0
    for i in range(len(memory)):
        if memory[i] != '.':
            sum += i*memory[i]

    print("2024 Day 9 part 2: ", sum)



part2()

