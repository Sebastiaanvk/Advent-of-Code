from collections import deque
import numpy as np

def buttonResult(current,button):
    res = [x for x in current]
    for i in button:
        res[i] = not res[i]
    return tuple(res)

def minPresses(goal, buttons):
    first = tuple([False for x in goal])
    seen = set(first)
    queue = deque([(first,0)])
    while len(queue)>0:
        current,steps = queue.popleft()
        # print(current)
        for button in buttons:
            next = buttonResult(current,button)
            if next == goal:
                return steps+1
            if next not in seen:
                seen.add(next)
                queue.append((next,steps+1))
    return -1


    



def part1():
    lines = list(map(lambda x: x.split(' '),open("Day 10.txt").read().split('\n')))

    sum = 0

    for line in lines:
        goal = tuple([True if x=='#' else False for x in line[0][1:-1]])
        buttons = []
        for buttonStr in line[1:-1]:
            # print(buttonStr)
            button = []
            for x in buttonStr[1:-1].split(','):
                button.append(int(x))
            buttons.append(tuple(button))
        # print(goal)
        # print(buttons)
        sum += minPresses(goal, buttons)
    print("Day 10 part 1:",sum)


# def buttonResult2(current,button):
#     res = [x for x in current]
#     for i in button:
#         res[i] += 1
#     return tuple(res)

# def tupleDiff(ys,xs):
#     res = [ y-x for y,x in zip(ys,xs) ]
#     return tuple(res)
    

# def minPresses2(goal, buttons):
#     sumGoal = sum(goal)
#     first = tuple([0 for x in goal])
#     seen = {first:0}
#     queue = deque([(first,0)])
#     minSteps = 1000000
#     while len(queue)>0:
#         current,steps = queue.popleft()
#         print(current)
#         diff = tupleDiff(goal,current)
#         if diff in seen:
#             minSteps = min(minSteps,steps+seen[diff]) 

#         if sum(current)<sumGoal//2:
#             for button in buttons:
#                 next = buttonResult2(current,button)
#                 if next == goal:
#                     return steps+1
#                 if next not in seen:
#                     seen[next] = steps + 1
#                     queue.append((next,steps+1))
#     return minSteps 

# def makeMinPressesDict(buttons, limit, currentButton, endButton,currentSum, currentPresses, seen):
#     if currentButton == endButton:
#         if tuple(currentSum) in seen:
#             seen[tuple(currentSum)] = min(seen[tuple(currentSum)],currentPresses)
#         else:
#             seen[tuple(currentSum)] = currentPresses
#         return
#     # beginSum = currentSum.copy()
#     beginPresses = currentPresses
#     while (currentSum<=limit).all():
#         makeMinPressesDict(buttons,limit,currentButton+1, endButton, currentSum.copy(), currentPresses, seen )
#         for i in buttons[currentButton]:
#             currentSum[i] += 1
#         currentPresses += 1
#     # currentSum = beginSum
#     currentPresses = beginPresses

# def minPresses2(goal, buttons):
#     sumGoal = sum(goal)
#     leftSeen = {}
#     currentSum = np.array([0 for x in goal])
#     currentPresses = 0
#     makeMinPressesDict(buttons,goal,0,(len(buttons)+1)//2,currentSum, currentPresses, leftSeen)
#     rightSeen = {}
#     currentSum = np.array([0 for x in goal])
#     currentPresses = 0
#     makeMinPressesDict(buttons,goal,(len(buttons)+1)//2,len(buttons),currentSum, currentPresses, rightSeen)
#     # print(leftSeen)
#     # print(rightSeen)

#     minSteps = 1000000
#     for x in leftSeen:
#         arrX = np.array(x)
#         diff = tuple(goal-arrX)
#         if diff in rightSeen:
#             minSteps = min(minSteps,leftSeen[x]+rightSeen[diff])

#     return minSteps 


# def part2():
#     lines = list(map(lambda x: x.split(' '),open("Day 10.txt").read().split('\n')))

#     sum = 0

#     for line in lines:
#         goal = np.array([ int(x) for x in line[-1][1:-1].split(',')])
#         print(goal)
#         buttons = []
#         for buttonStr in line[1:-1]:
#             # print(buttonStr)
#             button = []
#             for x in buttonStr[1:-1].split(','):
#                 button.append(int(x))
#             buttons.append(np.array(button))
#         # print(goal)
#         # print(buttons)
#         sum += minPresses2(goal, buttons)
#     print("Day 10 part 2:",sum)


def restOfRowZero(rows,col,row):
    for i in range(col):
        if  rows[row][i] != 0:
            return False
    return True

def calcNextRow(rows,col):
    for row in range(len(rows)):
        if rows[row][col] != 0 and restOfRowZero(rows,col,row):
            return row
    return -1

def allPositive(varsInUnknown,varVals):
    for line in varsInUnknown:
        val = (sum([a*x for a,x in zip(line[0],varVals)]) + line[1])//line[2]
        # print(val)
        if val<0:
            return False
    return True
