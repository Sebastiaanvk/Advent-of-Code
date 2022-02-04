#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void part1(){
    ifstream input("input.txt");
    int locations[4][3];
    int velocities[4][3]={{0}};
    for(int i=0; i<4;i++){
        input.ignore(3);
        input >> locations[i][0];
        input.ignore(4);
        input >> locations[i][1];
        input.ignore(4);
        input >> locations[i][2];
        input.ignore(256,'\n');
    }
    for(int steps=0; steps<1000; steps++){
        for(int i = 0; i<4; i++){
            for(int dim=0; dim<3; dim++){
                for(int other=0; other<4; other++){
                    if(i!=other){
                        if(locations[other][dim]>locations[i][dim]) velocities[i][dim]++;
                        else if (locations[other][dim]<locations[i][dim]) velocities[i][dim]--;
                    }
                }
            }
        }
        for(int i = 0; i<4; i++){
            for(int dim=0; dim<3; dim++){
                locations[i][dim]+=velocities[i][dim];
            }
        }
    }
    int total_energy=0;
    for(int i = 0; i<4; i++){
        int pot_energy=0;
        int kin_energy=0;
        for(int dim=0; dim<3; dim++){
            pot_energy += abs(locations[i][dim]);
            kin_energy += abs(velocities[i][dim]);
        }
        total_energy += pot_energy*kin_energy;
    }
    cout << total_energy << endl;
}

bool same_state(int locations[4][3],int initial_loc[4],int initial_vel[4],int velocities[4][3],const int& dim){
    for(int i=0; i<4; i++){
        if(locations[i][dim]!=initial_loc[i]||velocities[i][dim]!=initial_vel[i]){
            return false;
        }
    }
    return true;
}

long long gcd(long long x, long long y){
    if(x>y) swap(x,y);
    long long r=y%x;
    while(r!=0){
        y=x;
        x=r;
        r=y%x;
    }
    return x;
}

void part2(){
    ifstream input("input.txt");
    int locations[4][3];
    int velocities[4][3]={{0}};
    for(int i=0; i<4;i++){
        input.ignore(3);
        input >> locations[i][0];
        input.ignore(4);
        input >> locations[i][1];
        input.ignore(4);
        input >> locations[i][2];
        input.ignore(256,'\n');
    }

    long long total_time [3]={0};
    for(int dim=0; dim<3; dim++){
        int initial_loc[4];
        int initial_vel[4];
        for(int i=0;i<4; i++){
            initial_loc[i]=locations[i][dim];
            initial_vel[i]=velocities[i][dim];
        }
        do{
            for(int i = 0; i<4; i++){
                for(int other=0; other<4; other++){
                    if(i!=other){
                        if(locations[other][dim]>locations[i][dim]) velocities[i][dim]++;
                        else if (locations[other][dim]<locations[i][dim]) velocities[i][dim]--;
                    }
                }
            }
            for(int i = 0; i<4; i++){
                    locations[i][dim]+=velocities[i][dim];
            }
            total_time[dim]++;
        }while( !same_state(locations,initial_loc, initial_vel, velocities, dim) );
    }
    long long g = total_time[0]*total_time[1]/gcd(total_time[0],total_time[1]);
    cout << g*total_time[2]/gcd(g,total_time[2]);
}

int main()
{
    part2();
    return 0;
}
