#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Criterium{
    int a1;
    int b1;
    int a2;
    int b2;
};

struct Ticket{
    int arr [20];
};

ifstream& operator>>(ifstream& input, Ticket& t){
    input >> t.arr[0];
    char c;
    for(int i=1; i<20; i++){
        input >> c;
        input >> t.arr[i];
    }
    return input;
}

vector<Criterium> read_criteria(ifstream& input){
    char c;
    string s;
    int a1, b1, a2, b2;
    vector<Criterium> criteria;
    for(int i=0; i<10; i++){
        input >> s >> s >> a1 >>c>>b1 >> s >> a2 >> c >>b2;
        criteria.push_back({a1,b1,a2,b2});
    }
    for(int i=0; i<10; i++){
        input >>  s >> a1 >>c>>b1 >> s >> a2 >> c >>b2;
        criteria.push_back({a1,b1,a2,b2});
    }
    return criteria;
}

bool value_in_range(int& v, Criterium& c){
    return (c.a1<=v&&v<=c.b1)||(c.a2<=v&&v<=c.b2);
}


bool value_valid(int& v, vector<Criterium>& criteria){
    for(auto c:criteria){
        if( value_in_range(v,c) ){
            return true;
        }
    }

    return false;
}

int ticket_error(Ticket& t, vector<Criterium>& criteria){
    int sum = 0;
    for(int i=0; i<20; i++){
        if( !value_valid(t.arr[i],criteria) ){
            sum +=t.arr[i];
        }
    }
    return sum;
}

void part1(){
    ifstream input("input.txt");
    vector<Criterium> criteria = read_criteria(input);

    Ticket t;
    string s;
    input >> s >> s;
    input >> t;
    long long sum = ticket_error(t, criteria);
    input >> s >> s;
    input >> t;
    while(input){
        sum += ticket_error(t, criteria);
        input >> t;
    }
    cout << "Part1: " << sum << endl;

}

bool ticket_valid(Ticket& t, vector<Criterium>& criteria){
    for(int i=0; i<20; i++){
        if(!value_valid(t.arr[i],criteria)){
            return false;
        }
    }
    return true;
}

int count_bool(bool pos_fields [20] [20], int& row){
    int sum=0;
    for(int i=0; i<20; i++){
        if( pos_fields[row][i] ) sum++;
    }
    return sum;
}

vector<int> fix( bool pos_fields [20] [20]  ){
    vector<int> v;
    for(int i=0; i<20; i++) v.push_back(-1);

    for(int i=0; i<20; i++){
        int j=0;
        while( !( v[j]==-1 && count_bool(pos_fields,j)==1 ) ){
            j++;
        }
        int col=0;
        while( !pos_fields[j][col] ){
            col++;
        }
        v[j]=col;
        cout << j << endl;
        for(int k=0; k<20; k++) pos_fields[k][col] = false;
    }
    return v;
}

void part2(){
    ifstream input("input.txt");
    vector<Criterium> criteria = read_criteria(input);

    Ticket t;
    vector<Ticket> valid_tickets;
    string s;
    input >> s >> s;
    input >> t;
    valid_tickets.push_back(t);
    input >> s >> s;
    input >> t;

    while(input){
        if( ticket_valid(t, criteria) )
            valid_tickets.push_back(t);
        input >> t;
    }

    bool field_possible [20] [20];

    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++) field_possible[i][j]=true;
    }
    for(Ticket t:valid_tickets){
        for(int c_ind=0; c_ind<20; c_ind++){
            for(int t_ind=0; t_ind<20; t_ind++){
                if( !value_in_range(t.arr[t_ind],criteria[c_ind]) ){
                    field_possible[c_ind][t_ind]=false;
                }
            }

        }
    }
    for(int row=0; row<20; row++){
        for(int col=0; col<20; col++){
            cout << field_possible[row][col];
        }
        cout << endl;
    }

    vector<int> correct_indices = fix(field_possible);

    for(int row=0; row<20; row++){
        for(int col=0; col<20; col++){
            cout << field_possible[row][col];
        }
        cout << endl;
    }

    long long prod = 1;
    for(int i=0;i<6;i++){
        prod*=valid_tickets[0].arr[correct_indices[i]];
    }

    cout << "Part2: " << prod << endl;

}

int main()
{
    part1();
    part2();
    return 0;
}
