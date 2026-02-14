def findMirror(rows):
    cols = [''.join([x[i] for x in rows]) for i in range(len(rows[0]))]
    for i in range(len(cols)-1):
        l=i
        r=i+1
        while l>=0 and r<len(cols) and cols[l]==cols[r]:
            l-=1
            r+=1
        if l<0 or r==len(cols):
            # print("Col:", i+1)
            return i+1
    for i in range(len(rows)-1):
        l=i
        r=i+1
        while l>=0 and r<len(rows) and rows[l]==rows[r]:
            l-=1
            r+=1
        if l<0 or r==len(rows):
            # print("Row:", i+1)
            return (i+1)*100


    return 0


def part1():
    f = open("Day 13.txt").read().split("\n\n")
    sum = 0
    for s in f:
        sum += findMirror(s.split('\n'))
    print("Day 13 part 1: ",sum)

def stringDiff(s1,s2):
    diff = 0
    for (x,y) in zip(s1,s2):
        if x!=y:
            diff += 1
    return diff

def findSmudge(strings,multiplier):
    for i in range(len(strings)-1):
        charDiff = 0
        l=i
        r=i+1
        while l>=0 and r<len(strings) and charDiff <=1:
            charDiff += stringDiff(strings[l],strings[r])
            l-=1
            r+=1
        if charDiff==1:
            # print("Col:", i+1)
            return (i+1)*multiplier


    return 0


def part2():
    f = open("Day 13.txt").read().split("\n\n")
    sum = 0
    for s in f:
        rows = s.split('\n')
        cols = [''.join([x[i] for x in rows]) for i in range(len(rows[0]))]
        sum += findSmudge(rows,100)
        sum += findSmudge(cols,1)
    print("Day 13 part 2: ",sum)



part1()
part2()