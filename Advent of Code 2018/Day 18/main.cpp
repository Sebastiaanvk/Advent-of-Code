#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

char get_field(const vector<vector<char>>& area, const int& x, const int& y){
    if(x<0||y<0||x>=area[0].size()||y>=area.size()){
        return '.';
    }
    return area[y][x];
}

char new_state(const vector<vector<char>>& area, const int& x, const int& y){
    int trees=0;
    int lumberyards = 0;
    for(int i=-1;i<=1;i++){
        for(int j=-1; j<=1; j++){
            if(!(i==0&&j==0)){
                char c = get_field(area,x+i,y+j);
                if(c=='|') trees++;
                if(c=='#') lumberyards++;
            }
        }
    }
    if(area[y][x]=='.'&&trees>=3){
        return '|';
    }else if(area[y][x]=='|'&&lumberyards>=3){
        return '#';
    } else if( area[y][x]=='#'&&!(lumberyards>=1&&trees>=1)  ){
        return '.';
    }

    return area[y][x];
}

void print_area(vector<vector<char>>& area){
    for(int y=0; y<area.size(); y++){
        for(int x=0; x<area[0].size(); x++){
            cout << area[y][x];
        }
        cout << endl;
    }
    cout << endl;
}

int calc_score(vector<vector<char>>& area){
    int trees=0;
    int lumberyards=0;
    for(int y=0; y<area.size(); y++){
        for(int x=0; x<area[0].size(); x++){
            if(area[y][x]=='|') trees++;
            if(area[y][x]=='#') lumberyards++;
        }
    }
    return trees*lumberyards;
}

bool area_previous(const vector<vector<char>>& area, const vector<vector<vector<char>>>& previous_areas, int& loop_size){
    loop_size=1;
    for(int i=previous_areas.size()-1;i>=0;i--){
        if(previous_areas[i]==area){
            return true;
        }
        loop_size++;
    }
    return false;
}

void part1(){
    ifstream input("input.txt");
    char s;
    input.get(s);
    vector<vector<char>> area;
    vector<char> v;
    while(input){
        if(s=='\n'){
            area.push_back(v);
            v = { };

        } else {
            v.push_back(s);
        }
        input.get(s);
    }

    vector<vector<vector<char>>> previous_areas={area};
    vector<int> scores = {calc_score(area)};
    int loop_size;
    bool repetition =false;
    while(!repetition){
        vector<vector<char>> cpy;
        vector<char> line_copy;
        for(int y=0; y<area.size(); y++){
            for(int x=0; x<area[0].size(); x++){
                char c= new_state(area,x,y);
                line_copy.push_back( c );
            }
            cpy.push_back(line_copy);
            line_copy={};
        }
        area = cpy;
//        print_area(area);
        if(area_previous(area, previous_areas, loop_size)){
            repetition=true;
        } else {
            previous_areas.push_back(area);
        }
    }

    int non_loop=previous_areas.size()-loop_size;
    print_area(previous_areas[ (1000000000-non_loop)%loop_size +non_loop]);

    cout << "Answer: " << calc_score(previous_areas[(1000000000-non_loop)%loop_size+non_loop]) << endl;
}

int main()
{
    part1();
    return 0;
}
