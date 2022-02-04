#include <iostream>
#include <fstream>

using namespace std;

int read()
{
    ifstream inputfile;
    inputfile.open("AoC1text.txt");
    if(!inputfile.is_open())
    {
        cout << "Whoopsie poopsie something went wrong!";
        return 0;
    }
    char c;
    int integer;
    int value = 0;
    inputfile >> c;
    while(inputfile)
    {
        if(c!='+'&& c!='-')
        {
            cout << "Wrong c: " << c << endl;
            return 0;
        }
        else if(c=='+')
        {
            inputfile >> integer;
            value += integer;
        }
        else if(c=='-')
        {
            inputfile >> integer;
            value -= integer;
        }
        inputfile >> c;
    }
    return value;
}



int main()
{
    int value = 0;
    cout << "The end frequency is: "<< read() << endl;

    return 0;
}
