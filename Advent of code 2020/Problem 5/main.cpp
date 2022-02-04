#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
    ifstream input("input.txt");
    string s;
    getline(input,s);
    int m=0;
    vector<int> v;
    while(input){
        int p=1;
        int sum = 0;
        for(int i=s.size()-1;i>=0;i--){
            if(s[i]=='R'||s[i]=='B'){
                sum+=p;
            }
            p*=2;
        }
        v.push_back(sum);
        if(sum>m){
            m=sum;
        }
        getline(input,s);
    }
    cout << m << endl;
    sort(v.begin(),v.end());
    for(int i=0; i< v.size()-1;i++){
        if(v[i+1]-v[i]==2){
            cout << v[i]+1 << endl;
            return 0;
        }
    }
    return 0;
}
