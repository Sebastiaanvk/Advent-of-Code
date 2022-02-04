#include <iostream>
#include <map>

using namespace std;

struct Loc{
    int x;
    int y;
};
bool operator<(const Loc& l1, const Loc& l2){
    if(l1.y==l2.y) return l1.x<l2.x;
    return l1.y<l2.y;
}

bool operator==(const Loc& l1, const Loc& l2){
    return l1.x==l2.x&&l1.y==l2.y;
}

int main()
{
    map<Loc, int> m;
    for(int i=0; i<10000000; i++){
        m[{i,2*i+7}] = i*i;
    }
    return 0;
}
