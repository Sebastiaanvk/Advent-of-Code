

def in_range(x,y,width,height):
    return x>=0 and y>=0 and x<width and y<height

def part1():
    grid = open("Day 12.txt","r").read().split()
    width = len(grid[0])
    height = len(grid)
    x,y= 0,0
    for i in range(width):
        for j in range(height):
            if grid[j][i]=="S":
                x, y= i,j
    min_steps = {(x,y):0}
    queue = [(x,y)]

    dirs_x = [1,-1,0,0]
    dirs_y = [0,0,1,-1]
    found = False
    answer = 0
    while(len(queue) and not found):
        x,y = queue.pop(0)
        for i in range(4):
            new_x = x+dirs_x[i]
            new_y = y+dirs_y[i]
            if in_range(new_x,new_y,width,height):
                if grid[new_y][new_x]=="E":
                    if grid[y][x]=="z" or grid[y][x]=="y":
                        answer = min_steps[(x,y)]+1
                        found = True
                        break
                elif grid[y][x]=="S" or ord(grid[new_y][new_x]) <= ord(grid[y][x])+1:
                    if (new_x,new_y) not in min_steps:
                        min_steps[(new_x,new_y)] = min_steps[(x,y)]+1
                        queue.append((new_x,new_y))
    print("Part1:",answer)

def min_steps(grid,x,y):
    width = len(grid[0])
    height = len(grid)
    min_steps = {(x,y):0}
    queue = [(x,y)]

    dirs_x = [1,-1,0,0]
    dirs_y = [0,0,1,-1]
    while(len(queue)):
        x,y = queue.pop(0)
        for i in range(4):
            new_x = x+dirs_x[i]
            new_y = y+dirs_y[i]
            if in_range(new_x,new_y,width,height):
                if grid[new_y][new_x]=="E":
                    if grid[y][x]=="z" or grid[y][x]=="y":
                        return min_steps[(x,y)]+1
                elif ord(grid[new_y][new_x]) <= ord(grid[y][x])+1:
                    if (new_x,new_y) not in min_steps:
                        min_steps[(new_x,new_y)] = min_steps[(x,y)]+1
                        queue.append((new_x,new_y))
    return 1000000


def part2():
    grid = open("Day 12.txt","r").read().split()
    width = len(grid[0])
    height = len(grid)
    mini = 10000000
    for i in range(width):
        for j in range(height):
            if grid[j][i]=="a":
                mini = min(mini,min_steps(grid,i,j))
    
    
    print("Part2:",mini)
part1()
part2()