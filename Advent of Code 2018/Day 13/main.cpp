#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_part2=false;

struct Car{
    int x;
    int y;
    int dx;
    int dy;
    int turns=0;
};

bool operator<(const Car& c1, const Car& c2){
    if(c1.y==c2.y){
        return c1.x<c2.x;
    }
    return c1.y<c2.y;
}

bool operator==(const Car& c1, const Car& c2){
    return c1.x==c2.x&&c1.y==c2.y;
}

void read_input(vector<string>& tracks, vector<Car>& cars){
    ifstream input("input.txt");
    string s;
    getline(input,s);
    while(input){
        tracks.push_back(s);
        getline(input,s);
    }
    for(int y=0; y<tracks.size(); y++){
        for(int x=0; x<tracks[0].size(); x++){
            switch (tracks[y][x]){
                case '>': cars.push_back({x,y,1,0,0});    tracks[y][x]='-';break;
                case '^': cars.push_back({x,y,0,-1,0});   tracks[y][x]='|';break;
                case '<': cars.push_back({x,y,-1,0,0});   tracks[y][x]='-';break;
                case 'v': cars.push_back({x,y,0,1,0});    tracks[y][x]='|';break;
            }
        }
    }
}

bool crash_happened(const int& i, vector<Car>& cars ){
    for( int j=0; j<cars.size(); j++){
        if(i!=j&&cars[j]==cars[i]){
            return true;
        }
    }
    return false;
}

void turn_left(Car& car){
    int help=car.dy;
    car.dy=-1*car.dx;
    car.dx=help;
}

void turn_right(Car& car){
    int help=car.dy;
    car.dy=car.dx;
    car.dx=-1*help;
}

void turn_car(Car& car, const char& c){
    if(c=='+'){
        if(car.turns%3==0){
            turn_left(car);
        } else if( car.turns%3==2){
            turn_right(car);
        }
        car.turns = (car.turns+1)%3;
    } else if(c=='/'){
        if(car.dx==0){
            turn_right(car);
        } else {
            turn_left(car);
        }
    } else if(c=='\\'){
        if(car.dx==0){
            turn_left(car);
        } else {
            turn_right(car);
        }
    }
}

void move_car(Car& car){
    car.x += car.dx;
    car.y += car.dy;
}

bool move_cars(vector<string>& tracks,vector<Car>& cars, int& x, int& y){
    for(int i=0; i<cars.size(); i++){
        move_car(cars[i]);
        if(crash_happened(i, cars)){
            x=cars[i].x;
            y=cars[i].y;
            return true;
        }
        turn_car(cars[i],tracks[cars[i].y][cars[i].x]);
    }
    sort(cars.begin(),cars.end());
    return false;
}

void part1(){
    vector<string> tracks;
    vector<Car> cars;
    read_input(tracks,cars);
    sort(cars.begin(),cars.end());
    cout << "done" << endl;
    bool crash=false;
    int x,y;
    while(!crash){
        for(Car c: cars){
            cout << c.x << "," << c.y << endl;
        }
        cout << endl;
        if( move_cars(tracks,cars,x,y) ){
            crash=true;
        }
    }
    cout << "part1: " << x << "," << y << endl;
}

bool crash_happened_2(const int& i, vector<Car>& cars, int& k ){
    for( int j=0; j<cars.size(); j++){
        if(i!=j&&cars[j]==cars[i]){
            k=j;
            return true;
        }
    }
    return false;
}

void move_cars_2(vector<string>& tracks,vector<Car>& cars){
    int crashes=0;
    for(int i=0; i<cars.size(); i++){
        if(cars[i].y<1000){
            move_car(cars[i]);
            int j;

            turn_car(cars[i],tracks[cars[i].y][cars[i].x]);
            if(crash_happened_2(i, cars, j)){
                crashes++;
                cars[i].y=1000000;
                cars[j].y=1000000;
            }
        }
    }
    sort(cars.begin(),cars.end());
    for( int i=0; i<2*crashes; i++){
        cars.pop_back();
    }
}

void part2(){
    vector<string> tracks;
    vector<Car> cars;
    read_input(tracks,cars);
    sort(cars.begin(),cars.end());
//    cout << "done" << endl;
    while( cars.size()>1){
            /*
        for(Car c: cars){
            cout << c.x << "," << c.y << endl;
        }
        cout << endl;*/
        move_cars_2(tracks,cars);
    }

    cout << "part2: " << cars[0].x << "," << cars[0].y << endl;
}

int main()
{
    part2();
    return 0;
}
