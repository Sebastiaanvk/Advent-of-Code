#include <iostream>
#include <fstream>

using namespace std;

void part1(){
    ifstream input("input.txt");
    int sum = 0;
    int x;
    input >> x;
    while(input){
        sum += (x/3)-2;
        input >> x;
    }
    cout << sum;
}

void part2(){
    ifstream input("input.txt");
    int sum = 0;
    int x;
    input >> x;
    while(input){
        x = (x/3)-2;
        while(x>0){
            sum += x;
            x = (x/3)-2;
        }
        input >> x;
    }
    cout << sum;
}

int main()
{
    part2();
    return 0;
}
