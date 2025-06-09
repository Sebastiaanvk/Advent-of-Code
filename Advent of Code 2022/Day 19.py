

def maxGeodes(state, prices, maxGeodesTable):
    if state in maxGeodesTable:
        return maxGeodesTable[state]
    

def maxGeodes(prices):
    maxGeodesTable = {}



def part1():
    sum = 0
    for x in open("Day 19.txt","r").read().split("\n"):
        line = x.split(" ")
        index = int(line[1][:-1])
        prices = [
            (int(line[6]),0,0),
            (int(line[12]),0,0),
            (int(line[18]),int(line[21]),0),
            (int(line[27]),0,int(line[30]))
        ]
        sum += index*maxGeodes(prices)
    print("Day 19 part 1: ",sum)

part1()