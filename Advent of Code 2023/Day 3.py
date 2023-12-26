def part1():
    input = open("Day 3.txt","r").read().split("\n")
    sum = 0
    for i in range(len(input)):
        x=0
        while(x<len(input[i])):
            if (input[i][x].isdigit()):
                length = 1
                while(x+length<len(input[i]) and input[i][x+length].isdigit()):
                    length += 1
                nexttosymb=False
                if(i>0):
                    for j in range(max(0,x-1),min(x+length+1,len(input[i]))):
                        if(input[i-1][j]!="."):
                            nexttosymb = True
                if(i<len(input)-1):
                    for j in range(max(0,x-1),min(x+length+1,len(input[i]))):
                        if(input[i+1][j]!="."):
                            nexttosymb = True            
                if(x>0 and input[i][x-1]!="."):
                    nexttosymb = True
                if(x+length<len(input[i]) and input[i][x+length]!="."):
                    nexttosymb = True
                if(nexttosymb):
                    sum+=int(input[i][x:x+length])
                x += length   
            else:
                x+=1
    print("Part1:",sum)
part1()

def add_to_dict(y,x,dict,numb):
    if (y,x) in dict:
        dict[(y,x)].append(numb) 
    else:
        dict[(y,x)] = [numb]

def part2():
    input = open("Day 3.txt","r").read().split("\n")
    dict = {}
    for i in range(len(input)):
        x=0
        while(x<len(input[i])):
            if (input[i][x].isdigit()):
                length = 1
                while(x+length<len(input[i]) and input[i][x+length].isdigit()):
                    length += 1
                numb = int(input[i][x:x+length])
                if(i>0):
                    for j in range(max(0,x-1),min(x+length+1,len(input[i]))):
                        if(input[i-1][j]=="*"):
                            add_to_dict(i-1,j,dict,numb)
                            
                if(i<len(input)-1):
                    for j in range(max(0,x-1),min(x+length+1,len(input[i]))):
                        if(input[i+1][j]=="*"):
                            add_to_dict(i+1,j,dict,numb)           
                if(x>0 and input[i][x-1]=="*"):
                    add_to_dict(i,x-1,dict,numb)
                if(x+length<len(input[i]) and input[i][x+length]=="*"):
                    add_to_dict(i,x+length,dict,numb)
                x += length   
            else:
                x+=1
    sum = 0
    for key in dict:
        if(len(dict[key])==2):
            sum += dict[key][0]*dict[key][1]
    print("Part2:",sum)
part2()