#include <iostream>
#include <set>

using namespace std;

void part1(){
    int target_left, target_right, target_up, target_down;
    cin.ignore(15);
    cin >> target_left;
    cin.ignore(2);
    cin >> target_right;
    cin.ignore(4);
    cin >> target_down;
    cin.ignore(2);
    cin >> target_up;
// I solved it mathematically hehe. This doesn't always work, but it does if there's a starting x velocity such that the x velocity becomes 0 inside the
// areas x values and the y doesn't get inside the area before the x does.
    cout << "Part1: " << ( abs(target_down) * ( abs(target_down)-1 ) )/2 << endl;

    int cnt=0;

    for(int x_vel=0; x_vel<=target_right; x_vel++){
        for(int y_vel=target_down; y_vel<abs(target_down) ; y_vel++){
            int x=0;
            int y=0;
            int actual_x_vel=x_vel;
            int actual_y_vel=y_vel;
            while( !(x>target_right||y<target_down||(actual_x_vel==0&&x<target_left)) ){
                x += actual_x_vel;
                y += actual_y_vel;
                if(actual_x_vel>0) actual_x_vel--;
                actual_y_vel--;
                if(x>=target_left&&x<=target_right&&y>=target_down&&y<=target_up){
                    cnt++;
                    break;
                }
            }
        }
    }

    cout << "Part2: " << cnt << endl;
}

int main()
{
    part1();
    return 0;
}
