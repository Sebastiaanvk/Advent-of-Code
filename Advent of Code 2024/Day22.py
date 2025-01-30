

def getNextSecretNumber(x):
    prune = 16777216
    y = 64*x
    x = (x^y)%prune

    y = x // 32
    x = (x^y)%prune

    y = 2048*x
    x = (x^y)%prune
    return x

def part1():
    input = list(map(int,open("Day22.txt").read().split("\n")))
#    input = [1,10,100,2024]

    sum = 0
    for x in input:
        y = x
        for i in range(2000):
            y = getNextSecretNumber(y)
        sum += y

    print("Day 22 part1:",sum)


part1()


def part2():
    input = list(map(int,open("Day22.txt").read().split("\n")))
#    input = [1,10,100,2024]

    totalBananasChange = {}

    for x in input:
        ls = [x%10]
        y = x
        for i in range(2000):
            y = getNextSecretNumber(y)
            ls.append(y%10)
        i=0
        changesSeen = set()
        while i+4<len(ls):
            changes = (ls[i+1]-ls[i],ls[i+2]-ls[i+1],ls[i+3]-ls[i+2],ls[i+4]-ls[i+3])
            if changes not in changesSeen:
                changesSeen.add(changes)
                totalBananasChange[changes] = totalBananasChange.get(changes,0)+ls[i+4]

            i += 1
        
    maxBananas = 0
    for key in totalBananasChange:
        maxBananas = max(maxBananas,totalBananasChange[key])
    print("Day 22 part 2:",maxBananas)

part2()