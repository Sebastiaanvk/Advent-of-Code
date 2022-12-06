def part1():
    score = 0
    for s in open("Day 9.txt", "r"):
        index=0
        ignore = False
        depth = 1
        ignored = 0
        while(index<len(s)):
            char = s[index]
            if char == '!':
                index +=1
            elif ignore and char =='>':
                ignore=False
            elif not ignore and char == '<':
                ignore = True
            elif ignore:
                ignored += 1
            elif not ignore and char =='{':
                score += depth
                depth += 1
            elif not ignore and char == '}':
                depth -= 1
            index += 1
    print("Part1:",score)
    print("Part2:",ignored)
part1()
        