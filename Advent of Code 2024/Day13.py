


def part1():

    input = open("Day13.txt").read().split("\n\n")
    #input = open("test13.txt").read().split("\n\n")
    sum = 0
    for ln in  input:
        s = [ q.split() for q in ln.split("\n")]
        x1,y1 = int(s[0][2][2:-1]), int(s[0][3][2:])
        x2,y2 = int(s[1][2][2:-1]), int(s[1][3][2:])
        x,y = int(s[2][1][2:-1]), int(s[2][2][2:])

        if (x*y1-y*x1) % (x2*y1-y2*x1) == 0:
            b = (x*y1-y*x1) // (x2*y1-y2*x1)
            if b>=0 and (x-b*x2) % x1 ==0:
                a = (x-b*x2) // x1
                if a>=0:
                    sum += 3*a + b
#                    print(a,b)



    print("Day13 part1: ",sum)

part1()


def part2():

    input = open("Day13.txt").read().split("\n\n")
    #input = open("test13.txt").read().split("\n\n")
    sum = 0
    for ln in  input:
        s = [ q.split() for q in ln.split("\n")]
        x1,y1 = int(s[0][2][2:-1]), int(s[0][3][2:])
        x2,y2 = int(s[1][2][2:-1]), int(s[1][3][2:])
        x,y = int(s[2][1][2:-1])+10000000000000, int(s[2][2][2:])+10000000000000

        if (x*y1-y*x1) % (x2*y1-y2*x1) == 0:
            b = (x*y1-y*x1) // (x2*y1-y2*x1)
            if b>=0 and (x-b*x2) % x1 ==0:
                a = (x-b*x2) // x1
                if a>=0:
                    sum += 3*a + b
#                    print(a,b)



    print("Day13 part2: ",sum)






part2()