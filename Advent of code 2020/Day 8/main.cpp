#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

enum Operation{acc, jmp, nop};


struct Instruction{
    Operation op;
    int arg;
};

istream& operator>>(istream& input, Instruction& i){
    string s;
    input >> s;
    if(s=="acc"){
        i.op = acc;
    }else if( s=="jmp"){
        i.op = jmp;
    } else {
        i.op = nop;
    }
    char c;
    input.get(c);
    input.get(c);
    input >> i.arg;
    if(c=='-'){
        i.arg *= -1;
    }
}

int main()
{
    ifstream input("input.txt");
    vector<Instruction> v;
    Instruction i;
    input >> i;
    while(input){
        v.push_back(i);
        input >> i;
    }
    int accumulator = 0;
    int command_line = 0;
    unordered_set<int> commands;
    while( commands.count(command_line)==0 ){
        commands.insert(command_line);
        switch( v[command_line].op ){
            case jmp: command_line += v[command_line].arg; break;
            case acc: accumulator += v[command_line].arg;
            case nop: command_line++;
        }
    }
    cout << accumulator << endl;

//part2
    command_line = 0;
    unordered_set<int> commands2;
    vector<int>  indices_jmps_nops;
    while( commands2.count(command_line)==0 ){
        commands2.insert(command_line);
        switch( v[command_line].op ){
            case jmp: command_line += v[command_line].arg; indices_jmps_nops.push_back(command_line); break;
            case acc: accumulator += v[command_line].arg; command_line++; break;
            case nop: command_line++; indices_jmps_nops.push_back(command_line);
        }
    }
    bool answer_found = false;
    int answer;
    for(int i=0; !answer_found&&i<indices_jmps_nops.size(); i++){
        accumulator = 0;
        command_line = 0;
        unordered_set<int> commands3;
        while( command_line<v.size() && commands3.count(command_line)==0  ){
            commands3.insert(command_line);
            if(command_line==indices_jmps_nops[i]){
                switch( v[command_line].op ){
                    case nop: command_line += v[command_line].arg; break;
                    case acc: accumulator += v[command_line].arg;
                    case jmp: command_line++;
                }
            } else {
                switch( v[command_line].op ){
                    case jmp: command_line += v[command_line].arg; break;
                    case acc: accumulator += v[command_line].arg;
                    case nop: command_line++;
                }
            }
        }
        if(command_line==v.size()){
            answer_found=true;
            answer=accumulator;
        }
    }
    cout << accumulator << endl;


    return 0;
}
