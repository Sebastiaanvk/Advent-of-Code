def part1():
    inp = open("Day 11.txt").read().split('\n')
    adjList = {}
    for line in inp:
        spl = line.split()
        adj = [x for x in spl[1:]]
        adjList[spl[0][:-1]] = adj
    totalToOut = 0
    paths = {"you":1}
    while len(paths):
        newPaths = {}
        for s in paths:
            for t in adjList[s]: 
                if t=="out":
                    totalToOut += paths[s]
                else:
                    newPaths[t] = newPaths.get(t,0) +paths[s]
        paths = newPaths
    print("Day 11 part 1:",totalToOut)


def countPaths(adjList,source, target, illegal):
    totalToTarget = 0
    paths = {source:1}
    while len(paths):
        newPaths = {}
        for s in paths:
            for t in adjList[s]: 
                if t==target:
                    totalToTarget += paths[s]
                elif t != illegal and t != "out" :
                    newPaths[t] = newPaths.get(t,0) +paths[s]
        paths = newPaths
    return totalToTarget




def part2():
    inp = open("Day 11.txt").read().split('\n')
    adjList = {}
    for line in inp:
        spl = line.split()
        adj = [x for x in spl[1:]]
        adjList[spl[0][:-1]] = adj
    svrToDac = countPaths(adjList,"svr", "dac","fft")
    svrToFft = countPaths(adjList,"svr","fft", "dac")
    dacToOut = countPaths(adjList,"dac","out", "fft")
    fftToOut = countPaths(adjList,"fft","out", "dac")
    dacToFft = countPaths(adjList,"dac","fft", "out")
    fftToDac = countPaths(adjList,"fft","dac", "out")
    total = svrToDac*dacToFft*fftToOut + svrToFft*fftToDac*dacToOut
    print("Day 11 part 2:",total)

part1()
part2()