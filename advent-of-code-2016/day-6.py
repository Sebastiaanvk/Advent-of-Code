from collections import defaultdict

def part1():
    inp = open("day-6.txt").read().split('\n')[:-1]
    ans = ""
    for col in range(len(inp[0])):
        d = defaultdict(int)
        for row in range(len(inp)):
            d[inp[row][col]] += 1
        max = 0
        maxChar = 'a'
        for key in d:
            if d[key]>max:
                max = d[key]
                maxChar = key
        ans = ans + maxChar
    print(ans)

part1()
def part2():
    inp = open("day-6.txt").read().split('\n')[:-1]
    ans = ""
    for col in range(len(inp[0])):
        d = defaultdict(int)
        for row in range(len(inp)):
            d[inp[row][col]] += 1
        max = 100000000
        maxChar = 'a'
        for key in d:
            if d[key]<max:
                max = d[key]
                maxChar = key
        ans = ans + maxChar
    print(ans)

part2()