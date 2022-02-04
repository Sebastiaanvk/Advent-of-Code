#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool in_vector(vector<int>& freqs, int& value)
{
    for(int i =0;i<freqs.size();i++)
    {
        if(freqs[i]==value)
            return true;
    }
    return false;
}

bool read(vector<int>& freqs, int& value)
{
    ifstream inputfile;
    inputfile.open("AoC1text.txt");
//    inputfile.open("test.txt");

    if(!inputfile.is_open())
    {
        cout << "Whoopsie poopsie something went wrong!";
        return 0;
    }
    char c;
    int integer;
    inputfile >> c;
    while(inputfile)
    {
        inputfile >> integer;
        if(c!='+'&& c!='-')
        {
            cout << "Wrong c: " << c << endl;
            return 0;
        }
        else if(c=='+')
        {
            value += integer;

        }
        else if(c=='-')
        {
            value -= integer;
        }
        if(in_vector(freqs, value))
            return true;
        freqs.push_back(value);
        inputfile >> c;
    }
    return false;
}

void find_double_freq()
{
    vector<int> freqs ;
    freqs.push_back(0);
    bool found=false;
    int value = 0;
    while(!found)
    {
        found = read(freqs,value);
        cout << "Laatste element in freqs:  " << freqs[freqs.size()-1] << endl;
    }
    cout <<"Het antwoord: " << value;
}

int main()
{
    find_double_freq();
    return 0;
}
