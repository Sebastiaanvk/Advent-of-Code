#include <iostream>
#include <unordered_set>

using namespace std;

const long long P = 20201227;

void part1(){
    unordered_set<int> possible_keys;
    long long subject_key1 = 14788856;
//    long long subject_key1 = 5764801;

    long long v1=1;
    int i=0;
    while(v1!=subject_key1){
        v1=(7*v1)%P;
        i++;
    }
    cout << "loops:" << i << endl;
    long long subject_key2 = 19316454;
//    long long subject_key2 = 17807724;

    long long v2=1;
    for(int j=0; j<i; j++){
        v2=(v2*subject_key2)%P;
    }



    cout << "part1:" << v2 << endl;
}

int main()
{
    part1();
    return 0;
}
