#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

void zeroes(int alpha[26])
{
    for(int i=0;i<26;i++)
        alpha[i]=0;
}

bool two_in(int alpha[26])
{
    for(int i=0;i<26;i++)
    {
        if(alpha[i]==2)
            return true;
    }
    return false;
}

bool three_in(int alpha[26])
{
    for(int i=0;i<26;i++)
    {
        if(alpha[i]==3)
            return true;
    }
    return false;
}

void check23(string str, int alpha[26], int& count2, int& count3)
{
    //pre-con:
    assert(true);
    //post-con
    //Adds 1 to count 2 if there is a letter which appears exactly twice in the string
    //...
    zeroes(alpha);
    for(int i=0;i<str.size();i++)
    {
        alpha[str[i]-97]+= 1;
    }

    if(two_in(alpha))
        count2++;
    if(three_in(alpha))
        count3++;
}

int main()
{
    ifstream inputfile;
    inputfile.open("AoC2.txt");
    int count2=0;
    int count3=0;
    string str;
    inputfile >> str;
    int alpha[26];
    while(inputfile)
    {
        check23(str,alpha, count2, count3);
        inputfile >> str;
    }
    cout << "count2: "<< count2 << "count3: " << count3 << endl;
    cout << "count2*count3: " << count2*count3 << endl;


    return 0;
}
