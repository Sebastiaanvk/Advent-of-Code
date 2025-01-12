

input = open("Day11.txt").read().split(" ")
#input = open("test11.txt").read().split(" ")



def part1():
    nrIterations = 25
    ls = list(map(int, input))
    print(ls)
    for i  in range(nrIterations):
        newLs = []
        for nr in ls:
            if nr == 0:
                newLs.append(1)
            elif len(str(nr)) % 2 ==0: 
                st = str(nr)
                length = len(st)
                newLs.append(int(st[0:length//2]))
                newLs.append(int(st[length//2:]))
            else:
                newLs.append(nr*2024)
        ls = newLs

    print("Day11 part1: ", len(ls))

part1()


nrAndIterationsSize = {}

def dfs(number, iterationsLeft):
    if iterationsLeft ==0:
          return 1
    if (number,iterationsLeft) in nrAndIterationsSize:
        return nrAndIterationsSize[(number,iterationsLeft)]

    nrStones = 0

    if number == 0:
        nrStones = dfs(1,iterationsLeft-1)

    elif len(str(number)) % 2 ==0: 
        st = str(number)
        length = len(st)
        nr1 = int(st[0:length//2])
        nr2 = int(st[length//2:])
        nrStones = dfs(nr1,iterationsLeft-1) + dfs(nr2,iterationsLeft-1)
    else:
        nrStones = dfs(number*2024,iterationsLeft-1)
    
    nrAndIterationsSize[(number,iterationsLeft)] = nrStones
    return nrStones
    
def part2():
    nrIterations = 75
    ls = list(map(int, input))
    nrStones = 0
    for nr in ls:
        nrStones += dfs(nr,75)

    print("Day11 part2: ", nrStones)

part2()