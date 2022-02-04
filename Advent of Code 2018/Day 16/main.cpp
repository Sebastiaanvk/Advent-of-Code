#include <iostream>
#include <fstream>

using namespace std;

enum Opcode{addr,addi,mulr,muli,banr,bani,borr,bori,setr,seti,gtir,gtri,gtrr,eqir,eqri,eqrr,NR_OF_COM};

struct Command{
    int opcode_nr;
    int A;
    int B;
    int C;
};
typedef int Regs [4];

ifstream& operator>>(ifstream& input, Command& com){
    input>>com.opcode_nr>>com.A>>com.B>>com.C;
    return input;
}

ifstream& operator>>(ifstream& input, Regs regs){
    input.ignore(100,'[');
    char c;
    input>>regs[0]>>c>>regs[1]>>c>>regs[2]>>c>>regs[3]>>c;
    return input;
}

bool regs_equal(const Regs r1, const Regs r2){
    for(int i=0; i<4; i++){
        if( r1[i]!=r2[i] ){
            return false;
        }
    }
    return true;
}

void run_command(const Opcode& op,const int& A, const int& B, const int& C, int reg[4] ){
    switch(op){
        case addr: reg[C]=reg[A]+reg[B];    break;
        case addi: reg[C]=reg[A]+B;         break;
        case mulr: reg[C]=reg[A]*reg[B];    break;
        case muli: reg[C]=reg[A]*B;         break;
        case banr: reg[C]=reg[A]&reg[B];    break;
        case bani: reg[C]=reg[A]&B;         break;
        case borr: reg[C]=reg[A]|reg[B];    break;
        case bori: reg[C]=reg[A]|B;         break;
        case setr: reg[C]=reg[A];           break;
        case seti: reg[C]=A;                break;
        case gtir: reg[C]=A>reg[B];         break;
        case gtri: reg[C]=reg[A]>B;         break;
        case gtrr: reg[C]=reg[A]>reg[B];    break;
        case eqir: reg[C]=A==reg[B];        break;
        case eqri: reg[C]=reg[A]==B;        break;
        case eqrr: reg[C]=reg[A]==reg[B];   break;
        default: cout << "Error!\n";
    }
}

void read_next_change(ifstream& input, Regs in,Command& com, Regs out){
    input>>in>>com>>out;
    input.ignore(2);
}


bool three_possibilities(const Regs in, const Command& com, const Regs out){
    int pos=0;
    Regs reg;
    for(int i=0; i<Opcode::NR_OF_COM; i++){
        for( int j=0;j<4;j++) reg[j]=in[j];
        run_command(static_cast<Opcode>(i),com.A,com.B,com.C,reg);
        if( regs_equal(reg,out) ){
            pos++;
        }

    }
    return pos>=3;
}


void part1(){
    ifstream input("input.txt");
    int total=0;
    while(input.peek()=='B'){
        Regs in;
        Command com;
        Regs out;
        read_next_change(input, in, com, out);
        if( three_possibilities(in,com,out) ){
            total++;
        }

    }
    cout << "part1: " << total << endl;
}

void check_possibilities(const Regs in, const Command& com, const Regs out, bool possible[16][16]){
    Regs reg;
    for(int i=0; i<Opcode::NR_OF_COM; i++){
        for( int j=0;j<4;j++) reg[j]=in[j];
        run_command(static_cast<Opcode>(i),com.A,com.B,com.C,reg);
        if( !regs_equal(reg,out) ){
            possible[com.opcode_nr][i]=false;
        }
    }
}

bool only_one(bool possibilities [16][16], const int& input_code, int& opcode){
    bool found = false;
    for( int i=0; i<16; i++){
        if(possibilities[input_code][i]){
            if(found) return false;
            opcode=i;
            found=true;
        }
    }
    return found;
}

void part2(){
    ifstream input("input.txt");
    int total=0;
    bool possible[16][16];
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++) possible[i][j]=true;}
    while(input.peek()=='B'){
        Regs in;
        Command com;
        Regs out;
        read_next_change(input, in, com, out);
        check_possibilities(in, com, out, possible);
    }
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++) cout << possible[i][j];
        cout << endl;
        }

    int input_to_opcode[16];
    bool input_found[16]={false};
    int found=0;
    while(found<16){
        int input_code;
        int opcode;
        input_code=0;
        while( !( !input_found[input_code]&&only_one(possible, input_code, opcode) ) ){
            input_code++;
        }
        input_to_opcode[input_code]= opcode;
        input_found[input_code];
        for( int i=0; i<16; i++) possible[i][opcode]=false;
        found++;
        /*
        cout << endl;
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++) cout << possible[i][j];
            cout << endl;
        }*/

    }
    for( int i=0; i<16; i++) cout << i <<": " << input_to_opcode[i] << endl;

    Regs regs = {0,0,0,0};
    Command com;
    input>>com;
    while(input){
        run_command(static_cast<Opcode>(input_to_opcode[com.opcode_nr]),com.A,com.B,com.C,regs);
        input>>com;
    }
    cout << "Part2: " << regs[0] << endl;

}

int main()
{
    part2();
    return 0;
}
