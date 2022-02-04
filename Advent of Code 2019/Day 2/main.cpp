#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void part1(){
    vector<int> in;
    ifstream input("input.txt");
    int x;
    input >> x;
    while(input){
        in.push_back(x);
        input.get();
        input >> x;
    }
    in[1]=12;
    in[2]=2;
    int pos=0;
    while(in[pos]!=99){
        if(in[pos+3]>=in.size()){
            in.resize( in[pos+3]+1 );
        }
        if(in[pos]==1){
            in[in[pos+3]]=in[in[pos+1]]+in[in[pos+2]];
        } else {
            in[in[pos+3]]=in[in[pos+1]]*in[in[pos+2]];
        }
        pos +=4;
    }
    cout << in[0] << endl;
}

void part2(){
    vector<int> base_in;
    ifstream input("input.txt");
    int x;
    input >> x;
    while(input){
        base_in.push_back(x);
        input.get();
        input >> x;
    }

    for(int x=0; x<100; x++){
        for(int y=0; y<100; y++){
            vector<int> in = base_in;
            in[1]=x;
            in[2]=y;
            int pos=0;
            while(in[pos]!=99){
                if(in[pos+3]>=in.size()){
                    in.resize( in[pos+3]+1 );
                }
                if(in[pos]==1){
                    in[in[pos+3]]=in[in[pos+1]]+in[in[pos+2]];
                } else {
                    in[in[pos+3]]=in[in[pos+1]]*in[in[pos+2]];
                }
                pos +=4;
            }
            if(in[0]==19690720){
                cout << x << y << endl;
                return;
            }
        }
    }
}

int main()
{
    part2();
    return 0;
}
