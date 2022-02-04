#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>


using namespace std;

int illegal_value(string s, long long& autofinish_score){
    stack<char> stank;
    for(int i=0; i<s.size(); i++){
        char c = s[i];
        if(c==')'){
            if(stank.top()=='('){
                stank.pop();
            } else {
                return 3;
            }
        } else if(c==']'){
            if(stank.top()=='['){
                stank.pop();
            } else {
                return 57;
            }
        } else if(c=='}'){
            if(stank.top()=='{'){
                stank.pop();
            } else {
                return 1197;
            }
        } else if(c=='>'){
            if(stank.top()=='<'){
                stank.pop();
            } else {
                return 25137;
            }
        } else {
            stank.push(c);
        }
    }
    autofinish_score = 0;
    while(!stank.empty()){
        autofinish_score *= 5;
        char c=stank.top();
        stank.pop();
        if(c=='(') autofinish_score += 1;
        else if(c=='[') autofinish_score += 2;
        else if(c=='{') autofinish_score += 3;
        else  autofinish_score += 4;
    }


    return 0;
}

void part1(){
    ifstream input("input.txt");
    string s;
    getline(input,s);
    int sum=0;
    vector<long long> autofinish_scores;
    while(input){
        long long autofinish_score;
        int score = illegal_value(s, autofinish_score);
        sum += score;
        if(score==0){
            autofinish_scores.push_back(autofinish_score);
        }
        getline(input,s);
    }
    cout << "Part1: " << sum << endl;
    sort(autofinish_scores.begin(), autofinish_scores.end() );
    cout << "Part2: " << autofinish_scores[autofinish_scores.size()/2] << endl;
}

int main()
{
    part1();
    return 0;
}
