#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

list<char> read_file(string name){
    ifstream input(name);
    list<char> polymer;
    char c;
    input.get(c);
    while(input){
//            cout << c << endl;
        polymer.push_back(c);
        input.get(c);
    }
    return polymer;
}

bool loop_through_remove_matches(list<char>& polymer){
    list<char>::iterator it = polymer.begin();
    bool removed = false;
    while( next(it)!=polymer.end() ){
        if( ( *it==*next(it)+('A'-'a') ) || ( *it==*next(it)-('A'-'a') ) ){
            it = polymer.erase(it);
            it = polymer.erase(it);
            removed=true;
            if( it!=polymer.begin() ) it--;
        } else {
            it++;
        }
    }

    return removed;
}

void part1(){
    list<char> polymer = read_file("input.txt");
    while( loop_through_remove_matches(polymer) ){
        ;
    }
    cout << "The answer to part 1 is: " << polymer.size()-1 <<endl;
}

void part1_better(){
    ifstream input("input.txt");
    vector<char> v = {'\0'};
    char c;
    input>>c;
    while(input){
        if(c==v[v.size()-1]+('A'-'a') || c==v[v.size()-1]-('A'-'a') ){
            v.pop_back();
        } else {
            v.push_back(c);
        }
        input >> c;
    }

    cout << "The answer to part1: " << v.size()-1 << endl;
}

void part2(){
    vector<char> original_v;
    ifstream input("input.txt");
    char c;
    input>> c;
    while(input){
        original_v.push_back(c);
        input >> c;
    }
    int min_length=100000;
    for(int i=0; i<26; i++){
        vector<char> v = {'\0'};
        for( int j=0; j<original_v.size(); j++){
            char c=original_v[j];
            if( c!='a'+i && c!='A'+i){
                if(c==v[v.size()-1]+('A'-'a') || c==v[v.size()-1]-('A'-'a') ){
                    v.pop_back();
                } else {
                    v.push_back(c);
                }
            }
        }
        if(v.size()-1<min_length){
            min_length = v.size()-1;
        }
    }
    cout << "part2: " << min_length;
}

int main()
{
    part2();
    return 0;
}
