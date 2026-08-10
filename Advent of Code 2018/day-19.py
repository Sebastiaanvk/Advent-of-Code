from collections import defaultdict
from math import sqrt,floor

def runCode(line, regs):
    cmds = line.split()
    opcode = cmds[0]
    A = int(cmds[1])
    B = int(cmds[2])
    C = int(cmds[3])
    if opcode == "addr":
        regs[C] = regs[A] + regs[B] 
    elif opcode == "addi":
        regs[C] = regs[A] + B 
    elif opcode == "mulr":
        regs[C] = regs[A] * regs[B] 
    elif opcode == "muli":
        regs[C] = regs[A] * B 
    elif opcode == "banr":
        regs[C] = regs[A] & regs[B] 
    elif opcode == "bani":
        regs[C] = regs[A] & B 
    elif opcode == "borr":
        regs[C] = regs[A] | regs[B] 
    elif opcode == "bori":
        regs[C] = regs[A] | B 
    elif opcode == "setr":
        regs[C] = regs[A]
    elif opcode == "seti":
        regs[C] = A
    elif opcode == "gtir":
        if A>regs[B]:
            regs[C] = 1
        else:
            regs[C] = 0
    elif opcode == "gtri":
        if regs[A]>B:
            regs[C] = 1
        else:
            regs[C] = 0
    elif opcode == "gtrr":
        if regs[A]>regs[B]:
            regs[C] = 1
        else:
            regs[C] = 0
    elif opcode == "eqir":
        if A==regs[B]:
            regs[C] = 1
        else:
            regs[C] = 0
    elif opcode == "eqri":
        if regs[A]==B:
            regs[C] = 1
        else:
            regs[C] = 0
    elif opcode == "eqrr":
        if regs[A]==regs[B]:
            regs[C] = 1
        else:
            regs[C] = 0

def part1():
    inp = open("day-19.txt").read().split('\n')[:-1]
    instReg = int(inp[0].split()[1])
    lines = inp[1:]

    regs = defaultdict(int)

    while 0<=regs[instReg]<len(lines):
        # print(regs[instReg])
        # print(regs)
        runCode(lines[regs[instReg]],regs)
        regs[instReg] += 1
    print("Part 1: ",regs[0])


part1()

def part2():
    inp = open("day-19.txt").read().split('\n')[:-1]
    instReg = int(inp[0].split()[1])
    lines = inp[1:]

    regs = defaultdict(int)
    regs[0] = 1
    loops = 0

    while 0<=regs[instReg]<len(lines) and loops < 10000:
        runCode(lines[regs[instReg]],regs)
        regs[instReg] += 1
        loops += 1
    print(regs[2])
    y = regs[2]
    ans = 0
    for x in range(1,floor(sqrt(y))+1):
        if y%x==0:
            ans += x+y//x




    print("Part 2: ",ans)


part2()