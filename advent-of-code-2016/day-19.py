from sortedcontainers import SortedList

def part1():
    length = 3017957
    children = [ ((x+1)%length) for x in range(length)]
    currentIndex = 0
    while children[currentIndex]!=currentIndex:
        child = children[currentIndex]
        childchild = children[child]
        children[currentIndex] = childchild
        currentIndex = childchild

    print("Part 1: ",currentIndex+1)
part1()



def part2():
    length = 3017957
    # length = 5
    ls = SortedList(range(1,length+1))

    currentIndex = 0
    # print(ls)
    while len(ls)>1:
        acrossIndex = (currentIndex + len(ls)//2) % len(ls)
        acrossVal = ls[acrossIndex]
        ls.remove(acrossVal)

        if acrossIndex>currentIndex:
            currentIndex = (currentIndex+1)%len(ls)
        elif currentIndex == len(ls):
            currentIndex = 0
        # print(ls)
    print("Part 2: ", ls[0])

part2()