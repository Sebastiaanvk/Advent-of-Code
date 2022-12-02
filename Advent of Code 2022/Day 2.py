'''
input = open("Day 2.txt","r")
def part1():
    sum = 0
    for line in input:
        p1 = ord(line[0])-ord('A')+1
        p2 = ord(line[2])-ord('X')+1        
        sum += p2
        sum += (p2+1-p1)%3  * 3     

    print("Part1:",sum)
part1()
def part2():
    input = open("Day 2.txt","r")
    sum = 0
    for line in input:
        p1 = ord(line[0])-ord('A')
        p2 = ord(line[2])-ord('X')        
        sum += p2  * 3     
        sum += (p1+p2-1)%3+1
    print("Part2:",sum)
part2()
'''
#print("Part 1:",sum( ord(line[2])-ord('X')+1+((ord(line[2])-ord('X')-ord(line[0])+ord('A')+1)%3)*3 for line in open("Day 2.txt","r") ) ) 
#print("Part 2:", sum((ord(line[2])-ord('X'))*3+((ord(line[2])-ord('X')+ord(line[0])-ord('A')-1)%3)+1 for line in open("Day 2.txt","r") ) ) 

print("Part 1:",sum( x+1+(x-a+1)%3*3 for (a,x) in map(lambda s: (ord(s[0])-ord('A'),ord(s[2])-ord('X')),open("Day 2.txt","r")) ) ) 
print("Part 2:",sum( x*3+(x+a-1)%3+1 for (a,x) in map(lambda s: (ord(s[0])-ord('A'),ord(s[2])-ord('X')),open("Day 2.txt","r")) ) ) 
