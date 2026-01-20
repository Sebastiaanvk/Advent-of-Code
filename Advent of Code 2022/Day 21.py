
def getValue(monkeyName, monkeyValueDict, monkeyCombDict):
    if monkeyName not in monkeyValueDict:
        val1 = getValue(monkeyCombDict[monkeyName][0],monkeyValueDict,monkeyCombDict)
        operation = monkeyCombDict[monkeyName][1]
        val2 = getValue(monkeyCombDict[monkeyName][2],monkeyValueDict,monkeyCombDict)
        result = 0
        if operation == "+":
            result = val1 + val2
        elif operation == "-":
            result = val1 - val2
        elif operation == "*":
            result = val1 * val2
        elif operation == "/":
            result = val1 // val2
        monkeyValueDict[monkeyName] = result
    return monkeyValueDict[monkeyName]




def part1():
    input = open("Day 21.txt").read().split("\n")
    monkeyValueDict = {}
    monkeyCombDict = {}
    for line in input:
        splitLine = line.split(" ")

        if len(splitLine)==2:
            monkeyValueDict[splitLine[0][:-1]] = int(splitLine[1])     
        else:
            monkeyCombDict[splitLine[0][:-1]] = (splitLine[1],splitLine[2],splitLine[3])
    
    rootValue = getValue("root",monkeyValueDict,monkeyCombDict)
    print("Day 21 part 1:",rootValue)





part1()
