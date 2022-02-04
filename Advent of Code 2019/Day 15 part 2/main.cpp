#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const bool PART2 = true;


const int MAX_X = 50;
const int MAX_Y = 45;


pair<int,int> Dirs[5] = { {0,0},{-1,0},{1,0},{0,-1},{0,1} };

void print_board(char board[MAX_Y][MAX_X]){
    for(int y=0; y<MAX_Y; y++){
        for(int x=0; x<MAX_X;x++)
            cout << board[y][x];
        cout << endl;
    }
    cout << endl;
}

void fill_board(char board[MAX_Y][MAX_X]){
    for(int y=0;y<MAX_Y;y++)
        for(int x=0; x<MAX_X; x++)
            board[y][x] = ' ';
}

struct Computer{
    vector<int> data;
    int pos;
    int rel_base;
};

int computer_until_output(Computer& c, int in){
    while(true){
        int command = c.data[c.pos];
        int opcode = command%100;
        command/=100;
        int adr[3];
        for(int i=0;i<3&&c.pos+1+i<c.data.size();i++){
            if( command%10==0 ){
                adr[i] = c.data[c.pos+1+i];
            }else if(command%10==1){
                adr[i] = c.pos+1+i;
            } else if(command%10==2){
                adr[i] = c.rel_base+c.data[c.pos+1+i];
            }
            command /= 10;
        }
        if(opcode==1){
            c.data[adr[2]]=c.data[adr[0]]+c.data[adr[1]];
            c.pos+=4;
        } else if(opcode==2){
            c.data[adr[2]]=c.data[adr[0]]*c.data[adr[1]];
            c.pos+=4;
        } else if(opcode==3){
            c.data[adr[0]]=in;
            c.pos+=2;
        } else if(opcode==4){
            int out = c.data[adr[0]];
            c.pos+=2;
            return out;
        } else if(opcode==5){
            if(c.data[adr[0]]!=0){
                c.pos = c.data[ adr[1] ];
            } else {
                c.pos+=3;
            }
        } else if(opcode==6){
            if(c.data[ adr[0] ]==0){
                c.pos = c.data[ adr[1] ];
            } else {
                c.pos+=3;
            }
        } else if(opcode==7){
            if( c.data[ adr[0] ]<c.data[adr[1]] ){
                c.data[adr[2]] = 1;
            } else {
                c.data[adr[2]] = 0;
            }
            c.pos+=4;
        } else if(opcode==8){
            if( c.data[ adr[0] ]==c.data[adr[1]] ){
                c.data[adr[2]] = 1;
            } else {
                c.data[adr[2]] = 0;
            }
            c.pos+=4;
        } else if(opcode==9){
            c.rel_base += c.data[adr[0]];
            c.pos+=2;
        } else {
            return -1;
        }
    }
}

void explore_square(int y, int x, char board[MAX_Y][MAX_X], Computer& comp){
    for( int d=1; d<=4; d++){
        int new_y = y + Dirs[d].first;
        int new_x = x + Dirs[d].second;
        if(board[new_y][new_x]==' '){
            int out = computer_until_output(comp,d);
            if(out==0){
                board[new_y][new_x] = '#';
            } else {
                if(out==1) board[new_y][new_x] = '.';
                else board[new_y][new_x] = 'O';

                explore_square(new_y,new_x, board, comp);
                int back_d;
                if(d==1||d==3) back_d = d+1;
                else            back_d = d-1;
                computer_until_output(comp,back_d);
            }
        }
    }
}

void explore_board(char board[MAX_Y][MAX_X]){
    ifstream input("input.txt");
    Computer comp;
    comp.data.clear();
    int x;
    input >> x;
    while(input){
        comp.data.push_back(x);
        input.get();
        input >> x;
    }
    comp.pos = 0;
    comp.rel_base = 0;
    input.close();

    fill_board(board);

    explore_square(MAX_Y/2, MAX_X/2, board, comp);

    print_board(board);
}

void find_oxygen(char board[MAX_Y][MAX_X],int& oxygen_y, int& oxygen_x){
    for(int y=0; y<MAX_Y; y++)
        for(int x=0; x<MAX_X; x++){
            if(board[y][x]=='O'){
                oxygen_y=y;
                oxygen_x=x;
            }
        }
    return;
}

void calc_max_steps(char board[MAX_Y][MAX_X]){
    int steps_to_reach[MAX_Y][MAX_X] = {{0}};
    int oxygen_y, oxygen_x;
    find_oxygen(board, oxygen_y, oxygen_x);
    queue< pair<int,int> > que;
    if(!PART2){
        steps_to_reach[MAX_Y/2][MAX_X/2] = 1;
        que.push({MAX_Y/2,MAX_X/2});
    } else {
        steps_to_reach[oxygen_y][oxygen_x] = 1;
        que.push({oxygen_y,oxygen_x});
    }
    int max_steps = 0;
    while(!que.empty()){
        pair<int,int> loc = que.front();

        que.pop();
        int y_pos= loc.first;
        int x_pos = loc.second;
        max_steps = max(steps_to_reach[y_pos][x_pos]-1,max_steps);
        if(!PART2&&board[y_pos][x_pos]== 'O'){
            cout << "part1: " << steps_to_reach[y_pos][x_pos]-1 << endl;
            return;
        }

        if(board[y_pos-1][x_pos]!='#'&&steps_to_reach[y_pos-1][x_pos]==0){
            steps_to_reach[y_pos-1][x_pos] = steps_to_reach[y_pos][x_pos]+1;
            que.push({y_pos-1,x_pos});
        }

        if(board[y_pos+1][x_pos]!='#'&&steps_to_reach[y_pos+1][x_pos]==0){
            steps_to_reach[y_pos+1][x_pos] = steps_to_reach[y_pos][x_pos]+1;
            que.push({y_pos+1,x_pos});
        }

        if(board[y_pos][x_pos-1]!='#'&&steps_to_reach[y_pos][x_pos-1]==0){
            steps_to_reach[y_pos][x_pos-1] = steps_to_reach[y_pos][x_pos]+1;
            que.push({y_pos,x_pos-1});
        }

        if(board[y_pos][x_pos+1]!='#'&&steps_to_reach[y_pos][x_pos+1]==0){
            steps_to_reach[y_pos][x_pos+1] = steps_to_reach[y_pos][x_pos]+1;
            que.push({y_pos,x_pos+1});
        }
    }
    cout << "Part2: " << max_steps << endl;
}

void part2(){
    char board[MAX_Y][MAX_X];
    explore_board(board);
    calc_max_steps(board);
}

int main()
{
    part2();
    return 0;
}
