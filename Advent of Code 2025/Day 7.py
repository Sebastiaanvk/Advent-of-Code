def part1():
    input = open("Day 7.txt").read().split('\n')
    manifold = [[x for x in line] for line in input]
    width = len(manifold[0])
    for i in range(width):
        if manifold[0][i] == 'S':
            manifold[1][i] = '|'
    splits = 0
    for y in range(2,len(manifold)):
        for x in range(width):
            if manifold[y-1][x] == '|':
                if manifold[y][x] == '^':
                    splits += 1
                    manifold[y][x-1],manifold[y][x+1] = '|','|'
                elif manifold[y][x] == '.':
                    manifold[y][x] = '|'
    print("Day 7 part 1:",splits)
        
def part2():
    input = open("Day 7.txt").read().split('\n')
    manifold = [[x for x in line] for line in input]
    timelines = [[0 for x in line] for line in input]
    width = len(manifold[0])
    for i in range(width):
        if manifold[0][i] == 'S':
            timelines[1][i] = 1
    for y in range(2,len(manifold)):
        for x in range(width):
            if manifold[y][x] != '^':
                timelines[y][x] = timelines[y-1][x]
            if x>0 and manifold[y][x-1]== '^':
                timelines[y][x] += timelines[y-1][x-1]
            if x<width-1 and manifold[y][x+1]=='^':
                timelines[y][x] += timelines[y-1][x+1]
    totalTimelines = 0    
    for x in timelines[-1]:
        totalTimelines += x
    print("Day 7 part 2:",totalTimelines)
part1() 

part2() 