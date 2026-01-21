def inRanges(x,ranges):
    for (l,r) in ranges:
        if x>=l and x<=r:
            return True
    return False
    
def part1():
    
    inp = open("Day 5.txt").read().split("\n\n")
    ranges = [(int(x[0]),int(x[1])) for x in list(map( lambda y: y.split("-")  ,inp[0].split()))]
    nrs = list(map(int,inp[1].split()))

    count = 0

    for xStr in nrs:
        x = int(xStr)
        if inRanges(x,ranges):
            count += 1

    print("Day 5 part 1:",count)


def part2():
    
    inp = open("Day 5.txt").read().split("\n\n")
    ranges = [(int(x[0]),int(x[1])) for x in list(map( lambda y: y.split("-")  ,inp[0].split()))]
    ranges.sort(key = lambda x:x[0])
    currentLeft, currentRight = -1,-1
    i = 0
    effRanges = []
    while(i<len(ranges)):
        currentLeft = ranges[i][0]
        currentRight = ranges[i][1]
        j = i+1
        while j<len(ranges) and ranges[j][0]<=currentRight:
            currentRight = max(currentRight,ranges[j][1])
            j+=1
        effRanges.append((currentLeft,currentRight))
        i = j

    count = 0
    for range in effRanges:
        count += range[1]-range[0]+1



    print("Day 5 part 2:",count)


part1()
part2()