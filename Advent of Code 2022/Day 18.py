diffs = [
    (1,0,0),
    (-1,0,0),
    (0,1,0),
    (0,-1,0),
    (0,0,1),
    (0,0,-1),
]

def part1():
    cubes = set([])
    input = open("Day 18.txt","r").read().split()
    sides = 0
    for line in input:
        x,y,z = map(int,line.split(","))
        sides += 6
        for (dx,dy,dz) in  diffs:
            if (x+dx,y+dy,z+dz) in cubes:
                sides -= 2
        cubes.add((x,y,z))
    print("Day 18 part 1: ",sides)

def within_cube(x,y,z,minimum,maximum):
    if x<minimum[0] or y < minimum[1] or z < minimum[2]:
        return False
    if x>maximum[0] or y > maximum[1] or z > maximum[2]:
        return False
    return True

# I did this first with normal recursion, but apparently python cant handle deep recursions
# So we are doing it with iterative dfs instead
def dfs(start,cubes,minimum,maximum):
    nrSides = 0 
    stack = [start]
    explored = set([])

    while stack:
        current_location = stack.pop()
        if current_location in explored:
            continue
        explored.add(current_location)
        x,y,z = current_location
        for dx,dy,dz in diffs:
            newX,newY,newZ = x+dx,y+dy,z+dz
            if within_cube(newX,newY,newZ,minimum,maximum):
                if (newX,newY,newZ) in cubes:
                    nrSides += 1
                elif (newX,newY,newZ) not in explored:
                    stack.append((newX,newY,newZ))

    return nrSides

    

def part2():
    cubes = set([])
    input = open("Day 18.txt","r").read().split()
    minX,minY,minZ = float('inf'),float('inf'),float('inf')
    maxX, maxY, maxZ = float('-inf'),float('-inf'),float('-inf')
    for line in input:
        x,y,z = map(int,line.split(","))
        cubes.add((x,y,z))
        minX = min(minX,x)
        maxX = max(maxX,x)
        minY = min(minY,y)
        maxY = max(maxY,y)
        minZ = min(minZ,z)
        maxZ = max(maxZ,z)

    minimum = (minX-1,minY-1,minZ-1)
    maximum = (maxX+1,maxY+1,maxZ+1)

    current_location = minimum
    nrSides = dfs(current_location,cubes,minimum,maximum)

    print("Day 18 part 1: ",nrSides)


part1()
part2()