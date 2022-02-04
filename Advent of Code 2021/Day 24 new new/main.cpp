#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct ComChain{
    long long offset_1;
    long long div_26;
    long long offset_2;
};

void read_input(string name, vector<ComChain>& com_chains){
    com_chains.clear();
    com_chains.resize(14);
    ifstream input(name);
    string s;
    for(int i=0; i<14; i++){
        for(int line=1; line<=18; line++){
            getline(input,s);
            stringstream ss(s);
            if(line==5){

                ss.ignore(6);
                int x;
                ss>>x;
                com_chains[i].div_26=x;
            } else if(line==6){
                ss.ignore(6);
                ss>>com_chains[i].offset_1;
            } else if(line==16){
                ss.ignore(6);
                ss>>com_chains[i].offset_2;
            }
        }
    }
}
const long long pow_26 [14]= {1,26,676,17576,456976,11881376,308915776,8031810176};
vector<ComChain> com_chains_main;
string answer = "12345678901234";

bool try_input(long long z,int depth){
    if(depth==14){
        return z==0;
    }
    if( depth>=7&&z>=pow_26[14-depth] ){
        return false;
    }
//Switch the following two lines for part1 or part2.
//    for( long long w=1; w<=9; w++){
    for( long long w=9; w>=1; w--){
        if( (z%26)+com_chains_main[depth].offset_1==w ){
            if( try_input(z/com_chains_main[depth].div_26,depth+1) ){
                answer[depth]= '0'+w;
                return true;
            }
        } else {
            if( try_input( (z/com_chains_main[depth].div_26)*26+com_chains_main[depth].offset_2+w ,depth+1) ){
                answer[depth]= '0'+w;
                return true;
            }
        }
    }
    return false;
}

void part1(){
    read_input("input.txt", com_chains_main);
    try_input(0,0);
    cout << "Part1: " << answer;
}


int main()
{
    part1();
    return 0;
}
