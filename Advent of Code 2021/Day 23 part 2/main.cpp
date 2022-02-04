#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define EMPTY -1

const int COSTS [4] = {1,10,100,1000};
const int ROOMS_NR = 4;

//For part1, simply set LAYERS_NR to 2.
const int LAYERS_NR = 4;


struct Field{
    vector<int> hall;
    int room[ROOMS_NR][LAYERS_NR];
    bool pure_room [ROOMS_NR] = {false,false,false,false};
};

char int_to_char(int n){
    if(n==EMPTY) return '.';
    return 'A'+n;
}

void print_field(const Field& field){
    for(int i=0; i<field.hall.size(); i++){
        cout << int_to_char(field.hall[i]);
    }
    for(int i=0;i<LAYERS_NR;i++){
        cout << endl << "  ";
        for(int r=0;r<ROOMS_NR;r++){
            cout << int_to_char(field.room[r][i]) << " ";
        }
    }
    cout << endl << endl;
}


bool all_home( Field& field ){
    for(int r=0;r<ROOMS_NR;r++){
        for(int i=0;i<LAYERS_NR;i++){
            if(field.room[r][i]!=r) return false;
        }
    }
    return true;
}

bool hall_free(Field& field, int x_begin, int x_end){
    if(x_begin<x_end){
        for(int x=x_begin+1;x<=x_end;x++){
            if(field.hall[x]!=EMPTY){
                return false;
            }
        }
    } else {
        for(int x=x_begin-1;x>=x_end;x--){
            if(field.hall[x]!=EMPTY){
                return false;
            }
        }
    }
    return true;
}

bool in_front_of_door(int x){
    return x==2||x==4||x==6||x==8;
}

void try_min_path(Field& field, int current_score, int& min_score){
    if(current_score>=min_score){
        return;
    }
    if( all_home(field) ){
        min_score = min(current_score, min_score);
        return;
    }
    for(int x=0; x<field.hall.size(); x++){
        if(field.hall[x]!=EMPTY){
            int r = field.hall[x];
            if( field.pure_room[r]&&hall_free(field, x, 2+2*r)){
                int layer=0;
                while(layer<LAYERS_NR-1&&field.room[r][layer+1]==EMPTY) layer++;
                field.hall[x]=EMPTY;
                field.room[r][layer]=r;
                try_min_path(field, current_score+( 1+layer+abs(2+2*r-x) )*COSTS[r] ,min_score);
                field.room[r][layer]=EMPTY;
                field.hall[x]=r;
                return;
            }
        }
    }
    for(int r=0;r<ROOMS_NR; r++){
        if( field.pure_room[r] ){
            continue;
        }
        int layer=0;
        while(layer<LAYERS_NR&&field.room[r][layer]==EMPTY) layer++;
        if(layer==LAYERS_NR){
            continue;
        }
        int pod = field.room[r][layer];
        field.room[r][layer]=EMPTY;
        field.pure_room[r]=true;
        for(int y=layer+1;y<LAYERS_NR;y++){
            if(field.room[r][y]!=r){
                field.pure_room[r]=false;
            }
        }
        for(int x=2+2*r-1;x>=0&&field.hall[x]==EMPTY;x--){
            if( !in_front_of_door(x) ){
                field.hall[x]=pod;
                try_min_path(field,current_score+(1+layer+2+2*r-x)*COSTS[pod],min_score );
                field.hall[x]=EMPTY;
            }
        }
        for(int x=2+2*r+1;x<field.hall.size()&&field.hall[x]==EMPTY;x++){
            if( !in_front_of_door(x) ){
                field.hall[x]=pod;
                try_min_path(field,current_score+(1+layer+x-(2+2*r) )*COSTS[pod],min_score );
                field.hall[x]=EMPTY;
            }
        }

        field.room[r][layer] = pod;
        field.pure_room[r]=false;
    }
}

Field read_input(const string& in_name){
    ifstream input(in_name);
    Field field;
    string s;
    getline(input,s);
    getline(input,s);
    getline(input,s);
    for(int i=0;i<s.size()-2;i++){
        field.hall.push_back(-1);
    }
    string s1 ="  #D#C#B#A#";
    string s2 ="  #D#B#A#C#";
    for(int r=0;r<4;r++){
        field.room[r][0]=s[2*r+3]-'A';
        if(LAYERS_NR!=2) field.room[r][1]=s1[2*r+3]-'A';
        if(LAYERS_NR!=2) field.room[r][2]=s2[2*r+3]-'A';
    }
    getline(input,s);
    for(int r=0;r<ROOMS_NR;r++){
        field.room[r][LAYERS_NR-1]=s[2*r+3]-'A';
    }
    input >> s;

    return field;
}

void part2(){
    Field field = read_input("input.txt");
    print_field(field);

    int min_score=INT_MAX;
    try_min_path(field,0,min_score);
    cout << "Part2: " << min_score << endl;

}

int main()
{
    part2();
    return 0;
}
