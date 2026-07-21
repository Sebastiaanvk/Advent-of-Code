from collections import defaultdict

def getValue(cmd,regs):
    if cmd.isalpha():
        return regs[cmd]
    else:
        return int(cmd)


def part1():
    opcodes = open("day-12.txt").read().split('\n')[:-1]
    lineIndex = 0
    regs = defaultdict(int)
    while lineIndex < len(opcodes):
        cmds = opcodes[lineIndex].split()
        if cmds[0] == 'dec':
            regs[cmds[1]] -= 1
        elif cmds[0] == 'inc':
            regs[cmds[1]] += 1
        elif cmds[0] == 'cpy':
            regs[cmds[2]] = getValue(cmds[1],regs)

        if cmds[0] == "jnz" and getValue(cmds[1],regs)!=0:
            lineIndex += int(cmds[2])
        else:
            lineIndex += 1



    print("Part 1:",regs['a'])



part1()

def part2():
    opcodes = open("day-12.txt").read().split('\n')[:-1]
    lineIndex = 0
    regs = defaultdict(int)
    regs['c'] = 1
    while lineIndex < len(opcodes):
        cmds = opcodes[lineIndex].split()
        if cmds[0] == 'dec':
            regs[cmds[1]] -= 1
        elif cmds[0] == 'inc':
            regs[cmds[1]] += 1
        elif cmds[0] == 'cpy':
            regs[cmds[2]] = getValue(cmds[1],regs)

        if cmds[0] == "jnz" and getValue(cmds[1],regs)!=0:
            lineIndex += int(cmds[2])
        else:
            lineIndex += 1



    print("Part 2:",regs['a'])



part2()