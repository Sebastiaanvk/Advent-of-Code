import itertools

def part1():
    input = open("Day 6.txt","r").read().split("\n")
    times = list(map(int,input[0].split()[1:]))
    dists = list(map(int,input[1].split()[1:]))
    results = []
    for (t,d) in zip(times,dists):
        nr = 0
        x = t//2
        while(x*(t-x)>d):
            nr += 1
            x -= 1
        x = t//2 + 1
        while(x*(t-x)>d):
            nr += 1
            x += 1
        results.append(nr)
    ans = 1
    for x in results:
        ans *= x
    print("Day 6 part 1:",ans)
part1() 



def part2():
    input = open("Day 6.txt","r").read().split("\n")
    timeStr = ""
    for x in input[0].split()[1:]:
        timeStr += x
    time = int(timeStr)
    distStr = ""
    for x in input[1].split()[1:]:
        distStr += x
    dist = int(distStr)
    # time = 71530 
    # dist = 940200
    left = 1
    right = time//2
    while(left<right):
        mid = (left+right)//2
        if((time-mid)*mid)>dist:
            right = mid
        else:
            left = mid+1
    ans = 2*(time//2-left)+1
    if(time%2!=0):
        ans += 1
    print("Day 6 part2: ",ans)
part2()