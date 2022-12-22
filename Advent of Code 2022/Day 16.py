import itertools



def dfs(current_valve,time_left,already_turned_on,distances,flow_rates):
    best = 0
    for valve in flow_rates:
        if valve not in already_turned_on:
            dist = distances[(current_valve,valve)]
            if dist+1<time_left:
                already_turned_on.add(valve)
                score = (time_left-dist-1)*flow_rates[valve]+dfs(valve,time_left-dist-1,already_turned_on,distances,flow_rates)
                already_turned_on.remove(valve)
                best = max(best,score)

    return best

def dfs_double(current_valve1,finishing_time1,current_valve2,finishing_time2,time_left,already_turned_on,distances,flow_rates):
    best = 0
    if finishing_time1<=0:
        for valve in flow_rates:
            if valve not in already_turned_on:
                dist = distances[(current_valve1,valve)]
                if dist+1<time_left:
                    already_turned_on.add(valve)
                    busy = min(finishing_time2,dist+1)
                    busy = max(0,busy)

                    score = (time_left-dist-1)*flow_rates[valve]+dfs_double(valve,dist+1-busy,current_valve2,finishing_time2-busy,time_left-busy,already_turned_on,distances,flow_rates)
                    already_turned_on.remove(valve)
                    best = max(best,score)
    elif finishing_time2<=0:
        for valve in flow_rates:
            if valve not in already_turned_on:
                dist = distances[(current_valve2,valve)]
                if dist+1<time_left:
                    already_turned_on.add(valve)
                    busy = min(finishing_time1,dist+1)
                    busy = max(0,busy)

                    score = (time_left-dist-1)*flow_rates[valve]+dfs_double(current_valve1,finishing_time1-busy,valve,dist+1-busy,time_left-busy,already_turned_on,distances,flow_rates)
                    already_turned_on.remove(valve)
                    best = max(best,score)

    return best



def part1():
    
    flow_rates = {}
    distances = {}
    valves = []
    for l in open("Day 16.txt","r").read().split("\n")[:-1]:
        line = l.split(" ")
        name = line[1]
        valves.append(name)
        flow_rate = int(line[4][5:-1])
        if flow_rate !=0:
            flow_rates[name] = flow_rate
        for i in range(9,len(line)-1):
            distances[(name,line[i][:-1])] = 1
        distances[(name,line[-1])] = 1
        distances[(name,name)] = 0
    for k in valves:
        for i in valves:
            for j in valves:
                if i!=j and (i,k) in distances and (k,j) in distances:
                    if (i,j) not in distances:
                        distances[(i,j)] = distances[(i,k)] + distances[(k,j)]
                    else:
                        distances[(i,j)] = min(distances[(i,j)],distances[(i,k)]+distances[(k,j)])
    already_turned_on = set([])
    print("Part1:",dfs("AA",30,already_turned_on,distances,flow_rates))





part1()



def part2():
    flow_rates = {}
    distances = {}
    valves = []
    for l in open("Day 16.txt","r").read().split("\n")[:-1]:
        line = l.split(" ")
        name = line[1]
        valves.append(name)
        flow_rate = int(line[4][5:-1])
        if flow_rate !=0:
            flow_rates[name] = flow_rate
        for i in range(9,len(line)-1):
            distances[(name,line[i][:-1])] = 1
        distances[(name,line[-1])] = 1
        distances[(name,name)] = 0
    for k in valves:
        for i in valves:
            for j in valves:
                if i!=j and (i,k) in distances and (k,j) in distances:
                    if (i,j) not in distances:
                        distances[(i,j)] = distances[(i,k)] + distances[(k,j)]
                    else:
                        distances[(i,j)] = min(distances[(i,j)],distances[(i,k)]+distances[(k,j)])
    already_turned_on = set([])

    best = 0
    for r in range((len(flow_rates)+1)//2):
        for c in itertools.combinations(flow_rates,r):
            already_turned_on = set([])
            already_turned_on_comp = set([])
            for x in flow_rates:
                already_turned_on.add(x) if x in c else already_turned_on_comp.add(x)
            score = 0
            score += dfs("AA", 26, already_turned_on, distances,flow_rates)
            score += dfs("AA",26, already_turned_on_comp,distances,flow_rates)
            if score > best:
                best = score
                print(best)
            best = max(best,score)


    print("Part2:",best)
part2()





