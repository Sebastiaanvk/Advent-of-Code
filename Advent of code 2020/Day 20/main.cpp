#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

const int TILES_MAX = 144;

enum dir{North, East, South, West};

struct Tile{
    int id;
    string image [8];
    string border_n, border_e, border_s, border_w;
};

ifstream& operator>>(ifstream& input, Tile& t){
    input.ignore(5);
    input >> t.id;
    input.ignore(2);
    getline(input,t.border_n);
    if(!input) return input;
    t.border_w=t.border_n.substr(0,1);
    t.border_e=t.border_n.substr(9,1);
    string s;
    for(int i=0; i<8; i++){
        getline(input,s);
        t.border_w += s.substr(0,1);
        t.image[i] = s.substr(1,8);
        t.border_e += s.substr(9,1);
    }
    getline(input,t.border_s);
    t.border_w += t.border_s.substr(0,1);
    t.border_e += t.border_s.substr(9,1);
    reverse(t.border_s.begin(),t.border_s.end());
    reverse(t.border_w.begin(),t.border_w.end());
    return input;
}

void print_tile(Tile& t){
    cout << "id: " << t.id << endl;
    cout << "north border:" << t.border_n << endl;
    cout << "east border: " << t.border_e << endl;
    cout << "south border:" << t.border_s << endl;
    cout << "west border: " << t.border_w << endl;

    for(int i=0; i<8; i++){
        cout << t.image[i] << endl;
    }
    cout << endl;
}

string reverse_string_copy(string s){
    reverse(s.begin(), s.end());
    return s;
}

int count_matching_borders(Tile& t, unordered_map<string,int>& borders){
    int sum=0;
    if( borders[reverse_string_copy(t.border_n)] + borders[t.border_n]==2 ) sum++;
    if( borders[reverse_string_copy(t.border_e)] + borders[t.border_e]==2 ) sum++;
    if( borders[reverse_string_copy(t.border_s)] + borders[t.border_s]==2 ) sum++;
    if( borders[reverse_string_copy(t.border_w)] + borders[t.border_w]==2 ) sum++;
    return sum;
}

void add_to_map(string& s, unordered_map<string,int>& borders ){
    if(borders.count(s)){
        borders[s] += 1;
    } else {
        borders[s] = 1;
    }
}

void part1(){
    ifstream input("input.txt");


    vector<Tile> tiles;
    unordered_map<string,int> borders;
    Tile t;

    input >> t;
    while(input){
//        print_tile(t);
        tiles.push_back(t);
        add_to_map(t.border_n,borders);
        add_to_map(t.border_e,borders);
        add_to_map(t.border_s,borders);
        add_to_map(t.border_w,borders);


        input >> t;
    }

    long long product = 1;
    int found=0;
    for(Tile t:tiles){
        if( count_matching_borders(t, borders) == 2){
            product *= t.id;
//            cout << t.id << endl;
        }
    }

    cout << "part1:" << product << endl;



}


void flip_tile_ns(Tile& t){
    reverse(t.border_n.begin(), t.border_n.end());
    reverse(t.border_s.begin(), t.border_s.end());
    swap(t.border_n,t.border_s);
    reverse(t.border_w.begin(), t.border_w.end());
    reverse(t.border_e.begin(), t.border_e.end());
    for(int i=0; i<4; i++){
        swap(t.image[i],t.image[7-i]);
    }
}

void flip_tile_ew(Tile& t){
    reverse(t.border_n.begin(), t.border_n.end());
    reverse(t.border_s.begin(), t.border_s.end());
    reverse(t.border_w.begin(), t.border_w.end());
    reverse(t.border_e.begin(), t.border_e.end());
    swap(t.border_e,t.border_w);
    for(int i=0; i<8; i++){
        reverse(t.image[i].begin(), t.image[i].end());
    }
}

void turn_tile_clockwise(Tile& t){
    string border_help=t.border_n;
    t.border_n=t.border_w;
    t.border_w=t.border_s;
    t.border_s=t.border_e;
    t.border_e=border_help;

    string new_image [8];
    for(int i=0; i<8; i++){
        new_image[i] = "";
        for(int j=0; j<8; j++){
            new_image[i] += t.image[7-j][i];
        }
    }
    for(int i=0;i<8; i++){
        t.image[i]=new_image[i];
    }

}

bool borders_equal(string& s1, string& s2 ){
    return s1==s2||s1==reverse_string_copy(s2);
}

void check_border(string& b, int& id, unordered_map<string, int>& borders, vector<int> pairs [TILES_MAX] ){
    if( borders.count(b) ){
        int other_id = borders[b];
        pairs[id].push_back(other_id);
        pairs[other_id].push_back(id);
    } else if ( borders.count( reverse_string_copy(b) ) ){
        int other_id = borders[  reverse_string_copy(b) ];
        pairs[id].push_back(other_id);
        pairs[other_id].push_back(id);
    } else {
        borders[b] = id;
    }
}

bool border_to_tile( string& b, Tile& t ){
    if( b==t.border_n||b==reverse_string_copy(t.border_n) ){
        return true;
    }
    if( b==t.border_e||b==reverse_string_copy(t.border_e) ){
        return true;
    }
    if( b==t.border_s||b==reverse_string_copy(t.border_s) ){
        return true;
    }
    if( b==t.border_w||b==reverse_string_copy(t.border_w) ){
        return true;
    }
    return false;
}

