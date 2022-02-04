#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int main()
{
    vector<long long> numbers;
    ifstream input("input.txt");
    long long x;
    for(int i=0 ; i<25; i++){
        input >> x;
        numbers.push_back(x);
    }
    input >> x;
    long long answer1;
    bool answer_found =false;
    for(int i=25; !answer_found&&input; i++){
        cout << x << endl;
        numbers.push_back(x);
        bool adds_up = false;
        for(int i=1; i<=25&&!adds_up; i++){
            for(int j=1; j<i&&!adds_up; j++){
                if(numbers[numbers.size()-i-1]+numbers[numbers.size()-j-1]==x){
                    adds_up = true;
                }
            }
        }
        if(!adds_up){
            cout << "The answer to part 1 is: " << x << endl;
            answer1 = x;
            answer_found=true;
        }
        input >> x;
    }
    while(input){
        numbers.push_back(x);
        cout << x << endl;
        input >> x;
    }

    answer_found = false;
    for(int i=0;i<numbers.size()&&!answer_found; i++){
        long long sum = numbers[i];
        for(int j=1; sum<answer1&&i+j<numbers.size(); j++ ){
            sum+=numbers[i+j];
            if( sum==answer1 ){
                long long smallest=answer1;
                long long biggest = 0;
                for(int k=0; k<=j;k++){
                    if(numbers[i+k]>biggest){
                        biggest = numbers[i+k];
                    }
                    if(numbers[i+k]<smallest){
                        smallest = numbers[i+k];
                    }
                }
                cout << "The answer to part 2 is: " << smallest+biggest << endl;
                answer_found = true;
            }
        }
    }


    return 0;
}
