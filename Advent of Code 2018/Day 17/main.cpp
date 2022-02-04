#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MIN_X=450;
const int MAX_X=550;
const int MAX_Y=500;

int min_y;

enum Cell{Free, Clay, Spring, Water, Flow };

ostream& operator<<(ostream& out, const Cell& cell){
    char ch;
    switch(cell){
        case Free: ch='.'; break;
        case Clay: ch='#'; break;
        case Spring: ch='+'; break;
        case Water: ch='~'; break;
        case Flow: ch= '|'; break;
    }

    out << ch;
    return out;
}

struct Clay_Line{
    int x;
    int min_y;
    int max_y;
};

istream& operator>>(istream& input, Clay_Line& c){
    input.ignore(100,'=' );
    input>>c.x;
    input.ignore('100', '=');
    input>>c.min_y;
    input.ignore(2);
    input>>c.max_y;
    return input;
}

void print(const vector<vector<Cell>>& board){
    for(int y=0; y<board.size()&&y<=MAX_Y; y++){

        for(int x=MIN_X; x<MAX_X; x++){
            cout << board[y][x];
        }
        cout << endl;
    }
}


vector<vector<Cell>> read_input(string s){
    fstream input(s);
    vector<Clay_Line> vertical_lines;
    vector<Clay_Line> horizontal_lines;
    Clay_Line c;
    int max_x=0;
    int max_y=0;
    min_y=1000000;
    char ch;
    input>>ch;
    input>>c;
    while(input){
        if(ch=='x'){
            vertical_lines.push_back(c);
            max_x = max(max_x,c.x);
            max_y = max(max_y,c.max_y);
            min_y = min(min_y,c.min_y);
        } else {
            horizontal_lines.push_back(c);
            max_x = max(max_x,c.max_y);
            max_y = max(max_y,c.x);
            min_y = min(min_y,c.x);
        }
        input>>ch;
        input>>c;
    }
    vector<vector<Cell>> board;
    for(int y=0; y<=max_y; y++){
        vector<Cell> v;
        for(int x=0; x<=max_x; x++){
            v.push_back(Free);
        }
        board.push_back(v);
    }
    if(max_x<500){
        board[0][max_x/2] = Spring;
    } else {
        board[0][500]=Spring;
    }

    for(Clay_Line cl:vertical_lines){
        for(int y=cl.min_y; y<=cl.max_y; y++){
            board[y][cl.x] = Clay;
        }
    }
    for(Clay_Line cl:horizontal_lines){
        for(int x=cl.min_y; x<=cl.max_y; x++){
            board[cl.x][x] = Clay;
        }
    }
    return board;
}
/*
void check_stream(vector<vector<Cell>>& board, int x, int y){
    while(y+1<board.size()&&board[y+1][x]==Free){
        board[y+1][x]=Flow;
        y++;
    }
    if(y+1==board.size()||board[y+1][x]==Flow){
        return;
    }
    int x_right=x;
    bool Clay_right=false;
    while( (board[y+1][x_right]==Water||board[y+1][x_right]==Clay) && (board[y][x_right+1]==Free||board[y][x_right+1]==Flow) ){
        x_right++;
    }
    if( board[y+1][x_right]==Free ){
        Clay_right=false;
        check_stream(board,x_right,y);
    }
    if(( board[y][x_right+1]==Water||board[y][x_right+1]==Clay )) {
        Clay_right=true;
    }

    int x_left=x;
    bool Clay_left=false;
    while( (board[y+1][x_left]==Water||board[y+1][x_left]==Clay) && (board[y][x_left-1]==Free||board[y][x_left-1]==Flow) ){
        x_left--;
    }
    if( board[y+1][x_left]==Free ){
        Clay_right=false;
        check_stream(board,x_left,y);
    }
    if( (board[y][x_left-1]==Water||board[y][x_left-1]==Clay) ){
        Clay_left=true;
    }
    if(Clay_left&&Clay_right){
        for( int dx=x_left; dx<=x_right; dx++){
            board[y][dx]=Water;
        }
        check_stream(board,x,y-1);
    } else {
        for( int dx=x_left; dx<=x_right; dx++){
            board[y][dx]=Flow;
        }
    }
}*/

void check_stream(vector<vector<Cell>>& board,int x, int y){
    while( y+1<board.size() && board[y+1][x]==Free ){
        board[y+1][x]=Flow;
        y++;
    }
    if( y+1>=board.size()||board[y+1][x]==Flow ){
        return;
    }
    int right=x;
    while( !( board[y][right]==Clay || board[y+1][right]==Flow ||y+1>=board.size() ) ){
        if( board[y+1][right]==Free ){
            check_stream(board,right,y);
        } else {
            right++;
        }
    }

    int left=x;
    while( !( board[y][left]==Clay || board[y+1][left]==Flow ) ){
        if( board[y+1][left]==Free){
            check_stream(board,left,y);
        } else {
            left--;
        }
    }

    if(board[y][left]==Clay&&board[y][right]==Clay){
        for(int a=left+1; a<right; a++){
            board[y][a]=Water;
        }
//        print(board);
        if(board[y-1][x]==Flow){
            check_stream(board,x,y-1);
        }
    } else {
        for(int a=left; a<=right; a++){
            if(board[y][a]!=Clay)board[y][a]=Flow;
        }
    }

}


void part1(){
    vector<vector<Cell>> board = read_input("input.txt");
//    print(board);
    int total=0;
    int total2=0;
    check_stream(board, 500, 0);
    print(board);

    for( int y=min_y; y<board.size(); y++){
        for( int x=0; x<board[0].size(); x++){
            if( board[y][x]==Water || board[y][x]==Flow ){
                total++;
            }
            if( board[y][x]==Water  ){
                total2++;
            }
        }
    }

    cout << "Part1: " << total << endl;
    cout << "Part2: " << total2 << endl;

}

int main()
{
    part1();
    return 0;
}
