def part1():
    registers = {}
    max_all = 0
    for l in open("Day 8.txt","r"):
        line = l.split()
        reg1 = line[4]
        reg2 = int(line[6])
        if reg1 in registers:
            reg1 = registers[reg1]
        else:
            reg1 = 0
        comp = line[5]
        if comp=="<" and reg1<reg2 or comp==">"and reg1>reg2 or comp==">=" and reg1>=reg2 or comp=="<="and reg1<=reg2 or comp=="==" and reg1==reg2 or comp=="!=" and reg1!=reg2:
            if line[0] not in registers:
                registers[line[0]] = 0
            if line[1] == "inc":
                registers[line[0]] += int(line[2])
            else:
                registers[line[0]] -= int(line[2])
            max_all = max(max_all,registers[line[0]])
    print("Part1:",max(registers.values()))
    print("Part2:",max_all)


part1()

