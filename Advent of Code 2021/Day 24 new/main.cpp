#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Reg{
    long long val[4];
};

struct Command{
    string instruction;
    long long reg1;
    bool use_reg;
    long long value;
};

ostream& operator<<(ostream& out, const Command& com ){
    out << com.instruction << " " << static_cast<char>('w'+com.reg1) << " ";
    if(com.instruction!="inp"){
        if(com.use_reg){
            out << static_cast<char>('w'+com.value);
        } else {
            out << com.value;
        }
    }
    return out;
}


Command string_to_command(string s){
    stringstream ss(s);
    Command com;
    ss >> com.instruction;
    char c;
    ss >> c;
    com.reg1 = c-'w';
    if(com.instruction!="inp"){
        ss.ignore(1);
        char c2 = ss.peek();
        if(c2=='w'||c2=='x'||c2=='y'||c2=='z'){
            com.use_reg=true;
            com.value = c2- 'w';
        } else {
            com.use_reg=false;
            ss >> com.value;
        }
    }
    return com;
}

void read_input(string name, vector<vector<Command>>& commands){
    commands.clear();
    string s;
    vector<Command> v;
    ifstream input(name);
    getline(input, s);
    v.push_back(string_to_command(s));
    getline(input,s);
    while(input){
        Command c = string_to_command(s);
        if(c.instruction=="inp"){
            commands.push_back(v);
            v.clear();
        }
        v.push_back(c);
        getline(input,s);
    }
    commands.push_back(v);
}

Reg calc_new_register(const vector<Command>& coms, long long in, Reg reg ){
    for(Command com:coms){
        if(com.instruction=="inp"){
            reg.val[com.reg1] = in;
            continue;
        }
        long long value;
        if(com.use_reg){
            value = reg.val[com.value];
        } else {
            value = com.value;
        }
        if(com.instruction=="add"){
            reg.val[com.reg1] = reg.val[com.reg1]+value;
        } else if(com.instruction=="mul"){
            reg.val[com.reg1] = reg.val[com.reg1]*value;
        } else if(com.instruction=="div"){
            reg.val[com.reg1] = reg.val[com.reg1]/value;
        } else if(com.instruction=="mod"){
            reg.val[com.reg1] = reg.val[com.reg1]%value;
        } else if(com.instruction=="eql"){
            reg.val[com.reg1] = reg.val[com.reg1]==value;
        }
    }

    return reg;
}

void calc_registers(const vector<long long>& number_v,vector<Reg>& regs,int index, const vector<vector<Command>>& comss){
    while(index<14){
        if(index==0){
            regs[0] = calc_new_register(comss[0], number_v[0],{0,0,0,0});
        } else {
            regs[index] = calc_new_register(comss[index], number_v[index], regs[index-1]);
        }
        index++;
    }
}

void part1(){
    vector<vector<Command>> comss;
    read_input("input.txt", comss);
//    for(auto w:v){
//        for(auto x:w)
//            cout << x << endl;
//        cout << endl;
//    }

    vector<long long> number_v(14);
    vector<Reg> regs(14);
    fill(number_v.begin(), number_v.end(), 9);
    calc_registers(number_v, regs, 0, comss);
    while(regs[13].val[3]!=0){
        int index = 13;
        while(number_v[index]==1){
            number_v[index]=9;
            index--;
        }
        number_v[index]--;
        calc_registers(number_v, regs, index, comss);
    }

    cout << "Part1: ";
    for(int i=0;i<14;i++){
        cout << number_v[i];
    }
    cout << endl;

}

void testing(){
    vector<vector<Command>> comss;
    read_input("input.txt", comss);
    for(int in=1;in<=9; in++){
        Reg r = calc_new_register(comss[0],in,{0,0,0,0});
        printf("%d: w:%d, x:%d, y:%d, z:%d\n",in,r.val[0],r.val[1],r.val[2],r.val[3]);
    }
}


int main()
{
    part1();
    return 0;
}
