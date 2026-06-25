
dirs = [-1j,1,1j,-1]

def part1():
    inp = open("day-1.txt").read()
    dirIndex = 0
    pos = 0
    for comm in inp.split(", "):
        if comm[0] == 'L':
            dirIndex = (dirIndex-1)%4
        else:
            dirIndex = (dirIndex+1)%4
        steps = int(comm[1:])
        pos += steps * dirs[dirIndex]

    print("The answer to part 1 is :",abs(pos.real)+abs(pos.imag))


part1()
def part2():
    inp = open("day-1.txt").read()
    dirIndex = 0
    pos = 0
    visited = {pos}
    s = inp.split(", ")
    sIndex = 0
    while True:
        comm = s[sIndex]
        if comm[0] == 'L':
            dirIndex = (dirIndex-1)%4
        else:
            dirIndex = (dirIndex+1)%4
        steps = int(comm[1:])
        # pos += steps * dirs[dirIndex]
        for i in range(steps):
            pos += dirs[dirIndex]
            if pos in visited:
                print("The answer to part 2 is :",abs(pos.real)+abs(pos.imag))
                return
            visited.add(pos)
        sIndex = (sIndex+1)%len(s)




part2()