# def allGrowingPositive(varsInUnknown,varVals):
#     for line in varsInUnknown:
#         val = (sum([a*x for a,x in zip(line[0],varVals)]) + line[1])//line[2]
#         # print(val)
#         if val<0:
#             return False
#     return True

def stepsIfInteger(varsInUnknown,varVals):
    steps = sum(varVals)

    for line in varsInUnknown:
        num = (sum([a*x for a,x in zip(line[0],varVals)]) + line[1])
        if num%line[2]!=0:
            return False,-1
        steps += num//line[2]
    return True,steps

# def belowGoal(varVals,goal,freeVarButtons):
#     sum = np.zeros(len(goal))
#     for i in range(len(varVals)):
#         sum += varVals[i] *freeVarButtons
#     return (sum<=goal).all()



# def calcRemVarsRec(varsInUnknown,index,varVals,minStepsList,goal,freeVarButtons,freeVarSum):
def calcRemVarsRec(varsInUnknown,index,varVals,minStepsList,maxVar):
    if index == len(varVals):
        # print(varVals)
        isInt,steps = stepsIfInteger(varsInUnknown, varVals)
        if isInt and allPositive(varsInUnknown,varVals):
            minStepsList[0] = min(minStepsList[0],steps)
        return
    # print(varVals)
    # print("Is all positive?",allPositive(varsInUnknown,varVals))
    while(varVals[index]<=maxVar and sum(varVals)<=minStepsList[0]):
        calcRemVarsRec(varsInUnknown,index+1,varVals.copy(),minStepsList,maxVar)

        varVals[index] += 1





# def calcMinStepsVarsInUnknown(varsInUnknown,goal,freeVarButtons):
def calcMinStepsVarsInUnknown(varsInUnknown,maxVar):
    if len(varsInUnknown[0][0]) == 0:
        return sum([t[1]/t[2] for t in varsInUnknown])
    
    varVals = [0 for x in varsInUnknown[0][0]]
    minStepsList = [1000000]
    # calcRemVarsRec(varsInUnknown,0,varVals,minStepsList,goal,freeVarButtons)
    calcRemVarsRec(varsInUnknown,0,varVals,minStepsList,maxVar)
    # print(minStepsList[0])
    return minStepsList[0]

    




def calcRemVarsInUnknown(sweptRows,unknownColStart,freeVars):
    # For each variable that depends on the free variables,
    # We store the row as a three tuple, where the first element consists of the coefficients of the free variables
    # the second element is the constant factor and the third element is the denominator.
    # So if t is the tuple: val = (sum x_i*t[0][i] + t[1]) / t[2] 
    varsInUnknown = []
    for row in sweptRows:
        i=0
        while row[i]==0 and i<len(row)-1:
            i+=1            
        if i!=len(row)-1:
            varsInUnknown.append(([row[j] for j in freeVars],row[-1],(-1)*row[i]))
    return varsInUnknown




def calcMinPresses2(goal, buttons):
    rows = [ np.zeros(len(buttons)+1,dtype=int) for i in range(len(goal))   ]
    for i in range(len(buttons)):
        for j in buttons[i]:
            rows[j][i] = 1
    for i in range(len(goal)):
        rows[i][-1] = -goal[i]
    
    col = 0

    sweepingRow = calcNextRow(rows,col)
    freeVariables = []
    while(col<len(buttons) ):
        if sweepingRow != -1:
            for row in range(len(rows)):
                if row != sweepingRow and rows[row][col]!=0:
                    rows[row] = rows[sweepingRow][col]*rows[row] - rows[row][col]*rows[sweepingRow]
        else:
            freeVariables.append(col)

        col +=1
        sweepingRow = calcNextRow(rows,col)
    # print(rows)
    varsInUnknown = calcRemVarsInUnknown(rows,col,freeVariables)
    # print(varsInUnknown)
    freeVarButtons = [np.array(buttons[i]) for i in freeVariables]
    # return calcMinStepsVarsInUnknown(varsInUnknown,np.array(goal),freeVarButtons)
    print("Nr of free vars:",len(freeVariables))
    return calcMinStepsVarsInUnknown(varsInUnknown,max(goal))




def part2():
    # Nieuw plan: linear equality swiping

    lines = list(map(lambda x: x.split(' '),open("Day 10.txt").read().split('\n')))

    sum = 0

    for line in lines:
        goal = [ int(x) for x in line[-1][1:-1].split(',')]
        print(goal)
        buttons = []
        for buttonStr in line[1:-1]:
            # print(buttonStr)
            button = []
            for x in buttonStr[1:-1].split(','):
                button.append(int(x))
            buttons.append(button)
        # print(goal)
        # print(buttons)

        sum += calcMinPresses2(goal, buttons)
    print("Day 10 part 2:",sum)


part1()
part2()