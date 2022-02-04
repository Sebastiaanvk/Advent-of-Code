#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point{
    int x;
    int y;
    int vx;
    int vy;
};

istream& operator>>(istream& input, Point& p){
    input.ignore(100,'<');
    input>>p.x;
    input.ignore();
    input>>p.y;
    input.ignore(100,'<');
    input>>p.vx;
    input.get();
    input>>p.vy;
    input.ignore(100,'>');
    return input;
}

ostream& operator<<(ostream& output, Point& p){
    output << p.x << ", " << p.y << ", speed: " << p.vx << ", " << p.vy;
    return output;
}

int width( const vector<Point>& points ){
    int min_x = 1000000;
    int max_x = -1000000;
    for( Point p:points){
        if(p.x<min_x) min_x=p.x;
        if(p.x>max_x) max_x=p.x;
    }
    return max_x-min_x;
}

int height( const vector<Point>& points ){
    int min_y = 1000000;
    int max_y = -1000000;
    for( Point p:points){
        if(p.y<min_y) min_y=p.y;
        if(p.y>max_y) max_y=p.y;
    }
    return max_y-min_y;
}

void iterate_points(vector<Point>& points){
    for(int i=0; i<points.size(); i++){
        points[i].x += points[i].vx;
        points[i].y += points[i].vy;
    }
}

void print( vector<Point>& points ){
    int min_x = 1000000;
    int max_x = -1000000;
    int min_y = 1000000;
    int max_y = -1000000;
    for( Point p:points){
        if(p.x<min_x) min_x=p.x;
        if(p.x>max_x) max_x=p.x;
        if(p.y<min_y) min_y=p.y;
        if(p.y>max_y) max_y=p.y;
    }
    bool arr [max_y-min_y+1][max_x-min_x+1] = {false};
    for(auto p:points){
        arr[p.y-min_y][p.x-min_x] = true;
    }
    for(int y=0;y<=max_y-min_y; y++){
        for(int x=0; x<=max_x-min_x; x++){
            if(arr[y][x]) cout << '*';
            else cout << " ";
        }
        cout << endl;
    }

}

void part1(){
    vector<Point> points;
    Point p;
    ifstream input("input.txt");
    input >> p;
    while(input){
        cout << p << endl;
        points.push_back(p);
        input>>p;
    }

    const int relevant_height = 20;
    int time_waited=0;
    while( height(points)>relevant_height ){
        iterate_points(points);
        time_waited++;
    }
    while(height(points)<=relevant_height){
        cout << "Time waited: " << time_waited << endl;
        print(points);
        cout << endl << endl;
        iterate_points(points);
        time_waited++;
    }
}

int main()
{
    part1();
    return 0;
}
