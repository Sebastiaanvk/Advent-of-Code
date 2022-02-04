#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void read_input(string input_name, vector<vector<string>>& signal_patterns, vector<vector<string>>& output_values){
    ifstream input(input_name);
    string s;
    input >> s;
    while(input){
        vector<string> signal_pattern;
        for(int i=0; i<10; i++){
            signal_pattern.push_back(s);
            input >> s;
        }
        signal_patterns.push_back(signal_pattern);
        vector<string> output_value;
        for(int i=0; i<4; i++){
            input >> s;
            output_value.push_back(s);
        }
        output_values.push_back(output_value);

        input>> s;
    }
}

int overlap( const string& s1, const string& s2){
    int track = 0;
    for(char x:s1)
        for(char y:s2)
            if(x==y) track++;
    return track;

}

int get_digit(const string& s, string found_signal_pattern[10]){
    for( int i=0; i<10; i++){
        if(s.size()==found_signal_pattern[i].size()&&overlap(s, found_signal_pattern[i])==s.size()) return i;
    }
}

int get_output(vector<string> signal_pattern, vector<string>& output_value){
    string found_signal_pattern [10] = {""};
    bool found_which_number_this_is [10] = {false};
    for(int i=0; i<10; i++){
        if(signal_pattern[i].size()==2){
            found_signal_pattern[1] = signal_pattern[i];
            found_which_number_this_is[i]=true;
        } else if(signal_pattern[i].size()==3){
            found_signal_pattern[7] = signal_pattern[i];
            found_which_number_this_is[i]=true;
        } else if(signal_pattern[i].size()==4){
            found_signal_pattern[4] = signal_pattern[i];
            found_which_number_this_is[i]=true;
        } else if(signal_pattern[i].size()==7){
            found_signal_pattern[8] = signal_pattern[i];
            found_which_number_this_is[i]=true;
        }
    }

    for(int i=0; found_signal_pattern[3]=="";i++){
        if(found_which_number_this_is[i]==false&&signal_pattern[i].size()==5&&overlap(signal_pattern[i],found_signal_pattern[1])==2){
            found_which_number_this_is[i]=true;
            found_signal_pattern[3] = signal_pattern[i];
        }

    }
    for(int i=0; found_signal_pattern[2]=="";i++){
        if(found_which_number_this_is[i]==false&&signal_pattern[i].size()==5&&overlap(signal_pattern[i],found_signal_pattern[4])==2){
            found_which_number_this_is[i]=true;
            found_signal_pattern[2] = signal_pattern[i];
        }
    }
    for(int i=0; found_signal_pattern[5]=="";i++){
        if(found_which_number_this_is[i]==false&&signal_pattern[i].size()==5){
            found_which_number_this_is[i]=true;
            found_signal_pattern[5] = signal_pattern[i];
        }
    }
    for(int i=0; found_signal_pattern[6]=="";i++){
        if(found_which_number_this_is[i]==false&&overlap(signal_pattern[i],found_signal_pattern[1])!=2){
            found_which_number_this_is[i]=true;
            found_signal_pattern[6] = signal_pattern[i];
        }
    }
    for(int i=0; found_signal_pattern[9]=="";i++){
        if(found_which_number_this_is[i]==false&&overlap(signal_pattern[i],found_signal_pattern[4])==4){
            found_which_number_this_is[i]=true;
            found_signal_pattern[9] = signal_pattern[i];
        }
    }
    for(int i=0; found_signal_pattern[0]=="";i++){
        if(found_which_number_this_is[i]==false){
            found_which_number_this_is[i]=true;
            found_signal_pattern[0] = signal_pattern[i];
        }
    }
    int prod = 1;
    int sum = 0;
    for(int i=3; i>=0; i--,prod*=10){
        sum += prod*get_digit(output_value[i], found_signal_pattern);
    }
    return sum;
}

void part1(){
    vector<vector<string>> signal_patterns,output_values;
    read_input("input.txt", signal_patterns, output_values);
    int unique_lengths = 0;
    for(int i=0; i<output_values.size(); i++){
        for(int j=0; j<4; j++){
            int len = output_values[i][j].size();
            if(len==2||len==3||len==4||len==7) unique_lengths++;
        }
    }
    cout << "part1: " << unique_lengths << endl;

    int sum = 0;
    for(int i=0; i<signal_patterns.size(); i++){
        int output = get_output(signal_patterns[i],output_values[i]);
        cout << output << endl;
        sum += output;
    }

    cout << "part2: " << sum << endl;
}

int main()
{
    part1();
    return 0;
}
