def part1():
    inp = open("Day 6.txt").read().split("\n")
    # print(inp[0])
    line0 = list(map(int,inp[0].split()))
    # print(line0)
    line1 = list(map(int,inp[1].split()))
    line2 = list(map(int,inp[2].split()))
    line3 = list(map(int,inp[3].split()))
    ops = inp[4].split()
    sum = 0 
    for i in range(len(ops)):
        if ops[i]=='+':
            sum += line0[i] + line1[i] + line2[i] + line3[i]
        else:
            sum += line0[i] * line1[i] * line2[i] * line3[i]
    print("Day 6 part 1:",sum)

def part2():
    inp = open("Day 6.txt").read().split("\n")
    cols = []
    ops = []
    for i in range(len(inp[0])):
        cols.append(''.join([inp[0][i],inp[1][i],inp[2][i],inp[3][i]]) )
        ops.append(inp[4][i])
    i=0
    sum = 0
    while i<len(cols):
        val = 0
        op = ops[i]
        if op == '*':
            val = 1
        while i<len(cols) and cols[i] != '    ':
            if op=='*':
                val *= int(cols[i])
            else:
                val += int(cols[i])
            i+=1
        i+=1
        sum += val
    print("Day 6 part 2:",sum)


part1()
part2()