#include <iostream>

using namespace std;

const int N=1000000;

int lower(int x){
    if(x==1){
        return 9;
    }
    return x-1;
}

int next_n_steps(int x, int arr [11], int n){
    if(n<=0){
        return x;
    }
    return next_n_steps(arr[x], arr, n-1 );}



void next_config( int arr [11], int& current_val){
    int v1 = next_n_steps(current_val, arr, 1);
    int v2 = next_n_steps(current_val, arr, 2);
    int v3 = next_n_steps(current_val, arr, 3);
    arr[current_val] = next_n_steps(current_val, arr, 4);
    int l = lower(current_val);
    while(l==v1||l==v2||l==v3){
        l = lower(l);
    }
    int l_next=arr[l];
    arr[l]=v1;
    arr[v3]=l_next;
    current_val=arr[current_val];

}

void part1(){
    int arr [11];
    arr[0]=-1;
//853192647
    arr[1]=9;
    arr[2]=6;
    arr[3]=1;
    arr[4]=7;
    arr[5]=3;
    arr[6]=4;
    arr[7]=8;
    arr[8]=5;
    arr[9]=2;
    int current_val = 1;
    for(int i=0; i<100; i++){
        next_config(arr, current_val);
    }

    cout << "part1: ";
    current_val = arr[1];
    while(current_val!=1){
        cout << current_val;
        current_val = arr[current_val];
    }
    cout << endl;
}



int lower2(int x){
    if(x==1){
        return N;
    }
    return x-1;
}

int next_n_steps2(int x, int arr [N+1], int n){
    if(n<=0){
        return x;
    }
    return next_n_steps2(arr[x], arr, n-1 );}



void next_config2( int arr [N+1], int& current_val){
    /*
    int v1 = next_n_steps2(current_val, arr, 1);
    int v2 = next_n_steps2(current_val, arr, 2);
    int v3 = next_n_steps2(current_val, arr, 3);
    arr[current_val] = next_n_steps2(current_val, arr, 4);*/
    int v1 = arr[current_val];
    int v2 = arr[v1];
    int v3 = arr[v2];
    arr[current_val] = arr[v3];
    int l = lower2(current_val);
    while(l==v1||l==v2||l==v3){
        l = lower2(l);
    }
    int l_next=arr[l];
    arr[l]=v1;
    arr[v3]=l_next;
    current_val=arr[current_val];

}

void part2(){
    int * arr;
    arr = new int [N+1];


    arr[0]=-1;
//853192647
    arr[1]=9;
    arr[2]=6;
    arr[3]=1;
    arr[4]=7;
    arr[5]=3;
    arr[6]=4;
    arr[7]=10;
    arr[8]=5;
    arr[9]=2;
    for(int i=10; i<N; i++) arr[i]=i+1;
    arr[N]=8;

    int current_val = 8;
    for(int i=0; i<10*N; i++){
        next_config2(arr, current_val);
    }
    long long r=1;
    r *=arr[1];
    r *=arr[ arr[1] ];
    cout << arr[1] << endl;
    cout << arr[arr[1]] << endl;
    cout << "part2: " << r << endl;
}


int main()
{
    part1();
    part2();
    return 0;
}
