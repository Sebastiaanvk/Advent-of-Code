#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

long long calc_parenthesis(stringstream& ss);

long long to_value(stringstream&ss, char& c){
    if(c=='('){
        return calc_parenthesis(ss);
    } else {
        return c-'0';
    }
}

void combine(long long& result, char& op, long long r){
    if(op=='+'){
        result+=r;
    } else {
        result *=r;
    }
}

long long calc_parenthesis(stringstream& ss){
    char op;
    char c;
    ss >> c;
    long long result;
    result = to_value(ss, c);
    ss >> op;
    while(op!=')'){
        ss >> c;

        combine(result, op, to_value(ss,c) );

        ss >> op;
    }
    return result;
}

long long calc_line(string s){
    stringstream ss;
    ss.str(s);
    char op;
    char c;
    ss >> c;
    long long result;
    result = to_value(ss, c);
    ss >> op;
    ss >> c;
    while(ss){

        combine(result, op, to_value(ss,c) );

        ss >> op;
        ss >> c;
    }
    return result;
}

void part1(){
    ifstream input("input.txt");
    string s;
    getline(input, s);
    long long sum=0;
    while(input){
        sum += calc_line(s);
        getline(input,s);
    }
    cout << "part1: " << sum << endl;
}

long long calc_parenthesis2(stringstream& ss);

long long to_value2(stringstream&ss, char& c){
    if(c=='('){
        long long r = calc_parenthesis2(ss);
//        cout << r << endl;
        return r;
    } else {
//        cout << c-'0' << endl;
        return c-'0';
    }
}

long long calc_parenthesis2(stringstream& ss){
    char op;
    char c;
    ss >> c;
    long long result;
    result = to_value2(ss, c);
    ss >> op;
    bool cont = true;
    while( cont && op!=')'){
        if(op=='+'){
            ss >> c;
//            cout << c << endl;
            result+=to_value2(ss, c);
            ss >> op;
        } else {
            long long r = calc_parenthesis2(ss);
            cont = false;
            result*=r;
        }

//        cout << op << endl;
    }
    return result;
}

long long calc_line2(stringstream& ss){
    char op;
    char c;
    ss >> c;
    long long result;
    result = to_value2(ss, c);
    ss >> op;
    while(ss){
        if(op=='+'){
            ss >> c;
            result += to_value2(ss, c);
        } else {
            long long r= calc_line2(ss);
//            cout << result << endl << r << endl;
            result *= r;

        }


        ss >> op;
    }
    return result;
}

void part2(){
    ifstream input("input.txt");
    string s;
    getline(input, s);
    long long sum=0;
    while(input){
//        cout << s << endl;
        stringstream ss;
        ss.str(s);
        long long r = calc_line2(ss);
        sum += r;
//        cout << r << endl;
        getline(input,s);
    }
    cout << "part2: " << sum << endl;
}

int main()
{
    part1();
    part2();
    return 0;
}
