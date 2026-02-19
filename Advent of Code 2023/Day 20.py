
from collections import defaultdict,deque

LOW = False
HIGH = True

def part1():
    with open("Day 20.txt") as f:
        fl = f.read().split('\n')
        outL = defaultdict(list) 
        inL = defaultdict(dict)
        conjunctions = set()
        flipFlopPos = {}


        for l in fl:
            l2 = l.split(" -> ")
            source = l2[0][1:]
            if l2[0][0]=='&':
                conjunctions.add(source)
            if l2[0][0] == 'b':
                source = l2[0]
            flipFlopPos[source] = LOW
            l3 = l2[1].split(", ")
            for y in l3:
                outL[source].append(y)
                inL[y][source] = LOW
        lowPulses = 0
        highPulses = 0
        # for i in range(1):
        for i in range(1000):
            print(i)
            pulses = deque()
            pulses.append(("broadcaster","button",LOW)) #False = low,True=high
            while len(pulses)>0:
                target,source,highness = pulses.popleft()
                # print(source, "->", target,highness)
                if highness:
                    highPulses += 1
                else:
                    lowPulses += 1
                if target=="broadcaster":
                    for y in outL[target]:
                        pulses.append((y,target,highness))
                elif target in conjunctions:
                    inL[target][source] = highness
                    # print(inL[target])
                    outHighness = LOW
                    for y in inL[target]:
                        if not inL[target][y]:
                            outHighness = HIGH
                    # print(outHighness)
                    for y in outL[target]:
                        pulses.append((y,target,outHighness))
                elif target in flipFlopPos and not highness:
                    if flipFlopPos[target]==LOW:
                        flipFlopPos[target] = HIGH
                        for y in outL[target]:
                            pulses.append((y,target,HIGH))
                    else:
                        flipFlopPos[target] = LOW
                        for y in outL[target]:
                            pulses.append((y,target,LOW))
        print("Day 20 part 1:",lowPulses*highPulses)
part1()
def part2():
# Ok a typical advent of code problem solution (not a fan, but Im used to it at this point
# so in order to get a low pulse to rx, we need all pulses to ls to be high
# Turns out these pulses are high cyclically and these cycles are relative prime, so we can take the product of the cycle lengths
    with open("Day 20.txt") as f:
        fl = f.read().split('\n')
        outL = defaultdict(list) 
        inL = defaultdict(dict)
        conjunctions = set()
        flipFlopPos = {}


        for l in fl:
            l2 = l.split(" -> ")
            source = l2[0][1:]
            if l2[0][0]=='&':
                conjunctions.add(source)
            if l2[0][0] == 'b':
                source = l2[0]
            flipFlopPos[source] = LOW
            l3 = l2[1].split(", ")
            for y in l3:
                outL[source].append(y)
                inL[y][source] = LOW
        lowPulses = 0
        highPulses = 0
        # for i in range(1):
        highToLs = {}
        i=0
        while i<15000:
            i += 1
            pulses = deque()
            pulses.append(("broadcaster","button",LOW)) #False = low,True=high
            while len(pulses)>0:
                target,source,highness = pulses.popleft()
                # print(source, "->", target,highness)
                if target=="ls" and highness:
                    if source not in highToLs:
                        highToLs[source] = i
                    print(i)
                    print(source, "->", target,highness)
                if highness:
                    highPulses += 1
                else:
                    lowPulses += 1
                if target=="broadcaster":
                    for y in outL[target]:
                        pulses.append((y,target,highness))
                elif target=="rx" and not highness:
                    found = True

                elif target in conjunctions:
                    inL[target][source] = highness
                    # print(inL[target])
                    outHighness = LOW
                    for y in inL[target]:
                        if not inL[target][y]:
                            outHighness = HIGH
                    # print(outHighness)
                    for y in outL[target]:
                        pulses.append((y,target,outHighness))
                elif target in flipFlopPos and not highness:
                    if flipFlopPos[target]==LOW:
                        flipFlopPos[target] = HIGH
                        for y in outL[target]:
                            pulses.append((y,target,HIGH))
                    else:
                        flipFlopPos[target] = LOW
                        for y in outL[target]:
                            pulses.append((y,target,LOW))
        
        ans = 1
        for x in highToLs:
            ans *= highToLs[x]

        print("Day 20 part 2:",ans)
part2()