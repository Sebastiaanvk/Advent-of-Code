#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void run_computer(vector<long long> v){
    long long in = 2;
    int pos = 0;
    long long rel_base=0;
    while(true){
        long long command = v[pos];
        int opcode = command%100;
        command/=100;
        long long adr[3];
        for(int i=0;i<3&&pos+1+i<v.size();i++){
            if( command%10==0 ){
                adr[i] = v[pos+1+i];
            }else if(command%10==1){
                adr[i] = pos+1+i;
            } else if(command%10==2){
                adr[i] = rel_base+v[pos+1+i];
            }
            command /= 10;
        }
        if(opcode==1){
            v[adr[2]]=v[adr[0]]+v[adr[1]];
            pos+=4;
        } else if(opcode==2){
            v[adr[2]]=v[adr[0]]*v[adr[1]];
            pos+=4;
        } else if(opcode==3){
            v[adr[0]] = in;
            pos+=2;
        } else if(opcode==4){
            cout << v[adr[0]] << endl;
            pos+=2;
        } else if(opcode==5){
            if(v[adr[0]]!=0){
                pos = v[ adr[1] ];
            } else {
                pos+=3;
            }
        } else if(opcode==6){
            if(v[ adr[0] ]==0){
                pos = v[ adr[1] ];
            } else {
                pos+=3;
            }
        } else if(opcode==7){
            if( v[ adr[0] ]<v[adr[1]] ){
                v[adr[2]] = 1;
            } else {
                v[adr[2]] = 0;
            }
            pos+=4;
        } else if(opcode==8){
            if( v[ adr[0] ]==v[adr[1]] ){
                v[adr[2]] = 1;
            } else {
                v[adr[2]] = 0;
            }
            pos+=4;
        } else if(opcode==9){
            rel_base += v[adr[0]];
            pos+=2;
        } else{
            return;
        }
    }
}

void part1(){
    ifstream input("input.txt");
    vector<long long> v;
    long long x;
    input >> x;
    while(input){
        v.push_back(x);
        input.get();
        input >> x;
    }

    run_computer(v);


}

int main()
{
    part1();
    return 0;
}
