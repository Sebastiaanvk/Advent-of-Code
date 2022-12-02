input = "10	3	15	10	5	15	5	15	9	2	5	8	5	2	3	6"

def list_to_string(l):
    stri = ""
    for x in l:
        if x<10:
            stri+=' '
        stri += ' '+str(x)
    return stri    

def update_list(l):
    max = l[0]
    index = 0
    for i in range(1,len(l)):
        if l[i]>max:
            max = l[i]
            index = i 
    i = (index+1)%len(l)        
    blocks = l[index] 
    l[index] = 0
    while blocks>0:
        l[i] += 1
        i = (i+1)%len(l)
        blocks -= 1

def part1():
    l = list(map(int,input.split()))
    s = list_to_string(l)
    seet = set()
    cycles = 0
    while(s not in seet):
        cycles += 1
        seet.add(s) 
        update_list(l)
        s = list_to_string(l)
    print("Part1:",cycles)    
part1()

def part2():
    l = list(map(int,input.split()))
    s = list_to_string(l)
    seet = {} 
    cycles = 0
    while(s not in seet):
        seet[s] = cycles
        cycles += 1
        update_list(l)
        s = list_to_string(l)

    print("Part1:",cycles-seet[s])    
part2()