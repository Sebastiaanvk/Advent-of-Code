#include <iostream>
#include <fstream>

using namespace std;

void part1(){
    ifstream input("input.txt");
    int x=0;
    int y=0;

    int n;
    string s;
    input >> s >> n;
    while(input){
        if(s=="down") y+=n;
        if(s=="up")     y-=n;
        if(s=="forward")x+=n;

        input >> s >> n;
    }

    cout << "x: " << x << " y:" << y << endl;
    cout << x*y << endl;
}

void part2(){
    ifstream input("input.txt");
    int x=0;
    int aim= 0;
    int y=0;

    int n;
    string s;
    input >> s >> n;
    while(input){
        if(s=="down") aim+=n;
        if(s=="up")     aim-=n;
        if(s=="forward"){
            x+=n;
            y += aim*n;
        }

        input >> s >> n;
    }

    cout << "x: " << x << " y:" << y << endl;
    cout << x*y << endl;
}

int main()
{
    part2();
    return 0;
}
