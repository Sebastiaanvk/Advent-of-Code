#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>


using namespace std;

int bags_inside(int index, unordered_map<string, int>& bag_indices, vector<vector<string>>& bag_contains, vector<vector<int>>& bag_quantities, vector<int>& nr_bags ){
    if(nr_bags[index]!=-1){
        return nr_bags[index];
    }
    int bags = 0;
    for(int i=0; i<bag_contains[index].size(); i++){
        bags += bag_quantities[index][i]*(1+bags_inside( bag_indices[ bag_contains[index][i] ], bag_indices, bag_contains, bag_quantities, nr_bags) );
    }
    nr_bags[index]=bags;
    return bags;

}


int main()
{
    vector<vector<string>> bag_contains;
    unordered_map<string, int> bag_indices;
    vector<bool> contains_gold;
    vector<vector<int>> bag_quantities;
    vector<int> nr_bags;

    ifstream input("input.txt");
    string line_str;
    getline(input,line_str);
    int index_bag=0;
    while(input){
        istringstream line (line_str);
        string adj;
        string color;
        string throwaway;
        line >> adj;
        line >> color;
        bag_indices[adj+color] = index_bag;
//        cout << adj+color << " contains:\n";
        contains_gold.push_back(false);

        line >> throwaway;
        line >> throwaway;

        vector<string> v;
        vector<int> v2;

        int x;
        line >> x;
        line >> adj;
        line >> color;
        line >> throwaway;
        while(line){
//            cout << adj+color << endl;
            v.push_back(adj+color);
            v2.push_back(x);
            line >> x;
            line >> adj;
            line >> color;
            line >> throwaway;
        }
//        cout << endl;
        bag_contains.push_back(v);
        bag_quantities.push_back(v2);
        nr_bags.push_back(-1);
        index_bag++;
        getline(input, line_str);
    }
    int gold_index = bag_indices["shinygold"];
    contains_gold[gold_index]=true;

    bool change=true;
    while(change){
        change = false;
        for(int i=1; i<bag_contains.size(); i++){
            if( !contains_gold[i] ){
                for(auto s:bag_contains[i]){
//                    cout << s << endl;
                    if( contains_gold[ bag_indices[s] ] ){
                        contains_gold[i]=true;
                        change=true;
                    }
                }
            }
//            cout << endl;
        }
    }

    int total = 0;

    for(int i=1; i<contains_gold.size(); i++){
        if( contains_gold[i] ){
            total++;
        }
    }
    if(contains_gold[ bag_indices["shinygold"] ]){
        total--;
    }

    cout << "Answer to part 1: " << total << endl;

    cout << "Answer to part 2: " << bags_inside( bag_indices["shinygold"], bag_indices, bag_contains, bag_quantities, nr_bags) << endl;

    return 0;
}
