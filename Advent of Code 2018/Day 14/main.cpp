#include <iostream>
#include <vector>

using namespace std;

//const int NR_RECIPES = 51589;
const int NR_RECIPES = 702831;
const int NR_DIGITS = 6;

void part1(){
    vector<int> v = {3,7};
    int i1=0;
    int i2=1;
    while(v.size()<NR_RECIPES+10){
        int x=v[i1]+v[i2];
        if(x>=10){
            v.push_back(1);
        }
        v.push_back(x%10);
        i1 = (i1+v[i1]+1)%v.size();
        i2 = (i2+v[i2]+1)%v.size();
    }
    string s;
    for( int i=0; i<10; i++){
        s += to_string(v[NR_RECIPES+i]);
    }
    cout << "part1: " << s << endl;
}

bool ends_with_right_digits(const vector<int>& v){
    int i=v.size()-1;
    for( int n=NR_RECIPES; n>0; n/=10){
        if( i<0||n%10!=v[i] ){
            return false;
        }
        i--;
    }

    return true;
}


int part2(){
    vector<int> v = {3,7};
    int i1=0;
    int i2=1;
    while(true){
        int x=v[i1]+v[i2];
        //cout << x << endl;
        if(x>=10){
            v.push_back(1);
            if( ends_with_right_digits(v) ){
                return int(v.size()-NR_DIGITS);
            }
        }
        v.push_back(x%10);
        if( ends_with_right_digits(v) ){
                return int(v.size()-NR_DIGITS);
            }
        i1 = (i1+v[i1]+1)%v.size();
        i2 = (i2+v[i2]+1)%v.size();
    }
}

int main()
{
    cout << part2() << endl;
    return 0;
}
