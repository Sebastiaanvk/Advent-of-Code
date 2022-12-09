


def part1():
    
    s = set()
    head_y,head_x = 0,0
    tail_y,tail_x = 0,0
    s.add((tail_y,tail_x))
    dirs_y = {"U":-1,"D":1,"R":0,"L":0}
    dirs_x = {"U":0,"D":0,"R":1,"L":-1}
    for line in open("Day 9.txt","r"):
        dir,i = line.split()
        i = int(i)
        while i>0:
            head_y += dirs_y[dir]
            head_x += dirs_x[dir]
            if abs(head_y-tail_y)>=2:
                if head_y>tail_y:
                    tail_y +=1
                else:
                    tail_y -=1
                tail_x = head_x
            elif abs(head_x-tail_x)>=2:
                if head_x>tail_x:
                    tail_x += 1
                else:
                    tail_x -= 1
                tail_y = head_y

            s.add((tail_y,tail_x))
            i -= 1
    print("Part1:",len(s))

part1()


def part2():
    s = set()
    ys = [0 for i in range(10)]
    xs = [0 for i in range(10)]
    s.add((ys[9],xs[9]))
    dirs_y = {"U":-1,"D":1,"R":0,"L":0}
    dirs_x = {"U":0,"D":0,"R":1,"L":-1}
    for line in open("Day 9.txt","r"):
        dir,i = line.split()
        i = int(i)
        while i>0:
            ys[0] += dirs_y[dir]
            xs[0] += dirs_x[dir]
            for j in range(1,10):
                if abs(ys[j]-ys[j-1])>=2 and abs(xs[j]-xs[j-1])>=2:
                    if ys[j-1]>ys[j]:
                        ys[j]+=1
                    else:
                        ys[j]-=1
                    if xs[j-1]>xs[j]:
                        xs[j]+=1
                    else:
                        xs[j]-=1
                elif abs(ys[j]-ys[j-1])>=2:
                    ys[j] += (1 if ys[j-1]>ys[j] else -1)
                    xs[j] = xs[j-1]
                elif abs(xs[j]-xs[j-1])>=2:
                    xs[j] += (1 if xs[j-1]>xs[j] else -1)
                    ys[j] = ys[j-1]
            s.add((ys[9],xs[9]))
            i -= 1
    print("Part2:",len(s))

part2()