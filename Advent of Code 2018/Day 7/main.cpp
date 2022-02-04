#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using namespace std;

const int WORKERS=5;
const int ALPHABET_SIZE=26;

bool prerequisites_done(vector<int> prerequisites[ALPHABET_SIZE], bool letter_done [ALPHABET_SIZE], int& index){
    for(auto x:prerequisites[index]){
        if(!letter_done[x])return false;
    }
    return true;
}


void part1(){
    vector<int> prerequisites [ALPHABET_SIZE];
    ifstream input("input.txt");
    char p;
    char q;
    string s;
    input >> s >> p>>s>>s>>s>>s>>s>>q >>s>>s;
    while(input){
        cout << p << " before "<< q << endl;
        prerequisites[q-'A'].push_back(p-'A');
        input >> s >> p>>s>>s>>s>>s>>s>>q >>s>>s;
    }
    string answer;
    bool letter_done [ALPHABET_SIZE] = {false};
    for(int i=0; i<ALPHABET_SIZE; i++){
        bool next_found = false;
        for( int x=0; !next_found&&x<ALPHABET_SIZE; x++ ){
            if( !letter_done[x]&&prerequisites_done(prerequisites,letter_done, x)){
                next_found=true;
                letter_done[x]=true;
                answer += char('A'+x);
            }
        }
    }

    cout << "The answer to part 1 is: " << answer << endl;
}

void set_to_work(int& worker_index, int time_left [WORKERS], char letter_working_on [WORKERS],vector<int> prerequisites [ALPHABET_SIZE], bool letter_begun[ALPHABET_SIZE], bool letter_done [ALPHABET_SIZE] ){
    for( int x=0; x<ALPHABET_SIZE; x++ ){
        if( !letter_begun[x]&&prerequisites_done(prerequisites,letter_done, x)){
            time_left[worker_index] = 61+x;
            letter_working_on[worker_index] = char('A'+x);
            letter_begun[x]=true;
            return;
        }
    }
}

void part2(){
    vector<int> prerequisites [ALPHABET_SIZE];
    ifstream input("input.txt");
    char p;
    char q;
    string s;
    input >> s >> p>>s>>s>>s>>s>>s>>q >>s>>s;
    while(input){
        cout << p << " before "<< q << endl;
        prerequisites[q-'A'].push_back(p-'A');
        input >> s >> p>>s>>s>>s>>s>>s>>q >>s>>s;
    }
    string answer;
    bool letter_begun [ALPHABET_SIZE] = {false};
    bool letter_done [ALPHABET_SIZE] = {false};
    char letter_working_on [WORKERS];
    int time_left [WORKERS]={0};
    int total_time=0;
    while(answer.size()<ALPHABET_SIZE){
        total_time++;
        for( int i=0;i<WORKERS;i++){
            if(time_left[i]==0){
                set_to_work(i,time_left,letter_working_on, prerequisites, letter_begun, letter_done);
            }
        }
        for(int i=0; i<WORKERS; i++){
            if(time_left[i]==1){
                answer += letter_working_on[i];
                letter_done[ letter_working_on[i]-'A' ]=true;
                cout << total_time << ": " << letter_working_on[i] << endl;
            }
            if(time_left[i]>0) time_left[i]--;
        }

    }
    cout << "part2: " << total_time << endl;
}

int main()
{
    part2();
    return 0;
}
