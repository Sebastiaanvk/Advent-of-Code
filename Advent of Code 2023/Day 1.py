print("Part 1:",sum( int(l[0])*10+int(l[-1])  for l in map(lambda x: [c for c in x if c.isdigit()],open("Day 1.txt","r").read().split("\n")[:-1])) )

# def change_word(input, value, numbname):
#     if len(input)==0:
#         return ""

#     if input[0:len(numbname)]==numbname:
#         return value+change_word(input[len(numbname):],value,numbname)
#     return input[0]+change_word(input[1:],value,numbname)


# def part2():
#     ls = open("test1.txt","r").read().split("\n")[:-1]
#     for (val,s) in [("1","one"),("2","two"),("3","three"),("4","four"),("5","five"),("6","six"),("7","seven"),("8","eight"),("9","nine")]:
#         ls = list(map(lambda x: change_word(x,val,s),ls))
#     print(ls)
#     print("Part 2:",sum( int(l[0])*10+int(l[-1])  for l in map(lambda x: [c for c in x if c.isdigit()],ls) ) )

#numbPairs = [("1","one"),("2","two"),("3","three"),("4","four"),("5","five"),("6","six"),("7","seven"),("8","eight"),("9","nine")]

# def change_word(x):
#     if len(x)==0:
#         return ""
#     for (val,s) in numbPairs:
#         if x[0:len(s)]==s:
#             return val+change_word(x[len(s):])
#     return x[0]+change_word(x[1:])

numbPairs = [(1,"one"),(2,"two"),(3,"three"),(4,"four"),(5,"five"),(6,"six"),(7,"seven"),(8,"eight"),(9,"nine")]


def first_digit(x):
    if x[0].isdigit():
        return int(x[0])
    for (val,s) in numbPairs:
        if x[0:len(s)]==s:
             return val
    return first_digit(x[1:])

def last_digit(x):
    if x[-1].isdigit():
        return int(x[-1])
    for (val,s) in numbPairs:
        if x[-len(s):]==s:
             return val
    return last_digit(x[:-1])

def part2():
    ls = open("Day 1.txt","r").read().split("\n")[:-1]
    for x in ls:
        print(x)
        print("first:",first_digit(x))
        print("last:",last_digit(x))

    print("Part 2:",sum( first_digit(x)*10+last_digit(x)  for x in ls) )
part2()