#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>


using namespace std;

void part1(){
    ifstream input("input.txt");
    map<string,int> names_to_ints;
    names_to_ints["COM"] = 0;
    vector<int> index_orbits = {-1};
    int nr_planets = 1;
    string s;
    getline(input,s,')');
    while(input){
        int orbitee;
        if(names_to_ints.count(s)){
            orbitee = names_to_ints[s];
        } else {
            orbitee = nr_planets;
            names_to_ints[s] = nr_planets;
            nr_planets++;
            index_orbits.push_back(0);
        }
        getline(input,s);
        int orbiter;
        if(names_to_ints.count(s)){
            orbiter = names_to_ints[s];
        } else {
            orbiter = nr_planets;
            names_to_ints[s] = nr_planets;
            nr_planets++;
            index_orbits.push_back(0);
        }
        index_orbits[orbiter] = orbitee;
        getline(input,s,')');
    }

    int cnt = 0;
    for(int i=0; i<index_orbits.size(); i++){
        int j=i;
        while( index_orbits[j]!=-1 ){
            cnt++;
            j = index_orbits[j];
        }
    }
    cout << cnt << endl;
}

void part2(){
    ifstream input("input.txt");
    map<string,int> names_to_ints;
    names_to_ints["COM"] = 0;
    vector<int> index_orbits = {-1};
    int nr_planets = 1;
    string s;
    getline(input,s,')');
    int orbitee_you;
    int orbitee_san;
    while(input){
        int orbitee;
        if(names_to_ints.count(s)){
            orbitee = names_to_ints[s];
        } else {
            orbitee = nr_planets;
            names_to_ints[s] = nr_planets;
            nr_planets++;
            index_orbits.push_back(0);
        }
        getline(input,s);
        if(s=="YOU"){
            orbitee_you=orbitee;
        } else if(s=="SAN"){
            orbitee_san=orbitee;
        } else {

            int orbiter;
            if(names_to_ints.count(s)){
                orbiter = names_to_ints[s];
            } else {
                orbiter = nr_planets;
                names_to_ints[s] = nr_planets;
                nr_planets++;
                index_orbits.push_back(0);
            }
            index_orbits[orbiter] = orbitee;
        }
        getline(input,s,')');
    }



    int j=orbitee_you;
    vector<int> orbitee_path_you = {orbitee_you};
    while( index_orbits[j]!=-1 ){
        j = index_orbits[j];
        orbitee_path_you.push_back(j);
    }

    int cnt = 0;
    int k = orbitee_san;
    while(true){
        for(int i=0;i<orbitee_path_you.size(); i++){
            if(orbitee_path_you[i]==k){
                cout << cnt+i << endl;
                return;
            }
        }

        k=index_orbits[k];
        cnt++;
    }
}

int main()
{
    part2();
    return 0;
}
