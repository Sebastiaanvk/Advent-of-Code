
lines = open("Day 7.txt","r").read().split("\n")[:-1]
total = 0
total_space_used = 0
min_deleted = 0


def check_dir(index):
    global total,total_space_used
    value = 0
    while index<len(lines) and lines[index][:7]!="$ cd ..":
        ln = lines[index].split(" ")
        index += 1
        if ln[1]=="cd":
            extra_value,index = check_dir(index)
            value += extra_value
        elif ln[0] != "$" and ln[0]!="dir":
            value += int(ln[0])
    index += 1
    if value<=100000:
        total = total + value
    total_space_used=max(total_space_used,value)
    return value,index

def check_dir2(index):
    global total_space_used,min_deleted
    value = 0
    while index<len(lines) and lines[index][:7]!="$ cd ..":
        ln = lines[index].split(" ")
        index += 1
        if ln[1]=="cd":
            extra_value,index = check_dir2(index)
            value += extra_value
        elif ln[0] != "$" and ln[0]!="dir":
            value += int(ln[0])
    index += 1
    if value>=total_space_used-40000000:
        min_deleted = min(min_deleted,value)
    return value,index
def part1():
    check_dir(0)
    print("Part1:",total)
    global min_deleted,total_space_used 
    min_deleted = total_space_used
    print("Total used:",total_space_used)
    check_dir2(0)
    print("Part2:",min_deleted)





part1()