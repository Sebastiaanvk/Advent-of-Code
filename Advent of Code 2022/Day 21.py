
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

def findHumnRec(pos, monkeyCombDict, onPathToRoot):
    if pos not in monkeyCombDict:
        if pos=='humn':
            return True
        else:
            return False 
    for child in [monkeyCombDict[pos][0],monkeyCombDict[pos][2]]:
        if findHumnRec(child, monkeyCombDict, onPathToRoot):
            onPathToRoot.add(pos)
            return True
    return False

def part2():
    input = open("Day 21.txt").read().split("\n")
    monkeyValueDict = {}
    monkeyCombDict = {}
    for line in input:
        splitLine = line.split(" ")

        if len(splitLine)==2:
            monkeyValueDict[splitLine[0][:-1]] = int(splitLine[1])     
        else:
            monkeyCombDict[splitLine[0][:-1]] = (splitLine[1],splitLine[2],splitLine[3])

    onPathToRoot = set()
    findHumnRec("root", monkeyCombDict, onPathToRoot)
    
    currentPos = monkeyCombDict["root"][0]
    child = monkeyCombDict["root"][2]
    if child in onPathToRoot:
        currentPos, child = child, currentPos
    goal = getValue(child, monkeyValueDict, monkeyCombDict)

    while currentPos!="humn":
        operation = monkeyCombDict[currentPos][1]
        child = monkeyCombDict[currentPos][2]
        currentPos = monkeyCombDict[currentPos][0]
        swapped = False
        if child in onPathToRoot:
            currentPos, child = child, currentPos
            swapped = True
        val = getValue(child, monkeyValueDict, monkeyCombDict)
        if operation == "+":
            goal = goal - val
        elif operation == "-":
            if swapped:
                goal = val-goal
            else:
                goal = val+goal
        elif operation == "*":
            goal = goal // val
        elif operation == "/":
            if swapped:
                goal = val//goal
            else:
                goal = val*goal
    print("Day 22 part 2:",goal)



part1()
part2()
