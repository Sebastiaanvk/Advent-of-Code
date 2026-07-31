import itertools



'''
Part 2 is kinda dumb.
I just saw the grid and did it by hand.
There's a single empty node and there is a wall of very full nodes that are very big.
So I just assumed we need to move the empty spot to the up right corner and then move that data to the up left corner.

'''

def fits(a,b,infos):
    if infos[a]["Used"]== 0:
        return False
    return infos[a]["Used"]<=infos[b]["Avail"]

def part1():
    inp = open("day-22.txt").read().split('\n')[2:-1]
    infos = {}
    locs = []
    for l in inp:
        lSplit = l.split()
        l0 = lSplit[0].split('-')
        x,y = int(l0[1][1:]),int(l0[2][1:])
        size = int(lSplit[1][:-1])
        used = int(lSplit[2][:-1])
        avail = int(lSplit[3][:-1])
        usePerc = int(lSplit[4][:-1])
        infos[(x,y)] = {"Size":size,"Used":used,"Avail":avail,"Use":usePerc}
        locs.append((x,y))
    nPairs = 0
    for p1,p2 in itertools.combinations(locs,2):
        if fits(p1,p2,infos) or fits(p2,p1,infos):
            nPairs += 1
    print("Part 1: ", nPairs)

    grid = []

    for y in range(30):
        grid.append([])
        for x in range(33):
            if infos[(x,y)]["Use"] < 10:
                grid[y].append('_')
            elif infos[(x,y)]["Use"] > 90:
                grid[y].append('#')
            else:
                grid[y].append('.')
    print(grid)

    ans = 12 + 29 + 29 + 5*31
    print("Part 2:", ans)

    




part1()


