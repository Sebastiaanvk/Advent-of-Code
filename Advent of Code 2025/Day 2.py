
def part1():
    inp = open("Day 2.txt").read().split(",")
    sum = 0
    for range in inp:
        spl = range.split("-")
        left = int(spl[0])
        right = int(spl[1])

        leftcp = left
        leftNrDig = 1
        while leftcp >10:
            leftcp /= 10
            leftNrDig += 1
        tens = pow(10,(leftNrDig+1)//2)        
        digs = tens // 10
        if leftNrDig % 2==0:
            digs = left//tens

        nextCand = digs*tens+digs
        if nextCand < left:
            digs += 1
            nextCand = digs*tens+digs
        while nextCand <= right:
            sum += nextCand
            # print(nextCand)
            digs+=1
            if digs==tens:
                tens *= 10
            nextCand = digs*tens+digs
    print("Day 2 part 1:", sum)


def inRange(x, ranges):
    for range in ranges:
        if x>=range[0] and x<=range[1]:
            return True
    return False

def part2():
    ranges = [(int(spl[0]),int(spl[1])) for spl in [x.split("-") for x in open("Day 2.txt").read().split(",")]]
    maxR = max([x[1] for x in ranges])
    sum = 0
    digs = 1
    powCap = 10
    candSet = set([])
    while digs*powCap+digs <= maxR:
        cand = digs*powCap + digs
        while cand <= maxR:
            if(cand not in candSet and inRange(cand,ranges)):
                sum += cand
                candSet.add(cand)
            cand = cand*powCap + digs
        digs += 1
        if digs==powCap:
            powCap *= 10
    print("Day 2 part 2",sum)

part1()
part2()