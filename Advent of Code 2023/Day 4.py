print("Part 1:", sum( list(map(lambda x: 0 if x<1 else 2**(x-1),list(map(lambda x: len(set.intersection(set(x[0].split()),set(x[1].split()))),[ (x.split(":")[1]).split("|") for x in open("Day 4.txt","r").read().split("\n")]))))))


def part2():
    sum = 0
    input = list(map(lambda x: len(set.intersection(set(x[0].split()),set(x[1].split()))),[ (x.split(":")[1]).split("|") for x in open("Day 4.txt","r").read().split("\n")]))
    dict = {}
    for i in range(len(input)):
        dict[i] = 0
    for i in range(len(input)):
        sum += 1 + dict[i]
        for j in range(i+1,i+int(input[i])+1):
            dict[j] += 1 + dict[i]

    print("Part 2:", sum)


part2()