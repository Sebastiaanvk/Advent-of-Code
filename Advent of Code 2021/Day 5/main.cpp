#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void part1(){
    ifstream input("input.txt");
    map<pair<int,int>,int> field;
    char c;
    int x1,y1,x2,y2;
    input >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2;
    int overlaps = 0;
    while(input){
        if(x1==x2){
            if(y1>y2) swap(y1,y2);
            for(int i=y1; i<=y2; i++){
                field[{i,x1}]++;
                if(field[{i,x1}]==2) overlaps++;
            }
        } else if(y1==y2){
            if(x1>x2) swap(x1,x2);
            for(int i=x1; i<=x2; i++){
                field[{y1,i}]++;
                if(field[{y1,i}]==2) overlaps++;
            }
        }
        input >> x1 >> c >> y1 >> c>> c >> x2 >> c >> y2;
    }
    cout << "Part1: " << overlaps << endl;
}

void part2(){
    ifstream input("input.txt");
    map<pair<int,int>,int> field;
    char c;
    int x1,y1,x2,y2;
    input >> x1 >> c >> y1 >> c >> c >> x2 >> c >> y2;
    int overlaps = 0;
    while(input){
        if(x1==x2||y1==y2||abs(x1-x2)==abs(y1-y2)){
            int x_offset,y_offset;
            if(x2-x1>0) x_offset = 1;
            else if(x2==x1) x_offset = 0;
            else x_offset = -1;

            if(y2-y1>0) y_offset = 1;
            else if(y2==y1) y_offset = 0;
            else y_offset = -1;

            int x = x1;
            int y = y1;
            while(x!=x2+x_offset||y!=y2+y_offset){
                field[{y,x}]++;
                if(field[{y,x}]==2) overlaps++;
                x += x_offset;
                y += y_offset;
            }
        }


        input >> x1 >> c >> y1 >> c>> c >> x2 >> c >> y2;
    }
    cout << "Part2: " << overlaps << endl;
}

int main()
{
    part2();
    return 0;
}
