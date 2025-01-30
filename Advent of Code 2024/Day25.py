import itertools


def part1():
    input = list(map(lambda x:  x.split("\n"),open("Day25.txt").read().split("\n\n")))
    keys = []
    locks = []    

    for obj in input:
        if obj[0][0] == "#":
            ls = []
            for x in range(5):
                i=0
                while obj[i+1][x]=="#":
                    i += 1
                ls.append(i)
            locks.append(tuple(ls))
        else:
            ls = []
            for x in range(5):
                i=0
                while obj[5-i][x]=="#":
                    i += 1
                ls.append(i)
            keys.append(tuple(ls))

    sum = 0
    for key,lock in itertools.product(keys,locks):
        fits = True
        for i in range(5):
            if key[i]+lock[i]>5:
                fits = False
        if fits:
            sum += 1
    print("Day 25 part1:",sum)
        
part1()
