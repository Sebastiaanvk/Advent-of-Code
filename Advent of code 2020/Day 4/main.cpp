#include <iostream>
#include <vector>
#include <fstream>
#include <strstream>


using namespace std;

bool correct_char(string s){
    for(int i=0; i<s.size(); i++){
        char c = s[i];
        if(! ( (c>='0'&&c<='9') || (c>='a'&&c<='f') ) ){
            return false;
        }
    }
    return true;
}

bool only_digits(string s){
    for(int i=0; i<s.size(); i++){
        char c = s[i];
        if(! (c>='0'&&c<='9') ){
            return false;
        }
    }
    return true;
}


int main()
{
    ifstream input("input.txt");
    int track = 0;
    int valid_fields = 0;
    string s;
    getline(input,s);
    while(input){
        if(s==""){
            if(valid_fields>=7) track++;
            valid_fields = 0;
        } else {
            for(int i=3; i<s.size(); i++){
                if( s[i]==':'){
                    string field = s.substr(i-3,3);
                    if( field=="byr" && i+4<s.size() && ( i+5==s.size() || s[i+5]==' ') ){
                        int x = stoi(s.substr(i+1,4));
                        if(x>=1920&&x<=2002) valid_fields+=1;
                    } else if(field=="iyr"&&i+4<s.size()&&( i+5==s.size()||s[i+5]==' ') ){
                        int x = stoi(s.substr(i+1,4));
                        if(x>=2010&&x<=2020) valid_fields+=1;
                    } else if(field=="eyr"&&i+4<s.size()&&( i+5==s.size()||s[i+5]==' ') ){
                        int x = stoi(s.substr(i+1,4));
                        if(x>=2020&&x<=2030) valid_fields+=1;
                    } else if(field=="hgt"){
                        if( i+6==s.size()||s[i+6]==' ' ){
                            if(s[i+4]=='c'&&s[i+5]=='m'){
                                int x = stoi(s.substr(i+1,3));
                                if(x>=150&&x<=193){
                                    valid_fields++;
                                }
                            }
                        } else if (i+5==s.size()||s[i+5]==' '){
                            if(s[i+3]=='i'&&s[i+4]=='n'){
                                int x = stoi(s.substr(i+1,2));
                                if(x>=59&&x<=76){
                                    valid_fields++;
                                }
                            }
                        }

                    } else if(field=="hcl"&&i+7<s.size()&&( i+8==s.size()||s[i+8]==' ')&&s[i+1]=='#' ){
                        if( correct_char(s.substr(i+2,6)) ){
                            valid_fields++;

                        }
                    } else if(field=="ecl"&&i+3<s.size()&&( i+4==s.size()||s[i+4]==' ') ){
                        string sub = s.substr(i+1,3);
                        if(sub=="amb"||sub== "blu"||sub== "brn"||sub== "gry"||sub== "grn"||sub== "hzl"||sub== "oth") valid_fields++;
                    } else if(field=="pid"&&i+9<s.size()&&( i+10==s.size()||s[i+10]==' ')&&only_digits(s.substr(i+1,9)) ){
                        valid_fields++;

                    }
                }

            }
        }
        getline(input,s);
    }
    if(valid_fields==7) track++;

    cout << track << endl;
    return 0;
}
