#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main()
{
    fstream input("input.txt");
//    vector<string> forest;
    string s;
    input >> s;
    long long track1 = 0;
    int track3 = 0;
    int track5 = 0;
    int track7 = 0;
    int track2 = 0;
    int width = s.size();
    int layer = 0;
    while(input){
//        forest.push_back(s);
        if( s[layer%width]=='#' ) track1++;
        if( s[(layer*3)%width]=='#' ) track3++;
        if( s[(layer*5)%width]=='#' ) track5++;
        if( s[(layer*7)%width]=='#' ) track7++;
        if( layer%2==0&&s[(layer/2)%width]=='#' ) track2++;
//        cout << s << endl;
        input >> s;
        layer++;
    }

    cout << track1*track3*track5*track7*track2 << endl;
    return 0;
}
