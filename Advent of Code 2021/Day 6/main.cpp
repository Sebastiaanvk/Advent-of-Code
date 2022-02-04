#include <iostream>
#include <fstream>

using namespace std;

void part1(){
    ifstream input("input.txt");
    long long x;
    input >> x;

    long long fishes [9] = {0};

    while(input){
        fishes[x]++;
        input.ignore(1);
        input >> x;
    }

    for( int i=0; i<80; i++){
        long long zeroes = fishes[0];
        for(int i=0; i<8; i++){
            fishes[i] = fishes[i+1];
        }
        fishes[6] += zeroes;
        fishes[8] = zeroes;
    }

    long long total = 0;
    for(int i=0; i<=8; i++) {
        total += fishes[i];
    }

    cout << "part1: " << total << endl;

    for(int i=80; i<256; i++){
        long long zeroes = fishes[0];
        for(int i=0; i<8; i++){
            fishes[i] = fishes[i+1];
        }
        fishes[6] += zeroes;
        fishes[8] = zeroes;
    }

    total = 0;
    for(int i=0; i<=8; i++) {
        total += fishes[i];
    }

    cout << "part2: " << total << endl;
}

int main()
{
    part1();
    return 0;
}
