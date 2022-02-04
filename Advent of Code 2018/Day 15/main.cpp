#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const string FN = "input.txt";
int elf_attack=3;
bool is_part2=false;

const int MAX_HP=200;
const char G = 'G';
const char E = 'E';
const char H = '#';
const char D = '.';

int dx [4] = {0,-1,1,0};
int dy [4] = {-1,0,0,1};

enum Race{Elf, Gob};

struct Unit {
    int x;
    int y;
    Race race;
    int hp;
};

bool operator<(const Unit& u1, const Unit& u2){
    if(u1.hp<=0) return false;
    if(u2.hp<=0) return true;
    if(u1.y==u2.y){
        return u1.x<u2.x;
    }
    return u1.y<u2.y;
}

bool operator==(const Unit& u1, const Unit& u2){
    return (u1.hp<=0)==(u2.hp<=0)&&u1.x==u2.x&&u1.y==u2.y;
}

vector<string> board;
int y_size;
int x_size;
vector<Unit> units;

read_input(){
    cout << "test\n";
    ifstream input(FN);
    board.clear();
    string s;
    input >> s;
    while(input){
        board.push_back(s);
        input >> s;
    }
    y_size=board.size();
    x_size=board[0].size();
    units.clear();
    for(int y=0; y<y_size;y++){
        for(int x=0; x<x_size;x++){
            if(board[y][x]==G){
                units.push_back({x,y,Gob,MAX_HP});
            } else if(board[y][x]==E){
                units.push_back({x,y,Elf,MAX_HP});
            }
        }
    }
    sort(units.begin(),units.end());
    input.close();
}

bool two_races(){
    bool elfs=false;
    bool goblins=false;
    for( int i=0; i<units.size(); i++){
        if(units[i].hp>0){
            switch( units[i].race){
                case Elf: elfs=true; break;
                case Gob: goblins=true; break;
            }
            if(elfs&&goblins) return true;
        }
    }
    return false;
}

char enemy_char(const Unit& u){
    if(u.race==Gob){
        return 'E';
    }
    return 'G';
}

int index_unit_coordinates(const int& x, const int& y){
    int i=0;
    while( !(units[i].x==x&&units[i].y==y&&units[i].hp>0) ){
        i++;
    }
    return i;
}

void damage_unit(Unit& u){
    if(u.race==Gob){
        u.hp-=elf_attack;
    } else {
        u.hp-=3;
    }
    if(u.hp<=0){
        board[u.y][u.x]='.';
    }
}

bool next_to_enemy_attack(Unit& u){
    int min_hp=2*MAX_HP;
    int enemy_index = -1;
    char enemy = enemy_char(u);
    int y = u.y;
    int x = u.x;
    for(int i=0; i<4; i++){
        if( board[y+dy[i]][x+dx[i]]==enemy ){
            int index_enemy = index_unit_coordinates(x+dx[i],y+dy[i]);
            if( units[index_enemy].hp<min_hp ){
                enemy_index=index_enemy;
                min_hp = units[index_enemy].hp;
            }
        }
    }
    if(enemy_index==-1){
        return false;
    }
    damage_unit(units[enemy_index]);
    return true;
}

char unit_char(Unit& u){
    switch(u.race){
        case Gob:   return 'G';
        default:    return 'E';
    }
}
void print_steps(int* steps_board){
    for( int y=0;y<y_size;y++){
        for(int x=0; x<x_size;x++){
            cout << steps_board[y*x_size+x];
        }
        cout << endl;
    }
    cout << endl;
}

bool coords_smaller(const int& x1, const int& y1, const int& x2, const int& y2){
    if(y1==y2) return x1<x2;
    return y1<y2;
}

