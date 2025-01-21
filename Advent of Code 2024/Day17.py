


def part1():
    input = open("Day17.txt").read().split("\n")
    #input = open("test17.txt").read().split("\n")
    #input = open("test172.txt").read().split("\n")
    regA = int(input[0].split()[2])
    regB = int(input[1].split()[2])
    regC = int(input[2].split()[2])

    ops = list(map(int,input[4].split()[1].split(",")))
    out = ""
    i = 0
    while i<len(ops):
        instr = ops[i]
        operand = ops[i+1]
        combo = operand
        if operand == 4:
            combo = regA
        elif operand == 5:
            combo = regB
        elif operand == 6:
            combo = regC

        match instr:
            case 0:
                regA = regA // (2**combo)
            case 1:
                regB = regB^operand
            case 2:
                regB = combo % 8
            case 3:
                if regA != 0:
                    i = operand - 2
            case 4:
                regB = regB ^ regC
            case 5:
                out += str(combo%8) + ","
            case 6:
                regB = regA // (2**combo)        
            case 7:
                regC = regA // (2**combo)
        i += 2

    print(regA,regB,regC)
    print("Day 17 part1: ", out[:-1])

part1()




def singleLoop(inputA, ops):
    regA = inputA
    regB = 0
    regC = 0
    i = 0
    while i<len(ops):
        instr = ops[i]
        operand = ops[i+1]
        combo = operand
        if operand == 4:
            combo = regA
        elif operand == 5:
            combo = regB
        elif operand == 6:
            combo = regC

        match instr:
            case 0:
                regA = regA // (2**combo)
            case 1:
                regB = regB^operand
            case 2:
                regB = combo % 8
            case 3:
                if regA != 0:
                    i = operand - 2
            case 4:
                regB = regB ^ regC
            case 5:
                out = str(combo%8) 
                return out
            case 6:
                regB = regA // (2**combo)        
            case 7:
                regC = regA // (2**combo)
        i += 2
    print("Something went wrong!")

def findInitialA( goalA, opsIndex, ops ):
    if opsIndex<0:
        return goalA, True
    for a in range(8):
        output = singleLoop(8*goalA+a,ops)
        if int(output) == int(ops[opsIndex]) and not (a==0 and opsIndex==len(ops)-1): 
            initA, found = findInitialA(8*goalA+a,opsIndex-1, ops)
            if found:
                return initA,found
    return 0, False



def part2():
    input = open("Day17.txt").read().split("\n")
    #input = open("test17.txt").read().split("\n")
    #input = open("test172.txt").read().split("\n")
    ops = list(map(int,input[4].split()[1].split(",")))

    initialA, found = findInitialA(0,len(ops)-1,ops)

    print("Day 17 part2: ", initialA )

part2()