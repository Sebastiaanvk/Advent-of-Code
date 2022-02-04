#include <iostream>
#include <list>
#include <fstream>
#include <vector>

using namespace std;

void reduce_number(list<int>& number){
    bool reduction_found=true;
    while(reduction_found){
        reduction_found=false;
        int depth = 0;
        for(list<int>::iterator it=number.begin(); it!=number.end(); it++){
            if(*it==-1){
                depth++;
            } else if(*it==-2){
                depth--;
            }
            if(depth==5){
                reduction_found = true;
                list<int>::iterator it2;
                for( it2=prev(it) ;it2!=number.begin(); it2-- ){
                    if(*it2!=-1&&*it2!=-2){
                        *it2 += *(next(it));
                        break;
                    }
                }
                it2=it;
                advance(it2,4);
                for(;it2!=number.end();it2++){
                    if(*it2!=-1&&*it2!=-2){
                        *it2+=*(next(it,2));
                        break;
                    }
                }
                number.insert(next(it,4),0);
                number.erase(it,next(it,4));
                depth--;
                break;
            }
        }

        if(!reduction_found){
            for(list<int>::iterator it=number.begin();it!=number.end();it++){
                if(*it>=10){
                    reduction_found = true;
                    int x = *it;
                    *it=-1;
                    it++;
                    number.insert(it, x/2);
                    number.insert(it,(x+1)/2);
                    number.insert(it,-2);
                    break;
                }
            }
        }
    }
}

void print_number_it(list<int>::iterator& it){
    if(*it>=0){
        cout << *it;
        it++;
    } else {
        cout << '[';
        it++;
        print_number_it(it);
        cout << ',';
        print_number_it(it);
        cout << ']';
        it++;
    }
}

void print_number(list<int>& number){
    list<int>::iterator it = number.begin();
    print_number_it(it);
    cout << endl;
}

list<int> read_number(string s){
    list<int> number;
    for(int i=0;i<s.size(); i++){
        if(s[i]=='['){
            number.push_back(-1);
        } else if(s[i]==']'){
            number.push_back(-2);
        } else if(s[i]!=','){
            number.push_back(s[i]-'0');
        }
    }
    return number;
}

int calc_magnitude_it(list<int>::iterator& it){
    if(*it>=0){
        return *(it++);
    } else {
        int sum=0;
        //it++;
        sum+=3*calc_magnitude_it(++it);
        sum+=2*calc_magnitude_it(it);
        it++;
        return sum;
    }
}

int calc_magnitude(list<int>& number){
    list<int>::iterator it = number.begin();
    return calc_magnitude_it(it);
}

void part1(){
    ifstream input("input.txt");
    string s;
    input >> s;
    list<int> number = read_number(s);
    input >> s;
    while(input){
        list<int> new_number = read_number(s);
        number.push_front(-1);
        number.insert(number.end(),new_number.begin(),new_number.end());
        number.push_back(-2);
        reduce_number(number);
        input >> s;
    }
    cout << "Part1: " << calc_magnitude(number) << endl;
    //print_number(number);
}

void part2(){
    ifstream input("input.txt");
    string s;
    vector<list<int>> v;
    input >> s;
    while(input){
        list<int> number = read_number(s);
        v.push_back(number);
        input >> s;
    }
    int maxi=0;
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v.size();j++){
            if(i!=j){
                list<int> number = v[i];
                number.push_front(-1);
                number.insert(number.end(),v[j].begin(),v[j].end());
                number.push_back(-2);
                reduce_number(number);
                maxi = max(maxi,calc_magnitude(number));
            }
        }
    }
    cout << "Part2: " << maxi << endl;
}


int main()
{
    part1();
    part2();
    return 0;
}
