from collections import deque
from sortedcontainers import SortedList
import itertools

'''
this solution is quite slow. For part two it takes about a minute or two.
Probably some things I could optimize a big more, but this is fine by me.

'''

def stateLegal(state):
    for floor in state:
        for x in floor:
            if x<16:
                containsGen = False
                containsBuddy = False
                for y in floor:
                    if y>=16:
                        containsGen = True
                    if y==x+16:
                        containsBuddy = True
                if not containsBuddy and containsGen:
                    return False
    return True


def nextStates(inventory, elevatorPos):
    stateList = []
    for floorChange in [-1,1]:
        newPos = elevatorPos+floorChange 
        if newPos<0 or newPos>3:
            continue
        # first we do single moves
        for x in inventory[elevatorPos]:
            inventory[elevatorPos].remove(x)
            inventory[newPos].add(x)
            if stateLegal(inventory):
                stateList.append((tuple(floor.copy() for floor in inventory),newPos))
            inventory[newPos].remove(x)
            inventory[elevatorPos].add(x)
        for x,y in itertools.combinations(inventory[elevatorPos],2):
            inventory[elevatorPos].remove(x)
            inventory[newPos].add(x)
            inventory[elevatorPos].remove(y)
            inventory[newPos].add(y)
            if stateLegal(inventory):
                stateList.append((tuple(floor.copy() for floor in inventory),newPos))
            inventory[newPos].remove(x)
            inventory[elevatorPos].add(x)
            inventory[newPos].remove(y)
            inventory[elevatorPos].add(y)
    return stateList

        
def tupleVersion(inventory):
    return tuple(tuple(floor) for floor in inventory)

def part1():
    # inp = open("day-11.txt").read().split('\n')
    # gave the chips numbers and the corresponding generator is 16 plus the chip number
    inventoryFloors = (SortedList({16,0,17,1}),SortedList({19,18,2,20,4}),SortedList({3}),SortedList({}))
    print(inventoryFloors)
    elevatorPos = 0
    queue = deque()

    queue.append((0,inventoryFloors,0))

    # Optional: dont add duplicates
    seenStates = set()
    seenStates.add((tupleVersion(inventoryFloors),elevatorPos))

    while len(queue)>0:
        nrSteps, currentInventory, elevatorPos = queue[0]
        queue.popleft()
        stateList = nextStates(currentInventory,elevatorPos)
        for inventory,pos in stateList:
            # print(inventory, pos)
            if len(inventory[3]) == 10:
                print("Part 1: ", nrSteps+1)
                return
            if(tupleVersion(inventory),pos) not in seenStates:
                queue.append((nrSteps+1,inventory,pos))
                seenStates.add((tupleVersion(inventory),pos))

part1()

def stateLegalMask(state):
    for floorMask in state:
        for x in range(7):
            if (floorMask & (1<<x)) and (floorMask >= (1<<7)):
                if (floorMask & 1<<(x+7))==0:
                    return False
    return True

def nextStatesMask(inventory, elevatorPos):
    stateList = []
    for floorChange in [-1,1]:
        newPos = elevatorPos+floorChange 
        if newPos<0 or newPos>3:
            continue
        # first we do single moves
        for x in range(14):
            xBit = 1<<x
            if xBit & inventory[elevatorPos]:
                inventory[elevatorPos] -= xBit
                inventory[newPos] += xBit
                if stateLegalMask(inventory):
                    stateList.append((inventory.copy(),newPos))
                inventory[newPos] -= xBit
                inventory[elevatorPos] += xBit

        for x,y in itertools.combinations(range(14),2):
            xBit = 1<<x
            yBit = 1<<y
            if xBit & inventory[elevatorPos] and yBit & inventory[elevatorPos]:
                inventory[elevatorPos] -= xBit
                inventory[newPos] += xBit
                inventory[elevatorPos] -= yBit
                inventory[newPos] += yBit
                if stateLegalMask(inventory):
                    stateList.append((inventory.copy(),newPos))
                inventory[newPos] -= xBit
                inventory[elevatorPos] += xBit
                inventory[newPos] -= yBit
                inventory[elevatorPos] += yBit
    return stateList

def part2():
    # inp = open("day-11.txt").read().split('\n')
    # gave the chips numbers and the corresponding generator is 16 plus the chip number
    inventoryFloors = (SortedList({7,0,8,1,5,12,6,13}),SortedList({10,9,2,11,4}),SortedList({3}),SortedList({}))
    # inventoryFloors = (SortedList({7,0,8,1}),SortedList({10,9,2,11,4}),SortedList({3}),SortedList({}))
    invMask = [0,0,0,0]
    for i in range(4):
        for x in inventoryFloors[i]:
            invMask[i] += 1<<x
    queue = deque()

    queue.append((0,invMask,0))

    # Optional: dont add duplicates
    seenStates = set()
    seenStates.add((tuple(invMask),0))

    while len(queue)>0:
        nrSteps, currentInvMask, elevatorPos = queue[0]
        # print(currentInvMask)
        queue.popleft()
        stateList = nextStatesMask(currentInvMask,elevatorPos)
        # print(stateList)
        for invMask,pos in stateList:
            # print(inventory, pos)
            if sum([ invMask[i] for i in range(3)]) == 0:
                print("Part 2: ", nrSteps+1)
                return
            if(tuple(invMask),pos) not in seenStates:
                queue.append((nrSteps+1,invMask,pos))
                seenStates.add((tuple(invMask),pos))

            






part2()