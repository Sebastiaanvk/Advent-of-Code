from collections import defaultdict, deque

def tupleAdd(t1,t2):
    return tuple(x+y for x,y in zip(t1,t2))

def lowerBlock(block):
    return (tupleAdd(block[0],(0,0,-1)),tupleAdd(block[1],(0,0,-1)))

def cubesInBlock(block):
    s,t = block
    if s==t:
        yield s
        return
    for j in range(3):
        if s[j]!=t[j]:
            if t[j]<s[j]:
                s,t=t,s
            dl = [0,0,0]
            dl[j] = 1
            d = tuple(dl)
            while s!=t:
                yield s
                s = tupleAdd(s,d)
            yield t
            break

def cubesBelowBlock(block):
    s,t = block
    if s==t:
        yield tupleAdd(s,(0,0,-1))
        return
    for j in range(3):
        if s[j]!=t[j]:
            if t[j]<s[j]:
                s,t=t,s
            if j==2:
                yield tupleAdd(s,(0,0,-1))
                return
            dl = [0,0,0]
            dl[j] = 1
            d = tuple(dl)
            while s!=t:
                yield tupleAdd(s,(0,0,-1))
                s = tupleAdd(s,d)
            yield tupleAdd(t,(0,0,-1))
            break

def placeBlocksInSpace(blocks):
    cubes = {}
    for id,block in enumerate(blocks):
        for c in cubesInBlock(block):
            cubes[c] = id
    return cubes

def belowFree(block, cubes):
    if min(block[0][2],block[1][2])==1:
        return False

    for c in cubesBelowBlock(block):
        if c in cubes:
            return False
    return True

def part1():
    with open("Day 22.txt") as f:
        blocks = list(map(lambda x: tuple(map(lambda y: tuple(map(int,y.split(','))) ,x.split('~'))),f.read().split('\n')))
        blocksMoved = True
        while blocksMoved:
            blocksMoved = False
            cubes = placeBlocksInSpace(blocks)
            newBlocks = []
            for block in blocks:
                nBlock = block
                while belowFree(nBlock,cubes):
                    blocksMoved = True
                    nBlock = lowerBlock(nBlock)
                newBlocks.append(nBlock)
            blocks = newBlocks

        bricksAbove = defaultdict(set)
        bricksBelow = defaultdict(set)
        cubes = placeBlocksInSpace(blocks)
        for id,block in enumerate(blocks):
            for c in cubesBelowBlock(block):
                if c in cubes:
                    bricksAbove[cubes[c]].add(id)
                    bricksBelow[id].add(cubes[c])
        # print(bricksAbove)
        # print(bricksBelow)
        ans = 0
        # print(blocks)
        for id in range(len(blocks)):
            holdsSingleResponsibility = False
            for x in bricksAbove[id]:
                if len(bricksBelow[x])==1:
                    holdsSingleResponsibility = True
                    break
            if not holdsSingleResponsibility:
                ans += 1
        print("Day 22 part 1",ans)

part1()

def blocksThatWouldFall(id, bricksAbove, bricksBelow):
    q = deque()
    moved = set()
    moved.add(id)
    q.append(id)
    while len(q):
        current = q.popleft()
        for x in bricksAbove[current]:
            if all([y in moved for y in bricksBelow[x]]):
                moved.add(x)
                q.append(x)
    return len(moved)-1



def part2():
    with open("Day 22.txt") as f:
        blocks = list(map(lambda x: tuple(map(lambda y: tuple(map(int,y.split(','))) ,x.split('~'))),f.read().split('\n')))
        blocksMoved = True
        while blocksMoved:
            blocksMoved = False
            cubes = placeBlocksInSpace(blocks)
            newBlocks = []
            for block in blocks:
                nBlock = block
                while belowFree(nBlock,cubes):
                    blocksMoved = True
                    nBlock = lowerBlock(nBlock)
                newBlocks.append(nBlock)
            blocks = newBlocks

        bricksAbove = defaultdict(set)
        bricksBelow = defaultdict(set)
        cubes = placeBlocksInSpace(blocks)
        for id,block in enumerate(blocks):
            for c in cubesBelowBlock(block):
                if c in cubes:
                    bricksAbove[cubes[c]].add(id)
                    bricksBelow[id].add(cubes[c])
        # print(bricksAbove)
        # print(bricksBelow)
        ans = 0
        # print(blocks)
        for id in range(len(blocks)):
            ans += blocksThatWouldFall(id,bricksAbove,bricksBelow)
        print("Day 22 part 2",ans)





part2()




# def part1():
#     with open("Test 22.txt") as f:
#         blocks = list(map(lambda x: tuple(map(lambda y: tuple(map(int,y.split(','))) ,x.split('~'))),f.read().split('\n')))
#         cubes = {}
#         for id,block in enumerate(blocks):
#             for c in cubesInBlock(block):
#                 cubes[c] = id
#         # print(cubes)

#         bricksAbove = defaultdict(set)
#         bricksBelow = defaultdict(set)
#         for id,block in enumerate(blocks):
#             cubesBelow = list(cubesBelowBlock(block))
#             if len(cubesBelow)>0:
#                 cubeHit = False
#                 while cubesBelow[0][2]>0 and not cubeHit:
#                     for c in cubesBelow:
#                         if c in cubes:
#                             bricksBelow[id].add(cubes[c])
#                             bricksAbove[cubes[c]].add(id)
#                             cubeHit = True
#                     cubesBelow = [tupleAdd(c,(0,0,-1)) for x in cubesBelow] 
        
#         ans = 0
#         # print(bricksAbove)
#         # print(bricksBelow)
#         for id in range(len(blocks)):
#             # print(id)
#             # print(bricksAbove[id])
#             holdsSingleResponsibility = False
#             for x in bricksAbove[id]:
#                 if len(bricksBelow[x])==1:
#                     holdsSingleResponsibility = True
#                     continue
#             if not holdsSingleResponsibility:
#                 ans += 1
#         print("Day 22 part 1",ans)