int steps_to_enemy(const int& x, const int& y, const char& enemy, int& x_enemy, int& y_enemy){
    if( board[y][x]!='.' ) return -1;
    int steps_board[y_size][x_size] = {0};
    steps_board[y][x]=1;
    vector<int> explored_x = {x};
    vector<int> explored_y = {y};
    int i = 0;
    int steps=1;
    bool enemy_found = false;
    while(!enemy_found && i<explored_x.size()){
//        print_steps( *steps_board );
        while(i<explored_x.size()&&steps_board[ explored_y[i] ][ explored_x[i] ]==steps){
//            cout << "x:" << explored_x[i] << endl;
//            cout << "y:" << explored_y[i] << endl << endl;
            for(int dir=0;dir<4;dir++){
                int y_new=explored_y[i]+dy[dir];
                int x_new=explored_x[i]+dx[dir];
//                cout << "x:" << x_new << endl;
//                cout << "y:" << y_new << endl << endl;
                if(board[ y_new ][ x_new ]==enemy){
//                    print_steps(*steps_board);
                    steps_board[y_new][x_new] = steps+1;
                    enemy_found = true;
                }
                if( board[ y_new ][x_new]=='.' && steps_board[y_new][x_new]==0){
                    steps_board[y_new][x_new]=steps+1;
                    explored_y.push_back(y_new);
                    explored_x.push_back(x_new);
                }
            }
            i++;
        }
        steps++;
    }
    if(!enemy_found) return -1;
    for(int y_new=0; y_new<y_size; y_new++){
        for( int x_new=0; x_new<x_size; x_new++){
            if(board[y_new][x_new]==enemy&&steps_board[y_new][x_new]==steps){
                y_enemy=y_new;
                x_enemy=x_new;
                return steps;
            }
        }
    }
}

void unit_action( Unit& u){
    if(u.hp<=0){
        return;
    }
    if( next_to_enemy_attack(u) ){
        return;
    }
    char enemy = enemy_char(u);
    int min_steps=1000000;
    int best_dir=-1;
    int enemy_x;
    int enemy_y;
    for( int dir=0; dir<4; dir++){
        int x_holder;
        int y_holder;
        int s = steps_to_enemy(u.x+dx[dir],u.y+dy[dir],enemy,x_holder, y_holder);
        if( s!=-1 && (s<min_steps ||(s==min_steps && coords_smaller(x_holder,y_holder,enemy_x,enemy_y)) ) ){
            min_steps=s;
            enemy_x = x_holder;
            enemy_y = y_holder;
            best_dir=dir;
        }
    }
    if( best_dir==-1){
        return;
    }
    board[u.y][u.x]='.';
    u.x+=dx[best_dir];
    u.y+=dy[best_dir];
    board[u.y][u.x]=unit_char(u);

    next_to_enemy_attack(u);
}

void remove_dead(){
    for(int i=units.size()-1; i>=0&&units[i].hp<=0; i--){
        units.pop_back();
    }
}

void print_board(){
    for(int y=0; y<y_size; y++){
        cout << board[y] << endl;
    }
    for(Unit u:units){
        cout << u.x << "," << u.y << "hp: " << u.hp << endl;
    }

}

bool print = true;

bool part1(){
    read_input();
    int round = 0;
    int number_of_elfs=0;
    for( int i=0; i<units.size(); i++){
        if(units[i].race==Elf){
            number_of_elfs++;
        }
    }

    while( two_races() ){

        if(print) {
            cout << "After "<< round << " rounds:"<< endl;
            print_board();
        }

        bool full_round = true;
        for(int i=0; i<units.size(); i++){
            if( !two_races() ) full_round=false;
            unit_action( units[i] );
        }

        if(full_round){
            round++;
        }

        sort( units.begin(), units.end() );
        remove_dead();
    }
    if(print) {
        cout << "After "<< round << " rounds:"<< endl;
        print_board();
    }

    int total_hp=0;
    for(Unit u: units){
 //       cout << u.hp << endl;
        total_hp += u.hp;
    }
    cout << "part1: " << total_hp*(round) << endl;
    int elfs_remaining=0;
    for(int i=0; i<units.size(); i++){
        if(units[i].race==Elf){
            elfs_remaining++;
        }
    }
    return elfs_remaining==number_of_elfs;
}



void part2(){
    print=false;
    for( elf_attack=3; true; elf_attack++){
        cout << "Elf attack: " << elf_attack << endl;
        if( part1() ){
            return;
        }
        cout << endl;
    }
}

int main()
{
    part2();
//    read_input();
//    cout << steps_to_enemy( 3,5,'E' ) << endl;
    return 0;
}
