import itertools


def part1():
    inp = open("day-21.txt").read().split('\n')[:-1]
    ls = list("abcdefgh")
    # inp = open("day-21-test.txt").read().split('\n')[:-1]
    # ls = list("abcde")
    # print(ls)
    for l in inp:
        cmds = l.split()
        if cmds[0] == "swap":
            if cmds[1] == "position":
                pos1 = int(cmds[2])
                pos2 = int(cmds[5])
                ls[pos1],ls[pos2] = ls[pos2],ls[pos1]
            else:
                let1 = cmds[2]
                let2 = cmds[5]
                pos1 = 0
                pos2 = 0 
                for i in range(len(ls)):
                    if ls[i] == let1:
                        pos1 = i
                    if ls[i] == let2:
                        pos2 = i
                ls[pos1],ls[pos2] = ls[pos2],ls[pos1]
        elif cmds[0] == "rotate":
            if cmds[1] == "right":
                pivot = len(ls)-int(cmds[2])
                ls = ls[pivot:] + ls[:pivot]
            elif cmds[1] == "left":
                pivot = int(cmds[2])
                ls = ls[pivot:] + ls[:pivot]
            else:
                pos = 0
                for i in range(len(ls)):
                    if ls[i]==cmds[6]:
                        pos = i
                pivot = len(ls)-pos-1
                if pos>=4:
                    pivot -=1
                ls = ls[pivot:] + ls[:pivot]
        elif cmds[0] == "reverse":
            pos1 = int(cmds[2])
            pos2 = int(cmds[4])
            ls = ls[:pos1] + ls[pos1:pos2+1][::-1] + ls[pos2+1:]
        elif cmds[0] == "move":
            pos1 = int(cmds[2])
            pos2 = int(cmds[5])
            c = ls[pos1]
            ls = ls[:pos1] + ls[pos1+1:]
            ls = ls[:pos2] + [c] + ls[pos2:]
        # print(l)
        # print("".join(ls))
    print("Part 1: ","".join(ls))
part1()

cmdss = list( map(lambda x: x.split(),   open("day-21.txt").read().split('\n')[:-1]))

def scramble(ls):
    for cmds in cmdss:
        if cmds[0] == "swap":
            if cmds[1] == "position":
                pos1 = int(cmds[2])
                pos2 = int(cmds[5])
                ls[pos1],ls[pos2] = ls[pos2],ls[pos1]
            else:
                let1 = cmds[2]
                let2 = cmds[5]
                pos1 = 0
                pos2 = 0 
                for i in range(len(ls)):
                    if ls[i] == let1:
                        pos1 = i
                    if ls[i] == let2:
                        pos2 = i
                ls[pos1],ls[pos2] = ls[pos2],ls[pos1]
        elif cmds[0] == "rotate":
            if cmds[1] == "right":
                pivot = len(ls)-int(cmds[2])
                ls = ls[pivot:] + ls[:pivot]
            elif cmds[1] == "left":
                pivot = int(cmds[2])
                ls = ls[pivot:] + ls[:pivot]
            else:
                pos = 0
                for i in range(len(ls)):
                    if ls[i]==cmds[6]:
                        pos = i
                pivot = len(ls)-pos-1
                if pos>=4:
                    pivot -=1
                ls = ls[pivot:] + ls[:pivot]
        elif cmds[0] == "reverse":
            pos1 = int(cmds[2])
            pos2 = int(cmds[4])
            ls = ls[:pos1] + ls[pos1:pos2+1][::-1] + ls[pos2+1:]
        elif cmds[0] == "move":
            pos1 = int(cmds[2])
            pos2 = int(cmds[5])
            c = ls[pos1]
            ls = ls[:pos1] + ls[pos1+1:]
            ls = ls[:pos2] + [c] + ls[pos2:]
    return ls

def part2():
    for ls in itertools.permutations(list("abcdefgh")):
        if scramble(list(ls)) == list("fbgdceah"):
            print("Part 2: ", "".join(ls))



part2()


