

def part1(isPart2):
    inp = open("day-15.txt").read().split('\n')[:-1]
    data = []
    for i in range(len(inp)):
        line = inp[i]
        ls = line.split()
        poss = int(ls[3])
        start = int(ls[11][:-1])
        # capStart + i + 1 + start = 0 mod poss
        capStart = (2*poss-i-1-start) % poss
        data.append((capStart,poss))
    if isPart2:
        data.append((4,11))
    startTime = 0
    while True:
        allTrue = True
        for rem, m in data:
            if startTime % m != rem:
                allTrue = False
        if allTrue:
            if isPart2:
                print("Part 2:",startTime)
            else: 
                print("Part 1:",startTime)
            return
        startTime += 1
        


    


part1(False)
part1(True)