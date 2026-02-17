import heapq

def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def part1():
    with open("Day 17.txt") as f:
        g = f.read().split('\n')
        n,m = len(g),len(g[0])
        pq = []
        dirs = [(0,1),(1,0),(0,-1),(-1,0)]
        minDist = {}
        endFound = False
        heapq.heappush( pq,(0, ( (0,0), 0, 0)) )
        minEnd = 0
        while not endFound:
            (dist,(loc, dirI, straightSteps)) = heapq.heappop(pq)
            if loc==(n-1,m-1):
                endFound = True
                minEnd = dist
            elif (loc,dirI,straightSteps) not in minDist:
                minDist[(loc,dirI, straightSteps)] = dist
                nextSteps = [ ((dirI-1)%4,1),((dirI+1)%4,1)]
                if straightSteps<3:
                    nextSteps.append((dirI,straightSteps+1))
                for nDirI,nStraightSteps in nextSteps:
                    ny,nx = tupleAdd(loc,dirs[nDirI])
                    if 0<=ny<n and 0<=nx<m and ((ny,nx),nDirI,nStraightSteps) not in minDist:
                        heapq.heappush(pq,(dist+int(g[ny][nx]),((ny,nx),nDirI,nStraightSteps)))

        print("Day 17 part 1:",minEnd)

part1()

def part2():
    with open("Day 17.txt") as f:
        g = f.read().split('\n')
        n,m = len(g),len(g[0])
        pq = []
        dirs = [(0,1),(1,0),(0,-1),(-1,0)]
        minDist = {}
        endFound = False
        heapq.heappush( pq,(0, ( (0,0), 0, 0)) )
        minEnd = 0
        while not endFound:
            (dist,(loc, dirI, straightSteps)) = heapq.heappop(pq)
            if loc==(n-1,m-1):
                endFound = True
                minEnd = dist
            elif (loc,dirI,straightSteps) not in minDist:
                minDist[(loc,dirI, straightSteps)] = dist
                nextSteps = []
                if straightSteps>=4:
                    nextSteps.append(((dirI-1)%4,1))
                    nextSteps.append(((dirI+1)%4,1))
                if straightSteps<10:
                    nextSteps.append((dirI,straightSteps+1))
                for nDirI,nStraightSteps in nextSteps:
                    ny,nx = tupleAdd(loc,dirs[nDirI])
                    if 0<=ny<n and 0<=nx<m and ((ny,nx),nDirI,nStraightSteps) not in minDist:
                        heapq.heappush(pq,(dist+int(g[ny][nx]),((ny,nx),nDirI,nStraightSteps)))

        print("Day 17 part 2:",minEnd)

part2()