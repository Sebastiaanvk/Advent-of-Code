from collections import defaultdict
import itertools
# import copy

import sys
sys.setrecursionlimit(10000)

def dfsRec(current, end, adjList, seen,path):
    if current==end:
        return True
    for y in adjList[current]:
        if y not in seen:
            seen.add(y)
            path.append(y)
            if dfsRec(y,end, adjList, seen, path):
                return True
            path.pop()
    return False



def dfs(start, end, adjList):
    seen = set([start])
    path = [start]
    if dfsRec(start, end, adjList, seen, path):
        return path
    return None

    
def maxFlowUptoFour(source,target,adjList):
    flow = 0
    pathFound = True
    augmentedEdges = set()

    while pathFound and flow<4: 
        path = dfs(source,target,adjList)
        if path==None:
            pathFound = False
        else:
            flow += 1
            for x,y in zip(path[:-1],path[1:]):
                if (x,y) in augmentedEdges:
                    adjList[y].add(x)
                    augmentedEdges.remove((x,y))
                else:
                    augmentedEdges.add((y,x))
                    adjList[x].remove(y)
    for (x,y) in augmentedEdges:
        adjList[y].add(x)
    return flow

def clusterSizeRec(current,adjList,seen):
    for y in adjList[current]:
        if y not in seen:
            seen.add(y)
            clusterSizeRec(y,adjList,seen)

def clusterSize(start,adjList):
    seen = set([start])
    clusterSizeRec(start, adjList, seen)
    return len(seen)

# Pretty straightforward
# We first find two nodes for which the max flow between them is three
# then we brute force by removing each edge and seeing whether the max flow drops
# Obviously it could be heavily optimized by only considering the edges on the paths that are part of the max flow
# But yeah this was the simplest way to do it and its already fast enough (couple of seconds)

def part1():
    with open("Day 25.txt") as f:
        adjList = defaultdict(set)
        for lineStr in f.read().split("\n"):
            line = lineStr.split(" ")
            s = line[0][:-1]
            for t in line[1:]:
                adjList[s].add(t)
                adjList[t].add(s)
        # print(adjList)
        source, target  = "", ""
        for s,t in itertools.combinations(adjList,2):
                # if maxFlowUptoFour(s,t,copy.deepcopy(adjList))<4:
                if maxFlowUptoFour(s,t,adjList)<4:
                    source,target = s,t
                    break
        # print(adjList)
        for i in range(3):
            for s,t in itertools.combinations(adjList,2):
                if t in adjList[s]:
                    # assert(s in adjList[t])
                    adjList[s].remove(t)
                    adjList[t].remove(s)
                    if maxFlowUptoFour(s,t,adjList)<=2-i:
                        break
                    else:
                        adjList[s].add(t)
                        adjList[t].add(s)
        cs = clusterSize(source,adjList)
        print("Day 25 part 1:",(len(adjList)-cs)*(cs))

part1()