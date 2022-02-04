#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define EMPTY -1

const int COSTS [4] = {1,10,100,1000};

struct Field{
    vector<int> hall;
    int room[4][2];
};

char int_to_char(int n){
    if(n==-1) return '.';
    return 'A'+n;
}

void print_field(const Field& field){
    for(int i=0; i<field.hall.size(); i++){
        cout << int_to_char(field.hall[i]);
    }
    cout << endl << "  ";
    for(int r=0;r<4;r++){
        cout << int_to_char(field.room[r][0]) << " ";
    }
    cout << endl << "  ";
    for(int r=0;r<4;r++){
        cout << int_to_char(field.room[r][1]) << " ";
    }
    cout << endl << endl;
}


bool all_home( Field& field ){
    for(int i=0;i<4;i++){
        if(field.room[i][0]!=i||field.room[i][1]!=i){
            return false;
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
            if( field.room[r][0]==EMPTY&&hall_free(field, x, 2+2*r)){
                if( field.room[r][1]==EMPTY ){
                    field.hall[x]=EMPTY;
                    field.room[r][1]=r;
                    try_min_path(field, current_score+( 2+abs(2+2*r-x) )*COSTS[r] ,min_score);
                    field.room[r][1]=EMPTY;
                    field.hall[x]=r;
                } else if( field.room[r][1]==r ){
                    field.hall[x]=EMPTY;
                    field.room[r][0]=r;
                    try_min_path(field, current_score+( 1+abs(2+2*r-x) )*COSTS[r] ,min_score);
                    field.room[r][0]=EMPTY;
                    field.hall[x]=r;
                }
            }
        }
    }
    for(int r=0;r<4; r++){
        if( (field.room[r][0]==EMPTY&&field.room[r][1]==EMPTY) || field.room[r][1]==r&&( field.room[r][0]==EMPTY||field.room[r][0]==r ) ){
            continue;
        }
        bool move_deep=false;
        int pod;
        if(field.room[r][0]==EMPTY){
            move_deep=true;
            pod=field.room[r][1];
            field.room[r][1]=EMPTY;
        } else {
            pod=field.room[r][0];
            field.room[r][0]=EMPTY;
        }
        int extra_score=COSTS[pod];
        if(move_deep) extra_score += COSTS[pod];
        for(int x=2+2*r-1;x>=0&&field.hall[x]==EMPTY;x--){
            if( !in_front_of_door(x) ){
                field.hall[x]=pod;
                try_min_path(field,current_score+extra_score+(2+2*r-x)*COSTS[pod],min_score );
                field.hall[x]=EMPTY;
            }
        }
        for(int x=2+2*r+1;x<field.hall.size()&&field.hall[x]==EMPTY;x++){
            if( !in_front_of_door(x) ){
                field.hall[x]=pod;
                try_min_path(field,current_score+extra_score+(x-(2+2*r) )*COSTS[pod],min_score );
                field.hall[x]=EMPTY;
            }
        }
        if(move_deep){
            field.room[r][1]=pod;
        } else {
            field.room[r][0]=pod;
        }
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
    for(int r=0;r<4;r++){
        field.room[r][0]=s[2*r+3]-'A';
    }
    getline(input,s);
    for(int r=0;r<4;r++){
        field.room[r][1]=s[2*r+3]-'A';
    }
    input >> s;
    return field;
}

void part1(){
    Field field = read_input("input.txt");
    print_field(field);
    int min_score=INT_MAX;
    try_min_path(field,0,min_score);
    cout << "Part1: " << min_score << endl;

}

int main()
{
    part1();
    return 0;
}
