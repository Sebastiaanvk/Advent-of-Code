#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
    vector<long long> adapters = {0};
    ifstream input("input.txt");
    int x;
    input >> x;
    while(input){
        adapters.push_back(x);
        input >> x;
    }
    sort(adapters.begin(),adapters.end());
    int diff_1=0;
    int diff_3=1;

    for(int i=1; i<adapters.size(); i++){
        if(adapters[i]-adapters[i-1]==1) diff_1++;
        if(adapters[i]-adapters[i-1]==3) diff_3++;
    }

    cout <<"part1: " << diff_1*diff_3 << endl;

    vector<long long> nr_arrangements = {1};

    for(int i = 1; i<adapters.size(); i++){
        long long nr = 0;
        int j=1;
        while(i-j>=0 && adapters[i]-adapters[i-j]<=3){
            nr +=nr_arrangements[i-j];
            j++;
        }
        nr_arrangements.push_back(nr);
    }

    cout << "part2: " << nr_arrangements[nr_arrangements.size()-1] << endl;

    return 0;
}
