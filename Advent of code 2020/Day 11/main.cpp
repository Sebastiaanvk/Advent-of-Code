#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum Cell{Floor, Empty, Occupied};


struct Row{
    vector<Cell> v;
};

istream& operator>>(istream& input, Row& row){
    vector<Cell> v;
    char c;
    input.get(c);
    while(input && c!='\n'){
        if(c=='L') v.push_back(Empty);
        else if(c=='#') v.push_back(Occupied);
        else v.push_back(Floor);
        input.get(c);
    }
    row.v = v;
    return input;
}

bool coordinates_ok(vector<vector<Cell>>& grid, int x, int y){
    return x>=0&&y>=0&&y<grid.size()&&x<grid[0].size();
}

int count_occupied(vector<vector<Cell>>& grid, int x, int y){
    int cnt = 0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(coordinates_ok(grid, x+i,y+j)&&!(i==0&&j==0)&&grid[y+j][x+i]==Occupied) cnt++;
        }
    }
    return cnt;
}

void make_new_grid(vector<vector<Cell>>& old_grid, vector<vector<Cell>>& grid){
    old_grid = grid;
    int width = grid[0].size();
    int height = grid.size();
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int cnt = count_occupied(old_grid,x,y);
            if(old_grid[y][x]==Empty&&cnt==0){
                grid[y][x]=Occupied;
            }else if(old_grid[y][x]==Occupied&&cnt>=4){
                grid[y][x]=Empty;
            } else{
                grid[y][x]=old_grid[y][x];
            }

        }
    }

}

int count_occupied2(vector<vector<Cell>>& grid, int x, int y){
    int cnt = 0;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if( !(i==0&&j==0) ){
                int k=1;
                bool seat_found = false;
                while( coordinates_ok(grid, x+k*i, y+k*j) && !seat_found ){
                    if( grid[y+k*j][x+k*i]!=Floor ){
                        seat_found=true;
                        if(grid[y+k*j][x+k*i]==Occupied){
                            cnt++;
                        }
                    }
                    k++;
                }
            }
        }
    }

    return cnt;
}

void make_new_grid2(vector<vector<Cell>>& old_grid, vector<vector<Cell>>& grid){
    old_grid = grid;
    int width = grid[0].size();
    int height = grid.size();
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int cnt = count_occupied2(old_grid,x,y);
            if(old_grid[y][x]==Empty&&cnt==0){
                grid[y][x]=Occupied;
            }else if(old_grid[y][x]==Occupied&&cnt>=5){
                grid[y][x]=Empty;
            } else{
                grid[y][x]=old_grid[y][x];
            }

        }
    }

}

void print_grid(vector<vector<Cell>>& grid){
    int width = grid[0].size();
    int height = grid.size();
    for(int y=0;y<height; y++){
        for(int x=0; x<width; x++){
            switch( grid[y][x] ){
                case Floor: cout << '.' ; break;
                case Empty: cout << 'L' ; break;
                case Occupied: cout << '#';
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    ifstream input("input.txt");
    vector<vector<Cell>> old_grid;
    vector<vector<Cell>> grid;
    Row r;
    input >> r;
    while(input){
        grid.push_back(r.v);
        input >> r;
    }
    print_grid(grid);


    while(grid!=old_grid){
//        print_grid(grid);
        make_new_grid2(old_grid, grid);//Change to make_new_grid for answer part 1
    }

    int width = grid[0].size();
    int height = grid.size();
    int occupied_seats=0;
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(grid[y][x] == Occupied) occupied_seats++;

        }
    }
    cout << "Part 2:" << occupied_seats << endl;



    return 0;
}
