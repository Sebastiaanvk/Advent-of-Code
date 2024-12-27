from collections import defaultdict
import itertools

def part1():
    input = open('Day5.txt').read().split("\n\n")

    ordermap = defaultdict(set) 

    for line in input[0].split():
        s = line.split( '|')
        ordermap[int(s[0])].add(int(s[1]))

    sum = 0

    for line in input[1].split():
        legalLine = True
        s = list(map(int, line.split(',') ))

        for (x,y) in list(itertools.combinations(s,2)):
            if x in ordermap[y]:
                legalLine = False
                break
        if legalLine:
            sum += s[len(s)//2]

    print("2024 Day 5 part 1: ", sum)


part1()

def part2():
    input = open('Day5.txt').read().split("\n\n")

    ordermap = defaultdict(set) 

    for line in input[0].split():
        s = line.split( '|')
        ordermap[int(s[0])].add(int(s[1]))

    sum = 0

    for line in input[1].split():
        legalLine = True
        s = list(map(int, line.split(',') ))

        for (x,y) in list(itertools.combinations(s,2)):
            if x in ordermap[y]:
                legalLine = False
                break
        if not legalLine:
            for i in range(len(s)):
                j=i+1
                while j < len(s):
                    if s[i] in ordermap[s[j]]:
                        s[i], s[j] = s[j], s[i]
                        j = i+1
                    else:
                        j += 1
            sum += s[len(s)//2]

    print("2024 Day 5 part 2: ", sum)


part2()