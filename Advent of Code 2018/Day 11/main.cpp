#include <iostream>

using namespace std;

const int S=7347;

int fuel(int x, int y ){
    int rack =x+10;
    int power = rack*y;
    power += S;
    power *= rack;
    power = (power/100)%10;
    power -= 5;
    return power;
}

void part1(){
    int fuel_amount[301][301];
    for( int x=1; x<=300; x++){
        for(int y=1; y<=300; y++){
            fuel_amount[x][y]=fuel(x,y);
        }
    }
    int max_square_fuel=-1000000;
    int max_x;
    int max_y;

    for(int x=1;x<=298;x++){
        for(int y=1;y<=298;y++){
            int square_fuel=0;
            for(int dx=0;dx<3;dx++){
                for(int dy=0;dy<3;dy++){
                    square_fuel += fuel_amount[x+dx][y+dy];
                }
            }
            if(square_fuel>max_square_fuel){
                max_square_fuel=square_fuel;
                max_x=x;
                max_y=y;
            }
        }
    }
    cout << "Part1: " << max_x << "," << max_y << " Max square fuel: " << max_square_fuel << endl;
}

void part2(){
    int fuel_amount[301][301];
    for( int x=1; x<=300; x++){
        for(int y=1; y<=300; y++){
            fuel_amount[x][y]=fuel(x,y);
        }
    }
    int max_square_fuel=-1000000;
    int max_x;
    int max_y;
    int max_size;
    int square_fuel_amount[301][301]={0};
    for( int sizer=1;sizer<=300;sizer++){
        for(int x=1;x<=301-sizer;x++){
            for(int y=1;y<=301-sizer;y++){
                for(int i=0;i<sizer-1;i++){
                    square_fuel_amount[x][y] += fuel_amount[x+sizer-1][y+i];
                    square_fuel_amount[x][y] += fuel_amount[x+i][y+sizer-1];
                }
                square_fuel_amount[x][y]+=fuel_amount[x+sizer-1][y+sizer-1];
                if(square_fuel_amount[x][y]>max_square_fuel){
                    max_square_fuel=square_fuel_amount[x][y];
                    max_x=x;
                    max_y=y;
                    max_size = sizer;
                }
            }
        }
    }
    cout << "Part1: " << max_x << "," << max_y << ", " << max_size <<" Max square fuel: " << max_square_fuel << endl;
}

int main()
{
    part2();
    return 0;
}
