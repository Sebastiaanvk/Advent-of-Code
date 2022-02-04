#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void part1(){
    ifstream input("input.txt");
    vector<int> v;
    int x;
    input >> x;
    while(input){
        v.push_back(x);
        input.get();
        input >> x;
    }

    int in=1;
    int pos=0;
    bool cont=true;
    while(cont){
        int com = v[pos];
        int opcode = com%100;
        com/=100;
        switch(opcode){
            case 1:
            case 2:
                int x1,x2;
                if(com%10==0)   x1 = v[ v[pos+1] ];
                else            x1 = v[pos+1];
                com /= 10;
                if(com%10==0)   x2 = v[ v[pos+2] ];
                else            x2 = v[pos+2];
                if(opcode==1){
                    v[ v[pos+3] ] = x1+x2;
                } else {
                    v[ v[pos+3] ] = x1*x2;
                }
                pos += 4;
                break;
            case 3:
               v[v[pos+1]] = in;
               pos+=2;
               break;
            case 4:
                if(com==0){
                    cout << v[ v[pos+1] ] << endl;
                } else {
                    cout << v[pos+1] << endl;
                }
                pos+=2;
                break;
            default:
                return;
        }

    }
}

void part2(){
    ifstream input("input.txt");
    vector<int> v;
    int x;
    input >> x;
    while(input){
        v.push_back(x);
        input.get();
        input >> x;
    }

    int in=5;
    int pos=0;
    bool cont=true;
    while(cont){
        int com = v[pos];
        int opcode = com%100;
        com/=100;
        int x1,x2,x3;
        switch(opcode){
            case 1:
            case 2:
                if(com%10==0)   x1 = v[ v[pos+1] ];
                else            x1 = v[pos+1];
                com /= 10;
                if(com%10==0)   x2 = v[ v[pos+2] ];
                else            x2 = v[pos+2];
                if(opcode==1){
                    v[ v[pos+3] ] = x1+x2;
                } else {
                    v[ v[pos+3] ] = x1*x2;
                }
                pos += 4;
                break;
            case 3:
               v[v[pos+1]] = in;
               pos+=2;
               break;
            case 4:
                if(com==0){
                    cout << v[ v[pos+1] ] << endl;
                } else {
                    cout << v[pos+1] << endl;
                }
                pos+=2;
                break;
            case 5:
            case 6:
                if(com%10==0)   x1 = v[ v[pos+1] ];
                else            x1 = v[pos+1];
                com /= 10;
                if(com%10==0)   x2 = v[ v[pos+2] ];
                else            x2 = v[pos+2];
                if( (opcode==5&&x1!=0)||(opcode==6&&x1==0) ){
                    pos=x2;
                } else {
                    pos+=3;
                }
                break;
            case 7:
            case 8:
                if(com%10==0)   x1 = v[ v[pos+1] ];
                else            x1 = v[pos+1];
                com /= 10;
                if(com%10==0)   x2 = v[ v[pos+2] ];
                else            x2 = v[pos+2];
                /*
                com /= 10;
                if(com%10==0)   x3 = v[ pos+3] ;
                else            x3 = pos+3;
                */
                if( (opcode==7&&x1<x2) || (opcode==8&&x1==x2) ){
                    v[ v[ pos+3] ] = 1;
                } else {
                    v[ v[ pos+3] ] = 0;
                }
                pos += 4;
                break;
            default:
                return;
        }

    }
}

int main()
{
    part2();
    return 0;
}
