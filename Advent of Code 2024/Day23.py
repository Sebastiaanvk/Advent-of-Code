




def part1():
    input = open("Day23.txt").read().split("\n")
#    input = open("test23.txt").read().split("\n")
    adjList = {}
    triplesWithT = [] 
    for line in input:
        v,u = line.split("-")
        adjList.setdefault(v,set()).add(u)
        adjList.setdefault(u,set()).add(v)
    for x in adjList:
        for y in adjList[x]:
            overlap = adjList[x] & adjList[y]
            for z in overlap:
                if 't' in {x[0],y[0],z[0]}:
                    triplesWithT.append({x,y,z})
    print("Day 23 part1:",len(triplesWithT)//6)

part1()
 

            
def part2():
    input = open("Day23.txt").read().split("\n")
#    input = open("test23.txt").read().split("\n")
    adjList = {}
    for line in input:
        v,u = line.split("-")
        adjList.setdefault(v,set()).add(u)
        adjList.setdefault(u,set()).add(v)


    triples = set()
    for x in adjList:
        for y in adjList[x]:
            overlap = adjList[x] & adjList[y]
            for z in overlap:
                triples.add(tuple(sorted([x,y,z])))
    cliques = {}
    cliques[3] = triples
    i = 4
    maxClique = ()
    while len(cliques[i-1]):
        cliques[i] = set()
        for clique in cliques[i-1]:
            overlap = adjList[clique[0]]
            for x in clique:
                overlap = overlap & adjList[x]
            for y in overlap:
                tup = tuple(sorted(list(clique)+[y]))
                cliques[i].add(tup)
                maxClique = tup
        i += 1
    str = ""
    for s in maxClique:
        str += s + ","
    print("Day 23 part1:",str[:-1])


part2()
 

            
