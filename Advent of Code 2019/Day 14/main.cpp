#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>

using namespace std;

struct Ore_with_amount{
    long long id;
    long long amount;
};

long long ore_id;

long long ores_needed(const long long& chemical_id, const long long& amount, vector<long long>& chemicals_left_over, vector< pair<list<Ore_with_amount>,long long> >& trades){
    if(chemical_id==ore_id){
        return amount;
    }
    long long chemical_needed = max(0LL,amount - chemicals_left_over[chemical_id]);
    long long nr_of_trades;
    if(chemical_needed==0) nr_of_trades = 0;
    else nr_of_trades = ( (chemical_needed-1)/trades[chemical_id].second)+1;
    long long ores=0;
    if(nr_of_trades!=0){
        for(list<Ore_with_amount>::iterator it=trades[chemical_id].first.begin(); it!=trades[chemical_id].first.end(); it++){
            Ore_with_amount owa = *it;
            ores += ores_needed(owa.id, owa.amount*nr_of_trades, chemicals_left_over, trades);


        }
    }
    chemicals_left_over[chemical_id] += nr_of_trades*trades[chemical_id].second-amount;
    return ores;
}

void part1(){
    ifstream input("input.txt");
    long long nr_ores = 0;
    map<string, long long> ore_to_number;
    vector< pair<list< Ore_with_amount>,long long> > trades;
    string line;
    getline(input,line);
    while(input){
        stringstream str_line(line);
        list<Ore_with_amount> current_list;
        long long x;
        string s;
        str_line >> x;
        str_line >> s;
        while(s[s.size()-1]==','){
            s.pop_back();
            if( ore_to_number.count(s)==0 ){
                ore_to_number[s]=nr_ores;
                nr_ores++;
                trades.resize(nr_ores);
            }
            current_list.push_back( {ore_to_number[s],x} );
            str_line >> x;
            str_line >> s;
        }
        if( ore_to_number.count(s)==0 ){
            ore_to_number[s]=nr_ores;
            nr_ores++;
            trades.resize(nr_ores);
        }
        current_list.push_back( {ore_to_number[s],x} );

        str_line >> s;
        str_line >> x;
        str_line >> s;
        if( ore_to_number.count(s)==0 ){
            ore_to_number[s]=nr_ores;
            nr_ores++;
            trades.resize(nr_ores);
        }
        trades[ore_to_number[s] ] = {current_list,x};
        getline(input,line);
    }

    long long fuel_id = ore_to_number["FUEL"];
    ore_id = ore_to_number["ORE"];
    vector<long long> ores_left_over (nr_ores,0);
    long long on = ores_needed(fuel_id, 1,  ores_left_over, trades);
    cout << on<< endl;
}

long long ores_needed2(const long long& chemical_id, const long long& amount, vector<long long>& chemicals_left_over, vector< pair<list<Ore_with_amount>,long long> >& trades, long long& ore_left){
    if(chemical_id==ore_id){
        ore_left -= amount;
        return amount;
    }
    long long chemical_needed = max(0LL,amount - chemicals_left_over[chemical_id]);
    long long nr_of_trades;
    if(chemical_needed==0) nr_of_trades = 0;
    else nr_of_trades = ( (chemical_needed-1)/trades[chemical_id].second)+1;
    long long ores=0;
    if(nr_of_trades!=0){
        for(list<Ore_with_amount>::iterator it=trades[chemical_id].first.begin(); it!=trades[chemical_id].first.end(); it++){
            Ore_with_amount owa = *it;
            ores += ores_needed2(owa.id, owa.amount*nr_of_trades, chemicals_left_over, trades, ore_left);


        }
    }
    chemicals_left_over[chemical_id] += nr_of_trades*trades[chemical_id].second-amount;
    return ores;
}

void part2(){
    ifstream input("input.txt");
    long long nr_ores = 0;
    map<string, long long> ore_to_number;
    vector< pair<list< Ore_with_amount>,long long> > trades;
    string line;
    getline(input,line);
    while(input){
        stringstream str_line(line);
        list<Ore_with_amount> current_list;
        long long x;
        string s;
        str_line >> x;
        str_line >> s;
        while(s[s.size()-1]==','){
            s.pop_back();
            if( ore_to_number.count(s)==0 ){
                ore_to_number[s]=nr_ores;
                nr_ores++;
                trades.resize(nr_ores);
            }
            current_list.push_back( {ore_to_number[s],x} );
            str_line >> x;
            str_line >> s;
        }
        if( ore_to_number.count(s)==0 ){
            ore_to_number[s]=nr_ores;
            nr_ores++;
            trades.resize(nr_ores);
        }
        current_list.push_back( {ore_to_number[s],x} );

        str_line >> s;
        str_line >> x;
        str_line >> s;
        if( ore_to_number.count(s)==0 ){
            ore_to_number[s]=nr_ores;
            nr_ores++;
            trades.resize(nr_ores);
        }
        trades[ore_to_number[s] ] = {current_list,x};
        getline(input,line);
    }

    long long fuel_id = ore_to_number["FUEL"];
    ore_id = ore_to_number["ORE"];
    vector<long long> ores_left_over (nr_ores,0);
    long long ore_left = 1000000000000;
    //i just estimated this by trial and error
    // not very elegant
    long long fuel_estimate = 3650000;
    long long fuel = fuel_estimate-1;
    ores_needed2(fuel_id, fuel_estimate,  ores_left_over, trades, ore_left);
    while(ore_left>=0){
        ores_needed2(fuel_id, 1,  ores_left_over, trades, ore_left);
        //cout << ore_left << endl;
        fuel++;
    }
    cout << fuel << endl;
}

int main()
{
    part2();
    return 0;
}
