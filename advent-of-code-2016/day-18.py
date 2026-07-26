


def part1():
    inp = open("day-18.txt").read()[:-1]
    nrRows = 400000
    prevRow = "."
    safeTiles = 0
    for i in range(len(inp)):
        prevRow += inp[i]
        if inp[i]=='.':
            safeTiles += 1
    prevRow += '.'
    for j in range(nrRows-1):
        if j == 39:
            print("Part 1: ", safeTiles)
        newRow = '.'
        for i in range(1,len(prevRow)-1):
            above = prevRow[i-1:i+2]
            if above == '^^.' or above == '.^^' or above == "^.." or above == "..^":
                newRow += '^'
            else:
                newRow += '.'
                safeTiles +=1
        newRow += '.'
        prevRow = newRow
    print("Part 2: ",safeTiles)






part1()