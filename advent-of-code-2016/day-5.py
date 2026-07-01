import hashlib


def part1():

    id = "cxdnnyjw"
    ans = ""
    i = 0
    while len(ans)<8:
        s = id + str(i)
        res = hashlib.md5(s.encode()).hexdigest()
        if res[:5] == '00000':
            ans += res[5]
        i += 1

    print("Part 1: ", ans)

part1()
def part2():

    id = "cxdnnyjw"
    ans = ['0']*8
    i = 0
    indicesUsed = set()
    while len(indicesUsed)<8:
        s = id + str(i)
        res = hashlib.md5(s.encode()).hexdigest()
        if res[:5] == '00000' and res[5].isdigit():
            pos = int(res[5])
            if pos not in indicesUsed and pos<8 :
                indicesUsed.add(int(res[5]))
                ans[int(res[5])] = res[6]
        i += 1
    d = ""
    print("Part 2: ", d.join(ans))

part2()
