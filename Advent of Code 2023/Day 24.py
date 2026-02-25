
from collections import defaultdict
import itertools
from fractions import Fraction

def crossingXY(hail1,hail2):
    x1,y1,dx1,dy1 = hail1[0][0],hail1[0][1],hail1[1][0],hail1[1][1]
    x2,y2,dx2,dy2 = hail2[0][0],hail2[0][1],hail2[1][0],hail2[1][1]
    if dy1*dx2==dy2*dx1:
        return None
    x = (y1-x1*(dy1/dx1)-y2+x2*(dy2/dx2)) / (dy2/dx2-dy1/dx1)
    y = y1+(x-x1)*(dy1/dx1)
    if (x>x1 and dx1<0) or (x<x1 and dx1>0):
        return None
    if (x>x2 and dx2<0) or (x<x2 and dx2>0):
        return None
    return (y,x)



def part1():
    with open("Day 24.txt") as f:
        lines = f.read().split('\n')
        hails = []
        for line in lines:
            l1 = line.split(" @ ")
            hails.append( (tuple(map(int,l1[0].split(', '))),    tuple(map(int,l1[1].split(', ')))          ))
        ans = 0
        minLoc,maxLoc = 200000000000000, 400000000000000
        # minLoc,maxLoc = 7, 27
        for h1,h2 in itertools.combinations(hails,2):
            # print(h1,h2)
            crossing = crossingXY(h1,h2)
            # print(crossing)
            if crossing != None and minLoc<=crossing[0]<=maxLoc and minLoc<=crossing[1]<=maxLoc :
                ans += 1

        print("Day 24 part 1:",ans)

part1()

# def checkVels(dx,dy,hails):
#     (x1,y1,z1),(dx1,dy1,dz1) = hails[0]
#     (x2,y2,z2),(dx2,dy2,dz2) = hails[1]
#     (x3,y3,z3),(dx3,dy3,dz3) = hails[2]
#     f1 = Fraction(1,1)
#     if dx1-dx != 0:
#         f1 = Fraction(dy1-dy,dx1-dx)
#     f2 = Fraction(1,1)
#     if dx2-dx != 0:
#         f2 = Fraction(dy2-dy,dx2-dx)
#     x = y2-y1+x1*f1-x2*f2
#     y = y1+(x-x1)*f1
#     t1 = 0
#     t2=0
#     if dx1-dx!=0:
#         t1 = Fraction(x-x1,dx1-dx)
#     elif dy1-dy!=0:
#         t1 = Fraction(y-y1,dy1-dy)
#     if dx2-dx!=0:
#         t2 = Fraction(x-x2,dx2-dx)
#     elif dy2-dy!=0:
#         t2 = Fraction(y-y2,dy2-dy)
#     if t1-t2==0 or t1==0:
#         return False,0
#     z =  Fraction(z2*t1-z1*t2 + (dz2-dz1)*t1*t2,t1-t2)
#     dz = Fraction(z1-z+dz1*t1,t1)
#     if dx3-dx!=0:
#         t3 = Fraction(x-x3,dx3-dx)
#     elif dy3-dy!=0:
#         t3 = Fraction(y-y3,dy3-dy)
#     else:
#         t3 = Fraction(z-z3,dz3-dz)
#     if not (x.is_integer() and y.is_integer() and z.is_integer() and dz.is_integer):
#         return False, 0
#     if x+dx*t3 != x3+dx3*t3 or y+dy*t3 != y3+dy3*t3 or z+dz*t3 != z3+dz3*t3:
#         return False, 0
#     return True, int(x+y+z)
    
    


# def part2():
#     with open("Day 24.txt") as f:
#         lines = f.read().split('\n')
#         hails = []
#         for line in lines:
#             l1 = line.split(" @ ")
#             hails.append( (tuple(map(int,l1[0].split(', '))),    tuple(map(int,l1[1].split(', ')))          ))
#         ansFound  = False
#         velSum = 2
#         ans = 0
#         while not ansFound:
#             print(velSum)
#             dx = -velSum+1
#             while not ansFound and dx<velSum:
#                 if dx!=0:
#                     dy = velSum-abs(dx)
#                     ansFound, ans = checkVels(dx,dy,hails)                    
#                     if not ansFound:
#                         dy = dy*-1
#                         ansFound, ans = checkVels(dx,dy,hails)                    
#                 dx += 1
#             velSum += 1
#         print("Day 24 part 2:",ans)
# part2()

def calcStartWeight(hails):
    (x1,y1,z1,dx1,dy1,dz1) = hails[0]
    (x2,y2,z2,dx2,dy2,dz2) = hails[1]
    (x3,y3,z3,dx3,dy3,dz3) = hails[2]
    (x4,y4,z4,dx4,dy4,dz4) = hails[3]
    dw1 = dx1+dy1+dz1
    w1 = x1+y1+z1
    w2 = x2+y2+z2
    w3 = x3+y3+z3
    w4 = x4+y4+z4
    ansFound = False
    dw = 0
    while not ansFound:
        if dw!=dw1:
            a = (w2-w1)*( (dw1-dw)*(x1-x3) + w3*dx3 -w1*dx1   )
            b = (w3-w1)*( (dw1-dw)*(x1-x2) + w2*dx2 -w1*dx1   )
            w = Fraction(a-b,(dx1-dx2)*(w3-w1)-(dx1-dx3)*(w2-w1))
            dx = Fraction((dw1-dw)*(x1-x2) + w2*dx2-w1*dx1 + w*(dx1-dx2),(w2-w1))
            x = x1 + Fraction((w-w1)*(dx1-dx),dw1-dw)
            if (x-x4)*(dw1-dw) == (w-w4)*(dx4-dx):
                ansFound = True
                return w
        if dw<=0:
            dw = abs(dw)+1
        else:
            dw = -1*dw
    return 0
    

# Holy shit I hated this puzzle!!!!!
# Probably oversaw something simple that works for the data set
# But goddamn
# The time I spent doing algebra
# Was good practice though I guess
# Ugh
# In the end I opted for two dimensions: x and w where w is the sum of x and y and z
# In two dimensions, we need four lines to find the answer (two equalities per line and 8 unknowns)
# I found that a bunch of the lines have the same dw, so I took those to make the equations a bit easier
# and I also loop over the possible dw instead of finding them algebraically, because that saves one step of horrible mathematics.
# By far my least favorite advent of code puzzle

def part2():
    with open("Day 24.txt") as f:
        lines = f.read().split('\n')
        hails = []
        for line in lines:
            l1 = line.split(" @ ")
            hails.append( (tuple(map(int,l1[0].split(', '))),    tuple(map(int,l1[1].split(', ')))          ))
        velocities = [defaultdict(int),defaultdict(int),defaultdict(int),defaultdict(int)]
        for (x,y,z),(dx,dy,dz) in hails:
            velocities[0][dx] += 1
            velocities[1][dy] += 1
            velocities[2][dz] += 1
            velocities[3][dx+dy+dz] += 1
        hailsSameGrowth = []
        for (x,y,z),(dx,dy,dz) in hails:
            if velocities[3][dx+dy+dz]==4:
                hailsSameGrowth.append((x,y,z,dx,dy,dz))

        print("Day 24 part 2:",calcStartWeight(hailsSameGrowth))
part2()