#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

struct Password{
    string password;
    char letter;
    int min_occur;
    int max_occur;
};

ifstream& operator>>(ifstream& input, Password& p ){
    input >> p.min_occur;
    char c;
    input.get(c);
    input >> p.max_occur;
    input.get(c);
    input.get(p.letter);
//    input.get(c);
    input.get(c);
    input >> p.password;
}


int main()
{
    ifstream input("input.txt");
    vector<Password> v;
    Password p;
    input >> p;
    int track = 0;
    int track2 = 0;
    while(input){
        v.push_back(p);
        int count_letter = 0;
        for(int i=0; i<p.password.size()&&count_letter<=p.max_occur;i++){
            if(p.password[i]==p.letter){
                count_letter++;
            }
        }
        if(count_letter>=p.min_occur&&count_letter<=p.max_occur){
            track++;
        }
        if( ( p.min_occur-1<p.password.size()&&p.password[p.min_occur-1]==p.letter ) != ( p.max_occur-1<p.password.size()&&p.password[p.max_occur-1]==p.letter ) ){
            track2++;
        }


        input >> p;
    }
    cout << "The answer to part 1 is: " << track << endl;
    cout << "The answer to part 2 is: " << track2 << endl;

    return 0;
}
