#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void part1(){
    ifstream input("input.txt");
    string starting_string;
    input >> starting_string;
    map< pair<char,char>,char> reactions;
    string in;
    char out;
    input >> in;
    input.ignore(4);
    input >> out;
    while(input){
        reactions[{in[0],in[1]}] = out;
        input >> in;
        input.ignore(4);
        input >> out;
    }
    string current_pol = starting_string;
    for(int steps=0; steps<10; steps++){
        string new_pol = "";
        for(int i=0; i<current_pol.size()-1; i++){
            new_pol += current_pol[i];
            new_pol += reactions[ {current_pol[i],current_pol[i+1]} ];
        }
        new_pol += current_pol[current_pol.size()-1];
        current_pol = new_pol;
    }
    map<char,long long> occ;
    for( int i=0; i<current_pol.size(); i++){
        char c = current_pol[i];
        if( occ.count(c)==0 ) {
            occ[c]=1;
        }else occ[c]++;
    }
    long long mini = INT_MAX;
    long long maxi = INT_MIN;
    for(auto p:occ){
        long long value = p.second;
        maxi = max(value,maxi);
        mini = min(value, mini);
    }
    cout << "Part1: " << maxi-mini << endl;


}

void part2(){
    ifstream input("input.txt");
    string starting_string;
    input >> starting_string;
    map< pair<char,char>,char> reactions;
    string in;
    char out;
    input >> in;
    input.ignore(4);
    input >> out;
    while(input){
        reactions[{in[0],in[1]}] = out;
        input >> in;
        input.ignore(4);
        input >> out;
    }
    map< pair<char,char>,long long> current_pair_prevalence;
    for( int i=0; i<starting_string.size()-1; i++){
        current_pair_prevalence[{starting_string[i],starting_string[i+1]}]++;
    }


    for(int steps=0; steps<40; steps++){
        map< pair<char,char>,long long> next_pair_prevalence;
        for(auto p: current_pair_prevalence){
            char middle = reactions[p.first];
            next_pair_prevalence[{p.first.first,middle}] += p.second;
            next_pair_prevalence[{middle,p.first.second}] += p.second;
        }

        current_pair_prevalence = next_pair_prevalence;
    }

    map<char,long long> occ;
    occ[ starting_string[starting_string.size()-1] ] = 1;
    for(auto p:current_pair_prevalence){
        occ[p.first.first] += p.second;
    }
    long long mini = occ[starting_string[0]];
    long long maxi = 0;
    for(auto p:occ){
        long long value = p.second;
        maxi = max(value,maxi);
        mini = min(value, mini);
    }
    cout << maxi << " " << mini << endl;
    cout << "Part2: " << maxi-mini << endl;

}


int main()
{
    part2();
    return 0;
}
