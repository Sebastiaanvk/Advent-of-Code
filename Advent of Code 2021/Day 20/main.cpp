#include <iostream>
#include <set>
#include <unordered_set>
#include <fstream>
#include <vector>

using namespace std;

int loc_to_number(int y, int x, set<pair<int,int>> s){
    int sum = 0;
    int prod=1;
    for(int dy=1; dy>=-1;dy--){
        for(int dx=1;dx>=-1;dx--){
            if( s.count({y+dy,x+dx}) ){
                sum += prod;
            }
            prod *= 2;
        }
    }
    return sum;
}

void print(set<pair<int,int>> s, int min_y, int min_x, int max_y, int max_x){
    for(int y=min_y; y<=max_y; y++){
        for(int x=min_x; x<=max_x; x++){
            if( s.count({y,x})){
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}


void part1(){
    ifstream input("input.txt");
    string algo;
    input >> algo;
    cout << algo << endl;
    set<pair<int,int>> lit_loc;
    int min_x=0;
    int min_y=0;
    string s;
    input >> s;
    int max_x=s.size()-1;
    int line=0;
    while(input){
        for(int x=0;x<s.size();x++){
            if(s[x]=='#'){
                lit_loc.insert({line,x});
            }
        }
        line++;
        input >> s;
    }
    int max_y=line-1;

    for(int i=0; i<2; i++){
        print(lit_loc, min_y, min_x, max_y, max_x);
        min_x--;
        min_y--;
        max_x++;
        max_y++;
        set<pair<int,int>> new_set;
        for(int y=min_y;y<=max_y;y++){
            cout << y << endl;
            for(int x=min_x;x<=max_x;x++){
                if( algo[loc_to_number(y,x,lit_loc)]=='#' ){
                    new_set.insert({y,x});
                }
            }
        }
        lit_loc = new_set;
    }
    print(lit_loc, min_y, min_x, max_y, max_x);
    cout << "Part1: " << lit_loc.size() << endl;
}

void print_v(const vector<vector<char>>& v){
    for( auto vec:v){
        for(auto c:vec){
            cout << c;
        }
        cout << endl;
    }
    cout << endl;
}

int loc_to_number_v(int y, int x, vector<vector<char>>& vs){
    int sum = 0;
    int prod=1;
    for(int dy=1; dy>=-1;dy--){
        for(int dx=1;dx>=-1;dx--){
            if( vs[y+dy][x+dx]=='#' ){
                sum += prod;
            }
            prod *= 2;
        }
    }
    return sum;
}

int part1_vector(){
    ifstream input("input.txt");
    string algo;
    input >> algo;
    cout << algo << endl;
    vector<vector<char>> lit_loc_v;
    string s;
    lit_loc_v.push_back({});
    lit_loc_v.push_back({});
    input >> s;
    while(input){
        lit_loc_v.push_back({'.','.'});
        for(int x=0;x<s.size();x++){
            lit_loc_v[lit_loc_v.size()-1].push_back(s[x]);
        }
        lit_loc_v[lit_loc_v.size()-1].push_back('.');
        lit_loc_v[lit_loc_v.size()-1].push_back('.');
        input >> s;
    }
    vector<char> v (s.size()+4,'.');
    lit_loc_v[0] = v;
    lit_loc_v[1] = v;
    lit_loc_v.push_back(v);
    lit_loc_v.push_back(v);

    for(int i=0; i<50; i++){
//        print_v(lit_loc_v);
        char c = '.';
        if(i%2==0) c='#';
        vector<vector<char>> new_v(lit_loc_v.size()+2,vector<char>(lit_loc_v[0].size()+2,c) );


        for(int y=1;y<lit_loc_v.size()-1;y++){
            for(int x=1;x<lit_loc_v[0].size()-1;x++){
                if( algo[loc_to_number_v(y,x,lit_loc_v)]=='#'){
                    new_v[y+1][x+1] = '#';
                } else {
                    new_v[y+1][x+1] = '.';
                }
            }
        }
        lit_loc_v = new_v;
    }
    print_v(lit_loc_v);
    int track=0;
    for(auto v:lit_loc_v){
        for(auto c:v){
            if(c=='#'){
                track++;
            }
        }
    }

    cout << "Part1: " << track << endl;
}

int main()
{
    part1_vector();
    return 0;
}
