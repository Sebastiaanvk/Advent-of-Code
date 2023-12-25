

def part1():
    input = open("Day 2.txt","r").read().split("\n")[:-1]
    sum = 0
    for l in input:
        ind,fruits = l.split(":")
        fruits = fruits.split(";")
        ok = True
        for x in fruits:
            x = x.split(",")
            for y in x:
                y = y.split(" ")
                if y[2]=="green" and int(y[1])>13:
                    ok = False
                if y[2]=="red" and int(y[1])>12:
                    ok = False
                if y[2]=="blue" and int(y[1])>14:
                    ok = False
        if ok:
            sum += int(ind.split(" ")[1])

    print("Part 1:",sum)

part1()

def part2():
    input = open("Day 2.txt","r").read().split("\n")[:-1]
    sum = 0
    for l in input:
        ind,fruits = l.split(":")
        fruits = fruits.split(";")
        redmin,greenmin,bluemin =0,0,0
        for x in fruits:
            x = x.split(",")
            for y in x:
                y = y.split(" ")
                if y[2]=="green":
                    greenmin = max(greenmin,int(y[1]))
                if y[2]=="red":
                    redmin = max(redmin,int(y[1]))
                if y[2]=="blue":
                    bluemin = max(bluemin,int(y[1]))
        sum += redmin*greenmin*bluemin
    print("Part 2:",sum)

part2()