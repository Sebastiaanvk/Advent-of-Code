#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>

using namespace std;

void turn_tile(int x, int y, set< pair<int,int> >& turned_tiles, int& counter){
    if( turned_tiles.count( {x,y} ) ){
        counter--;
        turned_tiles.erase( {x,y} );
//        printf("double: x:%d,y:%d\n",x,y);
    } else {
        counter++;
        turned_tiles.insert( {x,y} );
//        printf("single: x:%d,y:%d\n",x,y);
    }

}

void part1(){
    set< pair<int,int> > turned_tiles;
    ifstream input("input.txt");
    int counter = 0;
    char c;
    input.get(c);
    int x=0;
    int y=0;
    while(input){
//        cout << x << " " <<y << endl;
//        cout << c;
        switch(c){
            case 'e':   x++; break;
            case 'w':   x--; break;
            case 'n':   input.get(c);
//                        cout << c;
                        if(c=='e'&&y%2==0) x++;
                        else if(c=='w'&&y%2!=0) x--;
                        y++;
                        break;
            case 's':   input.get(c);
//                        cout << c;
                        if( c=='e'&&y%2==0 ) x++;
                        else if( c=='w'&&y%2!=0 ) x--;
                        y--;
                        break;
            case '\n':  turn_tile(x,y,turned_tiles,counter); x=0; y=0;
        }
//        cout << endl;
        input.get(c);
    }
    if(c!='\n') turn_tile(x,y,turned_tiles,counter);
    cout << "part1: " << counter << endl;

}

const int N=500;

void flip_tile_matrix(int x, int y, bool turned_tiles[N][N], int& counter ){
    if( turned_tiles[x][y] ){
        counter--;
        turned_tiles[x][y]=false;
//        printf("double: x:%d,y:%d\n",x,y);
    } else {
        counter++;
        turned_tiles[x][y]=true;
//        printf("single: x:%d,y:%d\n",x,y);
    }
}

int count_true(bool turned_tiles[N][N], const int& x, const int& y){
    int track = 0;
    track += turned_tiles[x][y-1]+turned_tiles[x][y+1]+turned_tiles[x-1][y]+turned_tiles[x+1][y];
    if(y%2==0){
        track+=turned_tiles[x+1][y-1]+turned_tiles[x+1][y+1];
    } else {
        track+=turned_tiles[x-1][y-1]+turned_tiles[x-1][y+1];
    }

    return track;
}

void change_matrix( bool turned_tiles[N][N], int count_surrounding[N][N]){
    for(int x=1; x<N-1; x++){
        for(int y=1; y<N-1; y++){
            count_surrounding[x][y] = count_true(turned_tiles,x,y);
        }
    }
    for(int x=1; x<N-1; x++){
        for(int y=1; y<N-1; y++){
            turned_tiles[x][y] = count_surrounding[x][y]==2||(count_surrounding[x][y]==1&&turned_tiles[x][y]);
        }
    }

}

void part2(){
    bool turned_tiles[N][N]={false};
    ifstream input("input.txt");
    int counter = 0;
    char c;
    input.get(c);
    int x=N/2;
    int y=N/2;
    while(input){
//        cout << x << " " <<y << endl;
//        cout << c;
        switch(c){
            case 'e':   x++; break;
            case 'w':   x--; break;
            case 'n':   input.get(c);
//                        cout << c;
                        if(c=='e'&&y%2==0) x++;
                        else if(c=='w'&&y%2!=0) x--;
                        y++;
                        break;
            case 's':   input.get(c);
//                        cout << c;
                        if( c=='e'&&y%2==0 ) x++;
                        else if( c=='w'&&y%2!=0 ) x--;
                        y--;
                        break;
            case '\n':  flip_tile_matrix(x,y,turned_tiles,counter); x=N/2; y=N/2;
        }
//        cout << endl;
        input.get(c);
    }
    if(c!='\n') flip_tile_matrix(x,y,turned_tiles,counter);

    int count_surrounding[N][N];
    for(int i=0; i<100; i++){
        change_matrix(turned_tiles, count_surrounding);
    }
    counter=0;
    for(int x=1; x<N-1; x++){
        for(int y=1; y<N-1; y++){
            if(turned_tiles[x][y]){
                counter++;
            }
        }
    }

    cout << "part2: " << counter << endl;


}


int main()
{
//    part1();
    part2();
    return 0;
}
