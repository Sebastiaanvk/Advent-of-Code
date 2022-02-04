#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

void part1(){
    ifstream input("input.txt");
    string s;
    getline(input,s);
    set< pair<int,int> > points;
    while(s!=""){
        int x,y;
        stringstream ss(s);
        ss>>x;
        ss.ignore(1);
        ss>>y;
        points.insert({x,y});
        getline(input,s);
    }

    cout << "initial set size: " << points.size() << endl;

    getline(input,s);
    bool printed_part1 = false;
    while(input){
//        for(int y=0;y<50; y++){
//        for( int x=0; x<50; x++){
//            if(points.count({x,y})>0){
//                cout << '#';
//            } else {
//                cout << '.';
//            }
//        }
//        cout << endl;
//        }
        stringstream ss(s);
        ss.ignore(11);
        char c;
        ss>>c;

        ss.ignore();
        int n;
        ss>>n;
        vector<pair<int,int> > v;
        v.assign( points.begin(),points.end() );

        for(int i=0; i<v.size(); i++){
            pair<int,int> p = v[i];
            int x,y;
            x = p.first;
            y = p.second;
            if(c=='x'&&x>n){
                points.erase(p);
                points.insert({2*n-x,y});
            } else if(c=='y' && y>n ) {
                points.erase(p);
                points.insert({x,2*n-y});
            }
        }
        if(!printed_part1){
            printed_part1 = true;
            cout << "Part1: " << points.size() << endl;
        }

        getline(input,s);
    }

    for(int y=0;y<20; y++){
        for( int x=0; x<50; x++){
            if(points.count({x,y})>0){
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
}

int main()
{
    part1();
    return 0;
}
