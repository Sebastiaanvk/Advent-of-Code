#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <strstream>
#include <algorithm>

using namespace std;

struct Recipe{
    vector<string> ingredients;
    vector<string> allergens;
};

ifstream& operator>>(ifstream& input, Recipe& r){
    r.ingredients={};
    r.allergens={};
    string s;
    input >> s;
    while( input && s[0]!='(' ){
        r.ingredients.push_back(s);
//        cout << s << " ";
        input >> s;
    }
//    cout << endl;
    input >> s;
    while(input && s[s.size()-1]!=')'){
        r.allergens.push_back(s.substr(0,s.size()-1));
//        cout << r.allergens[r.allergens.size()-1] << " ";
        input >> s;
    }
    r.allergens.push_back(s.substr(0,s.size()-1));
//    cout << s.substr(0,s.size()-1) << endl << endl;
    getline(input,s);

    return input;
}

vector<string> vector_intersection( vector<string>& v1, vector<string>& v2 ){
    vector<string> v3;
    int i=0;
    int j=0;

    while( i<v1.size() && j<v2.size() ){
        if(v1[i]==v2[j]){
            v3.push_back(v1[i]);
            i++;
            j++;
        } else if(v1[i]<v2[j]){
            i++;
        } else {
            j++;
        }
    }
    return v3;
}

void check_allergen(string& allergen,vector<string> ingredients, int& free_index, unordered_map<string,int>& allergen_index, vector< vector<string> >& ingredients_containing_allergen, vector<string>& allergens ){
    if( allergen_index.count(allergen) ){
        int index = allergen_index[allergen];
        ingredients_containing_allergen[index]= vector_intersection(ingredients, ingredients_containing_allergen[index]);

    } else {
        allergen_index[allergen] = free_index;
        allergens.push_back(allergen);

        ingredients_containing_allergen.push_back(ingredients);
        free_index++;
    }
}

string part2(vector<string> allergens, vector<vector<string>> ingredients_containing_allergen, unordered_map<string,int> allergen_index){
    vector<bool> allergen_done;
    for(auto a:allergens) allergen_done.push_back(false);
    for(int i=0; i<allergens.size(); i++){
        int j=0;
        while( allergen_done[j] || ingredients_containing_allergen[j].size()!=1 ){
            j++;
        }
        allergen_done[j]=true;
        string ingr = ingredients_containing_allergen[j][0];
        for(int k=0; k<allergens.size(); k++){
            if(k!=j){
                vector<string>::iterator it = ingredients_containing_allergen[k].begin();
                while( it!=ingredients_containing_allergen[k].end() && *it!=ingr){
                    it++;
                }
                if(it!=ingredients_containing_allergen[k].end()){
                    ingredients_containing_allergen[k].erase(it);
                }
            }
        }

    }

    sort(allergens.begin(),allergens.end());
    string s="";
    for(string a:allergens){
        s+= ingredients_containing_allergen[ allergen_index[a] ][0] +",";
    }
    return s.substr(0,s.size()-1);
}

void part1(){
    unordered_map<string,int> allergen_index;
    vector<string> allergens;
    vector< vector<string> > ingredients_containing_allergen;

    ifstream input("input.txt");
    vector<Recipe> recipes;
    int free_index=0;
    Recipe r;
    input >> r;
    while(input){
        sort( r.ingredients.begin(), r.ingredients.end() );
        recipes.push_back(r);
        for(auto a:r.allergens){
            check_allergen(a,r.ingredients, free_index, allergen_index, ingredients_containing_allergen, allergens);
        }
        input >> r;
    }

    unordered_set<string> ingredients_with_allergens;
    for(auto ingr_set:ingredients_containing_allergen){
        for(auto ingr:ingr_set){
            ingredients_with_allergens.insert(ingr);
        }
    }
    int counter = 0;
    for(auto r:recipes){
        for(auto ingr:r.ingredients){
            if( !ingredients_with_allergens.count(ingr) ){
                counter++;
            }
        }
    }
    cout << "part1: " << counter << endl;


    cout << "part2: " << part2(allergens, ingredients_containing_allergen, allergen_index) << endl;
}

int main()
{
    part1();
    return 0;
}
