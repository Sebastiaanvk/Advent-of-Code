import itertools


def part1():
    area = open("Day8.txt").read().split("\n")
    height, width = len(area), len(area[0])
    antinodes = set()
    antennaLocs = {}
    for y,x in itertools.product(range(height),range(width)):
        antenna = area[y][x]
        if antenna !='.':
            if antenna in antennaLocs:
                antennaLocs[antenna].append((y,x))
            else:
                antennaLocs[antenna] = [(y,x)]
    for key in antennaLocs:
        ls = antennaLocs[key]
        for (y,x),(w,v) in itertools.combinations(ls,2):
            if 0<=2*w-y<height and 0<=2*v-x<width:
                antinodes.add((2*w-y,2*v-x))
            if 0<=2*y-w<height and 0<=2*x-v<width:
                antinodes.add((2*y-w,2*x-v))
    print("2024 Day 8 part 1: ", len(antinodes))




part1()

def part2():
    area = open("Day8.txt").read().split("\n")
    height, width = len(area), len(area[0])
    antinodes = set()
    antennaLocs = {}
    for y,x in itertools.product(range(height),range(width)):
        antenna = area[y][x]
        if antenna !='.':
            if antenna in antennaLocs:
                antennaLocs[antenna].append((y,x))
            else:
                antennaLocs[antenna] = [(y,x)]
    for key in antennaLocs:
        ls = antennaLocs[key]
        for (y,x),(w,v) in itertools.combinations(ls,2):
            dy, dx = y-w, x-v
            i=0
            while 0<=y+i*dy<height and 0<=x+i*dx<width:
                antinodes.add((y+i*dy,x+i*dx))
                i += 1
            i=-1
            while 0<=y+i*dy<height and 0<=x+i*dx<width:
                antinodes.add((y+i*dy,x+i*dx))
                i -= 1
   

    print("2024 Day 8 part 2: ", len(antinodes))

part2()