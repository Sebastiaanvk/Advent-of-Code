import hashlib
from collections import defaultdict

def part1():
    prefix = "yjdafjpo"
    # prefix = "abc"
    quintuplets = defaultdict(int)
    chars = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']
    for i in range(1000):
        inp = prefix + str(i)
        res = hashlib.md5(inp.encode()).hexdigest()
        for c in chars:
            quint = c+c+c+c+c
            if quint in res:
                quintuplets[c] = i
    index = 0
    keys = set()
    while True:
        shiftedInp = prefix + str(index+1000)
        shiftedRes = hashlib.md5(shiftedInp.encode()).hexdigest()
        for c in chars:
            quint = c+c+c+c+c
            if quint in shiftedRes:
                quintuplets[c] = index+1000
        
        inp = prefix + str(index)
        res = hashlib.md5(inp.encode()).hexdigest()

        firstTrip = True
        for i in range(len(res)-2):
        # for c in chars:
            if firstTrip and res[i]==res[i+1] and res[i+1]==res[i+2]:
                c = res[i]
                firstTrip = False
                if quintuplets[c]>index:
                    keys.add(index)
                    # print(index,quintuplets[c])
                    s = prefix + str(quintuplets[c])
                    # print(res,hashlib.md5(s.encode()).hexdigest())
                    if len(keys)==64:
                        print("Part 1:",index)
                        return

        index += 1

part1()

def getStretchedHash(s):
    for i in range(2017):
        s = hashlib.md5(s.encode()).hexdigest()
    return s


def part2():
    prefix = "yjdafjpo"
    # prefix = "abc"
    quintuplets = defaultdict(int)
    chars = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']
    for i in range(1000):
        inp = prefix + str(i)
        res = getStretchedHash(inp)
        for c in chars:
            quint = c+c+c+c+c
            if quint in res:
                quintuplets[c] = i
    index = 0
    keys = set()
    while True:
        shiftedInp = prefix + str(index+1000)
        shiftedRes = getStretchedHash(shiftedInp)
        for c in chars:
            quint = c+c+c+c+c
            if quint in shiftedRes:
                quintuplets[c] = index+1000
        
        inp = prefix + str(index)
        res = getStretchedHash(inp)

        firstTrip = True
        for i in range(len(res)-2):
        # for c in chars:
            if firstTrip and res[i]==res[i+1] and res[i+1]==res[i+2]:
                c = res[i]
                firstTrip = False
                if quintuplets[c]>index:
                    keys.add(index)
                    # print(index,quintuplets[c])
                    s = prefix + str(quintuplets[c])
                    # print(res,hashlib.md5(s.encode()).hexdigest())
                    if len(keys)==64:
                        print("Part 2:",index)
                        return

        index += 1


part2()