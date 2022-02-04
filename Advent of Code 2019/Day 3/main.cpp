#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Pos{
    int x;
    int y;
};

/*
struct Line{
    Pos pos1;
    Pos pos2;
};
*/

vector<Pos> read_line(string s){
    stringstream iss(s);
    char c;
    int dist;
    iss.get(c);
    iss >> dist;
    int x=0;
    int y=0;
    vector<Pos> positions;
    positions.push_back({0,0});
    while(iss){
        if(c=='U'){
            y -= dist;
        } else if(c=='D'){
            y += dist;
        } else if(c=='L'){
            x -= dist;
        } else {
            x+= dist;
        }

        positions.push_back({x,y});
        iss.get();
        iss.get(c);
        iss >> dist;
    }
    return positions;
}

int lines_cut(const Pos& p1, const Pos& p2, const Pos& q1, const Pos& q2){
    if(p1.y==p2.y){
        if(q1.y==q2.y){
            return 0;
        } else {
            if( (q1.y-p1.y)*(q2.y-p1.y)<=0  && (p1.x-q1.x)*(p2.x-q1.x)<=0 ){
                return abs(p1.y)+abs(q2.x);
            }
        }
    } else if(p1.x==p2.x){
        if(q1.x==q2.x){
            return 0;
        } else {
            if( (q1.x-p1.x)*(q2.x-p1.x)<=0  && (p1.y-q1.y)*(p2.y-q1.y)<=0 ){
                return abs(p1.x)+abs(q2.y);
            }
        }
    }
    return 0;
}



void part1(){
    ifstream input("input.txt");
    string s;
    getline(input,s);

    vector<Pos> first_positions = read_line(s);
    getline(input,s);
    vector<Pos> second_positions = read_line(s);
    int min_man=99999999;
    for(int i=1; i<first_positions.size(); i++){
        for( int j=1; j<second_positions.size(); j++){
            int d = lines_cut(first_positions[i-1],first_positions[i],second_positions[j-1],second_positions[j]);
            if(d!=0&&d<min_man){
                min_man = d;
            }
        }
    }
    cout << min_man << endl;

}

void part2(){
    ifstream input("input.txt");
    string s;
    getline(input,s);

    vector<Pos> first_positions = read_line(s);
    getline(input,s);
    vector<Pos> second_positions = read_line(s);
    int min_steps=99999999;
    int steps_first=0;
    for(int i=1; i<first_positions.size(); i++){

        int steps_second=0;
        for( int j=1; j<second_positions.size(); j++){

            int d = lines_cut(first_positions[i-1],first_positions[i],second_positions[j-1],second_positions[j]);
            if(d!=0){
                int extra_steps;
                if(first_positions[i-1].x==first_positions[i].x){
                    extra_steps = abs(first_positions[i-1].y-second_positions[j-1].y) + abs(second_positions[j-1].x-first_positions[i-1].x);
                } else {
                    extra_steps = abs(first_positions[i-1].x-second_positions[j-1].x) + abs(second_positions[j-1].y-first_positions[i-1].y);
                }
                if(steps_first+steps_second+extra_steps<min_steps){
                    min_steps = steps_first+steps_second+extra_steps;
                }
            }
            steps_second += abs(second_positions[j].x-second_positions[j-1].x) + abs(second_positions[j].y-second_positions[j-1].y);
        }
        steps_first += abs( first_positions[i].x-first_positions[i-1].x) + abs(first_positions[i].y-first_positions[i-1].y);
    }
    cout << min_steps << endl;

}


int main()
{
    part2();
    return 0;
}
