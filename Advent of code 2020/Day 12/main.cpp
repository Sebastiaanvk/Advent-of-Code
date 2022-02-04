#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Operation{North,South,East,West,Left,Right,Forward};

struct Instruction{
    Operation op;
    int arg;
};

vector<Instruction> read_input(){
    ifstream input("input.txt");
    vector<Instruction> insts;

    char c;
    int arg;
    Operation op;
    input.get(c);
    while(input){
        input>>arg;
        switch(c){
            case 'N': op=North; break;
            case 'S': op=South; break;
            case 'E': op=East; break;
            case 'W': op=West; break;
            case 'L': op=Left; break;
            case 'R': op=Right; break;
            case 'F': op=Forward; break;
        }
        insts.push_back({op,arg});
        input.get(c);
        input.get(c);
    }
    return insts;
}

void turn(int& dx, int& dy, Instruction& inst){
    if(inst.arg==180){
        dx *= -1;
        dy *= -1;
    } else if( (inst.op==Left&&inst.arg==90) || (inst.op==Right && inst.arg==270 ) ){
        int help = dy;
        dy = dx;
        dx = -1*help;
    } else {
        int help = dx;
        dx = dy;
        dy = -1*help;
    }
}

void part_one(vector<Instruction>& insts){
    int x = 0;
    int y = 0;
    int dx=1;
    int dy=0;
//    printf("x:%d,y:%d\n",x,y);

    for(auto inst: insts){
        switch(inst.op){
            case North:     y+=inst.arg;        break;
            case South:     y-=inst.arg;        break;
            case East:      x+=inst.arg;        break;
            case West:      x-=inst.arg;        break;
            case Left: case Right:  turn(dx, dy, inst); break;
            case Forward:   x+=dx*inst.arg; y+=dy*inst.arg; break;
        }
//        printf("x:%d,y:%d,dx:%d,dy:%d\n",x,y,dx,dy);
    }
    cout << "The answer to part one is: " << abs(x)+abs(y) << endl;
}

void turn_waypoint(int& waypoint_x, int& waypoint_y, Instruction inst){
    if(inst.arg==180){
        waypoint_x *= -1;
        waypoint_y *= -1;
    } else if( (inst.op==Left&&inst.arg==90) || (inst.op==Right && inst.arg==270 ) ){
        int help = waypoint_y;
        waypoint_y = waypoint_x;
        waypoint_x = -1*help;
    } else {
        int help = waypoint_x;
        waypoint_x = waypoint_y;
        waypoint_y = -1*help;
    }
}

void part_two(vector<Instruction>& insts){
    int x = 0;
    int y = 0;
    int waypoint_x=10;
    int waypoint_y=1;
//    printf("x:%d,y:%d\n",x,y);

    for(auto inst: insts){
        switch(inst.op){
            case North:     waypoint_y+=inst.arg;        break;
            case South:     waypoint_y-=inst.arg;        break;
            case East:      waypoint_x+=inst.arg;        break;
            case West:      waypoint_x-=inst.arg;        break;
            case Left: case Right:  turn_waypoint(waypoint_x, waypoint_y, inst); break;
            case Forward:   x+=waypoint_x*inst.arg; y+=waypoint_y*inst.arg; break;
        }
//        printf("x:%d,y:%d,dx:%d,dy:%d\n",x,y,dx,dy);
    }
    cout << "The answer to part two is: " << abs(x)+abs(y) << endl;
}

int main()
{
    vector<Instruction> instructions = read_input();
    part_one(instructions);
    part_two(instructions);
    return 0;
}
