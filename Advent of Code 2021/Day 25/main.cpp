#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const char E = '>';
const char S = 'v';
const char P = '.';

void part1(){
    ifstream input("input.txt");
    vector<string> field;
    string s;
    getline(input,s);
    while(input){
        field.push_back(s);
        getline(input,s);
    }

    int max_x=field[0].size()-1;
    int max_y=field.size()-1;

    int step=0;
    bool moved = true;
//    for(int i=0;i<field.size();i++) cout << field[i] << endl;
//    cout << endl;
    while(moved){

        step++;
        vector<pair<int,int>> move_east;
        for(int y=0;y<=max_y;y++){
            for(int x=0;x<=max_x;x++){
                if(field[y][x]==E){
                    if( (x<max_x&&field[y][x+1]==P)||(x==max_x&&field[y][0]==P ) ){
                        move_east.push_back({y,x});
                    }
                }
            }
        }
        moved = move_east.size()!=0;
        for(auto p:move_east){
            field[p.first][p.second]=P;
            if(p.second==max_x){
                field[p.first][0]=E;
            } else {
                field[p.first][p.second+1]=E;
            }
        }

        vector<pair<int,int>> move_south;
        for(int y=0;y<=max_y;y++){
            for(int x=0;x<=max_x;x++){
                if(field[y][x]==S){
                    if( (y<max_y&&field[y+1][x]==P)||(y==max_y&&field[0][x]==P ) ){
                        move_south.push_back({y,x});
                    }
                }
            }
        }
        moved = (move_south.size()!=0)||moved;
        for(auto p:move_south){
            field[p.first][p.second]=P;
            if(p.first==max_y){
                field[0][p.second]=S;
            } else {
                field[p.first+1][p.second]=S;
            }
        }
//        for(int i=0;i<field.size();i++) cout << field[i] << endl;
//        cout << endl;
    }
    cout << "Part1: " << step << endl;

}

int main()
{
    part1();
    return 0;
}
