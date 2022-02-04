#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const pair<int,int> directions [] = {{0,-1},{0,1},{-1,0},{1,0}};

vector<vector<int>> read_input(const string& input_string ){
    ifstream input(input_string);
    string s;
    vector<vector<int>> height_map;
    input >> s;
    while(input){
        vector<int> line;
        for(int i=0; i<s.size();i++){
            line.push_back(s[i]-'0');
        }
        height_map.push_back(line);
        input >> s;
    }
    return height_map;
}

bool in_range(const  pair<int,int>& p, const pair<int,int>& dir, const vector<vector<int>>& height_map ){
    return p.first+dir.first>=0&&p.first+dir.first<height_map.size()&&p.second+dir.second>=0&&p.second+dir.second<height_map[0].size();
}

int basin_size(const int& y, const int& x, vector<vector<bool>>& part_of_basin, const vector<vector<int>>& height_map){
    int cnt = 1;
    queue<pair<int,int>> que;
    que.push({y,x});
    part_of_basin[y][x] = true;
    while(!que.empty()){
        pair<int,int> p = que.front();
        que.pop();
        for(int i=0; i<4; i++){
            if( in_range(p,directions[i], height_map) && !part_of_basin[p.first+directions[i].first][p.second+directions[i].second] && height_map[p.first+directions[i].first][p.second+directions[i].second]<9   ){
                part_of_basin[p.first+directions[i].first][p.second+directions[i].second] = true;
                cnt++;
                que.push({p.first+directions[i].first,p.second+directions[i].second});
            }
        }
    }
    return cnt;
}

void part1(){
    vector<vector<int>> height_map = read_input("input.txt");
    int sum_low_points=0;
    int x_size = height_map[0].size();
    int y_size = height_map.size();

    for( int y=0; y<y_size; y++){
        for( int x=0; x<x_size; x++){
            int value = height_map[y][x];
            if( (x-1<0||height_map[y][x-1]>value) && (x+1==x_size||height_map[y][x+1]>value) && (y-1<0||height_map[y-1][x]>value) && (y+1==y_size||height_map[y+1][x]>value) ){
                //cout << "y: " << y << " x: " << x << " value: " << value << endl;
                sum_low_points += value+1;
            }
        }
    }
    cout << "part1: " << sum_low_points << endl;

    vector<vector<bool>> part_of_basin(y_size, vector<bool>(x_size, false) );
    vector<int> basin_sizes;
    for(int y=0; y<y_size; y++){
        for(int x=0; x<x_size; x++){
            if(!part_of_basin[y][x]&&height_map[y][x]!=9){
                int base_size = basin_size(y,x,part_of_basin, height_map);
                basin_sizes.push_back( base_size );
            }
        }
    }
    sort(basin_sizes.begin(),basin_sizes.end());
    int prod2 = basin_sizes[basin_sizes.size()-1] * basin_sizes[basin_sizes.size()-2]  * basin_sizes[basin_sizes.size()-3];
    cout << "part2: " << prod2 << endl;
}

int main()
{
    part1();
    return 0;
}
