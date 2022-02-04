#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void part1(){
    ifstream input("input.txt");

    int ones [12] = {0};
    int zeroes[12] = {0};
    string s;
    input >> s;
    while(input){
        for(int i=0;i<12; i++){
            if(s[i]=='1'){
                ones[i]++;
            } else {
                zeroes[i]++;
            }
        }
        input >> s;
    }
    int gamma=0;
    int epsilon=0;
    int prod=1;
    for(int i=11; i>=0; i--,prod*=2){
        if(ones[i]>zeroes[i]){
            gamma += prod;
        } else {
            epsilon += prod;
        }
    }
    cout << gamma*epsilon << endl;
}

void part2(){
    ifstream input("input.txt");
    string s;
    input >> s;
    vector<string> numbers;
    vector<bool> oxygen_in;
    vector<bool> c02_in;
    while(input){
        numbers.push_back(s);
        oxygen_in.push_back(true);
        c02_in.push_back(true);
        input >> s;
    }
    string c02_nr;
    for(int i=0; i<numbers[0].size(); i++){
        int ones=0;
        int zeroes=0;
        for(int j=0; j<numbers.size(); j++){
            if(oxygen_in[j]&&numbers[j][i]=='1') ones++;
            else if(oxygen_in[j]) zeroes++;
        }
        bool one_majority = ones>=zeroes;
        for(int j=0; j<numbers.size(); j++){
            if( (one_majority&&numbers[j][i]=='0')||(!one_majority&&numbers[j][i]=='1') ){
                oxygen_in[j] = false;
            }
        }

        ones=0;
        zeroes=0;
        for(int j=0; j<numbers.size(); j++){
            if(c02_in[j]&&numbers[j][i]=='1') ones++;
            else if(c02_in[j]) zeroes++;
        }
        one_majority = ones>=zeroes;
        for(int j=0; j<numbers.size(); j++){
            if( (one_majority&&numbers[j][i]=='1')||(!one_majority&&numbers[j][i]=='0') ){
                c02_in[j] = false;
            } else if(c02_in[j]){
                c02_nr = numbers[j];
            }
        }
    }
    string oxygen_nr;

    for(int j=0;j<numbers.size() ; j++){
        if(oxygen_in[j]){
            oxygen_nr=numbers[j];
        }
    }

    int oxygen_nr_int=0;
    int c02_nr_int=0;
    int prod = 1;
    for(int i=numbers[0].size()-1; i>=0; i--,prod*=2){
        if(oxygen_nr[i]=='1'){
            oxygen_nr_int += prod;
        }
        if(c02_nr[i]=='1'){
            c02_nr_int += prod;
        }
    }

    cout << oxygen_nr_int*c02_nr_int << endl;
}

int main()
{
    part2();
    return 0;
}
