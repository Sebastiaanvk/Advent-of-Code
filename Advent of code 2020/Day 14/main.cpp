#include <iostream>
#include <fstream>
#include <strstream>
#include <map>
#include <vector>

using namespace std;

const int MAX_ARRAY = 100000;

int extract_loc(string s){
    return stoi( s.substr(4,s.size()-5) );
}

long long combine_mask_value(int value, string mask){
    long long result = 0;
    long long power = 1;
    for(int i=1; i<=36; i++){
        if(mask[36-i]=='1'){
            result += power;
        } else if( !(mask[36-i]=='0') ){
            result += power*(value%2);
        }

        value /=2;
        power*=2;
    }
    return result;
}

void part1(){
    long long mem [MAX_ARRAY] = {0};
    string s;
    fstream input("input.txt");
    input >> s;
    string mask;
    int value;

    while(input){
        if(s=="mask"){
            input >> s;
            input >> mask;
        } else {
            int loc = extract_loc(s);

            input >> s;
            input >> value;
            mem[loc] = combine_mask_value(value, mask);
//            cout << combine_mask_value(value, mask) << endl;
       }

        input >> s;
    }

    long long sum = 0;

    for(int i=0; i<MAX_ARRAY; i++){
        sum += mem[i];
    }
    cout << "Part1: " << sum << endl;

}

vector<long long> combine_mask_loc(int loc, string mask){
    long long result_fixed_part = 0;
    long long power = 1;
    vector<long long> masked_locs = {0};

    for(int i=1; i<=36; i++){
        if(mask[36-i]=='1'){
            result_fixed_part += power;
        } else if( mask[36-i]=='0' ){
            result_fixed_part += power*(loc%2);
        } else {
            int length = masked_locs.size();
            for(int i=0; i<length; i++){
                masked_locs.push_back(masked_locs[i]+power);
            }
        }

        loc /=2;
        power*=2;
    }
    for(int i=0; i<masked_locs.size(); i++){
        masked_locs[i]+=result_fixed_part;
    }
    return masked_locs;
}

void part2(){
    map<long long, int> mem;
    string s;
    fstream input("input.txt");
    input >> s;
    string mask;
    int value;

    while(input){
        if(s=="mask"){
            input >> s;
            input >> mask; //I could have calculated the vector of possible locations at this point and then calculate the fixed part later.
        } else {
            vector<long long> locs = combine_mask_loc(extract_loc(s),mask);

            input >> s;
            input >> value;
            for(auto loc:locs){
                mem[loc]=value;
            }
       }
        input >> s;
    }

    long long sum = 0;
    map<long long, int>::iterator it;
    for(it=mem.begin(); it!=mem.end(); it++){
        sum += it->second;
    }

    cout << "Part2: " << sum << endl;

}



int main()
{
    part1();
    part2();
    return 0;
}
