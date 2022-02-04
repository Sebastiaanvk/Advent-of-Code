#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int output_program(vector<int> v, int input1, int input2){
    int pos=0;
    bool cont=true;
    bool first_input_had=false;
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
                if(!first_input_had){
                    v[v[pos+1]] = input1;
                    first_input_had=true;
                } else {
                    v[v[pos+1]] = input2;
                }
                pos+=2;
                break;
            case 4:
                if(com==0){
                    return v[ v[pos+1] ];
                } else {
                    return v[pos+1];
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
                if( (opcode==7&&x1<x2) || (opcode==8&&x1==x2) ){
                    v[ v[ pos+3] ] = 1;
                } else {
                    v[ v[ pos+3] ] = 0;
                }
                pos += 4;
                break;
            default:
                return -1;
        }

    }

}

void part1(){
    ifstream input("input.txt");
    int x;
    vector<int> program;
    input >> x;
    while(input){
        program.push_back(x);
        input.get();
        input >> x;
    }

    int max_out = 0;
    int ints[] = {0,1,2,3,4};
    do{
        int out1 = output_program(program, ints[0], 0);
        int out2 = output_program(program, ints[1], out1);
        int out3 = output_program(program, ints[2], out2);
        int out4 = output_program(program, ints[3], out3);
        int out5 = output_program(program, ints[4], out4);
        if(out5>max_out) max_out=out5;


    } while (next_permutation(ints,ints+5));

    cout << max_out << endl;

}

bool run_program(vector<int>& v, int& pos, bool& first_input_had, int input1, int input2, int& out){
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
                if(!first_input_had){
                    v[v[pos+1]] = input1;
                    first_input_had=true;
                } else {
                    v[v[pos+1]] = input2;
                }
                pos+=2;
                break;
            case 4:
                if(com==0){
                    out =  v[ v[pos+1] ];
                } else {
                    out = v[pos+1];
                }
                pos+=2;
                return true;
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
                if( (opcode==7&&x1<x2) || (opcode==8&&x1==x2) ){
                    v[ v[ pos+3] ] = 1;
                } else {
                    v[ v[ pos+3] ] = 0;
                }
                pos += 4;
                break;
            default:
                return false;
        }

    }

}

void part2(){
    ifstream input("input.txt");
    int x;
    vector<int> program;
    input >> x;
    while(input){
        program.push_back(x);
        input.get();
        input >> x;
    }

    int max_out = 0;
    int ints[] = {5,6,7,8,9};
    do{
        vector<int> program1 = program;
        vector<int> program2 = program;
        vector<int> program3 = program;
        vector<int> program4 = program;
        vector<int> program5 = program;

        int pos1 = 0;
        int pos2 = 0;
        int pos3 = 0;
        int pos4 = 0;
        int pos5 = 0;

        bool first_input_had1=false;
        bool first_input_had2=false;
        bool first_input_had3=false;
        bool first_input_had4=false;
        bool first_input_had5=false;

        bool cont = true;

        int out1;
        int out2;
        int out3;
        int out4;
        int out5 = 0;
        cont = run_program(program1,pos1,first_input_had1, ints[0], out5, out1);
        while(cont){
            run_program(program2,pos2,first_input_had2, ints[1], out1, out2);
            run_program(program3,pos3,first_input_had3, ints[2], out2, out3);
            run_program(program4,pos4,first_input_had4, ints[3], out3, out4);
            run_program(program5,pos5,first_input_had5, ints[4], out4, out5);
            cont = run_program(program1,pos1,first_input_had1, ints[0], out5, out1);
        }

        if(out5>max_out) max_out=out5;


    } while (next_permutation(ints,ints+5));

    cout << max_out << endl;

}

int main()
{
    part2();
    return 0;
}
