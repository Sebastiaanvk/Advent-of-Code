def part1():
    crates = [[] for i in range(0,10)]
    start,moves = open("Day 5.txt","r").read().split('\n\n')
    st = start.split('\n')
    for i in range(len(st)-2,-1,-1):
        for j in range(1,10):
            char = st[i][4*(j-1)+1]
            if char!=' ':
                crates[j].append(char)
    moves = moves.split('\n')
    for line in moves[:-1]:
        ln = line.split(' ')
        nr = int(ln[1])
        crate_origin = int(ln[3])
        crate_goal = int(ln[5])
        while nr>0:
            supp = crates[crate_origin].pop()
            crates[crate_goal].append(supp)
            nr -=1
    str = ""
    for i in range(1,10):
        str += crates[i][-1]
    print("Part1:",str)


part1()

def part2():
    crates = [[] for i in range(0,10)]
    start,moves = open("Day 5.txt","r").read().split('\n\n')
    st = start.split('\n')
    for i in range(len(st)-2,-1,-1):
        for j in range(1,10):
            char = st[i][4*(j-1)+1]
            if char!=' ':
                crates[j].append(char)
    moves = moves.split('\n')
    for line in moves[:-1]:
        ln = line.split(' ')
        nr = int(ln[1])
        crate_origin = int(ln[3])
        crate_goal = int(ln[5])
        crates[crate_goal].extend(crates[crate_origin][-nr:])
        crates[crate_origin] = crates[crate_origin][:-nr]
    str = ""
    for i in range(1,10):
        str += crates[i][-1]
    print("Part2:",str)


part2()