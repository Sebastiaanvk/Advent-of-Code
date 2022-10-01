input = open("Day 5.txt","r").read().split('\n')[:-1]


def part1():
    cop = list(map(lambda x: int(x),input))
    pos = 0
    steps = 0
    while(pos>=0 and pos <len(cop)):
        steps, cop[pos], pos = steps+1,cop[pos]+1, pos+cop[pos]
    print("Day 5 1:",steps)
part1()
def part2():
    cop = list(map(lambda x: int(x),input))
    pos = 0
    steps = 0
    while(pos>=0 and pos <len(cop)):
        steps,cop[pos],pos = steps+1, cop[pos]+1 if cop[pos]<3 else cop[pos]-1, pos+cop[pos]
    print("Day 5 2:",steps)
part2()