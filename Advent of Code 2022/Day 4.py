def part1():
    cnt = 0
    for l in open("Day 4.txt","r"):
        s = l.split(',')
        (a,b) = map(int,s[0].split('-'))
        (x,y) = map(int,s[1].split('-'))
        if (a<=x and y<=b) or (x<=a and b<=y):
            cnt += 1
    print("Part1:",cnt)
part1()
        
def part2():
    cnt = 0
    for l in open("Day 4.txt","r"):
        s = l.split(',')
        (a,b) = map(int,s[0].split('-'))
        (x,y) = map(int,s[1].split('-'))
        if (a<=x and x<=b) or (x<=a and a<=y):
            cnt += 1
    print("Part2:",cnt)
part2()
        
        
