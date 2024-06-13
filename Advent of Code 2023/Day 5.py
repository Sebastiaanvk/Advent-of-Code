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
    #input = open("test5.txt","r").read().split("\n\n")

    seeds_prim = list(map(int,input[0].split()[1:]))
    i = 0
    seeds = []
    while i<len(seeds_prim):
        seeds.append((seeds_prim[i],seeds_prim[i]+seeds_prim[i+1]-1))
        i += 2
    print(seeds)
    for i in range(1,len(input)):
        l = list(map(lambda x: list(map(int,x.split())),input[i].split("\n")[1:]))
        processed_seeds = []
        for window in l:
            next_current_seeds = []
            left = window[1]
            right = left + window[2]-1
            augment = window[0]-window[1]
            for p in seeds:
                x,y = p[0],p[1]
                if y<left or x >right:
                    next_current_seeds.append(  (x,y))
                elif x<left and y<=right:
                    next_current_seeds.append((x,left-1))
                    processed_seeds += [(left+augment,y+augment)]
                elif x>=left and y<= right:
                    processed_seeds += [(x+augment,y+augment)]
                elif x<left and y>right:
                    processed_seeds += [(left+augment,right+augment)]
                    next_current_seeds += [(x,left-1)]
                    next_current_seeds += [(right+1,y)]
                elif x>=left and y>right:
                    processed_seeds += [(x+augment,right+augment)]
                    next_current_seeds += [(right+1,y)]
            seeds = next_current_seeds
        seeds += processed_seeds
    print("Part2:", min(list(map(lambda x: x[0],seeds))))

part2()