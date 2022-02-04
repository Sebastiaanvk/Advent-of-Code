#include <iostream>
#include <fstream>

using namespace std;

void read_input1(bool state [15] [22] [22]){
    char c;
    ifstream input("input.txt");
    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
            input >> c;
            state [7][7+row][7+col] = c=='#';
        }
    }
}

int count_active(bool state [15] [22] [22], int& depth, int& row, int& col){
    int sum=0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            for(int k=-1;k<2;k++){
                if( state[depth+i][row+j][col+k] ){
                    sum++;
                }
            }
        }
    }
    if(state[depth][row][col]) sum--;
    return sum;
}

void next_state(bool state [15][22][22], int count_state [15][22][22] ){
    for(int d=1; d<=13;d++){
        for(int r=1; r<=20; r++){
            for(int c=1; c<=20; c++){
                count_state[d][r][c] = count_active(state, d, r, c);
            }
        }
    }
    for(int d=1; d<=13;d++){
        for(int r=1; r<=20; r++){
            for(int c=1; c<=20; c++){
                state[d][r][c] = (count_state[d][r][c]==3)||(state[d][r][c]&&count_state[d][r][c]==2);
            }
        }
    }
}

void print_state(bool state [15][22][22], int steps){

}

void part1(){
    bool state [15][22][22] = {false};
    read_input1(state);
    int count_state[15][22][22];
    for(int i=0; i<6; i++){
        next_state(state, count_state);
    }

    int sum=0;
    for(int d=1; d<=13;d++){
        for(int r=1; r<=20; r++){
            for(int c=1; c<=20; c++){
                if(state[d][r][c]) sum++;
            }
        }
    }
    cout << "part1: " << sum << endl;

}

void read_input2(bool state [15] [15] [22] [22]){
    char c;
    ifstream input("input.txt");
    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
            input >> c;
            state [7][7][7+row][7+col] = c=='#';
        }
    }
}

int count_active2(bool state [15] [15] [22] [22],int& hyperdepth, int& depth, int& row, int& col){
    int sum=0;
    for(int h=-1;h<=1;h++ ){
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                for(int k=-1;k<2;k++){
                    if( state[hyperdepth+h][depth+i][row+j][col+k] ){
                        sum++;
                    }
                }
            }
        }
    }
    if(state[hyperdepth][depth][row][col]) sum--;
    return sum;
}

void next_state2(bool state [15][15][22][22], int count_state [15][15][22][22] ){
    for(int h=1; h<=13; h++){
        for(int d=1; d<=13;d++){
            for(int r=1; r<=20; r++){
                for(int c=1; c<=20; c++){
                    count_state[h][d][r][c] = count_active2(state, h, d, r, c);
                }
            }
        }
    }
    for(int h=1; h<=13; h++){
        for(int d=1; d<=13;d++){
            for(int r=1; r<=20; r++){
                for(int c=1; c<=20; c++){
                    state[h][d][r][c] = (count_state[h][d][r][c]==3)||(state[h][d][r][c]&&count_state[h][d][r][c]==2);
                }
            }
        }
    }
}


void part2(){
    bool state [15][15][22][22] = {false};
    read_input2(state);
    int count_state[15][15][22][22];
    for(int i=0; i<6; i++){
        next_state2(state, count_state);
    }

    int sum=0;
    for(int h=1; h<=13; h++){
        for(int d=1; d<=13;d++){
            for(int r=1; r<=20; r++){
                for(int c=1; c<=20; c++){
                    if(state[h][d][r][c]) sum++;
                }
            }
        }
    }
    cout << "part2: " << sum << endl;

}

int main()
{
    part1();
    part2();
    return 0;
}
