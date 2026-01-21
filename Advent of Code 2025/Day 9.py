import itertools

def part1():
    locs = [ (int(x.split(",")[0]),int(x.split(",")[1])) for x in open("Day 9.txt").read().split('\n')]
    rectSizes = [ (abs(locs[i][0]-locs[j][0])+1) * (abs(locs[i][1]-locs[j][1])+1) for (i,j) in itertools.permutations(range(len(locs)),2)]
    print("Day 9 part 1:",max(rectSizes))


def inInteriorRectangle(edge, corner1, corner2):
    left = min(corner1[0],corner2[0])
    right = max(corner1[0],corner2[0])
    top = min(corner1[1],corner2[1])
    bottom = max(corner1[1],corner2[1])
    edgeLeft = min(edge[0][0],edge[1][0])
    edgeRight = max(edge[0][0],edge[1][0])
    edgeTop = min(edge[0][1],edge[1][1])
    edgeBottom = max(edge[0][1],edge[1][1])
    if edgeRight<=left or edgeLeft>=right or edgeBottom<=top or  edgeTop>=bottom:
        return False
    return True


def edgeInRectangle(edges,corner1,corner2):
    for edge in edges:
        if inInteriorRectangle(edge,corner1,corner2):
            return True
    return False


def part2():
    locs = [ (int(x.split(",")[0]),int(x.split(",")[1])) for x in open("Day 9.txt").read().split('\n')]

    rects = [ ((abs(locs[i][0]-locs[j][0])+1) * (abs(locs[i][1]-locs[j][1])+1),i,j) for (i,j) in itertools.combinations(range(len(locs)),2)]
    rects.sort(reverse=True,key= lambda x: x[0])
    # print(rects)
    edges = []
    locs.append(locs[0])
    for i in range(len(locs)-1):
        loc1=locs[i]
        loc2=locs[i+1]
        edges.append((loc1,loc2))
        # if loc1[0]==loc2[0]:
        #     for x in range(min(loc1[1],loc2[1]),max(loc1[1],loc2[1])+1):
        #         pointsOnEdge.append((loc1[0],x))
        # else:
        #     for y in range(min(loc1[0],loc2[0]),max(loc1[0],loc2[0])+1):
        #         pointsOnEdge.append((loc1[0],y))
    found = False
    i=-1
    while not found:
        i+=1
        # I am assuming that if an edge is in the interior of the rectangle then the rectangle has non green or red tiles
        # There is a counterexample you can have two edges that are adjacent to each other
        # But yeah sometimes in advent of code you can make these assumptions
        if not edgeInRectangle(edges,locs[rects[i][1]],locs[rects[i][2]]):
            found = True
    print("Day 9 part 2:",rects[i][0])
        



part1()
part2()