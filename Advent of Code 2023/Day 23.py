import sys
from collections import defaultdict
sys.setrecursionlimit(10000)



def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def explore(current, grid, traversedFields, maxDist):
    if current == (len(grid)-1,len(grid[0])-2):
        maxDist[0] = max(maxDist[0],len(traversedFields))
        return
    traversedFields.add(current)
    dirs = ((0,1),(1,0),(0,-1),(-1,0))
    arrowDir = {
        '>': (0,1),
        'v': (1,0),
        '<': (0,-1),
        '^': (-1,0),
        '.': (0,0)
    }
    currentChar = grid[current[0]][current[1]]
    nSquares = []
    assert(currentChar!='#')
    if currentChar == '.':
        for direction in dirs:
            nextLoc = tupleAdd(current,direction)
            nChar = grid[nextLoc[0]][nextLoc[1]]
            if nChar!='#' and tupleAdd(direction,arrowDir[nChar])!=(0,0):
                nSquares.append(nextLoc)
    else:
        direction = arrowDir[currentChar]
        nextLoc = tupleAdd(current,direction)
        nSquares.append(nextLoc)
    for nLoc in nSquares:
        if nLoc not in traversedFields:
            explore(nLoc, grid, traversedFields,maxDist)
    traversedFields.remove(current)
    return




def part1():
    with open("Day 23.txt") as f:
        g = f.read().split('\n')
        # Save the grid as a directed graph beforehand?
        # Or just do it on the grid? Will be slower, but might be easier to program
        # Ok lets do it the simplest way and see whether its fast enough
        maxDist = [0]
        traversedFields = set((0,0))
        explore((1,1),g,traversedFields,maxDist)
        print("Day 23 part 1:",maxDist[0])

part1()

def createGraphRec(g,loc,lastNode,pathsSeen,dist, adjList):
    n,m = len(g),len(g[0])
    if loc == (n-1,m-2):
        adjList[loc].append((lastNode,dist))
        adjList[lastNode].append((loc,dist))
        return
    dirs = [(0,1),(1,0),(0,-1),(-1,0)]
    adjCand = [tupleAdd(loc,d) for d in dirs]
    adjLegal = []
    # print("loc:",loc)
    for nl in adjCand:
        # print(nl)
        if g[nl[0]][nl[1]] != '#':
            adjLegal.append(nl)
    # adjLegal = [nl for nl in adjCand if g[nl[0]][nl[1]] != '#']
    if len(adjLegal)>2:
        adjList[loc].append((lastNode,dist))
        adjList[lastNode].append((loc,dist))
        for nLoc in adjLegal:
            if nLoc not in pathsSeen:
                createGraphRec(g,nLoc,loc,pathsSeen,1,adjList)
    else:
        pathsSeen.add(loc)
        for nLoc in adjLegal:
            if nLoc not in pathsSeen and nLoc!=lastNode:
                createGraphRec(g,nLoc,lastNode,pathsSeen,dist+1,adjList)

def createGraph(g):
    adjList = defaultdict(list)
    pathsSeen = set((0,1))
    createGraphRec(g,(1,1),(0,1),pathsSeen,1, adjList)
    return adjList

def exploreGraph(current, goal, adjList, traversedNodes, currentDist, maxDist):
    if current == goal:
        maxDist[0] = max(maxDist[0],currentDist)
        return
    traversedNodes.add(current)
    for nextNode,stepDist in adjList[current]:
        if nextNode not in traversedNodes:
            exploreGraph(nextNode, goal, adjList, traversedNodes, currentDist+stepDist, maxDist)
    traversedNodes.remove(current)
    return

def part2():
    with open("Day 23.txt") as f:
        g = f.read().split('\n')
        adjList = createGraph(g)
        # print(adjList)
        maxDist = [0]
        traversedNodes = set()
        exploreGraph((0,1),(len(g)-1,len(g[0])-2),adjList, traversedNodes,0,maxDist)

        print("Day 23 part 2:",maxDist[0])

part2()