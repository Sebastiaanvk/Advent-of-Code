

locToDigit = {(-1,-1):1,(-1,0):2,(-1,1):3,
              (0,-1):4,(0,0):5,(0,1):6,
              (1,-1):7,(1,0):8,(1,1):9}

def part1():
    input = open("day-2.txt").read().split('\n')[:-1]
    x=0
    y=0
    code = ""
    for line in input:
        for c in line:
            if c=='U':
                y = max(-1,y-1)
            elif c=='D':
                y = min(1,y+1)
            elif c=='L':
                x = max(-1,x-1)
            else:
                x = min(1,x+1)
        code += str(locToDigit[(y,x)] )
    print("Part 1: ",code)

part1()

locToDigit2 = {(-1,-1):'2',(-1,0):'3',(-1,1):'4',
              (0,-1):'6',(0,0):'7',(0,1):'8',
              (1,-1):'A',(1,0):'B',(1,1):'C',
                (-2,0):'1', (0,-2):'5',(0,2):'9',(2,0):'D' }

def part2():
    input = open("day-2.txt").read().split('\n')[:-1]
    x=0
    y=0
    code = ""
    for line in input:
        for c in line:
            if c=='U':
                if abs(x)+abs(y-1)<=2:
                    y -= 1
            elif c=='D':
                if abs(x)+abs(y+1)<=2:
                    y += 1
            elif c=='L':
                if abs(x-1)+abs(y)<=2:
                    x -= 1
            else:
                if abs(x+1)+abs(y)<=2:
                    x += 1
        code += locToDigit2[(y,x)]
    print("Part 2: ",code)

part2()
