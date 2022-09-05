from tkinter import Y


N = 368078

layer = 0
corner = 1
found = False
while(not found):
    if 4*layer*2+corner >= N:
        found = True
        while( corner < N):
            corner += 2*layer
        print("Day 1:", layer+abs(corner-layer-N))
    corner += 4*layer*2
    layer += 1



found2 = False

def get_value(x,y,dict):
    s = 0
    for i in range(-1,2):
        for j in range(-1,2):
            if((x+i,y+j) in dict):
                s += dict[(x+i,y+j)]
    return s

def explore_line(x,y,dx,dy,layer,dict):
    for i in range(0,2*layer):
        x += dx
        y += dy
        v = get_value(x,y,dict)
        dict[(x,y)] = v
        if(v>N):
            print("Day 2:",v)
            return 0,0,True
    return x,y,False


dict = {(0,0):1}
layer = 1
x,y=1,1
while(not found2): 
    x,y,found2 = explore_line(x,y,0,-1,layer,dict)
    if(found2): break
    x,y,found2 = explore_line(x,y,-1,0,layer,dict)
    if(found2): break
    x,y,found2 = explore_line(x,y,0,1,layer,dict)
    if(found2): break
    x,y,found2 = explore_line(x,y,1,0,layer,dict)
    if(found2): break
    layer += 1
    x+=1
    y+=1

