#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long gcd(long x, long y){
    if(x>y) swap(x,y);
    long r=y%x;
    while(r!=0){
        y=x;
        x=r;
        r=y%x;
    }
    return x;
}

void part2(){
    ifstream input("input.txt");
    long long time;
    input >> time;

    long long bus;
    input >> bus;
    time = 0;
    long long offset = bus;

    char c;
    input.get(c);

    long long extra = 0;

    while(input){
        extra++;
        c = input.peek();
        if(input&&c!='x'){
            input >> bus;
            cout << "Time waited " << extra << " bus id" << bus << endl;
            while( (time+extra)%bus!=0 ){
                time+=offset;
            }
            cout << time << endl;
            offset *=bus/(gcd(bus,offset));

        } else {
        input.get(c);
        }

        input.get(c);
    }
    cout << "part2:" << time << endl;
}

int main()
{
    ifstream input("input.txt");
    int time;
    input >> time;
    int min_waiting;
    int min_waiting_bus;

    int bus;
    input >> bus;
    min_waiting = bus - (time%bus);
    min_waiting_bus = bus;
    char c;
    input.get(c);

    while(input){
        c = input.peek();
        if(input&&c!='x'){
            input >> bus;
            if(bus - (time%bus)<min_waiting){
                min_waiting=bus - (time%bus);
                min_waiting_bus=bus;
            }
        } else {
        input.get(c);
        }

        input.get(c);
    }
    cout << "part1:" << min_waiting*min_waiting_bus << endl;

    part2();

    return 0;
}
