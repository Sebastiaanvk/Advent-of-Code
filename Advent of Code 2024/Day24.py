




def getValue(name, values, implications):
    if name in values:
        return values[name]
    x1 = getValue(implications[name][0], values, implications)
    x2 = getValue(implications[name][2], values, implications)
    opc = implications[name][1]
    value = 0
    if opc == "AND":
        value = x1*x2
    elif opc == "OR":
        value = x1|x2
    elif opc == "XOR":
        value = x1^x2
    values[name] = value
    return value





def part1():
    input = open("Day24.txt").read().split("\n\n")
    implications = {}
    values = {}
    for line in input[0].split("\n"):
        s = line.split(" ")
        values[s[0][:-1]] = int(s[1])
    maxZ = 0 
    zStrings = {}
    for line in input[1].split("\n"):
        s = line.split(" ")
        if s[4][0] == 'z':
            maxZ = max(maxZ,int(s[4][1:]))
            zStrings[int(s[4][1:])] = s[4]
        implications[s[4]] = (s[0],s[1],s[2])
    print(maxZ)
    i=maxZ
    result = 0
    while i>=0:
        result = 2*result + getValue(zStrings[i],values, implications)
        i -= 1
    print("Day 14 part1:",result)

part1()




def part2():
    input = open("Day24.txt").read().split("\n\n")[1].split("\n")


    variableAsInput = {}
    variableAsOutput = {}
    for line in input:
        l = line.split()
        tup = (l[0],l[1],l[2],l[4])
        variableAsInput[l[0]] = variableAsInput.get(l[0],[])+[tup]
        variableAsInput[l[2]] = variableAsInput.get(l[2],[])+[tup]
        variableAsOutput[l[4]] = tup
    certainSwitches = []
    for out in variableAsOutput:
        op = variableAsOutput[out][1]
        if out[0]=="z":
            if op !="XOR":
                certainSwitches.append(out)
        elif op == "XOR":
            if variableAsOutput[out][0][0] in {'x','y'}:
                if  len(variableAsInput[out])!=2:
                    certainSwitches.append(out)
            else:
                certainSwitches.append(out)
        elif op == "AND":
            if variableAsInput[out][0][1]!="OR":
                certainSwitches.append(out)
        elif op == "OR":
            if variableAsOutput[out][0][0] in {'x','y'}:
                if  len(variableAsInput[out])!=2:
                    certainSwitches.append(out)
    for x in certainSwitches:
        print(x)
        print(variableAsOutput[x])
        if x[0]!= 'z':
            print(variableAsInput[x])
        print()
    
    certainSwitches.sort()
    s = "" 
    for x in certainSwitches:
        if variableAsOutput[x][0] not in {"x00","y00"} and x != "z45":
            s += x + ","
    print(s[:-1])
    print("Ignore the ones at the start and at the end!")


part2()
        