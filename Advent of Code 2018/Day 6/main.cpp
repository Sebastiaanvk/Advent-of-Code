#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Coord{
    int x;
    int y;
};

ifstream& operator>>(ifstream& input, Coord& c){
    input>>c.x;
    char ch;
    input>>ch;
    input>>c.y;
    return input;
}

vector<Coord> read_input(){
    ifstream input("input.txt");
    Coord c;
    input >> c;
    vector<Coord> v;
    while(input){
        v.push_back(c);
        input >> c;
    }
    return v;
}

void part1(){
    vector<Coord> coordinates = read_input();
    int min_x = coordinates[0].x;
    int max_x = coordinates[0].x;
    int min_y = coordinates[0].y;
    int max_y = coordinates[0].y;
    for( int i=0; i<coordinates.size(); i++){
        min_x=min(min_x,coordinates[i].x);
        max_x=max(max_x,coordinates[i].x);
        min_y=min(min_y,coordinates[i].y);
        max_y=max(max_y,coordinates[i].y);
    }
    cout << min_x << " " << max_x << endl;
    cout << min_y << " " << max_y << endl;

    int track [coordinates.size()] = {0};
    for(int x=min_x;x<=max_x; x++){
        for(int y=min_y; y<=max_y; y++){
            int min_index;
            int min_distance=1000000;
            for( int i=0; i<coordinates.size(); i++){
                int distance = abs(coordinates[i].x-x)+abs(coordinates[i].y-y);
                if( distance<min_distance ){
                    min_distance=distance;
                    min_index=i;
                } else if( distance==min_distance ){
                    min_index=-1;
                }
            }
            if(min_index!=-1){
                if(x!=min_x&&x!=max_x&&y!=min_y&&y!=max_y&&track[min_index]!=-1){
                    track[min_index]++;
                } else {
                    track[min_index]=-1;
                }
            }
        }
    }
    int m=0;
    for( int i=0; i<coordinates.size(); i++){
        if(track[i]>m){
            m=track[i];
        }
    }
    cout << "Part1: " << m << endl;
}

void part2(){
    vector<int> xs;
    vector<int> ys;
    char c;
    ifstream input("input.txt");
    int x,y;
    input >> x >> c >> y;
    while(input){
        xs.push_back(x);
        ys.push_back(y);
        input>>x>>c>>y;
    }
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    int sum_x=0;
    for( auto x:xs){
        sum_x+=x;
    }
    int sum_y=0;
    for(auto y:ys){
        sum_y+=y;
    }
    cout << sum_x << endl;
    cout << sum_y << endl;

    int arr_x [1000] = {0};
    for(int i=0; i<1000; i++){
        int sum=0;
        for( auto x:xs){
            sum+=abs(x-i);
        }
        arr_x[i]=sum;
    }

    int arr_y [1000] = {0};

    for(int i=0; i<1000; i++){
        int sum=0;
        for( auto y:ys){
            sum+=abs(y-i);
        }
        arr_y[i]=sum;
    }

    int total=0;
    for(int x=0; x<1000; x++){
        int y_left=0;
        while( y_left<10000 && arr_x[x]+arr_y[y_left]>10000) y_left++;
        int y_right=1000-1;
        while(y_right>=0&&arr_x[x]+arr_y[y_right]>10000) y_right--;
        if(y_right>=y_left){
            total+=y_right-y_left+1;
        }
    }


    cout << "part2: " << total;
}

int main()
{
    part2();
    return 0;
}
