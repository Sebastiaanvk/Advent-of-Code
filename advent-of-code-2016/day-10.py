from collections import defaultdict
from collections import deque

def part1():
    inventory = defaultdict(list)
    targets = defaultdict(list)
    q = deque()

    inp = open("day-10.txt").read().split('\n')[:-1]
    for line in inp:
        ls = line.split()
        if len(ls)==6:
            target = ls[4]+ls[5]
            inventory[target].append(int(ls[1]))
            if len(inventory[target])==2:
                q.append(target)
        else:
            bot = ls[0]+ls[1]
            targets[bot].append(ls[5]+ls[6])
            targets[bot].append(ls[10]+ls[11])
    while len(q)>0:
        x = q.popleft()
        if x[:3]!="bot":
            continue

        if set(inventory[x]) == {61,17}:
            print(x)
            return
        
        lowTarget = targets[x][0]
        highTarget = targets[x][1]
        inventory[lowTarget].append(min(inventory[x]))
        if len(inventory[lowTarget])==2:
            q.append(lowTarget)
        inventory[highTarget].append(max(inventory[x]))
        if len(inventory[highTarget])==2:
            q.append(highTarget)
part1()

def part2():
    inventory = defaultdict(list)
    targets = defaultdict(list)
    q = deque()

    inp = open("day-10.txt").read().split('\n')[:-1]
    for line in inp:
        ls = line.split()
        if len(ls)==6:
            target = ls[4]+ls[5]
            inventory[target].append(int(ls[1]))
            if len(inventory[target])==2:
                q.append(target)
        else:
            bot = ls[0]+ls[1]
            targets[bot].append(ls[5]+ls[6])
            targets[bot].append(ls[10]+ls[11])
    while len(q)>0:
        x = q.popleft()
        if x[:3]!="bot":
            continue

        lowTarget = targets[x][0]
        highTarget = targets[x][1]
        inventory[lowTarget].append(min(inventory[x]))
        if len(inventory[lowTarget])==2:
            q.append(lowTarget)
        inventory[highTarget].append(max(inventory[x]))
        if len(inventory[highTarget])==2:
            q.append(highTarget)
    print(inventory["output"+"0"][0]*inventory["output"+"1"][0]*inventory["output"+"2"][0])
part2()
