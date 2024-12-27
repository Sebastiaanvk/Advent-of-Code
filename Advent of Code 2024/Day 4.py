
dirs = [(0,1),(1,0),(1,1),(1,-1)]


def part1():
    input = open("Day 4.txt").read().split()
    width = len(input[0])
    height = len(input)

    count = 0

    for y in range(height):
        for x in range(width):
            for (dx,dy) in dirs:
                if 0 <= y+3*dy < height and 0 <= x+3*dx < width:
                    word = [input[y+i*dy][x+i*dx] for i in range(4)]
                    if word==['X','M','A','S'] or word==['S','A','M','X']:
                        count += 1

    
    print("The answer to day 4 part 1 is: ", count)



part1()

def part2():
    input = open("Day 4.txt").read().split()
    width = len(input[0])
    height = len(input)

    count = 0

    for y in range(1, height-1):
        for x in range(1, width-1):
            if input[y][x] == 'A':
                set1 = {input[y-1][x-1], input[y+1][x+1]}
                set2 = {input[y+1][x-1], input[y-1][x+1]}
                if set1 == {'M','S'} and set2 == {'M','S'}:
                    count += 1
    
    print("The answer to day 4 part 1 is: ", count)




part2()
