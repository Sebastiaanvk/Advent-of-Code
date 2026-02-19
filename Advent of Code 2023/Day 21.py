import itertools
from collections import deque,defaultdict

def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def part1():
    with open("Day 21.txt") as f:
        g = f.read().split('\n')
        n,m = len(g),len(g[0])
        start = (0,0)
        for y,x in itertools.product(range(n),range(m)):
            if g[y][x] == 'S':
                start = (y,x)
                break
        q = deque([(start,0)])
        dirs = [(1,0),(0,1),(-1,0),(0,-1)]
        seen = set([start])
        ans = 0
        maxSteps = 64
        while len(q):
            pos,dist = q.popleft()
            if dist % 2 ==0:
                ans += 1
            for dir in dirs:
                nPos = tupleAdd(pos,dir)
                if nPos not in seen and g[nPos[0]][nPos[1]]=='.' and dist<maxSteps:
                    seen.add(nPos)
                    q.append((nPos,dist+1))
        print("Day 21 part 1:",ans)


part1()

def calcDistances(g,starts):
    n,m = len(g),len(g[0])
    distances = {}
    q = deque()
    for start in starts:
        q.append((start,0))
        distances[start] = 0
    dirs = [(1,0),(0,1),(-1,0),(0,-1)]
    while len(q):
        pos,dist = q.popleft()
        for dir in dirs:
            nPos = tupleAdd(pos,dir)
            if nPos[0] in range(n) and nPos[1] in range(m) and nPos not in distances and g[nPos[0]][nPos[1]]!='#':
                distances[nPos] = dist + 1
                q.append((nPos,dist+1))
    return distances

def calcAccDistances(distances):
    numberAtDistance = defaultdict(int)
    maxDist = 0
    for x in distances:
        numberAtDistance[distances[x]] += 1
        maxDist = max(maxDist,distances[x])
    accEven = 0
    accOdd = 0
    accDistances = {}
    for i in range(0,maxDist+1):
        if i%2==0:
            accEven += numberAtDistance[i]
            accDistances[i] = accEven
        else:
            accOdd += numberAtDistance[i]
            accDistances[i] = accOdd

    return accDistances,maxDist

def calcEndSquares(distToStart,distances,maxSteps,m,n):
    ans = 0
    accDistances,maxDist = calcAccDistances(distances)
    xg = 0
    while distToStart + xg*m<=maxSteps:
        remainingSteps = maxSteps-distToStart-xg*m
        yg = 0
        if remainingSteps-maxDist>=0:
            yg = (remainingSteps-maxDist)//n+1 #yg is the number of grids we can add so that we are sure that we can reach all (even/odd) fields in the grid at (xg,yg)
            ans += (yg//2)*accDistances[maxDist]+(yg//2)*accDistances[maxDist-1]
            if yg%2==1:
                if remainingSteps%2==maxDist%2:
                    ans += accDistances[maxDist]
                else:
                    ans += accDistances[maxDist-1]

        while remainingSteps-yg*n>=0:
            ans += accDistances[remainingSteps-yg*n]
            yg += 1
        xg += 1
    return ans

# This was the aoc puzzle I spent the most time on
# First, the exact logic was pretty hard to get correct
# and they be sure there wasnt a better way to do things.
# Then I got stuck super long, because I didnt realize theres a cross without blockades in the middle of the grid

def part2():
    with open("Day 21.txt") as f:
        g = f.read().split('\n')
        n,m = len(g),len(g[0])
        start = (0,0)
        for y,x in itertools.product(range(n),range(m)):
            if g[y][x] == 'S':
                start = (y,x)
                break
        # maxSteps = 1000
        maxSteps = 26501365
        corners = [(0,0),(0,m-1),(n-1,m-1),(n-1,0)]
        distancesFromStart = calcDistances(g,[start])
        # print(distancesFromStart)
        # print(calcAccDistances(distancesFromStart))
        
        ans = 0
        for loc in distancesFromStart:
            dist = distancesFromStart[loc]
            if dist%2==maxSteps%2 and dist<=maxSteps:
                ans += 1
        distancesFromCornerDict = {}
        for corner in corners:
            distancesFromCornerDict[corner] = calcDistances(g,[corner])
            # print(distancesFromCornerDict[corner])


        for corner in corners:
            distancesFromCorner = distancesFromCornerDict[corner]
            distToCorner = distancesFromStart[(n-1-corner[0],m-1-corner[1])] + 2
            ans += calcEndSquares(distToCorner,distancesFromCorner,maxSteps,m,n)
            # print(corner,calcEndSquares(distToCorner,distancesFromCorner,maxSteps,m,n))
        
        # for c1,c2,d in [((0,0),(0,m-1),n),((0,m-1),(n-1,m-1),m),((n-1,m-1),(n-1,0),n),((n-1,0),(0,0),m)]:
        #     distToCorner1 = distancesFromStart[(n-1-c1[0],m-1-c1[1])] + 1
        #     distToCorner2 = distancesFromStart[(n-1-c2[0],m-1-c2[1])] + 1
        #     distancesFromCorner1 = distancesFromCornerDict[c1]
        #     distancesFromCorner2 = distancesFromCornerDict[c2]
        #     distToCorner = min(distToCorner1,distToCorner2)
        #     distancesFromCorner = {}
        #     for loc in distancesFromCorner1:
        #         distancesFromCorner[loc] = min(distToCorner1+distancesFromCorner1[loc],distToCorner2+distancesFromCorner2[loc])-distToCorner
        #     accDistances,maxDist = calcAccDistances(distancesFromCorner)

        #     remainingSteps = maxSteps-distToCorner
        #     zg = 0
        #     if remainingSteps-maxDist >=0:
        #         zg = (remainingSteps-maxDist)//d+1
        #         ans += (zg//2)*accDistances[maxDist] + (zg//2)*accDistances[maxDist-1]
        #         if zg%2==1:
        #             if remainingSteps%2==maxDist%2:
        #                 ans += accDistances[maxDist]
        #             else:
        #                 ans += accDistances[maxDist-1]
        #         # zg += 1
        #     while remainingSteps-zg*d>=0:
        #         ans += accDistances[remainingSteps-zg*d]
        #         zg += 1
        for entry,d in [((start[0],0),m),((start[0],m-1),m),((0,start[1]),n),((n-1,start[1]),n)]:
            
            distances = calcDistances(g,[entry])
            accDistances,maxDist = calcAccDistances(distances)

            distToCorner = (d-1)//2+1
            remainingSteps = maxSteps-distToCorner
            zg = 0
            if remainingSteps-maxDist >=0:
                zg = (remainingSteps-maxDist)//d+1
                ans += (zg//2)*accDistances[maxDist] + (zg//2)*accDistances[maxDist-1]
                if zg%2==1:
                    if remainingSteps%2==maxDist%2:
                        ans += accDistances[maxDist]
                    else:
                        ans += accDistances[maxDist-1]
                # zg += 1
            while remainingSteps-zg*d>=0:
                ans += accDistances[remainingSteps-zg*d]
                zg += 1

        
        print("Day 21 part 2:",ans)






part2()