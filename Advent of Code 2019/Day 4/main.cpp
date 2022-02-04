#include <iostream>
#include <vector>

using namespace std;

bool is_password(int x){
    bool double_digits = false;
    int last_digit=x%10;
    x/=10;
    while(x!=0){
        int digit = x%10;
        if(digit==last_digit) double_digits = true;
        if( digit>last_digit) return false;
        last_digit=digit;
        x/=10;
    }
    return double_digits;
}

void part1(){
    int minimum = 278384;
    int maximum = 824795;
    int track = 0;
    for(int x=278384; x<maximum; x++){
        if(is_password(x)) track++;
    }
    cout << track << endl;
}

bool is_password2(int x){
    vector<int> v;
    int last_digit=x%10;
    x/=10;
    v.push_back(last_digit);
    while(x!=0){
        int digit = x%10;
        if( digit>last_digit) return false;
        last_digit=digit;
        v.push_back(last_digit);
        x/=10;
    }
    if(v[0]==v[1]&&v[1]!=v[2]) return true;
    if(v[5]==v[4]&&v[3]!=v[4]) return true;
    for(int i=1; i<4;i++){
        if(v[i]==v[i+1]&&v[i]!=v[i-1]&&v[i+1]!=v[i+2]) return true;
    }

    return false;
}

void part2(){
    int minimum = 278384;
    int maximum = 824795;
    int track = 0;
    for(int x=278384; x<maximum; x++){
        if(is_password2(x)) track++;
    }
    cout << track << endl;
}

int main()
{
    part2();
    return 0;
}
