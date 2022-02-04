#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

struct Pos{
    int x,y,z;
};
Pos operator+(const Pos& p1, const Pos& p2){
    return {p1.x+p2.x,p1.y+p2.y,p1.z+p2.z};
}
Pos operator-(const Pos& p1, const Pos& p2){
    return {p1.x-p2.x,p1.y-p2.y,p1.z-p2.z};
}
bool operator==(const Pos& p1, const Pos& p2){
    return p1.x==p2.x&&p1.y==p2.y&&p1.z==p2.z;
}
bool operator<(const Pos& p1, const Pos& p2){
    if(p1.x!=p2.x) return p1.x<p2.x;
    if(p1.y!=p2.y) return p1.y<p2.y;
    return p1.z<p2.z;
}

Pos rot(const Pos& p, int rot_id){
    int x,y,z;
    int a=p.x;
    int b=p.y;
    int c=p.z;
    int dir = rot_id/4;
    int turn = rot_id%4;
    if(turn==1){
        int h = b;
        b =c;
        c=-h;
    } else if(turn==2){
        b*=-1;
        c*=-1;
    } else if(turn==3){
        int h = c;
        c = b;
        b = -h;
    }
    if(dir==0){
        x=a;
        y=b;
        z=c;
    }else if(dir==1){
        x=c;
        y=a;
        z=b;
    }else if(dir==2){
        x=b;
        y=c;
        z=a;
    }else if(dir==3){
        x=-a;
        y=b;
        z=-c;
    }else if(dir==4){
        x=-c;
        y=-a;
        z=b;
    }else if(dir==5){
        x=b;
        y=-c;
        z=-a;
    }
    return {x,y,z};
}

bool try_to_match(int i, int j, vector<set<Pos>>& v, Pos scanner_pos [] ){
    for(int d=0;d<24;d++){
        for(Pos p_start_i:v[i]){
            for(Pos p_start_j:v[j]){
                Pos pivot = rot(p_start_j,d);
                int cnt=0;
                for(Pos p:v[j]){
                    if(v[i].count(p_start_i+(rot(p,d)-pivot) )){
                        cnt++;
                    }
                }
                if(cnt>=12){
                    set<Pos> new_vj;
                    for(Pos p:v[j]){
                        new_vj.insert(rot(p,d));
                    }
                    v[j] = new_vj;
                    scanner_pos[j]=scanner_pos[i]+p_start_i-pivot;

                    return true;
                }
            }
        }
    }
    return false;
}

void part1(){
    ifstream input("input.txt");
    vector<set<Pos>> v;
    set<Pos> current_scanner;
    string s;
    getline(input,s);
    getline(input,s);
    while(input){
        if(s==""){
            getline(input,s);
            v.push_back(current_scanner);
            current_scanner.clear();
        } else {
            stringstream ss(s);
            int x,y,z;
            char c;
            ss >> x >> c >> y >>c >> z;
            current_scanner.insert({x,y,z});
        }
        getline(input,s);
    }
    v.push_back(current_scanner);
//    for( int i=0; i<v.size(); i++){
//        cout << "Scanner " << i << ":\n";
//        for(int j=0; j<v[i].size(); j++){
//            cout << v[i][j].x << " " << v[i][j].y << " " << v[i][j].z << endl;
//        }
//    }
    bool found [v.size()] ={false};
    Pos scanner_pos [v.size()];
    found[0] = true;
    scanner_pos[0]={0,0,0};
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int new_found = q.front();
        q.pop();
        for(int j=0;j<v.size();j++){
            if(!found[j]){
                if( try_to_match(new_found,j,v,scanner_pos) ){
                    q.push(j);
                    found[j]=true;
                }
            }
        }
    }
    set<Pos> beacons;
    for(int i=0; i<v.size();i++){
        for(Pos p:v[i]){
            beacons.insert(scanner_pos[i]+p);
        }
    }
    cout << "Part1: " << beacons.size() << endl;


    int max_dist=0;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v.size();j++){
            int dist = abs(scanner_pos[i].x-scanner_pos[j].x)+abs(scanner_pos[i].y-scanner_pos[j].y)+abs(scanner_pos[i].z-scanner_pos[j].z);
            max_dist=max(dist,max_dist);
        }
    }
    cout << "Part2: " << max_dist << endl;

}
/*
Runs in ~60s. Could be optimized in a couple of ways, but I always try to see if there's a more naive way that's already good enough for me and this was fine by me.
Little explanation:
For each scanner I put all relative beacon locations in a set and I put these sets in a vector.
Each time I'm sure of the location and orientation of a new scanner, I put this in in a queue.
This queue initially only contains scanner 0.
I take the front scanner from the queue. Then I loop through all the scanners that I'm not sure of
and compare with the scanner from the queue to see if they overlap for some orientation.
Given a scanner s that I know and an unknown scanner t, I loop through orientations and pairs of beacons, one in s and one in t.
Then I loop through all the beacons in the unknown scanner and see where this beacon would be if s and t were the same beacon and the
the second scanner had the given orientation.
If we count twelve or more overlapping beacons I know the location and orientation of the scanner t.
I rotate the beacons of t in the set, so that they give their true position.
*/
int main()
{
    part1();
    return 0;
}
