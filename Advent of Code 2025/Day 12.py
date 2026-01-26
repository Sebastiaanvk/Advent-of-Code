def part1():
    inp = open("Day 12.txt").read().split("\n\n")
    shapePips = []
    for shape in inp[:-1]:
        pips = 0
        for x in shape:
            if x=='#':
                pips+=1
        shapePips.append(pips)
    
    nrFittingRegions = 0
    for regionStr in inp[-1].split('\n'):
        region = regionStr.split()

        width,height = map(int,region[0][:-1].split('x'))
        presents = list(map(int,region[1:]))
        nrPips = sum([x*y for x,y in zip(shapePips,presents)])
        if nrPips<=width*height:
            if (width//3)*(height//3)>=sum(presents):
                nrFittingRegions += 1
            else:
                print("Unsure whether it fits. ",regionStr)
    print("Day 12 part 1:",nrFittingRegions)




part1()