


def part1(memSize):
    x = open("day-16.txt").read()[:-1]
    while len(x) < memSize:
        initLength = len(x)
        x += '0'
        for i in range(initLength-1,0-1,-1):
            if x[i] == '0':
                x += '1'
            else:
                x += '0'
    x = x[:memSize]
    while len(x)%2==0:
        y = ''
        for i in range(0,len(x),2):
            if x[i]==x[i+1]:
                y += '1'
            else:
                y += '0'
        x = y
    print("Answer: ",x)

part1(272)
part1(35651584)