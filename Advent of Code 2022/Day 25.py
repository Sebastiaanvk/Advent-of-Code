def part1():
    inp = open("Day 25.txt").read().split('\n')
    total = 0
    for line in inp:
        sum = 0
        power = 1
        for char in reversed(line):
            if char == '1':
                sum += power
            elif char == '2':
                sum += 2*power
            elif char == '-':
                sum -= power
            elif char == '=':
                sum -= 2*power
            power *= 5

        total += sum
    
    snafu = ""
    while total != 0:
        rem = total % 5
        if rem == 1:
            snafu += '1'
            total -= 1
        elif rem == 2:
            snafu += '2'
            total -= 2
        elif rem  == 3:
            snafu += '='
            total += 2
        elif rem == 4:
            snafu += '-'
            total += 1
        else:
            snafu += '0'

        total /= 5
    print("Day 25 part 1:",snafu[::-1])
        
    


part1()