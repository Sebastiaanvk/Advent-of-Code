#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void part1(){
    ifstream input("input.txt");
    string s;
    vector<vector<int>> v = {{0}};
    int sum = 0;
    getline(input,s);
    for(int i=1; i<s.size(); i++){
        sum += s[i]-'0';
        v[0].push_back(sum);
    }
    getline(input,s);
    while(input){
        vector<int> line = { (s[0]-'0')+v[v.size()-1][0] };
        for(int i=1; i<s.size(); i++){
            line.push_back( s[i]-'0'+ min( line[i-1],v[v.size()-1][i] ) );
        }
        v.push_back(line);
        getline(input,s);
    }
    cout << "Part1: " << v[ v.size()-1 ][v[0].size()-1] << endl;
}

void part2(){
    ifstream input("input.txt");
    string s;
    vector< vector<int> > original_map;
    getline(input,s);
    while(input){
        vector<int> line;
        for(int i=0; i<s.size(); i++){
            line.push_back(s[i]-'0');
        }
        original_map.push_back(line);
        getline(input,s);
    }
    int w = original_map[0].size();
    int h = original_map.size();
    vector<vector<int>> v;
    bool second_strategy = true;
    if(second_strategy){
        vector< vector<int> > new_map;
        new_map.resize(5*h);
        for(int y=0;y<5*h;y++){
            new_map[y].resize(5*w);
            for(int x=0; x<5*w; x++){
                new_map[y][x]=(original_map[y%h][x%w]+y/h+x/w-1)%9+1;
            }
        }

//        for(int y=0; y<new_map.size(); y++){
//            for(int x=0; x<new_map[0].size(); x++){
//                cout << new_map[y][x];
//            }
//            cout << endl;
//        }
        v = {{0}};
        for( int x=1; x<new_map[0].size(); x++){
            v[0].push_back(v[0][x-1]+new_map[0][x]);
        }
        for( int y=1; y<new_map.size(); y++){
            v.push_back({v[y-1][0]+new_map[y][0]});
            for(int x=1; x<v[0].size(); x++){
                v[y].push_back(new_map[y][x]+min(v[y][x-1],v[y-1][x]) );
            }
        }
    }else{
        v = {{}};
        int sum = -original_map[0][0];
        for(int m=0; m<5; m++){
            for(int i=0; i<w; i++){
                sum += (original_map[0][i]+m-1)%9+1;
                v[0].push_back(sum);
            }
        }

        for(int y=1; y<5*h; y++){
            vector<int> line = { v[y-1][0]+(original_map[y%h][0]+y/h-1)%9+1 };
            for( int x=1; x<5*w; x++){
                int n = (original_map[y%h][x%w]+y/h+x/w-1)%9+1;
                line.push_back(n + min(line[x-1],v[y-1][x]));
            }
            v.push_back(line);
        }
    }

    cout << "Part2: " << v[ v.size()-1 ][v[0].size()-1] << endl;
}

int main()
{
    part2();
    return 0;
}
