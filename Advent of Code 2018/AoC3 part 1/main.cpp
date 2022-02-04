#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Claim
{
    int id;
    int loc_x;
    int loc_y;
    int width;
    int height;
};
const int N = 1100;
int fabric [N][N];

ifstream& operator>>(ifstream& in, Claim& claim)
{
    //pre-cond
    assert(true);
    //post-cond:
    //one line is read for all member of one Claim struct
    char c;
    in >> c;
    in >> claim.id >> c;
    in >> claim.loc_x >> c >> claim.loc_y >> c;
    in >> claim.width >> c >> claim.height;
    return in;
}

void cut_claim(Claim claim)
{
    for(int x=claim.loc_x; x-claim.loc_x<claim.width;x++)
        for (int y = claim.loc_y; y-claim.loc_y<claim.height;y++)
            fabric[x][y] = fabric[x][y]+1;
}

bool check_claim(Claim claim)
{
    for(int x=claim.loc_x; x-claim.loc_x<claim.width;x++)
        for (int y = claim.loc_y; y-claim.loc_y<claim.height;y++)
            if(fabric[x][y]!=1)
                return false;
    return true;
}

void best_claim(vector<Claim>& claims)
{
    for(int i=0;i<claims.size(); i++)
        if(check_claim(claims[i]))
        {
            cout << "The best claim we found is claim nubmer: " << i+1 << endl;
            return;
        }
}


void check_squares(vector<Claim>& claims)
{
    //pre-cond
    assert(true);
    //post-cond
    //Counts the number of squares that multiple elves are claiming

    for(int i=0;i<claims.size();i++)
    {
        cut_claim(claims[i]);
    }
    int counter = 0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if (fabric[i][j]>1)
                counter += 1;
        }
    }
    cout << "The answer is: " << counter << endl;
}

int main()
{
    ifstream inputfile;
    inputfile.open("AoC3.txt");
    vector<Claim> claims;
    Claim claim;
    inputfile >> claim;
    while(inputfile)
    {
//        cout << claim.id << claim.loc_x << claim.loc_y << claim. width << claim.height << endl;
        claims.push_back(claim);
        inputfile >> claim;
    }
    cout << "Vector size: " << claims.size() << endl;
    cout << "Fabric random locations:" << fabric[200][100]<<fabric[10][10]<<fabric[0][0];
    check_squares( claims );
    best_claim(claims);
    return 0;
}
