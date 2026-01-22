#include<bits/stdc++.h>
using namespace std;

int linear_search(vector <int> arr,int n){
    for(int i=0;i<arr.size();i++){
        if(arr[i]==n){
            return i;
        }
    }
    return -1;
}

int main(){
    vector <int> arr={1,2,0,5,6,4,0,0,0,2,0};
    int n;
    cout<<"Enter value to be searched : ";
    cin>>n;
    int n1=linear_search(arr,n);
    if(n1==-1){
        cout<<"The value is not present";
    }
    else{
        cout<<"The value is at index "<<n1;
    }
    return 0;
}