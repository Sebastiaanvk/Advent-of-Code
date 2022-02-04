#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void part1(){
    ifstream input("input.txt");
    vector<char> image;
    char c;
    input>>c;
    while(input){
        image.push_back(c);

        input>> c;
    }

    int max_0 = INT_MAX;
    int max_layer;

    for(int i=0; i+149<image.size(); i+=150){
        int nr_0=0;
        for(int j=0; j<150; j++){
            if(image[i+j]=='0'){
                nr_0++;
            }
        }
        if(nr_0<max_0){
            max_0=nr_0;
            max_layer=i/150;
        }
    }
    int nr_1=0;
    int nr_2=0;
    for( int i=0; i<150; i++ ){
        cout << i << endl;
        if( image[150*max_layer+i]=='1' ) nr_1++;
        else if( image[150*max_layer+i]=='2' ) nr_2++;
    }
    cout << nr_1*nr_2 << endl;
}

void part2(){
    ifstream input("input.txt");
    vector<char> image;
    char c;
    input>>c;
    while(input){
        image.push_back(c);

        input>> c;
    }
    for(int y=0; y<6; y++){
        for(int x=0;x<25; x++){
            int layer=0;
            while(image[x+25*y+150*layer]=='2'){
                layer++;
            }
            if(image[x+25*y+150*layer]=='0'){
                cout << " ";
            } else {
                cout << "*";
            }
        }
        cout << endl;
    }
}

int main()
{
    part2();
    return 0;
}
