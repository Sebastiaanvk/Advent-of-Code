#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int gcd(int x, int y){
    x = abs(x);
    y = abs(y);
    if(x>y) swap(x,y);
    int r=y%x;
    while(r!=0){
        y=x;
        x=r;
        r=y%x;
    }
    return x;
}

bool ast_inbetween(const vector<string>& field, const int& x, const int& y, const int& v, const int& w){
    int dif_x=v-x;
    int dif_y=w-y;
    if(dif_x==0){
        if(dif_y>0)dif_y=1;
        else dif_y=-1;
    }else if(dif_y==0){
        if(dif_x>0) dif_x=1;
        else        dif_x=-1;
    } else {
        int g = gcd(dif_x,dif_y);
        dif_x/=g;
        dif_y/=g;
    }
    int check_x = x+dif_x;
    int check_y = y+dif_y;
    while(check_x!=v||check_y!=w){
        if(field[check_y][check_x]=='#'){
            return true;
        }
        check_x+=dif_x;
        check_y+=dif_y;
    }
    return false;
}

void part1(){
    ifstream input("input.txt");
    vector<string> field;
    string s;
    input >> s;
    while(input){
        field.push_back(s);
        input >> s;
    }
    int max_ast_vis = 0;
    int best_x;
    int best_y;

    for(int y=0; y<field.size(); y++){
        for(int x=0; x<field[0].size(); x++){
            if(field[y][x]=='#'){
                int ast_vis=0;
                for(int w=0; w<field.size(); w++){
                    for(int v=0; v<field[0].size(); v++){
                        if(field[w][v]=='#'&&!(x==v&&y==w)){
                            if(!ast_inbetween(field,x,y,v,w)){
                                ast_vis++;
                            }
                        }
                    }
                }
                if(ast_vis>max_ast_vis){
                    max_ast_vis=ast_vis;
                    best_x=x;
                    best_y=y;
                }
            }
        }
    }

    cout << max_ast_vis << endl;
    cout << "with x:"<< best_x << ",y:"<<best_y << endl;
    //best_x:20, best_y:20
}


struct Loc{
    int x;
    int y;
    bool alive;
};

bool operator<(const Loc& l1, const Loc& l2){
    if(l1.y*l2.x==l2.y*l1.x){
        return l1.x*l1.x+l1.y*l1.y<l2.x*l2.x+l2.y*l2.y;
    }
    return l1.y*l2.x<l2.y*l1.x;

}

Loc next_shot(vector<Loc> asteroids[4], int& current_vector, int& current_pos ){
    while(true){
        if(asteroids[current_vector][current_pos].alive){
            Loc loc = asteroids[current_vector][current_pos];
//            cout << loc.x << " " << loc.y << endl;
            asteroids[current_vector][current_pos].alive=false;
            current_pos++;
            while( current_pos<asteroids[current_vector].size() && loc.y*asteroids[current_vector][current_pos].x==loc.x*asteroids[current_vector][current_pos].y ){
                current_pos++;
            }
            if(current_pos==asteroids[current_vector].size()){
                current_pos=0;
                current_vector = (current_vector+1)%4;
            }

            return loc;
        }
        current_pos++;
        if(current_pos=asteroids[current_vector].size()){
            current_pos=0;
            current_vector = (current_vector+1)%4;
        }
    }
}

void part2(){
    ifstream input("input.txt");
    vector<string> field;
    string s;
    input >> s;


    while(input){
        field.push_back(s);
        input >> s;
    }
    vector<Loc> asteroids [4];

    int x_base = 20;
    int y_base = 20;
    int nr_destroyed=200;
    /*
    int x_base = 8;
    int y_base = 3;
    int nr_destroyed=200;*/

    for(int y=0;y<field.size(); y++){
        for(int x=0; x<field[0].size(); x++){
            if(field[y][x]=='#'){
                int dx= x-x_base;
                int dy = y-y_base;
                if(dx==0){
                    if(dy<0){
                        asteroids[0].push_back({dx,dy,true});
                    } else if(dy>0){
                        asteroids[2].push_back({dx,dy,true});
                    }
                } else if(dx>0){
                    asteroids[1].push_back({dx,dy,true});
                } else {
                    asteroids[3].push_back({dx,dy,true});
                }
            }
        }
    }
    for(int i=0;i<4; i++){
        sort(asteroids[i].begin(),asteroids[i].end()  );
    }
    int next_asteroid_nr = 1;
    int current_vector = 0;
    int current_pos = 0;
    Loc loc;
    while(next_asteroid_nr<=nr_destroyed){
        loc = next_shot(asteroids,current_vector, current_pos);
        next_asteroid_nr++;
    }
    cout << (x_base+loc.x)*100+(y_base+loc.y) << endl;
}

int main()
{
    part2();
    return 0;
}
