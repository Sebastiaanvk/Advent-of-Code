#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

const int FIELD_SIZE=200;


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

class Hull{
    public:
    bool hull_squares[FIELD_SIZE][FIELD_SIZE] ={ {false} };
    Loc location;
    Loc direction;
    bool paint_now;

    Hull(){
        location = {FIELD_SIZE/2,FIELD_SIZE/2};
        direction = {0,-1};
        paint_now=true;
        hull_squares[location.y][location.x] = true;
    }
    ~Hull(){

    }

    int give_input_to_computer(){
        return hull_squares[location.y][location.x];
    }

    void get_output_from_computer(bool b){
        if(paint_now){
            hull_squares[location.y][location.x] = b;

        } else {
            int help = direction.y;
            if(b){
                direction.y=direction.x;
                direction.x=(-1)*help;
            } else {
                direction.y=(-1)*direction.x;
                direction.x=help;
            }
            location.x += direction.x;
            location.y += direction.y;
        }

        paint_now = !paint_now;
    }

    void end_hull(){
        int middle_x = FIELD_SIZE/2;
        int middle_y = FIELD_SIZE/2;
        for(int y=-20; y<20; y++){
            for(int x=-20; x<60; x++){
                if(hull_squares[y+middle_y][x+middle_x]) cout << "#";
                else                    cout << " ";
            }
            cout << endl;
        }
    }
};



void run_computer(vector<long long> v){
    Hull hull;

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
            v[adr[0]] = hull.give_input_to_computer();
            pos+=2;
        } else if(opcode==4){
            hull.get_output_from_computer( v[adr[0]] );
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
            hull.end_hull();
            cout << "done\n";
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
