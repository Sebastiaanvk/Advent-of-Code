
def part1():
    # inp = 1
    # maxLoops = 10000
    # while True:
    #     # print(inp)
    #     if runCode(inp,maxLoops):

    #         print("Part 1: ",inp)
    #         return
    #     inp += 1
    print("Part 1: ", 2730-2534)
    '''
    Explanation:
        Took me a bit to understand the assembunny code, but what the program does is:
        First it stores the input plus 7*362=2534 in register d.
        Then every loop we use a to decide the next output.
        The first time a is equal to the value in d.
        Then it lets c be 2 if a is even and c is 1 if a is odd and a becomes floor(a/2).
        If a becomes 0 at the end of the loop, it gets the value of d again.
        We want to output 0,1,0,1,0,1,0,1.
        This means that in register d, we want a binary number in the shape of 1010101010...
        Because this makes the values of 'a' alternate between even and odd.
        The first number of this form thats bigger than 2534 is 2730.
    '''

part1()


# from collections import defaultdict


# def getValue(cmd,regs):
#     if cmd.isalpha():
#         return regs[cmd]
#     else:
#         return int(cmd)

# def isRegister(cmd):
#     return cmd.isalpha()

# def outputOk(out):
#     for i in range(len(out)):
#         if out[i]!= i%2:
#             return False
#     return True


# def runCode(inp,maxLoops):
#     opcodes = list(map(lambda x: x.split(),open("day-25.txt").read().split('\n')[:-1]))
#     regs = defaultdict(int)
#     regs['a'] = inp
#     opcodeIndex = 0
#     loops = 0
#     output = []
#     while opcodeIndex<len(opcodes) and loops < maxLoops and outputOk(output):
#         # print(opcodeIndex)
#         cmds = opcodes[opcodeIndex]
#         opcodeJump = 1
#         if opcodeIndex == 1:
#             regs['d'] += 7*362
#             regs['c'] = 0
#             regs['b'] = 0
#             opcodeIndex = 8
#             continue

#         if cmds[0] == 'dec':
#             if isRegister(cmds[1]):
#                 regs[cmds[1]] -= 1
#         elif cmds[0] == 'inc':
#             if isRegister(cmds[1]):
#                 regs[cmds[1]] += 1
#         elif cmds[0] == 'cpy':
#             if isRegister(cmds[2]):
#                 regs[cmds[2]] = getValue(cmds[1],regs)
#         elif cmds[0] == 'out':
#             output.append(getValue(cmds[1]))
#         elif cmds[0] == "jnz" and getValue(cmds[1],regs)!=0:
#             opcodeJump = getValue(cmds[2],regs)
#         elif cmds[0] == 'tgl':
#             targetIndex = opcodeIndex + getValue(cmds[1],regs)
#             if 0<=targetIndex<len(opcodes):
#                 if len(opcodes[targetIndex])==2:
#                     if opcodes[targetIndex][0]=="inc":
#                         opcodes[targetIndex][0] = "dec"
#                     else:
#                         opcodes[targetIndex][0] = "inc"
#                 else:
#                     if opcodes[targetIndex][0]=="jnz":
#                         opcodes[targetIndex][0] = "cpy"
#                     else:
#                         opcodes[targetIndex][0] = "jnz"
#         loops += 1
#         opcodeIndex += opcodeJump
#     if len(output):
#         print(output)
#     if len(output)>5 and outputOk(output):
#         return True
#     return False

