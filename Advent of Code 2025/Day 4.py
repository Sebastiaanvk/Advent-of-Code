def countPR(y, x, field):
    rows = len(field)
    cols = len(field[0])
    cnt = 0
    for dy in range(-1,2):
        for dx in range(-1,2):
            if not (dy==0 and dx==0):
                newY = y+dy
                newX = x+dx
                if newY>=0 and newY<rows and newX>=0 and newX<cols and field[newY][newX] == '@':
                    cnt += 1
                
    return cnt




def part1():
    field = open("Day 4.txt").read().split()
    # field = open("Test 4.txt").read().split()
    count = 0
    for y in range( len(field) ):
        for x in range( len(field[y]) ):
            if field[y][x]=='@' and countPR(y,x,field)<4 :
                count += 1
                # print(y,x)
    print("Day 4 part 1:",count)

def part2():
    inp = open("Day 4.txt").read().split()
    # inp = open("Test 4.txt").read().split()
    field = [[x for x in line] for line in inp]
    totalCount = 0
    cont = True
    while cont:
        removedPR = []
        for y in range( len(field) ):
            for x in range( len(field[y]) ):
                if field[y][x]=='@' and countPR(y,x,field)<4 :
                    removedPR.append((y,x))
                    # print(y,x)
        if len(removedPR)==0:
            cont = False
        else:
            totalCount += len(removedPR)
            for (y,x) in removedPR:
                field[y][x] = '.'
    print("Day 4 part 2:",totalCount)






part1()
part2()