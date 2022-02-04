#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

using namespace std;

const int SIZ=1000000;
const int ZEROSTART = 90;
const int POWS2[5] = {1,2,4,8,16};
const long long GEN = 50000000000;

int string_to_bin(const string& s){
    int sum=0;
    for(int i=0; i<5; i++){
        if(s[i]=='#'){
            sum = sum +( POWS2[i] );
        }
    }
    return sum;
}

void next_generation(bool plants [SIZ], bool rules [32], int& total){
    bool new_plants [SIZ]={false};
    for(int i=2;i<SIZ-2;i++){
        int config=0;
        for(int dx=-2;dx<=2;dx++){
            if( plants[i+dx] ){
                config += POWS2[dx+2];
            }
        }
        if( rules[config] ){
            new_plants[i]=true;
            total++;
        }

    }
    for(int i=0;i<SIZ;i++){
        plants[i]=new_plants[i];
    }
}

int config_value(bool plants [SIZ]){
    int sum = 0;
    for(int i=0; i<SIZ; i++){
        if(plants[i]){
            sum+= i-ZEROSTART;
        }
    }
    return sum;
}

int config_value(vector<bool>& plants){
    int sum = 0;
    for(int i=0; i<SIZ; i++){
        if(plants[i]){
            sum+= i-ZEROSTART;
        }
    }
    return sum;
}

void part1(){
    ifstream input("input.txt");
    input.ignore(200,':');
    string s;
    input>>s;
    cout << s << endl;
    bool plants [SIZ]={false};
    int total=0;
    for( int i=0; s[i]!='\0';i++){
        if(s[i]=='#'){
            plants[ZEROSTART+i]=true;
            total++;
        }
    }

    bool rules [32]={false};
    string str;
    input >> str;
    for(int i=0;input;i++){
        cout <<str << endl;
        input.ignore(4);
        char c;
        input>>c;
        cout << c << endl;
        rules[string_to_bin(str)] = c=='#';
        input >> str;
    }

    for( int i=50; i<1000; i++){
        if(plants[i]){
            cout << '#';
        } else {
            cout << '.';
        }
    }
    cout << endl;

    for(long long j=0; j<GEN; j++){
        next_generation(plants,rules,total);
        /*
        for( int i=50; i<1000; i++){
            if(plants[i]){
                cout << '#';
            } else {
                cout << '.';
            }
        }*/
        cout <<"Generation: " << j+1;
        cout <<": "<< config_value(plants);
        cout << endl;
    }



    cout << "Part1: " << config_value(plants);
}

vector<bool> plant_to_vector(bool arr [SIZ]){
    vector<bool> v;
    for(int i=0; i<SIZ; i++){
        v.push_back(arr[i]);
    }
    return v;
}


void part2(){
    ifstream input("input.txt");
    input.ignore(200,':');
    string s;
    input>>s;
    bool plants [SIZ]={false};
    int total=0;
    for( int i=0; s[i]!='\0';i++){
        if(s[i]=='#'){
            plants[ZEROSTART+i]=true;
            total++;
        }
    }

    bool rules [32]={false};
    string str;
    input >> str;
    for(int i=0;input;i++){
        input.ignore(4);
        char c;
        input>>c;
        rules[string_to_bin(str)] = c=='#';
        input >> str;
    }

    vector<vector<bool>> configs_vec;
    configs_vec.push_back( plant_to_vector(plants) );
    bool double_found=false;
    long long i;
    for(int j=0; !double_found&&j<SIZ-1000; j++){
        next_generation(plants,rules,total);
        vector<bool> v = plant_to_vector(plants);
        for(i=configs_vec.size()-1; !double_found&& i>=0; i--){
            if( configs_vec[i]==v ){
                cout << "double found!\n";
                double_found=true;
            }
        }
        if(!double_found){
            configs_vec.push_back(v);
        }
    }
    long long first_repeat=configs_vec.size();
    cout << i << endl;
    cout << first_repeat << endl;
    long long b=50000000000;
    b = b-i;
    b = b%(first_repeat-i);
    cout << "Part2: " << config_value( configs_vec[i+b] ) << endl;
}

int main()
{
    part1();
    return 0;
}
