import itertools
import bisect

def part1(gapDist):
    inp = open("Day 11.txt").read().split("\n")
    height,width = len(inp),len(inp[0])
    galaxies = []
    nonEmptyRows = set()
    nonEmptyColumns = set()
    for y,x in itertools.product(range(height),range(width)):
        if inp[y][x] == '#':
            galaxies.append((y,x))
            nonEmptyRows.add(y)
            nonEmptyColumns.add(x)
    emptyRows = []
    emptyCols = []
    for row in range(height):
        if row not in nonEmptyRows:
            emptyRows.append(row)
    
    for col in range(width):
        if col not in nonEmptyColumns:
            emptyCols.append(col)
    totalDist = 0
    for i in range(len(galaxies)):
        for j in range(i+1,len(galaxies)):
            (y0,x0),(y1,x1) = galaxies[i],galaxies[j]
            totalDist += abs(y1-y0) + abs(x1-x0) 
            totalDist += gapDist*(bisect.bisect_right(emptyCols, max(x0,x1)) - bisect.bisect_left(emptyCols, min(x0,x1)))
            totalDist += gapDist*(bisect.bisect_right(emptyRows, max(y0,y1)) - bisect.bisect_left(emptyRows, min(y0,y1)))
    return totalDist

print("Day 11 part 1:",part1(1))
print("Day 11 part 2:", part1(999999))
