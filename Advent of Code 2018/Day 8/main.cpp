#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum_metadata_next_node(ifstream& input){
    int nr_nodes;
    int nr_meta_data;
    input>>nr_nodes>>nr_meta_data;
    int total=0;
    for(int i=0;i<nr_nodes;i++){
        total+=sum_metadata_next_node(input);
    }
    int x;
    for(int i=0;i<nr_meta_data;i++){
        input>>x;
        total+=x;
    }
    return total;
}

void part1(){
    ifstream input("input.txt");

    cout << "Part1: " << sum_metadata_next_node(input);

}

int next_node_value(ifstream& input){
    int nr_nodes;
    int nr_meta_data;
    input>>nr_nodes>>nr_meta_data;
    int total=0;
    if(nr_nodes==0){
        int x;
        for(int i=0;i<nr_meta_data;i++){
            input>>x;
            total+=x;
        }
        return total;
    }
    vector<int> value_children;
    for(int i=0;i<nr_nodes;i++){
        value_children.push_back( next_node_value(input) );
    }
    int x;
    for(int i=0;i<nr_meta_data;i++){
        input>>x;
        if( x>0&&x<=nr_nodes ) total+=value_children[x-1];
    }
    return total;
}

void part2(){
    ifstream input("input.txt");

    cout << "Part2: " << next_node_value(input);

}

int main()
{
    part2();
    return 0;
}
