#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Reg{
    int val[4];
};

void run_command(const string& s, Reg& r, const vector<int>& v, int& pos){
    stringstream ss(s);
    string com;
    ss >> com;
    char c;
    ss >> c;
    if(com=="inp"){
        r.val[c-'w'] = v[pos];
        pos++;
    } else {
        ss.ignore(1);
        char c2 = ss.peek();
        int value;
        if(c2=='w'||c2=='x'||c2=='y'||c2=='z'){
            value = r.val[c2- 'w'];
        } else {
            ss >> value;
        }
        if(com=="add"){
            r.val[c-'w'] = r.val[c-'w']+value;
        } else if(com=="mul"){
            r.val[c-'w'] = r.val[c-'w']*value;
        } else if(com=="div"){
            r.val[c-'w'] = r.val[c-'w']/value;
        } else if(com=="mod"){
            r.val[c-'w'] = r.val[c-'w']%value;
        } else if(com=="eql"){
            r.val[c-'w'] = r.val[c-'w']==value;
        }
    }
}

bool try_model_number(const vector<int>& v){
    ifstream input("input.txt");
    Reg r = {{0,0,0,0}};
    string s;
    getline(input,s);
    int pos=0;
    while(input){
        run_command(s,r,v,pos);
        getline(input,s);
    }
    input.close();
    return r.val[3]==0;
}

void lower_number_v( vector<int>& v ){
    for(int i=v.size()-1;i>=0;i--){
        if(v[i]!=1){
            v[i]--;
            return;
        }
        v[i]=9;
    }

}

void part1(){
    vector<int> number_v(14);
    fill(number_v.begin(), number_v.end(), 9);
    bool number_valid = try_model_number(number_v);
    while(!number_valid){
        lower_number_v(number_v);
        number_valid=try_model_number(number_v);
    }
    cout << "Part1: ";
    for(int i=0;i<14;i++){
        cout << number_v[i];
    }
    cout << endl;
}

int main()
{
    part1();
    return 0;
}
