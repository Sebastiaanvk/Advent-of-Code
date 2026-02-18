def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def tupleMult(t,a):
    return tuple(a*x for x in t)



def part1():
    with open("Day 18.txt") as f:
        moves = f.read().split('\n')
        locs = []
        loc = (0,0)
        locs.append(loc)
        exteriorSize = 0
        dirMap = {
            'L':(0,-1),
            'R':(0,1),
            'U':(-1,0),
            'D':(1,0)
        }
        for l in moves:
            s = l.split(' ')
            dir = s[0]
            loc = tupleAdd(loc,tupleMult(dirMap[dir],int(s[1])))
            exteriorSize += int(s[1])
            locs.append(loc)
        area = 0 
        for l1,l2 in zip(locs[:-1],locs[1:]):
            area += l1[0]*l2[1]-l1[1]*l2[0]
        area = abs(area)//2
        area += exteriorSize//2 + 1
        print("Day 18 part 1:", area)


part1()
def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def tupleMult(t,a):
    return tuple(a*x for x in t)

def hexDecimalStringToInt(s):
    res = 0
    for c in s:
        res *= 16
        if ord(c) in range(ord('0'),ord('9')+1):
            res += int(c)
        else:
            res += ord(c)-ord('a')+10

    return res



def part2():
    with open("Day 18.txt") as f:
        moves = f.read().split('\n')
        locs = []
        loc = (0,0)
        locs.append(loc)
        exteriorSize = 0
        dirMap = {
            '2':(0,-1),
            '0':(0,1),
            '3':(-1,0),
            '1':(1,0)
        }
        for l in moves:
            s = l.split(' ')
            code = s[2][1:-1]
            dir = code[-1]
            steps = hexDecimalStringToInt(code[1:-1])

            loc = tupleAdd(loc,tupleMult(dirMap[dir],steps))
            # print(dir,steps)
            exteriorSize += steps
            locs.append(loc)
        area = 0 
        # print(locs)
        for l1,l2 in zip(locs[:-1],locs[1:]):
            area += l1[0]*l2[1]-l1[1]*l2[0]
        area = abs(area)//2
        area += exteriorSize//2 + 1
        print("Day 18 part 2:", area)


part2()