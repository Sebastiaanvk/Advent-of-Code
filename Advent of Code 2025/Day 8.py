

def calcDistSq(loc1, loc2):
    return (loc1[0]-loc2[0])**2+(loc1[1]-loc2[1])**2+(loc1[2]-loc2[2])**2

def dfs(pos, adjList, explored):
    size = 1
    explored[pos] = True 
    for y in adjList[pos]:
        if not explored[y]:
            size += dfs(y,adjList, explored)

    return size





def part1():
    # input = open("Test 8.txt").read().split('\n')
    input = open("Day 8.txt").read().split('\n')
    locs = []
    for line in input:
        x,y,z = line.split(',')
        locs.append((int(x),int(y),int(z)))
    # distancesSqDict = {}
    distsSqList = []
    for i in range(len(locs)):
        for j in range(i+1,len(locs)):
            # distancesSqDict[(i,j)] = calcDistSq(locs[i],locs[j])
            distsSqList.append( ( calcDistSq(locs[i],locs[j]),i,j) ) 
    distsSqList.sort(key= lambda t: t[0])

    adjacencyList = [[] for i in range(len(locs))]
    for i in range(1000):
    # for i in range(10):
        x,y = distsSqList[i][1],distsSqList[i][2]
        adjacencyList[x].append(y)
        adjacencyList[y].append(x)
    explored = [False for x in locs]
    clusterSizes = []
    for x in range(len(locs)):
        if not explored[x]:
            clusterSizes.append(dfs(x,adjacencyList,explored))
    # print(clusterSizes)
    clusterSizes.sort(reverse=True)

    print("Day 8 part 1:",clusterSizes[0]*clusterSizes[1]*clusterSizes[2])

def parentRoot(x, parents):
    while parents[x]!=-1:
        x = parents[x]
    return x
    


def part2():
    # input = open("Test 8.txt").read().split('\n')
    input = open("Day 8.txt").read().split('\n')
    locs = []
    for line in input:
        x,y,z = line.split(',')
        locs.append((int(x),int(y),int(z)))
    # distancesSqDict = {}
    distsSqList = []
    for i in range(len(locs)):
        for j in range(i+1,len(locs)):
            # distancesSqDict[(i,j)] = calcDistSq(locs[i],locs[j])
            distsSqList.append( ( calcDistSq(locs[i],locs[j]),i,j) ) 
    distsSqList.sort(key= lambda t: t[0])

    parents = [-1 for x in locs]
    nrClusters = len(locs)

    i = -1
    while nrClusters > 1:
        i += 1
        x,y = distsSqList[i][1],distsSqList[i][2]
        parentRootX = parentRoot(x,parents)
        parentRootY = parentRoot(y,parents)
        if parentRootX!=parentRootY:
            nrClusters-=1
            parents[parentRootX] = parentRootY
    lastX,lastY = distsSqList[i][1],distsSqList[i][2]


    print("Day 8 part 2:",locs[lastX][0]*locs[lastY][0])


part1()

part2()