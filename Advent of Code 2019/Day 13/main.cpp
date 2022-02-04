#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_SCREEN_SIZE_y=25;
const int MAX_SCREEN_SIZE_x = 40;

bool PART2=true;

struct Game{
    public:
    int screen[MAX_SCREEN_SIZE_y][MAX_SCREEN_SIZE_x] = {{0}};
    int which_input_now;
    int current_x;
    int current_y;
    int x_paddle,x_ball,y_ball,x_dir,y_dir;
    int score;
    //bool about_to_hit_paddle =false;

    Game(){
        which_input_now=0;
        score=0;
        x_ball=10;
        //x_dir=1;
        //y_dir=1;
    }


    void get_output_from_computer(int i){
        //cout << i << endl;
        //cout << which_input_now << endl;
        if(which_input_now==0){
            current_x = i;
            if(current_x<-1||current_x>=MAX_SCREEN_SIZE_x){
                cout << current_x << ": SCREEN TOO SMALL!!!!\n";
            }
            which_input_now++;
        } else if(which_input_now==1){
            current_y = i;
            if(current_y<0||current_y>=MAX_SCREEN_SIZE_y){
                cout <<current_y << ": SCREEN TOO SMALL!!!!\n";
            }
            which_input_now++;
        } else {
            if(current_x!=-1||current_y!=0){
                screen[current_y][current_x] = i;
                if(i==3){
                    x_paddle=current_x;
                } else if(i==4){
                    /*if(current_x>x_ball) x_dir=1;
                    else x_dir=-1;
                    if(current_y>y_ball) y_dir=1;
                    else y_dir=-1;*/
                    x_ball = current_x;
                    //y_ball = current_y;
                    /*
                    if(screen[current_y+y_dir][current_x]==3||screen[current_y+y_dir][current_x+x_dir]==3){
                        about_to_hit_paddle = true;
                    } else {
                        about_to_hit_paddle = false;
                    }

                    int next_square_hor=screen[y_ball][x_ball+x_dir];
                    int next_square_vert=screen[y_ball+y_dir][x_ball];
                    int next_square_dia=screen[y_ball+y_dir][x_ball+x_dir];
                    if(next_square_hor!=0) x_dir *= -1;
                    if(next_square_vert!=0) y_dir *= -1;
                    if(next_square_hor==0&&next_square_vert==0&&next_square_dia!=0){
                        x_dir*=-1;
                        y_dir*=-1;
                    }*/

                }
            }

            else{
                score = i;
            }
            which_input_now=0;
        }
    }

    int direction_paddle(){
        /*
        if(about_to_hit_paddle||x_paddle==x_ball+x_dir ){
            return 0;
        } else if( x_paddle==x_ball ){
            return x_dir;
        }
        if(x_ball>x_paddle) return 1;
        return -1;*/
        if(x_ball>x_paddle){
            return 1;
        } else if(x_ball<x_paddle){
            return -1;
        }

        return 0;
    }

    void end_screen(){
        if(!PART2){
            int nr_blocks=0;
            for(int y=0; y<MAX_SCREEN_SIZE_y; y++){
                for(int x=0; x<MAX_SCREEN_SIZE_x; x++){
                    if(screen[y][x]==2){
                        nr_blocks++;
                    }
                }
            }
            cout << nr_blocks << endl;
        } else {
            cout << "score: " << score << endl;
        }
    }

    void display(){
        cout << "SCORE: " << score << endl;
        for(int y=0; y<MAX_SCREEN_SIZE_y; y++){
            for(int x=0; x<MAX_SCREEN_SIZE_x; x++){
                if(screen[y][x]==0){
                    cout << " ";
                } else {
                    cout << screen[y][x];
                }
            }
            cout << endl;
        }
    }


};


void run_computer(vector<long long> v){
    Game game ;
    int pos = 0;
    long long rel_base=0;
    while(true){
        long long command = v[pos];
        int opcode = command%100;
        //cout << opcode << endl;
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
            //game.display();
            v[adr[0]] = game.direction_paddle();
            //cin >> v[adr[0]];
            pos+=2;
        } else if(opcode==4){
            game.get_output_from_computer( v[adr[0]] );
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
            game.display();
            game.end_screen();
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
    input.close();
    if(PART2) v[0]=2;
    run_computer(v);

}


int main()
{
    part1();
    return 0;
}
