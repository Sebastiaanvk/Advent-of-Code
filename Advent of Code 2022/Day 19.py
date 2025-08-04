MAXDAYS = 24 


def canAfford(state, buy, prices):
    for i in range(3):
        if( state[i]<buy[0]*prices[0][i] + buy[1]*prices[1][i] + buy[2]*prices[2][i] + buy[3]*prices[3][i]):
            return False
    return True


def maxGeodes(prices):
    maxOrePrice = max([x[0] for x in prices])
    maxClayPrice = max([x[1] for x in prices])
    stateCount = 0

    stateMap = {(0,0,0,1,0,0):0}
    for it in range(MAXDAYS):
        print(it,stateCount)
        newMap = {} 
        for state in stateMap:
            buy = [0,0,0,0]
            oldGeodeValue = stateMap[state]
            while(canAfford(state,buy,prices)):
                while(canAfford(state,buy,prices)):
                    while(canAfford(state,buy,prices)):
                        while(canAfford(state,buy,prices)):
                            newState = list(state)
                            stateCount += 1
                            # print(stateCount,newState,buy)
                            for i in range(3):
                                newState[i] -= buy[0]*prices[0][i]+buy[1]*prices[1][i]+buy[2]*prices[2][i]+buy[3]*prices[3][i]
                            for i in range(3):
                                newState[i] += newState[3+i]
                            for i in range(3):
                                newState[3+i] += buy[i]
                            newGeodeValue = oldGeodeValue + buy[3]*(MAXDAYS-1-it)
                            newMap[tuple(newState)] = max(newMap.get(tuple(newState),newGeodeValue),newGeodeValue)
                            buy[3] += 1
                        buy[3] = 0
                        buy[2] += 1
                    buy[2] = 0
                    buy[1] += 1
                buy[1] = 0
                buy[0] += 1
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

part1()
# maxGeodes([(2,0,0),(3,0,0),(3,17,0),(3,0,10)])