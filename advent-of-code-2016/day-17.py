from collections import deque
import hashlib

dirs = [-1j,1j,-1,1]
dirChars = ['U','D','L','R']


def part1():
    inp = "njfxhljp"
    Q = deque()
    Q.append((0,""))
    longestPath = ""
    shortestPathFound = False

    while len(Q) > 0:
        pos,path = Q.popleft()
        hash = hashlib.md5((inp+path).encode()).hexdigest()
        for i in range(4):
            if hash[i] in ['b','c','d','e','f']:
                newPos = pos + dirs[i]
                if newPos == 3+3j:
                    if not shortestPathFound:
                        shortestPathFound = True
                        print("Part 1: ", path+dirChars[i]) 
                    longestPath = path+dirChars[i]
                elif 0<=newPos.real <4 and 0<=newPos.imag < 4:
                    Q.append((newPos,path+dirChars[i]))
    print("Part 2: ",len(longestPath))
                





part1()