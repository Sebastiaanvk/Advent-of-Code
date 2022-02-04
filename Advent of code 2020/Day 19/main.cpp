#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <set>

using namespace std;

struct Rule{
    int i1;
    int i2;
    int o1;
    int o2;
};

void generate_strings( vector<string> pws [150], Rule rules [150], int index ){
    if(pws[index].size()!=0){
        return;
    }
    Rule rule = rules[index];
    if(rule.i2 != -1){
        if(pws[rule.i1].size()==0){
            generate_strings(pws, rules, rule.i1);
        }
        if(pws[rule.i2].size()==0){
            generate_strings(pws, rules, rule.i2);
        }
        for(string s1:pws[rule.i1]){
            for(string s2:pws[rule.i2]){
                pws[index].push_back(s1+s2);
            }
        }

    } else {
        if(pws[rule.i1].size()==0){
            generate_strings(pws, rules, rule.i1);
        }
        for(string s: pws[rule.i1]){
            pws[index].push_back(s);
        }
    }
    if(rule.o1!=-1 && rule.o2!=-1){
        if(pws[rule.o1].size()==0){
            generate_strings(pws, rules, rule.o1);
        }
        if(pws[rule.o2].size()==0){
            generate_strings(pws, rules, rule.o2);
        }
        for(string s1:pws[rule.o1]){
            for(string s2:pws[rule.o2]){
                pws[index].push_back(s1+s2);
            }
        }

    } else if(rule.o1!=-1){
        if(pws[rule.o1].size()==0){
            generate_strings(pws, rules, rule.o1);
        }
        for(string s: pws[rule.o1]){
            pws[index].push_back(s);
        }
    }

}

void part1(){
    fstream input("input.txt");

    Rule rules [150];
    string line;
    int index;
    string s;
    char c;

    getline(input, line);
    while( line!="" ){
        stringstream ss;
        ss.str(line);
        ss >> index >>c;
        if(index!=65&&index!=74){
            ss >> rules[index].i1 >> s;
            if( ss && s!="|" ) {
                rules[index].i2 = stoi(s);
                ss >> s;
            } else {
                rules[index].i2 = -1;
            }
            if(ss){
                ss >> rules[index].o1 >> s;
                if( ss && s!="|" ) {
                    rules[index].o2 = stoi(s);
                    ss >> s;
                } else {
                    rules[index].o2 = -1;
                }
            } else {
                rules[index].o1 = -1;
                rules[index].o2 = -1;
            }
            printf("index:%d, i1:%d, i2:%d, o1:%d, o2: %d\n",index, rules[index].i1, rules[index].i2, rules[index].o1, rules[index].o2);
        }

        getline(input, line);
    }

    vector<string> pws [150];
    pws[65] = {"b"};
    pws[74] = {"a"};

    generate_strings(pws, rules, 0);

    int total = 0;
    unordered_set<string> ok_strings;
    for(string s:pws[0]){
        ok_strings.insert(s);
    }

    getline(input, line);
    while(input){
        if(ok_strings.count(line)){
            total++;
        }
        getline(input, line);
    }

    cout << "part1: "<< total << endl;
}

bool multiple_8(string s, set<string>& strings_42){
    if(s.size()%8!=0){
        return false;
    }
    for(int i=0; i+7<s.size(); i+=8){
        if( strings_42.count( s.substr(i,8) )==0 ){
            return false;
        }
    }

    return true;
}

bool multiple_11(string s, set<string>& strings_42, set<string>& strings_31){
    if(s.size()%16!=0){
        return false;
    }
    int j=s.size()-8;
    for(int i=0; i<j; i+=8){
        if( strings_42.count( s.substr(i,8) )==0 || strings_31.count( s.substr(j,8) )==0 ){
            return false;
        }
        j -= 8;
    }

    return true;
}

bool string_rule_0(string s, set<string>& strings_42, set<string>& strings_31 ){
    if(s.size()%8!=0){
        return false;
    }
    for(int i = 8; i<=s.size()-8; i+=8){
        if( multiple_8( s.substr(0,i), strings_42 ) && multiple_11( s.substr(i,s.size()-i), strings_42, strings_31 ) ){
            return true;
        }
    }

    return false;
}


void part2(){
    fstream input("input.txt");

    Rule rules [150];
    string line;
    int index;
    string s;
    char c;

    getline(input, line);
    while( line!="" ){
        stringstream ss;
        ss.str(line);
        ss >> index >>c;
        if(index!=65&&index!=74){
            ss >> rules[index].i1 >> s;
            if( ss && s!="|" ) {
                rules[index].i2 = stoi(s);
                ss >> s;
            } else {
                rules[index].i2 = -1;
            }
            if(ss){
                ss >> rules[index].o1 >> s;
                if( ss && s!="|" ) {
                    rules[index].o2 = stoi(s);
                    ss >> s;
                } else {
                    rules[index].o2 = -1;
                }
            } else {
                rules[index].o1 = -1;
                rules[index].o2 = -1;
            }
            printf("index:%d, i1:%d, i2:%d, o1:%d, o2: %d\n",index, rules[index].i1, rules[index].i2, rules[index].o1, rules[index].o2);
        }

        getline(input, line);
    }

    vector<string> pws [150];
    pws[65] = {"b"};
    pws[74] = {"a"};

    generate_strings(pws, rules, 0);

    set<string> ok_strings_42;
    set<string> ok_strings_31;
    for( string s : pws[42] ){
        ok_strings_42.insert(s);
    }
//    for(string s: ok_strings_42) cout << s << endl;

    for( string s : pws[31] ){
        ok_strings_31.insert(s);
    }
//    cout << "31: " << endl;
//   for(string s: ok_strings_31) cout << s << endl;



    int total=0;
    getline(input, line);
    while(input){
        if( string_rule_0(line, ok_strings_42, ok_strings_31)  ){
            total++;

        }
        getline(input, line);
    }

    cout << "part2: "<< total << endl;
}

int main()
{
    part2();
    return 0;
}
