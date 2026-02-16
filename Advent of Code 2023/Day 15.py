def part1():
    with open("Day 15.txt") as f:
        codes = f.read().split(",")
        sum = 0
        for code in codes:
            val = 0
            for c in code:
                val = (val+ord(c))*17 %256
            sum += val
        print("Day 15 part 1:",sum)

def calcHash(label):
    val = 0
    for c in label:
        val = ((val+ord(c))*17) %256
    return val

def part2():
    with open("Day 15.txt") as f:
        codes = f.read().split(",")
        boxes = [[] for i in range(256)]
        for code in codes:
            # print(boxes)
            # input("Any key to continue")
            # print(code)
            if code[-1] == '-':
                label = code[:-1]
                box = calcHash(label)
                for i in range(len(boxes[box])):
                    if boxes[box][i][0]==label:
                        del boxes[box][i]
                        break
            else:
                label = code[:-2]
                box = calcHash(label)
                focalStrength = int(code[-1])
                i = 0
                labelFound = False
                while i<len(boxes[box]) and not labelFound:
                    if boxes[box][i][0]==label:
                        boxes[box][i] = (label,focalStrength)
                        labelFound = True
                    i+=1
                if not labelFound:
                    boxes[box].append((label,focalStrength))
        sum = 0
        for box in range(256):
            # print(boxes[box])
            for i in range(len(boxes[box])):
                sum += (box+1)*(i+1)*boxes[box][i][1]
        print("Day 15 part 2:",sum)
part1()
part2()