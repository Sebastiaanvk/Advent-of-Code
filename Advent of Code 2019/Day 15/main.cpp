#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const bool PART2 = false;

const int MAX_X = 70;
const int MAX_Y = 80;

enum Dir{north=1,south,west,east};


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

void run_computer(vector<long long>& v){
    int pos = 0;
    int x=MAX_X/2;
    int y=MAX_Y/2;
    Dir dir;
    char board[MAX_Y][MAX_X];
    fill_board(board);
    board[y][x] = 'S';
    int oxygen_x,oxygen_y;
    long long rel_base=0;
    int max_nr_steps = 10000000;
    int nr_steps=0;
    srand(606060);
    while(nr_steps<max_nr_steps){
        long long command = v[pos];
        int opcode = command%100;
        //cout << opcode << endl;
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

            int in;
            if(nr_steps>max_nr_steps){
                print_board(board);
                cout << "Enter direction: (north=1,south=2,west=3,east=4)";
                cin >> in;
                while(in!=1&&in!=2&&in!=3&&in!=4){
                    cout << "Try again: (north=1,south=2,west=3,east=4)";
                    cin >> in;
                }
            }
            else {
                int new_x,new_y;
                do{
                    in = (rand() %4)+1;
                    dir = static_cast<Dir>(in);
                    new_x=x;
                    new_y=y;
                    switch(dir){
                        case north:new_y--; break;
                        case south:new_y++; break;
                        case east: new_x++; break;
                        case west: new_x--; break;
                    }
                }while( board[new_y][new_x]=='#' );
                nr_steps++;
            }
            v[adr[0]]=in;

            pos+=2;
        } else if(opcode==4){
            int output = v[adr[0]];
            int new_x=x;
            int new_y=y;
            switch(dir){
                case north:new_y--; break;
                case south:new_y++; break;
                case east: new_x++; break;
                case west: new_x--; break;
            }
            if(output==0){
                board[new_y][new_x]='#';
            } else if(output==1){
                if(board[y][x]=='D')board[y][x] = '.';
                if(board[new_y][new_x]!='S')board[new_y][new_x] = 'D';
                x=new_x;
                y=new_y;
            } else{
                if(board[y][x]=='D')board[y][x] = '.';
                board[new_y][new_x] = 'O';
                oxygen_x=new_x;
                oxygen_y=new_y;
                x=new_x;
                y=new_y;
            }
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
    print_board(board);
    int steps_to_reach[MAX_Y][MAX_X] = {{0}};
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
    input.close();
    run_computer(v);

}

int main()
{
    part1();
    return 0;
}
