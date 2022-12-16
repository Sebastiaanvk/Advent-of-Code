import itertools


def part1():
    solid_parts = set([])
    bottom = 0
    for li in open("Day 14.txt","r"):
        ls = li.split()
        x,y = map(int,ls[0].split(","))
        bottom = max(bottom,y)
        for i in range(2,len(ls),2):
            new_x,new_y = map(int,ls[i].split(","))
            bottom = max(bottom,new_y)
            for s,t in itertools.product(range(min(x,new_x),max(x,new_x)+1),range(min(y,new_y),max(y,new_y)+1)):
                solid_parts.add((s,t))
            x,y=new_x,new_y
    
    sand_added = -1 
    cont = True
    while(cont):
        sand_added += 1
        x,y=500,0
        looking = True
        while(looking):
            if y>bottom:
                looking = False
                cont = False
            else:
                if (x,y+1) not in solid_parts:
                    y += 1
                elif (x-1,y+1) not in solid_parts:
                    y += 1
                    x -= 1
                elif (x+1,y+1) not in solid_parts:
                    y += 1
                    x += 1
                else:
                    looking = False
                    solid_parts.add((x,y))
    print("Part1:",sand_added)

def part2():
    solid_parts = set([])
    bottom = 0
    for li in open("Day 14.txt","r"):
        ls = li.split()
        x,y = map(int,ls[0].split(","))
        bottom = max(bottom,y)
        for i in range(2,len(ls),2):
            new_x,new_y = map(int,ls[i].split(","))
            bottom = max(bottom,new_y)
            for s,t in itertools.product(range(min(x,new_x),max(x,new_x)+1),range(min(y,new_y),max(y,new_y)+1)):
                solid_parts.add((s,t))
            x,y=new_x,new_y
    
    sand_added =  0
    cont = True
    while((500,0) not in solid_parts):
        sand_added += 1
        x,y=500,0
        looking = True
        while(looking):
            if y==bottom+1:
                looking = False
                solid_parts.add((x,y))
            else:
                if (x,y+1) not in solid_parts:
                    y += 1
                elif (x-1,y+1) not in solid_parts:
                    y += 1
                    x -= 1
                elif (x+1,y+1) not in solid_parts:
                    y += 1
                    x += 1
                else:
                    looking = False
                    solid_parts.add((x,y))
    print("Part2:",sand_added)
part1()
part2()