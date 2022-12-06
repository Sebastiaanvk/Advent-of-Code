'''
def part1():
    for line in open("Day 6.txt","r"):
        sum = 0
        sum2=0
        i = 0
        while( len(set(line[i:i+4])) !=4):
            i+=1
        sum += i+4
        i = 0
        while( len(set(line[i:i+14])) !=14):
            i+=1
        sum2 += i+14

    print("Part1:",sum)
    print("Part2:",sum2)
part1()
'''
print("Part1:",sum([i for i in range(len(l)-4) if len(set(l[i:i+4]))==4 ][0]+4 for l in open("Day 6.txt","r")))     
print("Part2:",sum([i for i in range(len(l)-14) if len(set(l[i:i+14]))==14 ][0]+14 for l in open("Day 6.txt","r")))     