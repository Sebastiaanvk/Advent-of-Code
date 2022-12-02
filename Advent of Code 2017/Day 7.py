
def part1():
    input = open("Day 7.txt","r")
    base = None
    below = {}
    for line in input:
        list = line.split()
        base = list[0]    
        for i in range(3,len(list)):
            str = list[i][:-1] if i<len(list)-1 else list[i]
            below[str] = list[0]
    while(base in below):
        base = below[base]
        
    print("Part 1:",base)
part1()

above = {}
weights = {}
total_weights = {}

def total_weight(program):
    if program not in total_weights:
        total_weights[program] = weights[program] 
        if program in above:
            total_weights[program] += sum(total_weight(d) for d in above[program])
    return total_weights[program]


def part2():
    input = open("Day 7.txt","r")
    base = None
    below = {}
    for line in input:
        list = line.split()
        base = list[0]    
        weights[list[0]] = int(list[1][1:-1])
        for i in range(3,len(list)):
            str = list[i][:-1] if i<len(list)-1 else list[i]
            below[str] = list[0]
            if(list[0] not in above):
                above[list[0]] = [str]
            else:
                above[list[0]].append(str)
    while(base in below):
        base = below[base]
    discrep = 0 
    found = False
    new_weight = 0
    current_program = base
    while not found:
        if current_program not in above:
            found = True
            new_weight = weights[current_program] + discrep
        elif len(above[current_program])>2:
            wrong_disc=current_program
            for disc1 in above[current_program]:
                diffs = 0
                for disc2 in above[current_program]:
                   if total_weight(disc1)!=total_weight(disc2):
                    diffs+=1 
                if diffs>=2:
                    wrong_disc = disc1
            if wrong_disc==current_program:
                found=True
                new_weight = weights[current_program]+discrep
            else:
                diff_disc = above[current_program][0]
                if diff_disc == wrong_disc:
                    diff_disc = above[current_program][1]
                discrep =  total_weight(diff_disc)-total_weight(wrong_disc)
                current_program = wrong_disc
        elif len(above[current_program]==2):
            first = above[current_program][0]
            second = above[current_program][1]
            if total_weight(first)==total_weight(second):
                found = True
                new_weight = weights[current_program]+discrep
            elif total_weight(first)<total_weight(second) and discrep>0 or total_weight(first)>total_weight(second)and discrep<0:
                current_program = first
            else:
                current_program = second
    

    print("Part2:",new_weight)
part2()