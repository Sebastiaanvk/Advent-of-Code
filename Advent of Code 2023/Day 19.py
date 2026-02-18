import re

def part1():
    with open("Day 19.txt") as f:
        t = f.read().split("\n\n")
        rulesString = t[0].split("\n")
        parts = t[1].split("\n")
        rules = {}
        for ruleS in rulesString:
            s = ruleS.split('{')
            l = []
            for x in s[1][:-1].split(','):
                # print(x)
                if '<' in x:
                    i1,i2 = x.find('<'),x.find(':')
                    l.append((x[:i1],'<',int(x[i1+1:i2]),x[i2+1:] ))
                elif '>' in x:
                    i1,i2 = x.find('>'),x.find(':')
                    l.append((x[:i1],'>',int(x[i1+1:i2]),x[i2+1:] ))
                else:
                    l.append( (x,) )
            rules[s[0]] = l
        ans = 0
        for partString in parts:
            stats = partString[1:-1].split(',')
            statDict = {}
            for stat in stats:
                name,val = stat.split('=')
                statDict[name] = int(val)
            pos = "in"
            ind = 0
            while pos not in ['A','R']:
                rule = rules[pos][ind]
                if len(rule)==1:
                    pos = rule[0]
                    ind = 0
                elif rule[1]=='<' and statDict[rule[0]]<rule[2]:
                    pos = rule[3]
                    ind = 0
                elif rule[1]=='>' and statDict[rule[0]]>rule[2]:
                    pos = rule[3]
                    ind = 0
                else:
                    ind += 1

                
            if pos=='A':
                for key in statDict:
                    ans += statDict[key]
        print("Day 19 part 1:",ans)

part1()

def calcPoss(curr, index, rules, lowerBounds, upperBounds,ans):
    if curr=='A':
        options = 1
        for c in "xmas":
            options *= upperBounds[c]+1-lowerBounds[c]
        ans[0] += options
        return
    if curr =='R':
        return
    rule = rules[curr][index]
    # print(rule)
    if len(rule)==1:
        calcPoss(rule[0],0,rules,lowerBounds,upperBounds,ans)
    else:
        c = rule[0]
        numb = rule[2]
        if rule[1]=='>':
            if upperBounds[c]>numb:
                oldLB = lowerBounds[c]
                lowerBounds[c] = numb+1       
                calcPoss(rule[3],0,rules,lowerBounds,upperBounds,ans)
                lowerBounds[c] = oldLB
            if lowerBounds[c]<=numb:
                oldUB = upperBounds[c]
                upperBounds[c] = numb       
                calcPoss(curr,index+1,rules,lowerBounds,upperBounds,ans)
                upperBounds[c] = oldUB
        else: #c<numb
            if lowerBounds[c]<numb:
                oldUB = upperBounds[c]
                upperBounds[c] = numb-1      
                calcPoss(rule[3],0,rules,lowerBounds,upperBounds,ans)
                upperBounds[c] = oldUB
            if upperBounds[c]>=numb:
                oldLB = lowerBounds[c]
                lowerBounds[c] = numb       
                calcPoss(curr,index+1,rules,lowerBounds,upperBounds,ans)
                lowerBounds[c] = oldLB



def part2():
    with open("Day 19.txt") as f:
        t = f.read().split("\n\n")
        rulesString = t[0].split("\n")
        parts = t[1].split("\n")
        rules = {}
        for ruleS in rulesString:
            s = ruleS.split('{')
            l = []
            for x in s[1][:-1].split(','):
                # print(x)
                if '<' in x:
                    i1,i2 = x.find('<'),x.find(':')
                    l.append((x[:i1],'<',int(x[i1+1:i2]),x[i2+1:] ))
                elif '>' in x:
                    i1,i2 = x.find('>'),x.find(':')
                    l.append((x[:i1],'>',int(x[i1+1:i2]),x[i2+1:] ))
                else:
                    l.append( (x,) )
            rules[s[0]] = l
        ans = [0]
        lowerBounds = {
            'x':1,
            'm':1,
            'a':1,
            's':1
        }
        upperBounds = {
            'x':4000,
            'm':4000,
            'a':4000,
            's':4000
        }
        calcPoss('in',0,rules,lowerBounds,upperBounds,ans)

        print("Day 19 part 2:",ans[0])
part2()