#include <iostream>
#include <unordered_map>

using namespace std;

void part2(){
    unordered_map<int,int> indices;
    indices[0]=1;
    indices[13]= 2;
    indices[1]=3;
    indices[16]=4;
    indices[6]=5;

    int last = 17;
    int now;

    for(int turn=7; turn<=30000000; turn++){
        if(indices.count(last)==0){
            now = 0;
        } else {
            now = turn-1-indices[last];
        }

        indices[last]=turn-1;
        last = now;
//        printf("turn:%d value:%d\n",turn,last);
    }
    cout << "part2: " << last << endl;
}

void part1(){
    const int MAX_TURNS = 30000000;

   static int indices[MAX_TURNS+1]={0};
   indices[0]=1;
   indices[13]= 2;
   indices[1]=3;
   indices[16]=4;
   indices[6]=5;

   int last = 17;

   for(int turn=7; turn<=MAX_TURNS; turn++){
        int now;
        if(indices[last]==0){
            now = 0;
        } else {
            now = turn-1-indices[last];
        }

        indices[last]=turn-1;
        last = now;
   }
   cout << "part1: " << last << endl;

}

int main()
{
    part1();
//    part2();
    return 0;
}
