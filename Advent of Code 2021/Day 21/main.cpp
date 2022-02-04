#include <iostream>

using namespace std;

void part1(){
    int pos[2];
    int score [2] = {0};
    cin.ignore(28);
    cin >> pos[0];
    cin.ignore(28);
    cin >> pos[1];
    int dice_value=1;
    int rolls=0;
    bool player2_turn=false;
    while(score[0]<1000&&score[1]<1000){
        for(int i=0;i<3;i++){
            pos[player2_turn] = (pos[player2_turn]+dice_value-1)%10 +1;
            dice_value = dice_value%100 + 1;
        }
        score[player2_turn] += pos[player2_turn];
        player2_turn = !player2_turn;
        rolls+=3;
    }
    cout << "Part1: " << rolls*min(score[0],score[1]) << endl;
}

void part2(){
    long long dice [10]={0};
    for(int x=1;x<=3;x++) for(int y=1;y<=3;y++)for(int z=1;z<=3;z++) dice[x+y+z]++;
//    for(int i=0; i<10; i++) cout << i << ": " << dice[i] << endl;
    int pos[2]={10,9};
//    cin.ignore(28);
//    cin >> pos[0];
//    cin.ignore(28);
//    cin >> pos[1];
    const int MAX_STEPS = 20;
    long long outcomes_1[MAX_STEPS+1][11][22] = {{0}};
    outcomes_1[0][pos[0]][0] = 1;
    long long outcomes_2[MAX_STEPS+1][11][22] = {{0}};
    outcomes_2[0][pos[1]][0] = 1;
    for(int step=1;step<=MAX_STEPS;step++){
        for(int roll=3;roll<=9;roll++){
            for(int p=1;p<=10;p++){
                for(int s=0;s<21;s++){
                    int new_pos = (p+roll-1)%10+1;
                    int new_score = s+new_pos;
                    if(new_score>=21){
                        outcomes_1[step][0][21] += outcomes_1[step-1][p][s]*dice[roll];
                        outcomes_2[step][0][21] += outcomes_2[step-1][p][s]*dice[roll];
                    } else {
                        outcomes_1[step][new_pos][new_score] += outcomes_1[step-1][p][s]*dice[roll];
                        outcomes_2[step][new_pos][new_score] += outcomes_2[step-1][p][s]*dice[roll];
                    }
                }
            }
        }
    }
    long long universes_1_won=0;
    long long universes_2_won=0;
    for(int step=1;step<=MAX_STEPS;step++){
        long long total_left_over_1=0;
        long long total_left_over_2=0;
        for(int p=1;p<=10;p++){
            for(int score=0;score<21;score++){
                total_left_over_1+=outcomes_1[step][p][score];
                total_left_over_2+=outcomes_2[step-1][p][score];
            }
        }
        universes_1_won += outcomes_1[step][0][21]*total_left_over_2;
        universes_2_won += outcomes_2[step][0][21]*total_left_over_1;
    }
    cout <<"Player 1: " << universes_1_won <<"\nPlayer 2: " << universes_2_won << "\nPart2: " << max(universes_1_won,universes_2_won) << endl;
}

int main()
{
    part2();
    return 0;
}
