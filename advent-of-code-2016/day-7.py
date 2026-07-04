import itertools


def containsAbba(s):
    for i in range(len(s)-3):
        if s[i]!=s[i+1] and s[i+1]==s[i+2] and s[i] == s[i+3]:
            return True
    return False

def part1():
    inp = open("day-7.txt").read()[:-1].split("\n")
    ans = 0
    for line in inp:
        abbaRight = False
        noAbbaWrong = True
        ss = line.split("[")
        outs = [ss[0]]
        ins = []
        for s in ss[1:]:
            t1,t2 = s.split(']')
            outs.append(t2)
            ins.append(t1)
        for s in outs:
            if containsAbba(s):
                abbaRight = True
        for s in ins:
            if containsAbba(s):
                noAbbaWrong = False
        if abbaRight and noAbbaWrong:
            ans += 1

    print(ans)

part1()

def strContainsStr(s,substr):
    for i in range(len(s)+1-len(substr)):
        if s[i:i+len(substr)] == substr:
            return True
    return False

def listContainsSubtr(l,substr):
    for s in l:
        if strContainsStr(s,substr):
            return True
    return False
        

def containsSSL(outs,ins):
    chars = [chr(x) for x in range(ord('a'),ord('z')+1)]
    for x,y in itertools.product(chars,chars):
        if x != y:
            s1 = ""+x+y+x
            s2 = ""+y+x+y
            if listContainsSubtr(outs,s1) and listContainsSubtr(ins,s2):
                return True
            

    return False


def part2():
    inp = open("day-7.txt").read()[:-1].split("\n")
    ans = 0
    for line in inp:
        ss = line.split("[")
        outs = [ss[0]]
        ins = []
        for s in ss[1:]:
            t1,t2 = s.split(']')
            outs.append(t2)
            ins.append(t1)
        if containsSSL(outs,ins):
            ans += 1

    print(ans)

part2()