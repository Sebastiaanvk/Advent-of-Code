from collections import defaultdict

def getValue(cmd,regs):
    if cmd.isalpha():
        return regs[cmd]
    else:
        return int(cmd)

def isRegister(cmd):
    return cmd.isalpha()

def runCode(inp,maxLoops):
    # opcodes = list(map(lambda x: x.split(),open("day-23-test.txt").read().split('\n')[:-1]))
    opcodes = list(map(lambda x: x.split(),open("day-23.txt").read().split('\n')[:-1]))
    regs = defaultdict(int)
    regs['a'] = inp
    opcodeIndex = 0
    loops = 0
    while opcodeIndex<len(opcodes) and loops < maxLoops:
        # print(regs['a'])
        # print(opcodes)
        cmds = opcodes[opcodeIndex]
        if cmds[0] == 'dec':
            if isRegister(cmds[1]):
                regs[cmds[1]] -= 1
        elif cmds[0] == 'inc':
            if isRegister(cmds[1]):
                regs[cmds[1]] += 1
        elif cmds[0] == 'cpy':
            if isRegister(cmds[2]):
                regs[cmds[2]] = getValue(cmds[1],regs)

        opcodeJump = 1
        if cmds[0] == "jnz" and getValue(cmds[1],regs)!=0:
            opcodeJump = getValue(cmds[2],regs)

        if cmds[0] == 'tgl':
            targetIndex = opcodeIndex + getValue(cmds[1],regs)
            if 0<=targetIndex<len(opcodes):
                if len(opcodes[targetIndex])==2:
                    if opcodes[targetIndex][0]=="inc":
                        opcodes[targetIndex][0] = "dec"
                    else:
                        opcodes[targetIndex][0] = "inc"
                else:
                    if opcodes[targetIndex][0]=="jnz":
                        opcodes[targetIndex][0] = "cpy"
                    else:
                        opcodes[targetIndex][0] = "jnz"
        loops += 1
        opcodeIndex += opcodeJump

    if loops<maxLoops:
        print("Answer: ",regs['a'])
        return True
    return False

runCode(7,100000)



def part2():
    opcodes = list(map(lambda x: x.split(),open("day-23.txt").read().split('\n')[:-1]))
    regs = defaultdict(int)
    regs['a'] = 12 
    opcodeIndex = 0
    while opcodeIndex<len(opcodes):
        # print(opcodeIndex)
        # print(opcodes[opcodeIndex+2])
        # if opcodeIndex + 5 < len(opcodes) and opcodes[opcodeIndex][0]=="cpy" and opcodes[opcodeIndex+5][0] == "jnz" and opcodes[opcodeIndex+5][2] == "-5":
        if opcodeIndex == 4:
            regs['a'] = (regs['b'])*(regs['d'])
            regs['c'] = 0
            regs['d'] = 0
            opcodeIndex += 6
            continue
        if opcodeIndex + 2 < len(opcodes) and opcodes[opcodeIndex+2][0] == "jnz" and opcodes[opcodeIndex+2][2] == "-2":
            # print("yes")
            source = opcodes[opcodeIndex+2][1]
            if regs[source] !=0:
                sourceIndex = opcodeIndex
                targetIndex = opcodeIndex + 1
                if opcodes[sourceIndex][1] != source:
                    sourceIndex += 1
                    targetIndex -= 1
                target = opcodes[targetIndex][1]
                diff = abs(regs[source])
                if opcodes[targetIndex][0] == "inc":
                    regs[target] += diff
                else:
                    regs[target] -= diff
            regs[source] = 0
            opcodeIndex += 3
            continue
        # print("no")

        cmds = opcodes[opcodeIndex]
        if cmds[0] == 'dec':
            if isRegister(cmds[1]):
                regs[cmds[1]] -= 1
        elif cmds[0] == 'inc':
            if isRegister(cmds[1]):
                regs[cmds[1]] += 1
        elif cmds[0] == 'cpy':
            if isRegister(cmds[2]):
                regs[cmds[2]] = getValue(cmds[1],regs)

        opcodeJump = 1
        if cmds[0] == "jnz" and getValue(cmds[1],regs)!=0:
            opcodeJump = getValue(cmds[2],regs)

        if cmds[0] == 'tgl':
            targetIndex = opcodeIndex + getValue(cmds[1],regs)
            if 0<=targetIndex<len(opcodes):
                if len(opcodes[targetIndex])==2:
                    if opcodes[targetIndex][0]=="inc":
                        opcodes[targetIndex][0] = "dec"
                    else:
                        opcodes[targetIndex][0] = "inc"
                else:
                    if opcodes[targetIndex][0]=="jnz":
                        opcodes[targetIndex][0] = "cpy"
                    else:
                        opcodes[targetIndex][0] = "jnz"
        opcodeIndex += opcodeJump

    print("Part 2: ",regs['a'])

part2()







