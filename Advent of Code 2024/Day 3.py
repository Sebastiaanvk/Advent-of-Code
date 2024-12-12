import itertools

input = open("Day 3.txt").read()

print("Day 3 part 1:",sum([sum([ int(l[4:4+i])*int(l[5+i:5+i+j])  for l in  [ input[k:k+6+i+j] for k in range(len(input)-(6+i+j))] if( l[0:4] == "mul(" and l[4:4+i].isdigit() and l[4+i]==',' and l[5+i:5+i+j].isdigit() and l[5+i+j] == ')')])for (i,j) in itertools.product([1,2,3],[1,2,3])]) )

def part2():
    sum = 0
    mul_enabled = True
    i = 0
    while(i<len(input)):
        if i+4<=len(input) and input[i:i+4] == "do()":
            mul_enabled = True
            i += 4

        elif i+7<=len(input) and input[i:i+7] == "don't()":
            mul_enabled = False
            i += 7
        elif mul_enabled and input[i:i+4] == "mul(":
            i += 4
            ok = False
            last_j = 0
            last_k = 0
            for (j,k) in itertools.product([1,2,3],[1,2,3]):
                if input[i:i+j].isdigit() and input[i+j]==',' and input[i+j+1:i+j+1+k].isdigit() and input[i+j+k+1] == ')':
                    ok = True
                    last_j = j
                    last_k = k
            if ok:
                sum += int(input[i:i+last_j])*int(input[i+last_j+1:i+last_j+last_k+1]) 
                i += last_j+last_k+2
        else:
            i += 1
    print("Day 3 part 2: " , sum)

part2()




