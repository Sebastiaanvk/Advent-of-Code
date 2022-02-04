#include <iostream>
#include <deque>
#include <fstream>
#include <set>
#include <unordered_set>

using namespace std;

void load_input(deque<int>& d, ifstream& input){
    string s;
    getline(input,s);
    getline(input,s);
    while(input&&s!=""){
        cout << s << endl;
        d.push_back(stoi(s));
        getline(input,s);
    }
}

long long calc_score(deque<int>& deck){
    long long score=0;
    int i=1;
    while(deck.size()>0){
        score += i*deck.back();
        deck.pop_back();
        i++;
    }
    return score;
}

void part1(){
    deque<int> deck1;
    deque<int> deck2;
    ifstream input("input.txt");
    load_input(deck1, input);
    cout << endl;
    load_input(deck2, input);

    while(deck1.size()>0&&deck2.size()>0){
        int card1 = deck1.front();
        int card2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();
        if(card1>card2){
            deck1.push_back(card1);
            deck1.push_back(card2);
        } else {
            deck2.push_back(card2);
            deck2.push_back(card1);
        }
    }
    if(deck1.size()==0){
        cout << "part1: " << calc_score(deck2) << endl;
    } else {
        cout << "part1: " << calc_score(deck1) << endl;
    }
}

string deq_to_str(deque<int>& d1, deque<int>& d2){
    string s = "";
    for(auto x:d1) s += to_string(x) + ",";
    s+="&&";
    for(auto x:d2) s+=to_string(x) + ",";
    return s;
}


bool sub_game(deque<int>& old_deck1, int& length1, deque<int>& old_deck2, int& length2){
    deque<int> deck1;
    int m=0;
    int m_in_1 = false;
    for(int i=0; i<length1; i++) {
        deck1.push_back( old_deck1[i] );
        if(old_deck1[i]>m){
            m=old_deck1[i];
            m_in_1=true;
        }
    }
    deque<int> deck2;
    for(int i=0; i<length2; i++) {
        deck2.push_back( old_deck2[i] );
        if(old_deck2[i]>m){
            m=old_deck2[i];
            m_in_1=false;
        }
    }
    if(m_in_1){
        return true;
    }
    set<string> configs;
    while(deck1.size()>0&&deck2.size()>0){
        string s = deq_to_str(deck1, deck2);
//        cout << s << endl;
        if( configs.count(s) ){
            return true;
        } else {
            configs.insert(s);
        }
        int card1 = deck1.front();
        int card2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();
        if( card1>deck1.size() || card2>deck2.size()){
            if(card1>card2){
                deck1.push_back(card1);
                deck1.push_back(card2);
            } else {
                deck2.push_back(card2);
                deck2.push_back(card1);
            }
        } else {

            if( sub_game(deck1, card1, deck2, card2) ){
                deck1.push_back(card1);
                deck1.push_back(card2);
            } else {
                deck2.push_back(card2);
                deck2.push_back(card1);
            }
        }
    }

    if(deck2.size()==0){
        return true;
    } else {
        return false;
    }


}

void part2(){
    deque<int> deck1;
    deque<int> deck2;
    ifstream input("input.txt");
    load_input(deck1, input);
    cout << endl;
    load_input(deck2, input);
    set< string > game1_configs;
    while(deck1.size()>0&&deck2.size()>0){
        string s = deq_to_str(deck1, deck2);
        cout << s << endl;
        if(game1_configs.count(s)){
            cout << "part2: " << calc_score(deck1) << endl;
            return;
        } else {
            game1_configs.insert(s);
        }
        int card1 = deck1.front();
        int card2 = deck2.front();
        deck1.pop_front();
        deck2.pop_front();
        if( card1>deck1.size() || card2>deck2.size()){
            if(card1>card2){
                deck1.push_back(card1);
                deck1.push_back(card2);
            } else {
                deck2.push_back(card2);
                deck2.push_back(card1);
            }
        } else {
            if( sub_game(deck1, card1, deck2, card2) ){
                deck1.push_back(card1);
                deck1.push_back(card2);
            } else {
                deck2.push_back(card2);
                deck2.push_back(card1);
            }
        }
    }
    if(deck2.size()==0){
        cout << "part2: " << calc_score(deck1) << endl;
    } else {
        cout << "part2: " << calc_score(deck2) << endl;
    }
}

int main()
{
//    part1();
    part2();
    return 0;
}
