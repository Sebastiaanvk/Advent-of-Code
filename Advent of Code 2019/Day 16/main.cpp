#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

void part1(){
    string s;
    cin >> s;
    stringstream ss(s);
    vector<int> v;
    for(auto c:s){
        v.push_back(c-'0');
    }
    for(int i=0; i<100; i++){
        vector<int> new_v;
        for(int i=1; i<=v.size(); i++){
            long long sum=0;
            for(int j=i-1; j<v.size(); j+=4*i){
                for(int k=0;k<i&&j+k<v.size();k++){
                    sum +=v[j+k];
                }
            }
            for(int j=3*i-1; j<v.size(); j+=4*i){
                for(int k=0;k<i&&j+k<v.size();k++){
                    sum -=v[j+k];
                }
            }
            if(sum<0) sum*=-1;
            new_v.push_back(sum%10);
        }
        v = new_v;
    }
    for(int i=0; i<8; i++){
        cout << v[i];
    }
    cout << endl;
}

void part2(){
    string s;
    cin >> s;
    stringstream ss(s);
    vector<int> v;
    for(auto c:s){
        v.push_back(c-'0');
    }

    int offset = stoi( s.substr(0,7) );

    for(int i=1; i<10000; i++){
        for(int j=0; j< s.size(); j++){
            v.push_back(v[j]);
        }
    }

    int init_length = v.size();

    vector<int> new_v;
    for(int i=offset; i<v.size();i++){
        new_v.push_back(v[i]);
    }
    v = new_v;
    int len = v.size();

    for(int step=0; step<100; step++){
// Sum UPTO index i. Not including!
        vector<int> sub_sums = {0};
        int sub_sum=0;
        for(int i=0; i<v.size();i++){
            sub_sum+=v[i];
            sub_sums.push_back(sub_sum);
        }

        vector<int> new_v;
        for(int width=offset+1; width<=init_length; width++){
            long long sum=0;
            for(int j=width-1-offset; j<v.size(); j+=4*width){
                int m = min(j+width,len );
                sum += sub_sums[ m ] - sub_sums[j];
            }
            for(int j=3*width-1-offset; j<v.size(); j+=4*width){
                int m = min(j+width,len);
                sum -= sub_sums[m]-sub_sums[j];

            }
            if(sum<0) sum*=-1;
            new_v.push_back(sum%10);
        }
        v = new_v;
    }



    for(int i=0; i<8; i++){
        cout << v[i];
    }
    cout << endl;
}
/*
int length;

int get_value(int index, int layer,unordered_map<int,int>& values){
    if(layer<100&&values.count(100*index+layer)>0){
        return values[100*index+layer];
    }
    int sum = 0;
    int i=index+1;
    for(int j=i-1; j<length; j+=4*i){
        for(int k=0;k<i&&j+k<length;k++){
            sum +=get_value(j+k,layer-1,values);
        }
    }
    for(int j=3*i-1; j<length; j+=4*i){
        for(int k=0;k<i&&j+k<length;k++){
            sum -=get_value(j+k,layer-1,values);
        }
    }
    if(sum<0) sum*=-1;
    sum = sum%10;

    if(layer<100) values[100*index+layer]=sum;
    return sum;
}

void part2_new(){
    string s;
    cin >> s;
    stringstream ss(s);
    vector<int> v;
    for(auto c:s){
        v.push_back(c-'0');
    }
    int offset = stoi( s.substr(0,7) );

    cout << offset << endl;

    for(int i=1; i<10000; i++){
        for(int j=0; j< s.size(); j++){
            v.push_back(v[j]);
        }
    }
    length = v.size();

    unordered_map<int,int> values;

    for(int i=0; i<v.size(); i++){
        values[i*100]=v[i];
    }

    int result =    10000000*get_value(offset,100,values)+
                    1000000 *get_value(offset+1,100,values)+
                    100000  *get_value(offset+2,100,values)+
                    10000   *get_value(offset+3,100,values)+
                    1000    *get_value(offset+4,100,values)+
                    100     *get_value(offset+5,100,values)+
                    10      *get_value(offset+6,100,values)+
                    1       *get_value(offset+7,100,values);

    cout << "Part2: " <<  result << endl;
}*/

int main()
{
    part2();
    return 0;
}
