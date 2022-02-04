#include <iostream>
#include <fstream>

using namespace std;

void part1(){
    ifstream input("input.txt");
    int x;
    int last;
    input >> last;

    input >> x;
    int higher = 0;
    while(input){
        if(x>last)higher++;
        last = x;
        input >> x;
    }
    cout << higher << endl;
}

void part2(){
    ifstream input("input.txt");
    int x, last, last_last, sum;
    input >> x;
    input >> last_last;
    input >> last;
    sum =x+last_last+last;
    input >> x;
    int higher = 0;
    while(input){
        if(x+last+last_last>sum) higher++;
        sum = x+last+last_last;
        last_last=last;
        last = x;
        input >> x;
    }
    cout << higher << endl;
}

int main()
{
    part2();
    return 0;
}
