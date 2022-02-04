#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

const bool PART2 = true;

struct Loc{
    int x;
    int y;
};
bool operator<(const Loc& l1, const Loc& l2){
    if(l1.y==l2.y) return l1.x<l2.x;
    return l1.y<l2.y;
}

bool operator==(const Loc& l1, const Loc& l2){
    return l1.x==l2.x&&l1.y==l2.y;
}

class Hull{
    public:
    map<Loc, bool> hull_squares;
    Loc location;
    Loc direction;
    int total_painted;
    bool paint_now;

    Hull(){
        location = {0,0};
        direction = {0,-1};
        total_painted=0;
        hull_squares.clear();
        paint_now=true;
        if(PART2){
            hull_squares.insert(make_pair(location,true));
        }
    }

    int give_input_to_computer(){
        if(hull_squares.count(location)==0 ){
            return false;
        } else {
            return hull_squares[location];
        }
    }

    void get_output_from_computer(bool b){
        if(paint_now){
            if( hull_squares.count(location)==0 && b ){
                for(map<Loc,bool>::iterator iter=hull_squares.begin(); iter!=hull_squares.end(); iter++){
                    Loc l = iter->first;
                    cout << l.x << " " << l.y << endl;
                }
                cout << "dit\n";
                cout << location.x << " " << location.y << endl;
                hull_squares.insert( make_pair(location,true) );
                //hull_squares[{location.x,location.y}] = true;
                cout << "gaat nog goed\n";
                total_painted++;
            } else if( hull_squares.count(location)>0&&hull_squares[location]!=b ){
                hull_squares[location] = b;
            }

        } else {
            int help = direction.y;
            if(b){
                direction.y=direction.x;
                direction.x=(-1)*help;
            } else {
                direction.y=(-1)*direction.x;
                direction.x=help;
            }
            location.x += direction.x;
            location.y += direction.y;
        }

        paint_now = !paint_now;
    }

    void end_hull(){
        if(!PART2){
            cout << total_painted << endl;
        } else {
            cout << "hoi" << endl;

            int smallest_x = INT_MAX;
            int smallest_y = INT_MAX;
            for(map<Loc,bool>::iterator iter = hull_squares.begin(); iter!=hull_squares.end(); iter++){
                Loc l = iter -> first;
                bool b = iter -> second;
                if(b){
                    smallest_x = min(smallest_x, l.x);
                    smallest_y = min(smallest_y, l.y);
                }
            }
            int current_x=smallest_x;
            int current_y=smallest_y;
            for(map<Loc,bool>::iterator iter = hull_squares.begin(); iter!=hull_squares.end(); iter++){
                Loc l = iter -> first;
                bool b = iter -> second;
                if(b){
                    while(current_y<l.y){
                        cout << endl;
                        current_x = smallest_x;
                        current_y++;
                    }
                    while(current_x<l.x){
                        cout << " ";
                        current_x++;
                    }
                    cout << "#";
                    current_x++;
                }
            }
            cout << endl;
        }



    }
};



void run_computer(vector<long long> v){
    Hull hull;

    int pos = 0;
    long long rel_base=0;
    while(true){
        long long command = v[pos];
        int opcode = command%100;
//        cout << opcode << endl;
        command/=100;
        long long adr[3];
        for(int i=0;i<3&&pos+1+i<v.size();i++){
            if( command%10==0 ){
                adr[i] = v[pos+1+i];
            }else if(command%10==1){
                adr[i] = pos+1+i;
            } else if(command%10==2){
                adr[i] = rel_base+v[pos+1+i];
            }
            command /= 10;
        }
        if(opcode==1){
            v[adr[2]]=v[adr[0]]+v[adr[1]];
            pos+=4;
        } else if(opcode==2){
            v[adr[2]]=v[adr[0]]*v[adr[1]];
            pos+=4;
        } else if(opcode==3){
            v[adr[0]] = hull.give_input_to_computer();
            pos+=2;
        } else if(opcode==4){
            hull.get_output_from_computer( v[adr[0]] );
            pos+=2;
        } else if(opcode==5){
            if(v[adr[0]]!=0){
                pos = v[ adr[1] ];
            } else {
                pos+=3;
            }
        } else if(opcode==6){
            if(v[ adr[0] ]==0){
                pos = v[ adr[1] ];
            } else {
                pos+=3;
            }
        } else if(opcode==7){
            if( v[ adr[0] ]<v[adr[1]] ){
                v[adr[2]] = 1;
            } else {
                v[adr[2]] = 0;
            }
            pos+=4;
        } else if(opcode==8){
            if( v[ adr[0] ]==v[adr[1]] ){
                v[adr[2]] = 1;
            } else {
                v[adr[2]] = 0;
            }
            pos+=4;
        } else if(opcode==9){
            rel_base += v[adr[0]];
            pos+=2;
        } else{
            hull.end_hull();
            return;
        }
    }
}

void part1(){
    ifstream input("input.txt");
    vector<long long> v;
    long long x;
    input >> x;
    while(input){
        v.push_back(x);
        input.get();
        input >> x;
    }

    run_computer(v);
}


int main()
{
    part1();
    return 0;
}
