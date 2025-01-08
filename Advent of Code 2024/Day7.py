import itertools


def part1():
    input = open("Day7.txt").read().split("\n")

    sum = 0 
    for line in input:
        ls = line.split(" ")
        goal = int(ls[0][:-1])
        numbers = list(map(int,ls[1:]))
        goalAchieved = False
        for el in itertools.product([0,1], repeat = len(numbers)-1):
            number = numbers[0]
            for i in range(1,len(numbers)):
                if el[i-1]==0:
                    number += numbers[i]
                else:
                    number *= numbers[i]
            if number == goal:
                goalAchieved = True
                break


        if goalAchieved:
            sum += goal


    print("2024 day 7 part 1: ", sum)




part1()


def part2():
    input = open("Day7.txt").read().split("\n")

    sum = 0 
    for line in input:
        ls = line.split(" ")
        goal = int(ls[0][:-1])
        numbers = list(map(int,ls[1:]))
        goalAchieved = False
        for el in itertools.product([0,1,2], repeat = len(numbers)-1):
            number = numbers[0]
            for i in range(1,len(numbers)):
                if el[i-1]==0:
                    number += numbers[i]
                elif el[i-1]==1:
                    number *= numbers[i]
                else:
                    number = int(str(number)+str(numbers[i]))

            if number == goal:
                goalAchieved = True
                break


        if goalAchieved:
            sum += goal


    print("2024 day 7 part 2: ", sum)




part2()