
def part1(part1=True):
    monkey_items = {}
    monkey_operation = {}
    monkey_test = {}
    monkey_target_true = {}
    monkey_target_false = {}
    monkeys = 0
    for s in open("Day 11.txt","r").read().split("\n\n"):
        monkeys += 1
        lines = s.split('\n')
        s = lines[0].split()
        monkey = int(s[1][:-1])
        lst = []
        s = lines[1].split()
        for i in range(2,len(s)):
            if s[i][-1] == ",":
                lst.append(int(s[i][:-1]))
            else:
                lst.append(int(s[i]))
        monkey_items[monkey] = lst
        s = lines[2].split()
        if s[-1]=="old":
            if s[-2] == "+":
                monkey_operation[monkey] = lambda l: l+l
            else:
                monkey_operation[monkey] = lambda l: l * l
        else:
            x = int(s[-1])
            if s[-2] == "+":
                monkey_operation[monkey] = lambda l,a=x: l+a
            else:
                monkey_operation[monkey] = lambda l,a=x: a * l
        monkey_test[monkey] =  int(lines[3].split()[3])
        monkey_target_true[monkey] = int(lines[4].split()[5])
        monkey_target_false[monkey] = int(lines[5].split()[5])
    item_checks = {i:0 for i in range(monkeys)}
    rounds = 20
    if not part1:
        rounds = 10000

    modulo = 1
    for i in range(monkeys):
        modulo *= monkey_test[i]
    for i in range(rounds):
        for monkey in range(monkeys):
            while(len(monkey_items[monkey])!=0):
                item_checks[monkey] += 1
                item = monkey_items[monkey].pop(0)
                item = monkey_operation[monkey](item)
                if part1:
                    item = item//3
                if not part1:
                    item = item% modulo
                if item%monkey_test[monkey]==0:
                    target = monkey_target_true[monkey]
                else:
                    target = monkey_target_false[monkey]
                monkey_items[target].append(item)
    checks = sorted([item_checks[i] for i in range(monkeys)])
    if part1:
        print("Part1:",checks[-1]*checks[-2])
    else:
        print("Part2:",checks[-1]*checks[-2])


part1()
part1(part1=False)