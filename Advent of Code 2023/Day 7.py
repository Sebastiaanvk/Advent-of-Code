
letterToRank = {'A':5, 'K':4, 'Q':3, 'J':2, 'T':1}

def ltChar( c, d ):
    if '2'<=c<='9':
        if '2'<=d<='9':
            return c<d
        return True
    if '2'<=d<='9':
        return False
    return letterToRank[c]<letterToRank[d]

class HandPoints:
    hand = "" 
    points = 0
    type = 0



    def __init__(self,hand,points):
        self.hand =  hand
        self.points = points
        dict = {}
        for c in hand:
            dict[c] = dict.get(c,0) + 1
        pairsDict = {}
        for k in dict:
            number = dict[k]
            pairsDict[number] = pairsDict.get(number,0) + 1
        if 5 in pairsDict:
            type = 6
        elif 4 in pairsDict:
            type = 5
        elif 3 in pairsDict and 2 in pairsDict:
            type = 4
        elif 3 in pairsDict:
            type = 3
        elif 2 in pairsDict and pairsDict[2]==2:
            type = 2
        elif 2 in pairsDict:
            type = 1
        else:
            type = 0
        self.type = type

    def __lt__(self,other):
        if self.type!=other.type:
            return self.type<other.type
        for i in range(5):
            if self.hand[i]!=other.hand[i]:
                return ltChar(self.hand[i],other.hand[i])
        return False





def part1():
    input = open("Day 7.txt").read().split("\n")
    # input = open("test7.txt").read().split("\n")
    handPointsList = []
    for line in input:
        hand = line.split()[0]
        points = int(line.split()[1])
        handPointsList.append(HandPoints(hand,points))
    handPointsList.sort()
    
    score = 0
    for i in range(len(handPointsList)):
        score += (i+1)*handPointsList[i].points
        # print(handPointsList[i].hand,handPointsList[i].type)
    print("Day 7 part 1:",score)


part1()

letterToRank2 = {'A':5, 'K':4, 'Q':3, 'J':2, 'T':1}

def ltChar2( c, d ):
    if d=='J':
        return False
    if c=='J':
        return True
    if '2'<=c<='9':
        if '2'<=d<='9':
            return c<d
        return True
    if '2'<=d<='9':
        return False
    return letterToRank[c]<letterToRank[d]

class HandPoints2:
    hand = "" 
    points = 0
    type = 0



    def __init__(self,hand,points):
        self.hand =  hand
        self.points = points
        dict = {}
        jokers = 0 
        for c in hand:
            if(c=='J'):
                # print("joker found")
                jokers += 1
            else:
                dict[c] = dict.get(c,0) + 1
        pairsDict = {}
        for k in dict:
            number = dict[k]
            pairsDict[number] = pairsDict.get(number,0) + 1
        if (5 in pairsDict) or (4 in pairsDict and jokers==1) or (3 in pairsDict and jokers==2) or (2 in pairsDict and jokers==3) or jokers==4 or jokers==5:
            type = 6
        elif 4 in pairsDict or (3 in pairsDict and jokers==1) or (2 in pairsDict and jokers==2) or jokers==3:
            type = 5
        elif (3 in pairsDict and 2 in pairsDict) or (2 in pairsDict and pairsDict[2]==2 and jokers==1) :
            type = 4
        elif (3 in pairsDict) or (jokers==2) or (jokers==1 and 2 in pairsDict):
            type = 3
        elif 2 in pairsDict and pairsDict[2]==2:
            type = 2
        elif 2 in pairsDict or jokers==1:
            type = 1
        else:
            type = 0
        self.type = type

    def __lt__(self,other):
        if self.type!=other.type:
            return self.type<other.type
        for i in range(5):
            if self.hand[i]!=other.hand[i]:
                return ltChar2(self.hand[i],other.hand[i])
        return False
def part2():
    input = open("Day 7.txt").read().split("\n")
    # input = open("test7.txt").read().split("\n")
    handPointsList = []
    for line in input:
        hand = line.split()[0]
        points = int(line.split()[1])
        handPointsList.append(HandPoints2(hand,points))
    handPointsList.sort()
    
    score = 0
    for i in range(len(handPointsList)):
        score += (i+1)*handPointsList[i].points
        print(handPointsList[i].hand,handPointsList[i].type)
    print("Day 7 part 2:",score)


part2()