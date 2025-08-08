import itertools
def part1():
    input = [(x,False) for x in list(map(int,open("Day 20.txt").read().split()))]
    l = len(input)
    index = 0
    while index<l:
        if input[index][1]==False:
            # print(input)
            diff = input[index][0]
            if diff>0:
                change = (input[index][0])%(l-1)
                newIndex = (index+change)%(l-1)
                if newIndex>index:
                    for k in range(index,newIndex):
                        input[k],input[k+1] = input[k+1],input[k]
                    input[newIndex]=(input[newIndex][0],True)
                else:
                    for k in range(index,newIndex,-1):
                        input[k],input[k-1] = input[k-1],input[k]
                    input[newIndex]=(input[newIndex][0],True)
            else:
                change = (input[index][0])%(l-1)
                newIndex = (index+change)%(l-1)
                if newIndex>index:
                    for k in range(index,newIndex):
                        input[k],input[k+1] = input[k+1],input[k]
                    input[newIndex]=(input[newIndex][0],True)
                else:
                    for k in range(index,newIndex,-1):
                        input[k],input[k-1] = input[k-1],input[k]
                    input[newIndex]=(input[newIndex][0],True)
        else: 
            index += 1
    i = 0
    # print(input)
    while(input[i][0]!=0):
        i+=1
    print("Part 1: ",input[(i+1000)%l][0]+input[(i+2000)%l][0]+input[(i+3000)%l][0])
        
part1()



def part2():
    inputInt = list(map(int,open("Day 20.txt").read().split()))
    input = [(x*811589153,i) for (i,x) in zip(itertools.count(),inputInt)]
    l = len(input)
    # print(input)
    for i in range(10):
        for j in range(l):
            index = 0
            while input[index][1]!=j:
                index += 1
            change = input[index][0]%(l-1)
            newIndex = (index+change)%(l-1)
            if newIndex>index:
                for k in range(index,newIndex):
                    input[k],input[k+1] = input[k+1],input[k]
            else:
                for k in range(index,newIndex,-1):
                    input[k],input[k-1] = input[k-1],input[k]
        # print(input)
    i = 0
    # print(input)
    while(input[i][0]!=0):
        i+=1
    print("Part 2: ",input[(i+1000)%l][0]+input[(i+2000)%l][0]+input[(i+3000)%l][0] )
part2()