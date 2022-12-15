import functools

def compare_lists(s1,i1,s2,i2):
    if s1.isnumeric() and s2.isnumeric():
        if int(s1)<int(s2):
            return 1
        elif int(s1) == int(s2):
            return 0
        else:
            return -1

    while(i1<len(s1) and i2<len(s2)):
        next_i1 = i1+1
        new_s1 = ""
        if s1[i1]=="[":
            open_bracket = 1
            while open_bracket>0:
                if s1[next_i1]=="[":
                    open_bracket += 1
                elif s1[next_i1]=="]":
                    open_bracket -= 1
                next_i1 += 1
            new_s1 = s1[i1+1:next_i1-1]
        else:
            while next_i1<len(s1) and s1[next_i1].isnumeric():
                next_i1 += 1
            new_s1 = s1[i1:next_i1]

        new_s2 = "" 
        next_i2 = i2+1
        if s2[i2]=="[":
            open_bracket = 1
            while open_bracket>0:
                if s2[next_i2] == "[":
                    open_bracket += 1
                elif s2[next_i2]=="]":
                    open_bracket -= 1
                next_i2 += 1
            new_s2 = s2[i2+1:next_i2-1]
        else:
            while next_i2<len(s2) and s2[next_i2].isnumeric():
                next_i2 += 1
            new_s2 = s2[i2:next_i2]
        res = compare_lists(new_s1,0,new_s2,0)
        if res ==1:
            return 1
        elif res == -1:
            return -1
        i1=next_i1
        if i1<len(s1) and s1[i1]==",":
            i1 += 1
        i2=next_i2
        if i2<len(s2) and s2[i2]==",":
            i2 += 1

    if i2!=len(s2):
        return 1
    elif i1!=len(s1):
        return -1
    return 0

def part1():
    sum = 0
    pairnr = 1
    for s in open("Day 13.txt","r").read().split("\n\n"):
        p1,p2 = s.split()
        if compare_lists(p1[1:-1],0,p2[1:-1],0)!=-1:
            print("Right order:")
            sum += pairnr
        else:
            print("Wrong order:")
        print(p1)
        print(p2,"\n")
        pairnr += 1
    print("Part1:",sum)
        

def part2():
    ls = ["[[6]]","[[2]]"]
    for s in open("Day 13.txt","r").read().split("\n\n"):
        p1,p2 = s.split()
        ls.append(p1)
        ls.append(p2)
    
    ls.sort(key=functools.cmp_to_key(lambda x,y:compare_lists(x,0,y,0)),reverse=True)

    prod = 1
    for i in range(len(ls)):
        if ls[i]=="[[6]]" or ls[i]=="[[2]]":
            prod *= (i+1)
    print("Part2:",prod)

part1()
part2()