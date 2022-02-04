#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

map<char,string> chars_to_bin = {
    {'0',"0000"},{'1',"0001"},
    {'2',"0010"},{'3',"0011"},
    {'4',"0100"},{'5',"0101"},
    {'6',"0110"},{'7',"0111"},
    {'8',"1000"},{'9',"1001"},
    {'A',"1010"},{'B',"1011"},
    {'C',"1100"},{'D',"1101"},
    {'E',"1110"},{'F',"1111"}
};

string read_input(const string& s){

    //string q;
    //getline(cin,q);
    //stringstream input(q);
    ifstream input(s);
    string binary_number ;
    char c;
    input >> c;
    while(input){
        binary_number += chars_to_bin[c];
        input >> c;
    }

    return binary_number;
}

int number(const vector<bool>& binary_number, const int& left_index, const int& length){
    int sum=0;
    int prod = 1;
    for(int i=left_index+length-1;i>=left_index;i--,prod*=2){
        if(binary_number[i]){
            sum+=prod;
        }
    }
    return sum;
}

long long traverse(const vector<bool>& binary_number, int& index, int& versions_total){
    int version = number(binary_number,index,3);
    versions_total+=version;
    int type_id = number(binary_number,index+3,3);
    index += 6;
    if(type_id==4){
        vector<long long> nrs;
        while(binary_number[index]==1){
            nrs.push_back(number(binary_number,index+1,4));
            index+=5;
        }
        nrs.push_back(number(binary_number,index+1,4));
        index+=5;
        long long result=0;
        long long prod = 1;
        for(int i=nrs.size()-1;i>=0; i--,prod*=16){
            result += nrs[i]*prod;
        }
        return result;
    } else {
        vector<long long> subs;
        if(binary_number[index]){
            int nr_sub_packets = number(binary_number,index+1,11);
            index+=12;
            for(int i=0; i<nr_sub_packets; i++){
                subs.push_back(traverse(binary_number,index,versions_total));
            }
        } else {
            int sub_packets_length = number(binary_number,index+1,15);
            index+=16;
            int index_start=index;
            while(index<index_start+sub_packets_length){
                subs.push_back(traverse(binary_number,index,versions_total));
            }
        }
        if(type_id==0){
            long long sum=0;
            for(auto x:subs) sum+=x;
            return sum;
        } else if(type_id==1){
            long long p=1;
            for(auto x:subs) p*=x;
            return p;
        } else if(type_id==2){
            long long mini = subs[0];
            for(auto x:subs) mini = min(mini,x);
            return mini;
        } else if(type_id==3){
            long long maxi = subs[0];
            for(auto x:subs) maxi = max(maxi,x);
            return maxi;
        } else if(type_id==5){
            return subs[0]>subs[1];
        } else if(type_id==6){
            return subs[0]<subs[1];
        } else if(type_id==7){
            return subs[0]==subs[1];
        }

    }
}


void part1(){
    string binary_number_str = read_input("input.txt");
    vector<bool> binary_number;
    for(int i=0; i<binary_number_str.size(); i++){
        binary_number.push_back(binary_number_str[i]=='1');
    }
    int index=0;
    int versions_total=0;
    cout << "Part2: " << traverse(binary_number,index,versions_total) << endl;
    cout << "Part1: " << versions_total << endl;
}



int main()
{
    part1();
    return 0;
}
