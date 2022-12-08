import itertools
dirs = [(0,1),(0,-1),(-1,0),(1,0)]

def in_range(x,y,grid):
    if x<0 or y<0:
        return False
    if x>=len(grid[0]) or y>=len(grid):
        return False
    return True

def part1():
    grid = open("Day 8.txt","r").read().split("\n")[:-1]
    visible = 2*len(grid)+2*len(grid[0])-4
    max_score = 0
    for (p1,p2) in itertools.product(range(1,len(grid[0])-1),range(1,len(grid)-1)):
        vis = False
        score = 1
        for (d1,d2) in dirs:
            x,y = p1+d1,p2+d2
            see = True
            dist = 0
            while(in_range(x,y,grid) and see):
                if(int(grid[y][x])>=int(grid[p2][p1])):
                    see = False
                x += d1
                y += d2
                dist += 1
            if see:
                vis = True
            score *= dist
        if vis:
            visible += 1
        max_score = max(max_score,score)
                
    print("Part1: ",visible)
    print("Part2: ",max_score)
part1()