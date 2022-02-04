#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_input(){
    ifstream input("input.txt");
    int x;
    vector<int> numbers;
    input >> x;
    while(input){
        numbers.push_back(x);
        input.ignore(1);
        input >> x;
    }
    return numbers;
}

void part1(){
    vector<int> positions = get_input();
    sort(positions.begin(),positions.end());
    int crabs_smaller_or_equal = 0;
    int minimal_movement = INT_MAX;
    int minimal_position;
    int current_steps = 0;
    for(int i=0; i<positions.size(); i++){
        current_steps += positions[i]-(positions[0]-1);
    }
    int index_crabs_smaller=-1;
    for(int meetup=positions[0]; meetup <=positions[positions.size()-1]; meetup++ ){
        current_steps += crabs_smaller_or_equal - (positions.size()-crabs_smaller_or_equal);
        if(current_steps<minimal_movement){
            minimal_movement = current_steps;
            minimal_position = meetup;
        }
        while(crabs_smaller_or_equal<positions.size() && positions[crabs_smaller_or_equal]<=meetup){
            crabs_smaller_or_equal++;
        }
    }
    cout << "part1: " << minimal_movement << endl;
}

long long nr_of_steps(const int& n){
    return n*(n+1)/2;
}

void part2(){
    vector<int> positions = get_input();
    int left= INT_MAX;
    int right = INT_MIN;
    for(auto x:positions){
        right = max(right,x);
        left = min(left,x);
    }

    long long min_steps = INT_MAX;

    for( int meetup=left; meetup<=right; meetup++){
        long long current_steps = 0;
        for(int i=0; i<positions.size(); i++){
            current_steps += nr_of_steps(abs(positions[i]-meetup));
        }
        min_steps = min(min_steps,current_steps);
    }

    cout << "part2: " << min_steps << endl;
}

int main()
{
    part2();
    return 0;
}
