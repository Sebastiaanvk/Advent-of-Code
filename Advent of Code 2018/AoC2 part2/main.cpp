#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;

bool compare(string string1, string string2)
{
    int i = 0;
    while(i<string1.size()&&string1[i]==string2[i])
    {
        i++;
    }
    if(i==string1.size())
        return true;
    i++;
    for(i;i<string1.size();i++)
    {
        if(string1[i]!=string2[i])
            return false;
    }
    return true;
}

void find_id(vector<string>& strings)
{
    for(int i=0; i<strings.size();i++)
    {
        for(int j=i+1; j<strings.size(); j++)
        {
            if(compare(strings[i],strings[j]))
            {
                cout << strings[i]<<endl<<strings[j]<<endl;
                return;
            }
        }
    }
}

int main()
{
    ifstream inputfile;
    inputfile.open("AoC2.txt");
    vector<string> strings;
    string str;
    inputfile >> str;
    while(inputfile)
    {
        strings.push_back(str);
        inputfile >> str;
    }
    find_id(strings);
    return 0;
}
