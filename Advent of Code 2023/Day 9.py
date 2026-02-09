
def part1():
    inp = open("Day 9.txt").read().split('\n')
    answer = 0
    for line in inp:
        sequences = [list(map(int,line.split(' ')))]
        while not all( x==0 for x in sequences[-1]):
            sequences.append([y-x for (x,y) in list(zip(sequences[-1][:-1],sequences[-1][1:])) ])
        answer += sum(l[-1] for l in sequences)
    print("Day 9 part 1:",answer)


def part2():
    inp = open("Day 9.txt").read().split('\n')
    answer = 0
    for line in inp:
        sequences = [list(map(int,line.split(' ')))]
        while not all( x==0 for x in sequences[-1]):
            sequences.append([y-x for (x,y) in list(zip(sequences[-1][:-1],sequences[-1][1:])) ])
        for i in range(len(sequences)):
            if i%2 == 0:
                answer += sequences[i][0]
            else:
                answer -= sequences[i][0]
    print("Day 9 part 2:",answer)


part1()
part2()