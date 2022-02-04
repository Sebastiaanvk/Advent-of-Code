#include <iostream>
#include <fstream>


using namespace std;


int main()
{
    ifstream input("input.txt");
    int questions [26]={0};
    string s;
    int total = 0;
    while(input){
        int group_size = 0;
        getline(input, s);
        while( input&&s!="" ){
            group_size++;
            for(int i=0; i<s.size(); i++){
                questions[ s[i]-'a' ] += 1;
            }
            getline(input, s);
        }
        for(int i=0;i<26;i++){
            if( questions[i]==group_size ){
                total++;
            }
            questions[i]=0;
        }

    }
    cout << total << endl;
    return 0;
}
