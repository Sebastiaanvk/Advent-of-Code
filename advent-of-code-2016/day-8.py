

maxWidth= 50 
maxHeight = 6

def part1():
    inp = open("day-8.txt").read().split('\n')[:-1]

    field = [ [False for col in range(maxWidth)] for row in range(maxHeight)]
    for line in inp:
        s = line.split()
        if s[0]=='rect':
            t = s[1].split('x')
            for col in range(int(t[0])):
                for row in range(int(t[1])):
                    field[row][col] = True
        elif s[1] == "column":
            col = int(s[2][2:])
            dist = int(s[4])
            oldCol = [field[row][col] for row in range(maxHeight)]
            for row in range(maxHeight):
                field[row][col] = oldCol[(row-dist)%maxHeight]
        elif s[1] == "row":
            # print(oldField)
            row = int(s[2][2:])
            dist = int(s[4])
            oldRow = [x for x in field[row]]
            for col in range(maxWidth):
                field[row][col] = oldRow[(col-dist)%maxWidth]
    cnt = 0
    for row in range(maxHeight):
        for col in range(maxWidth):
            if field[row][col]:
                cnt += 1
    print("Part 1: ",cnt)

    for col in range(0,46,5):
        print()
        for dy in range(6):
            l = ""
            for dx in range(5):
                if field[dy][col+dx]:
                    l = l+'0'
                else:
                    l = l + '.'

            print(l)


    



part1()
