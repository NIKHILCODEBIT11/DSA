#include<bits/stdc++.h>
using namespace std;

bool check(vector <int> arr,int n){
    for(int i=0;i<arr.size();i++){
        if(arr[i]<=arr[i+1]){
        }
        else{
            return false;
        }
    }
    return true;
}

int main(){
    vector <int> arr={1,2,3,41,4,55,65,66};
    cout<<"The array is sorted : "<<check(arr,arr.size());
    return 0;
}