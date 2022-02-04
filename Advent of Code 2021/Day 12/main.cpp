#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <set>

using namespace std;

void count_paths(const string& current_string, set<string>& visited, map<string,list< string>>& graph, int& total){
    if(current_string=="end"){
        total++;
        return;
    }
    for( auto s:graph[current_string] ){
        if( (s[0]>='A'&&s[0]<='Z')  ){
            count_paths(s,visited,graph,total);
        } else if(visited.count(s)==0){
            visited.insert(s);
            count_paths(s,visited,graph,total);
            visited.erase(s);
        }
    }
}

void count_paths2(const string& current_string, set<string>& visited, map<string,list< string>>& graph, int& total, bool& double_small){
    if(current_string=="end"){
        total++;
        return;
    }
    for( auto s:graph[current_string] ){
        if( (s[0]>='A'&&s[0]<='Z')  ){
            count_paths2(s,visited,graph,total, double_small);
        } else if(visited.count(s)==0){
            visited.insert(s);
            count_paths2(s,visited,graph,total,double_small);
            visited.erase(s);
        } else if( !double_small&&s!="start" ){
            double_small = true;
            count_paths2(s,visited,graph,total,double_small);
            double_small = false;
        }
    }
}

void part1(){
    ifstream input("input.txt");
    string s1, s2;
    map<string,list<string>> graph;
    getline(input, s1, '-');
    getline(input, s2);
    while(input){
        cout << s1 << " and " << s2 << endl;
        if( graph.count(s1)==0 ){
            graph[s1] = {s2};
        } else {
            graph[s1].push_back(s2);
        }

        if( graph.count(s2)==0 ){
            graph[s2] = {s1};
        } else {
            graph[s2].push_back(s1);
        }

        getline(input,s1,'-');
        getline(input,s2);
    }

    set<string> visited = {"start"};
    int total = 0;
    count_paths("start",visited, graph,total);
    cout << "Part1: " << total << endl;

    total=0;
    bool double_small = false;
    count_paths2("start",visited, graph,total,double_small);
    cout << "Part2: " << total << endl;
}

int main()
{
    part1();
    return 0;
}
