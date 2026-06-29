

def part1():
    input = open("day-3.txt").read().split('\n')
    ans = 0
    for line in input[:-1]:
        l = list(map(int,line.split()))

        allBigger = True
        for i in range(3):
            if sum(l) <= 2*l[i]:
                allBigger = False
        if allBigger:
            ans += 1
    print("Part 1: ", ans)

part1()


def part2():
    input = list(map(lambda l: list(map(int,l.split())),open("day-3.txt").read().split('\n')[:-1]))
    ans = 0
    for y in range(0,len(input),3):
        for x in range(3):
            l = [input[y+i][x] for i in range(3)]
            allBigger = True
            for i in range(3):
                if sum(l) <= 2*l[i]:
                    allBigger = False
            if allBigger:
                ans += 1
    print("Part 2: ", ans)



part2()