void turn_nw_corner_correctly(Tile& nwcorner, Tile& t1, Tile& t2){
    while( !( border_to_tile(nwcorner.border_e,t1) && border_to_tile(nwcorner.border_s,t2) ) && !( border_to_tile(nwcorner.border_e,t2) && border_to_tile(nwcorner.border_s,t1) ) ){
        turn_tile_clockwise(nwcorner);
    }
}

void add_east_row(int& row, vector<vector<int>>& config, Tile tiles [TILES_MAX], vector<int> pairs [TILES_MAX]){

    int index=config[row][0];
    for(int k=0; k<11; k++){
        int i=0;
        string eastern_border = tiles[index].border_e;
        while( !border_to_tile( eastern_border , tiles[pairs[index][i]] ) ){
            i++;
        }
        int eastern_index = pairs[index][i];
        config[row].push_back(eastern_index);
        while( !borders_equal(eastern_border,tiles[eastern_index].border_w)){
            turn_tile_clockwise( tiles[eastern_index] );
        }
        if( eastern_border==tiles[eastern_index].border_w ){
            flip_tile_ns( tiles[eastern_index] );
        }
        index=eastern_index;
    }
}

void add_south(vector<vector<int>>& config, Tile tiles [TILES_MAX], vector<int> pairs [TILES_MAX] ){
    int index=config[config.size()-1][0];

    int i=0;
    string southern_border = tiles[index].border_s;
    while( !border_to_tile( southern_border , tiles[pairs[index][i]] ) ){
        i++;
    }
    int southern_index = pairs[index][i];
    config.push_back({southern_index});
    while(!borders_equal(southern_border,tiles[southern_index].border_n)){
        turn_tile_clockwise( tiles[southern_index] );
    }
    if(southern_border==tiles[southern_index].border_n){
        flip_tile_ew( tiles[southern_index] );
    }

}

void flip_final_image(string final_image [96]){
    for(int i=0;i<48;i++){
        swap(final_image[i],final_image[95-i]);
    }
}

void turn_final_image(string final_image [96]){
    string new_image [96];
    for(int i=0; i<96; i++){
        new_image[i]="";
        for(int j=0; j<96; j++){
            new_image[i] += final_image[95-j][i];
        }
    }

    for(int i=0; i<96; i++){
        final_image[i]=new_image[i];
    }
}

bool seamonster_on_loc(string final_image [96], string sea_monster [3], int& row, int& col){
    for(int drow=0; drow<3; drow++){
        for(int dcol=0; dcol<20; dcol++){
            if(sea_monster[drow][dcol]=='#'&&final_image[row+drow][col+dcol]!='#'){
                return false;
            }
        }
    }
    return true;
}

int count_seamonsters( string final_image [96], string sea_monster [3]){
    int sum=0;
    for(int row=0; row+2<96; row++){
        for(int col=0; col+19<96; col++){
            if( seamonster_on_loc(final_image, sea_monster, row, col) ){
                sum++;
            }
        }
    }
    return sum;
}

void part2(){
    ifstream input("input.txt");

    unordered_map<string,int> borders;
    Tile tiles [TILES_MAX];
    vector<int> pairs [TILES_MAX]= {{}};
    Tile t;
    int count_tiles=0;

    input >> t;
    while(input){

//        print_tile(t);
        t.id=count_tiles;
        tiles[t.id] = t;

        check_border(t.border_n, t.id, borders, pairs);
        check_border(t.border_e, t.id, borders, pairs);
        check_border(t.border_s, t.id, borders, pairs);
        check_border(t.border_w, t.id, borders, pairs);

        count_tiles++;
        input >> t;
    }

    int nw_ind=0;
    while(pairs[nw_ind].size()!=2){
        nw_ind++;
    }

    turn_nw_corner_correctly( tiles[nw_ind], tiles[pairs[nw_ind][0]], tiles[pairs[nw_ind][1]] );
    vector< vector<int> > config;
    config.push_back({nw_ind});
    for(int i=1; i<12; i++){
        add_south(config, tiles, pairs);
    }

    for(int i=0; i<12; i++){
        add_east_row(i,config,tiles,pairs);
    }
    /*
    for(int i=0; i<12; i++){
        for(int j=0; j<12; j++){
            cout << tiles[ config[i][j] ].border_w << " " << tiles[ config[i][j] ].border_e << " ";
        }
        cout << endl;
    }*/
    string final_image [96];
    for(int big_row=0; big_row<12; big_row++){
        for(int row=0; row<8; row++ ){
                final_image[8*big_row+row] = "";
            }
        for(int x=0;x<12;x++){
            for(int row=0; row<8; row++ ){
                final_image[8*big_row+row] += tiles[ config[big_row][x] ].image[row];
            }
        }
    }
    int total_hashtag=0;
    for(int i=0;i<96; i++){
        for(int j=0; j<96; j++){
//            cout << final_image[i][j];
            if(final_image[i][j]=='#'){
                total_hashtag++;
            }
        }
//        cout << endl;
    }
//    cout << "Total hashtag: " << total_hashtag << endl;
    string seamonster [3] = {   "..................#.",
                                "#....##....##....###",
                                ".#..#..#..#..#..#..."};
    int seamonsters = count_seamonsters(final_image,seamonster);
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        flip_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    if(seamonsters==0){
        turn_final_image(final_image);
        seamonsters = count_seamonsters(final_image,seamonster);
    }
    cout << "part2: " << total_hashtag-15*seamonsters << endl;
}

int main()
{
    part1();
    part2();
    return 0;
}
