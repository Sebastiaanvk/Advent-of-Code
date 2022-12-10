


def part1():
    s = set([20,60,100,140,180,220])
    sum = 0
    cycle = 0
    register = 1
    grid = [["." for i in range(40)] for j in range(6)]
    for line in open("Day 10.txt", "r"):
        li = line.split()
        if li[0]=="noop":
            if abs(cycle%40 -register)<=1:
                grid[cycle//40][cycle%40] = "#"
            cycle += 1
            if (cycle+1) in s:
                sum += (cycle+1)*register
        else:
            x = int(li[1])
            if abs(cycle%40 -register)<=1:
                grid[cycle//40][cycle%40] = "#"

            cycle += 1
            if cycle+1 in s:
                sum += (cycle+1)*register
            if abs(cycle%40 -register)<=1:
                grid[cycle//40][cycle%40] = "#"
  
            cycle+=1
            register += x
            if (cycle+1) in s:
                sum+= (cycle+1)*register

    print("Part1:",sum)
    for row in range(6):
        str = ""
        for i in range(40):
            str += grid[row][i]
        print(str)
part1()
