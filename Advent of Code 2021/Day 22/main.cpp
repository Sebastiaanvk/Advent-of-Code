#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

void part1(){
    ifstream input("input.txt");
    bool arr[101][101][101] = {{{false}}};
    string s;
    input >> s;
    while(input){
        int in[6];
        input.ignore(3);input>>in[0];input.ignore(2);input>>in[1];input.ignore(3);
        input>>in[2];input.ignore(2);input>>in[3];input.ignore(3);
        input>>in[4];input.ignore(2);input>>in[5];
//        cout << s << " ";
//        for(int i=0; i<6; i++) cout << in[i] << " ";
//        cout << endl;
        for( int x=max(-50,in[0]); x<=min(50,in[1]);x++ )
            for( int y=max(-50,in[2]); y<=min(50,in[3]);y++ )
                for( int z=max(-50,in[4]); z<=min(50,in[5]);z++ )
                    arr[x+50][y+50][z+50] =(s=="on");

        input >> s;
        }
    int total = 0;
    for(int i=0;i<101;i++) for(int j=0;j<101;j++) for(int k=0;k<101;k++) if(arr[i][j][k]) total++;
    cout << "Part1: " << total << endl;
}

struct Box{
    long long min_x,max_x,min_y,max_y,min_z,max_z;
};

bool overlap(const Box& b, const Box& c){
    return      b.min_x<=c.max_x&&b.max_x>=c.min_x
            &&  b.min_y<=c.max_y&&b.max_y>=c.min_y
            &&  b.min_z<=c.max_z&&b.max_z>=c.min_z;
}

void break_overlap(list<Box>& boxlist, const Box& b){
    list<Box>::iterator it = boxlist.begin();
    while(it!=boxlist.end()){
        Box c = *it;
        if( overlap(c,b) ){
            it = boxlist.erase(it);
            if(c.min_x<b.min_x){
                boxlist.insert(it,{c.min_x,b.min_x-1,c.min_y,c.max_y,c.min_z,c.max_z});
            }
            if(c.max_x>b.max_x){
                boxlist.insert(it,{b.max_x+1,c.max_x,c.min_y,c.max_y,c.min_z,c.max_z});
            }
            long long min_x=max(c.min_x,b.min_x);
            long long max_x=min(c.max_x,b.max_x);
            if(c.min_y<b.min_y){
                boxlist.insert(it,{min_x,max_x,c.min_y,b.min_y-1,c.min_z,c.max_z});
            }
            if(c.max_y>b.max_y){
                boxlist.insert(it,{min_x,max_x,b.max_y+1,c.max_y,c.min_z,c.max_z});
            }
            long long min_y=max(c.min_y,b.min_y);
            long long max_y=min(c.max_y,b.max_y);
            if(c.min_z<b.min_z){
                boxlist.insert(it,{min_x,max_x,min_y,max_y,c.min_z,b.min_z-1});
            }
            if(c.max_z>b.max_z){
                boxlist.insert(it,{min_x,max_x,min_y,max_y,b.max_z+1,c.max_z});
            }
        } else {
            it++;
        }
    }
}

void part2(){
    ifstream input("input.txt");
    list<Box> boxlist;
    string s;
    input >> s;
    while(input){
        Box b;
        input.ignore(3);input>>b.min_x;input.ignore(2);input>>b.max_x;input.ignore(3);
        input>>b.min_y;input.ignore(2);input>>b.max_y;input.ignore(3);
        input>>b.min_z;input.ignore(2);input>>b.max_z;
//        cout << b.min_x << " " << b.max_x << endl;
//        cout << b.min_z << " " << b.max_z << endl;
        break_overlap(boxlist,b);
        if(s=="on") boxlist.push_back(b);
//        for(Box b:boxlist){
//            printf(" %lld..%lld,%lld..%lld,%lld..%lld\n",b.min_x,b.max_x,b.min_y,b.max_y,b.min_z,b.max_z);
//        }
//        cout << endl;
        input >> s;
        }
    long long total = 0;
    for(Box b:boxlist){
//        printf(" %lld..%lld,%lld..%lld,%lld..%lld\n",b.min_x,b.max_x,b.min_y,b.max_y,b.min_z,b.max_z);
        total += (b.max_x+1-b.min_x)*(b.max_y+1-b.min_y)*(b.max_z+1-b.min_z);
    }
    cout << "Part2: " << total << endl;
}

int main()
{
    part2();
    return 0;
}
