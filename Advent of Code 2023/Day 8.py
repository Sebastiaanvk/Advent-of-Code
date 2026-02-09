import re
from math import lcm

def part1():
    inp = open("Day 8.txt").read().split("\n\n")
    steps = inp[0]
    adjList = {}
    for line in inp[1].split("\n"):
        m = re.match(r"(\w+) = \((\w+), (\w+)\)",line).groups()
        adjList[m[0]] = [m[1],m[2]]
    i = 0
    found = False
    current_pos = 'AAA'
    while not found:
        move  = steps[i%len(steps)]
        if move == 'L':
            current_pos = adjList[current_pos][0]
        else:
            current_pos = adjList[current_pos][1]
        if current_pos=='ZZZ':
            found = True
        i += 1
    print("Day 8 part 1:",i)


def part2():
    # Ok this only works for the specific type of input that advent of code gives.
    # The input is setup in a way that for each starting point, it reaches and end node after x steps
    # and then x is actually the length of the cycle afterwards.
    inp = open("Day 8.txt").read().split("\n\n")
    steps = inp[0]
    adjList = {}
    for line in inp[1].split("\n"):
        m = re.match(r"(\w+) = \((\w+), (\w+)\)",line).groups()
        adjList[m[0]] = [m[1],m[2]]
    i = 0
    # found = False
    current_positions = [name for name in adjList if name[-1]=='A'] 
    # print(current_positions)
    last_seen = [ 0 for _ in current_positions]
    loop_size = {}
    while len(loop_size)<len(last_seen):
        move  = steps[i%len(steps)]

        if move == 'L':
            for j in range(len(current_positions)):
                current_positions[j] = adjList[current_positions[j]][0]
        else:
            for j in range(len(current_positions)):
                current_positions[j] = adjList[current_positions[j]][1]

        # print(current_positions)
        # if all(list(map(lambda x: x[-1]=='Z',current_positions))):

        #     found = True
        i += 1
        for j in range(len(current_positions)):
            if current_positions[j][-1] == 'Z':
                loop_size[j] = i-last_seen[j]
                print(j, ": ", i-last_seen[j] )
                last_seen[j] = i
    loop_size_list = [loop_size[x] for x in loop_size]
    answer = loop_size_list[0]
    for i in range(1,len(loop_size_list)):
        answer = lcm(loop_size_list[i],answer)
    print("Day 8 part 2:",answer)


part1()
part2()