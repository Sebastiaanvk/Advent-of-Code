


def part1():
    input = open("Day 1.txt").read().split()
    count = 0
    start = 50
    for line in input:
        nr = int(line[1:])
        if line[0] == 'L':
            start = (start-nr)%100
        else:
            start = (start+nr)%100
        if start==0:
            count += 1
    print("Day 1 part 1: ", count)


def part2():
    input = open("Day 1.txt").read().split()
    count = 0
    pos = 50
    for line in input:
        nr = int(line[1:])
        count += nr // 100
        nr %= 100
        if line[0] == 'L':
            if pos!=0 and pos<=nr:
                count += 1 
            pos = (pos-nr) % 100
        else:
            pos = pos+nr
            if pos>=100:
                count += 1
            pos = pos % 100

    print("Day 2 part 2: ", count)


part1()
part2()