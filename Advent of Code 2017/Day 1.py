"""
f = open("Day 1.txt", "r")
sum = 0
s = f.read()
for i in range(1,len(s)):
    if(s[i]==s[i-1]):
        sum += ord(s[i-1]) - ord('0')
if(s[0]==s[len(s)-2]):
    sum += ord(s[0]) - ord('0')
print("Day 1:",sum)

sum = 0
half = len(s)//2
for i in range((len(s)-1)//2):
    if(s[i]==s[(i+half)]):
        sum += 2*(ord(s[i]) - ord('0'))
print("Day 2:", sum)
"""    
# This solution I kinda half copied from a comment on reddit
# I did do it the next day by memory though
# I'm  trying to get better at python 
s = open("Day 1.txt","r").read()[:-1]
print("Day 1:", sum(int(c) for c,d in zip(s,s[1:]+s[:1]) if c==d ) )
print("Day 2:", sum(int(c) for c,d in zip(s, s[len(s)//2:]+s[:len(s)//2]) if c==d))
