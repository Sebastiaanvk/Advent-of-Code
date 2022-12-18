

def part1():
    not_allowed = set([])
    beacond_on_line = set([])
    line_nr = 2000000
    #line_nr = 10
    for l in open("Day 15.txt","r"):
        line = l.split()
        x,y = int(line[2][2:-1]),int(line[3][2:-1])
        b_x,b_y = int(line[8][2:-1]),int(line[9][2:])
        if b_y==line_nr:
            beacond_on_line.add(b_x)
        dist = abs(x-b_x) + abs(y-b_y)
        for d_x in range(dist - abs(line_nr-y)+1):
            not_allowed.add(x+d_x)
            not_allowed.add(x-d_x)
    print("Part1:",len(not_allowed)-len(beacond_on_line))


def part2():
    max_x,max_y = 4000000,4000000
    starts = [[] for row in range(0,max_y+1)]
    ends = [[] for row in range(0,max_y+1)]
    for l in open("Day 15.txt","r"):
        print(l)
        line = l.split()
        x,y = int(line[2][2:-1]),int(line[3][2:-1])
        b_x,b_y = int(line[8][2:-1]),int(line[9][2:])
        dist = abs(x-b_x) + abs(y-b_y)
        for row in range(max(0,y-dist),min(max_y,y+dist)+1):
            starts[row].append(max(0,x-(dist-abs(row-y))))
            ends[row].append(min(max_x,x+(dist-abs(row-y))))


    answer = 0
    for y in range(max_y+1):
        starts[y].sort()
        ends[y].sort()

        inside_tuples = 0
        i_start = 0
        i_end = 0
        while(i_end<len(ends[y])):
            inside_tuples -= 1
            while(i_start<len(starts[y]) and starts[y][i_start]<=ends[y][i_end]):
                i_start += 1
                inside_tuples += 1
            if inside_tuples==0 and ends[y][i_end]<max_x and ((i_start==len(starts[y])) or starts[y][i_start]>ends[y][i_end]+1):
                answer = y+4000000*(ends[y][i_end]+1)

            i_end += 1

    
    print("Part2:",answer)



part1()
part2()