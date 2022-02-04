#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    ifstream input("input.txt");
    vector<int> v;
    unordered_set<int> s;
    while(input){
        int x;
        input >> x;
        v.push_back(x);
        s.insert(x);
    }
    sort(v.begin(),v.end());
    int i=0;
    int j = v.size()-1;
    while(i<j&&v[i]+v[j]!=2020){
        if(v[i]+v[j]>2020){
            j--;
        } else {
            i++;
        }
    }
    if(v[i]+v[j]==2020){
        cout << "The answer to problem 1 is: " << v[i]*v[j] << endl;
    }
    sort(v.begin(),v.end());
    for(int i=0; i<v.size(); i++){
        for(int j=i+1; j<v.size()&&v[i]+v[j]<2020; j++){
            if( s.count( 2020-v[i]-v[j] ) ){
                long long a = v[i]*v[j]*(2020-v[i]-v[j]);
                cout << v[i] << endl;
                cout << v[j] << endl;
                cout << 2020-v[i]-v[j] << endl;
                cout << "The answer to the second part is: " << a << endl;
                return 0;
            }
        }
    }



    return 0;
}
