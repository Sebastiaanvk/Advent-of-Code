def part1():
    input = open("Day 5.txt","r").read().split("\n\n")
    seeds = list(map(int,input[0].split()[1:]))

    for i in range(1,len(input)):
        l = list(map(lambda x: list(map(int,x.split())),input[i].split("\n")[1:]))
        for j in range(len(seeds)):
            for x in l:
                if seeds[j] in range(x[1],x[1]+x[2]):
                    seeds[j] = (seeds[j]-x[1])+x[0]
                    break
    print("Part1:", min(seeds))

part1()


def part2():
    input = open("Day 5.txt","r").read().split("\n\n")
    seeds_prim = list(map(int,input[0].split()[1:]))
    i = 0
    seeds = []
    while i<len(seeds_prim):
        seeds.append((seeds_prim[i],seeds_prim[1]))
        i += 2

    for i in range(1,len(input)):
        new_seeds = []
        l = list(map(lambda x: list(map(int,x.split())),input[i].split("\n")[1:]))
        for j in range(len(seeds)):
            start = seeds[j][0]
            length = seeds[j][1]
            for x in l:
                if start in range(x[1],x[1]+x[2]) and start+length-1 in range(x[1,x[1]+x[2]]):
 
                else if:

                else if:
        
        new_seeds
        seeds = new_seeds
    print("Part2:", min(list(map(lambda x: x[0],seeds)))

part2()