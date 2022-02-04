#include <iostream>

using namespace std;

const long long PLAYERS=400;
const long long MAX_MARBLE = 7186400;

long long forward_marble [MAX_MARBLE+1]; //forward is clockwise
long long backward_marble [MAX_MARBLE+1];

void insert_marble(long long& current_marble, const long long& new_marble){
    long long next = forward_marble[current_marble];
    forward_marble[new_marble]=forward_marble[next];
    forward_marble[next]=new_marble;
    backward_marble[new_marble]=next;
    backward_marble[forward_marble[new_marble]]=new_marble;
    current_marble = new_marble;
}

long long delete_seven_clockwise(long long& current_marble){
    long long back_marble = current_marble;
    for( long long i=0; i<7; i++){
        back_marble = backward_marble[back_marble];
    }
    forward_marble[backward_marble[back_marble]]=forward_marble[back_marble];
    backward_marble[forward_marble[back_marble]]=backward_marble[back_marble];
    current_marble=forward_marble[back_marble];
    return back_marble;
}

void part1(){
    long long scores[PLAYERS]={0};

    long long current_marble=0;
    long long player_current=0;
    forward_marble[0]=0;
    backward_marble[0]=0;
    for(long long new_marble=1; new_marble<=MAX_MARBLE; new_marble++){
        if(new_marble%23!=0){
            insert_marble(current_marble, new_marble);
        } else {
            scores[player_current] += new_marble+delete_seven_clockwise(current_marble);
        }

        player_current = (player_current+1)%PLAYERS;
    }

    long long max_score=0;
    for( long long i=0;i<PLAYERS;i++){
        if(scores[i]>max_score) max_score=scores[i];
    }
    cout << "Part1: " << max_score << endl;
}

int main()
{
    part1();
    return 0;
}
