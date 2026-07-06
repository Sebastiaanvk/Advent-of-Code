

def part1():
    inp = open("day-9.txt").read()[:-1]
    totalLength = 0
    pos = 0
    while pos <len(inp):
        if inp[pos] == "(":
            end = pos+1
            while inp[end]!=")":
                end += 1
            s = inp[pos+1:end].split('x')
            totalLength += int(s[0]) * int(s[1])
            pos = end + 1 + int(s[0])
        else:
            pos += 1
            totalLength += 1
    print(totalLength)
part1()


def charsInterval(s, start, end):
    # interval: [start,end)
    totalLength = 0
    pos = start
    while pos < end:
        if s[pos] == "(":
            closingBracketPos = pos+1
            while s[closingBracketPos]!=")":
                closingBracketPos += 1
            withinParenthese = s[pos+1:closingBracketPos].split('x')
            subStrLength = int(withinParenthese[0])
            repeats = int(withinParenthese[1])
            
            totalLength += charsInterval(s,closingBracketPos+1,closingBracketPos+1+subStrLength) * repeats
            pos = closingBracketPos + 1 + subStrLength
        else:
            pos += 1
            totalLength += 1
    return totalLength




def part2():
    inp = open("day-9.txt").read()[:-1]
    print(charsInterval(inp,0,len(inp)))
part2()