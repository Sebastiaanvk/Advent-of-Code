from collections import defaultdict
import string

def part1():
    input = open("day-4.txt").read().split("\n")[:-1]
    ans = 0
    for l in input:
        l2 = l.split('-')
        lastStrs = l2[-1].split('[')
        id = int(lastStrs[0])
        checksum = lastStrs[1][:-1]
        d = defaultdict(int)
        for word in l2[:-1]:
            for c in word:
                d[c] += 1
        letterNrPairs = []
        for c in string.ascii_lowercase:
            letterNrPairs.append((-d[c],c))
        letterNrPairs.sort()
        # print(l)
        # print(letterNrPairs)
        legal = True
        for i in range(5):
            if checksum[i]!=letterNrPairs[i][1]:
                legal = False
        if legal:
            ans += id
    print("Part 1: ",ans)


part1()




def part2():
    input = open("day-4.txt").read().split("\n")[:-1]
    ans = 0
    for l in input:
        l2 = l.split('-')
        lastStrs = l2[-1].split('[')
        id = int(lastStrs[0])
        decrypted = []
        containsWord = False
        for word in l2[:-1]:
            newWord = ""
            for c in word:
                newWord += chr( ord('a') + (((ord(c)-ord('a'))+id)%26) )
            if newWord == 'northpole': # First tried storage and then saw that one of then contained the word northpole
                containsWord = True
            decrypted.append(newWord)
        if containsWord:
            print(decrypted)
            print(id)

    # print("Part 2: ",ans)


part2()