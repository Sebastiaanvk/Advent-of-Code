'''
I actually read all the assembly code and then manually translated it to a readable program:

A:  R2 <= R3 | 2^16
    R3 <= 832312

B:  R3 <= (R3+(R2 mod 2^8)) mod 2^24
    R3 <= (R3*65899) mod 2^24
    IF R2 < 2^8:
        JUMP TO E
    R2 <= floor(R2 // 256)
    JUMP TO B

E:  IF R0 == R3:
        END
    JUMP TO A



Part 1:
    Straightforward (Once decompiled).
    R2 gets value 2^16, which means the B loop runs three times.
    The first two times we just multiply R3 and the last time we also add 1 to R3 before multiplying.
    Then we want R0 to be equal to R3.
    Answer: 212115

Part 2:


'''



def part2():
    valuesSet = set()
    lastVal = 0

    R3 = 0
    R2 = 0

    while True:
        R2 = R3 | 1<<16
        R3 = 832312
        while R2>0:
            R3 = R3 + (R2 % 256)
            R3 = R3 % (1<<24)
            R3 *= 65899
            R3 %= 1<<24
            R2 = R2 // (1<<8)
        print(R3)
        if R3 in valuesSet:
            print("Part 2: ",lastVal)
            return
        lastVal = R3
        valuesSet.add(R3)
part2()
