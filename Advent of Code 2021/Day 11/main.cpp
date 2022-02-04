#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Energy_Expl{
    int energy;
    bool flashed;
};

void increase_energy(vector<vector<Energy_Expl>>& field){
    for(int y=0; y<field.size(); y++){
        for(int x=0; x<field[0].size(); x++){
            field[y][x].energy++;
        }
    }
}

bool reset_explosions(vector<vector<Energy_Expl>>& field, int& flashes){
    bool all_flashed = true;
    for(int y=0; y<field.size(); y++){
        for(int x=0; x<field[0].size(); x++){

            if(field[y][x].flashed){
                field[y][x].flashed = false;
                field[y][x].energy = 0;
                flashes++;
            } else {
                all_flashed=false;
            }
        }
    }
    return all_flashed;
}

void change_energy(vector<vector<Energy_Expl>>& field, int y, int x){
    if(x<0||y<0||y>=field.size()||x>=field[0].size())
        return;
    field[y][x].energy++;
}

bool check_for_explosions(vector<vector<Energy_Expl>>& field){
    bool flash_occured = false;
    for(int y=0; y<field.size(); y++){
        for(int x=0; x<field[0].size(); x++){
            if(field[y][x].energy>9&&!field[y][x].flashed){
                flash_occured = true;
                field[y][x].flashed = true;
                for(int i=-1; i<=1; i++){
                    for(int j=-1; j<=1; j++){
                        if(!(i==0&&j==0)){
                            change_energy(field, y+i, x+j);
                        }
                    }
                }
            }
        }
    }
    return flash_occured;
}

void part1(){
    ifstream input("input.txt");
    string s;
    vector<vector<Energy_Expl>> field;
    getline(input,s);
    while(input){
        vector<Energy_Expl> line;
        for(int i=0; i<s.size(); i++){
            line.push_back({s[i]-'0',false});
        }
        field.push_back(line);
        getline(input,s);
    }

    vector<vector<Energy_Expl>> field_copy = field;

    int flashes = 0;
    for(int i=0; i<100; i++){
        increase_energy(field);
        bool explosion_occured;
        do{
            explosion_occured = check_for_explosions(field);
        }while(explosion_occured);
        reset_explosions(field,flashes);
    }
    cout << "part1: " << flashes << endl;

    for(int step=1; ; step++){
        increase_energy(field_copy);
        bool explosion_occured;
        do{
            explosion_occured = check_for_explosions(field_copy);
        }while(explosion_occured);

        if ( reset_explosions(field_copy,flashes) ){
            cout << "part2: " << step << endl;
            return;
        }
    }


}

int main()
{
    part1();
    return 0;
}
