#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int x_d [4] = {0,-1,0,1};
const int y_d [4] = {1,0,-1,0};

struct Square{
    int y,x,dist;
};

bool operator<(const Square& s1, const Square& s2){
    return s1.dist>s2.dist;
}

bool operator==(const Square& s1, const Square& s2){
    return s1.dist==s2.dist;
}

void part2(){
    ifstream input("input.txt");
    string s;
    vector<vector<int>> original_map;
    getline(input,s);
    while(input){
        vector<int> line;
        for( int i=0; i<s.size(); i++){
            line.push_back( s[i]-'0' );
        }
        original_map.push_back(line);
        getline(input,s);
    }
    int h = original_map.size();
    int w = original_map[0].size();

    vector<vector<int>> arr(5*h,vector<int>(5*w,0));
    for(int y=0; y<5*h; y++){
        for( int x=0; x<5*w; x++){
            arr[y][x] = ( (original_map[y%h][x%w]+ (y/h) + (x/w)-1)%9 )+1;
        }
    }
//    for(int y=0; y<5*h; y++){
//        for( int x=0; x<5*w; x++){
//            arr[y][x] = ( (original_map[y%h][x%w]+ (y/h) + (x/w)-1)%9 )+1;
//            cout << arr[y][x];
//        }
//        cout << endl;
//    }


    vector<vector<int>> current_min_dist(5*h,vector<int>(5*w,INT_MAX));

    vector<vector<bool>> min_dist_found(5*h,vector<bool>(5*w,false) );
    current_min_dist[0][0]=0;
    priority_queue<Square> q;
    q.push({0,0,0});
    while( !q.empty() ){
        Square s = q.top();
        //cout << s.x << " " << s.y << endl;
        q.pop();
        if(s.y==5*h-1&&s.x==5*w-1){
            cout << "Part2: " << s.dist <<  endl;
            return;
        }
        if(!min_dist_found[s.y][s.x]){
            min_dist_found[s.y][s.x] = true;
            for( int i=0; i<4; i++){
                int new_x = s.x+x_d[i];
                int new_y = s.y+y_d[i];
                if( new_x>=0&&new_y>=0&&new_x<5*w&&new_y<5*h ){
                    if( !min_dist_found[new_y][new_x]&& current_min_dist[s.y][s.x]+arr[new_y][new_x]<current_min_dist[new_y][new_x] ){
                        current_min_dist[new_y][new_x] = current_min_dist[s.y][s.x]+arr[new_y][new_x];
                        q.push({new_y,new_x,current_min_dist[new_y][new_x]});
                    }
                }
            }
        }
    }
    cout << "Error: End not found\n";

}

int main()
{
    part2();
    return 0;
}
