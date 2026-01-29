

def canAfford(state, buy, prices):
    for i in range(3):
        if( state[i]<buy[0]*prices[0][i] + buy[1]*prices[1][i] + buy[2]*prices[2][i] + buy[3]*prices[3][i]):
            return False
    return True


def maxGeodes(prices,maxDays=24):
    maxOrePrice = max([x[0] for x in prices])
    maxClayPrice = max([x[1] for x in prices])
    stateCount = 0

    stateMap = {(0,0,0,1,0,0):0}
    for it in range(maxDays):
        print(it,stateCount)
        newMap = {} 
        for state in stateMap:
            if state[3]>maxOrePrice or state[4] > maxClayPrice:
                continue

            oldGeodeValue = stateMap[state]
            if canAfford(state,[0,0,0,1],prices):
                buy = [0,0,0,1]
                newState = list(state)
                stateCount += 1
                # print(stateCount,newState,buy)
                for i in range(3):
                    newState[i] -= buy[0]*prices[0][i]+buy[1]*prices[1][i]+buy[2]*prices[2][i]+buy[3]*prices[3][i]
                for i in range(3):
                    newState[i] += newState[3+i]
                for i in range(3):
                    newState[3+i] += buy[i]
                newGeodeValue = oldGeodeValue + buy[3]*(maxDays-1-it)
                newMap[tuple(newState)] = max(newMap.get(tuple(newState),newGeodeValue),newGeodeValue)
            elif canAfford(state,[0,0,1,0],prices):
                buy = [0,0,1,0]
                newState = list(state)
                stateCount += 1
                # print(stateCount,newState,buy)
                for i in range(3):
                    newState[i] -= buy[0]*prices[0][i]+buy[1]*prices[1][i]+buy[2]*prices[2][i]+buy[3]*prices[3][i]
                for i in range(3):
                    newState[i] += newState[3+i]
                for i in range(3):
                    newState[3+i] += buy[i]
                newGeodeValue = oldGeodeValue + buy[3]*(maxDays-1-it)
                newMap[tuple(newState)] = max(newMap.get(tuple(newState),newGeodeValue),newGeodeValue)
            else:
                for buy in [[0,0,0,0],[1,0,0,0],[0,1,0,0]]:
                    if canAfford(state,buy,prices):
                        newState = list(state)
                        stateCount += 1
                        # print(stateCount,newState,buy)
                        for i in range(3):
                            newState[i] -= buy[0]*prices[0][i]+buy[1]*prices[1][i]+buy[2]*prices[2][i]+buy[3]*prices[3][i]
                        for i in range(3):
                            newState[i] += newState[3+i]
                        for i in range(3):
                            newState[3+i] += buy[i]
                        newGeodeValue = oldGeodeValue + buy[3]*(maxDays-1-it)
                        newMap[tuple(newState)] = max(newMap.get(tuple(newState),newGeodeValue),newGeodeValue)
        stateMap = newMap
    maxGeode = 0
    for state in stateMap:
        maxGeode  = max(maxGeode, stateMap[state])
    return maxGeode

def part1():

    sum = 0
    for x in open("Day 19.txt","r").read().split("\n"):
        line = x.split(" ")
        index = int(line[1][:-1])
        prices = [
            (int(line[6]),0,0),
            (int(line[12]),0,0),
            (int(line[18]),int(line[21]),0),
            (int(line[27]),0,int(line[30]))
        ]
        sum += index*maxGeodes(prices)
    print("Day 19 part 1: ",sum)

def part2():

    prod = 1

    lines = open("Day 19.txt","r").read().split("\n")
    for i in range(3):
        x = lines[i]
        line = x.split(" ")
        index = int(line[1][:-1])
        prices = [
            (int(line[6]),0,0),
            (int(line[12]),0,0),
            (int(line[18]),int(line[21]),0),
            (int(line[27]),0,int(line[30]))
        ]
        prod *= maxGeodes(prices,maxDays=32)

    print("Day 19 part 2: ",prod)

# part1()
part2()




# maxGeodes([(2,0,0),(3,0,0),(3,17,0),(3,0,10)])