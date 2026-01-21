

def part1():
    inp = open("Day 3.txt").read().split()
    sum = 0

    for line in inp:
        highest = -1
        highestLoc = -1
        for i in range(0,len(line)-1):
            y = int(line[i])
            if y > highest:
                highest = y
                highestLoc = i
        secondHighest = -1
        for i in range(highestLoc+1,len(line)):
            y = int(line[i])
            if y >secondHighest:
                secondHighest = y
        sum += 10*highest + secondHighest
    print("Day 3 part 1:", sum)


def part2():
    inp = open("Day 3.txt").read().split()
    sum = 0

    for line in inp:
        values = [-1]
        locs = [-1]
        for j in range(12):
            highest = -1
            highestLoc = -1
            for i in range(locs[j]+1,len(line)-11+j):
                y = int(line[i])
                if y > highest:
                    highest = y
                    highestLoc = i
            values.append(highest)
            locs.append(highestLoc)
        value = 0
        for i in range(1,13):
            value = 10*value + values[i]

        # print(value)
        sum += value
    print("Day 3 part 2:", sum)
part1()
part2()