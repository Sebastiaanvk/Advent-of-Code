#include <iostream>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include <vector>

using namespace std;

bool PART2=true;

struct BingoCard{
    int card [5][5];
    bool still_in;
};

istream& operator>>(istream& in, BingoCard& card){
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++){
            in >> card.card[y][x];
        }
    }
    card.still_in=true;
    return in;
}

bool row_bingo( const int card[5][5], const int& y,const unordered_set<int>& number_in ){
    for(int x=0;x<5; x++){
        if(number_in.count(card[y][x])==0)
            return false;
    }
    return true;
}

bool column_bingo( const int card[5][5], const int& x,const unordered_set<int>& number_in ){
    for(int y=0;y<5; y++){
        if(number_in.count(card[y][x])==0)
            return false;
    }
    return true;
}

int calc_score(const int card [5][5], unordered_set<int>& number_in){
    int sum=0;
    for(int y=0; y<5; y++){
        for(int x=0; x<5; x++){
            if(number_in.count(card[y][x])==0){
                sum+=card[y][x];
            }
        }
    }
    return sum;
}

int first_bingo(const vector<BingoCard>& cards, const vector<int>& numbers){
    unordered_set<int> number_in;
    for( int i=0; i<numbers.size(); i++){
        number_in.insert(numbers[i]);
        for(int j=0; j<cards.size(); j++){
            for(int y=0; y<5; y++){
                for(int x=0;x<5; x++){
                    if(cards[j].card[y][x]==numbers[i]){
                        if(row_bingo( cards[j].card, y, number_in)||column_bingo(cards[j].card, x, number_in)){
                            return numbers[i]*calc_score(cards[j].card,number_in);
                        }
                    }
                }
            }

        }
    }
    return -1;
}

int last_bingo(vector<BingoCard>& cards, const vector<int>& numbers){
    unordered_set<int> number_in;
    int last_bingo_value;
    for( int i=0; i<numbers.size(); i++){
        number_in.insert(numbers[i]);
        for(int j=0; j<cards.size(); j++){
            if(cards[j].still_in){
                for(int y=0; y<5; y++){
                    for(int x=0;x<5; x++){
                        if(cards[j].card[y][x]==numbers[i]){
                            if(row_bingo( cards[j].card, y, number_in)||column_bingo(cards[j].card, x, number_in)){
                                cards[j].still_in=false;
                                last_bingo_value = numbers[i]*calc_score(cards[j].card,number_in);
                            }
                        }
                    }
                }
            }

        }
    }
    return last_bingo_value;
}

void part1(){
    ifstream input("input.txt");

    vector<int> numbers;
    string s;
    getline(input,s);
    stringstream ss(s);
    int x;
    ss >> x;
    while(ss){
        numbers.push_back(x);
        cout << x << endl;
        ss.ignore(1);
        ss >> x;
    }

    vector<BingoCard> cards;
    BingoCard card;
    input >> card;
    while(input){
        cards.push_back(card);
        input >> card;
    }
    if(!PART2)cout << first_bingo(cards, numbers) << endl;
    else cout << last_bingo(cards, numbers) << endl;

}



int main()
{
    part1();
    return 0;
}
