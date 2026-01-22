#include<bits/stdc++.h>
using namespace std;

void bubble(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            if(arr[j]<arr[i]){
                swap(arr[i],arr[j]);
            }
        }
    }
}

int main(){
    int arr[]={23,32,2,3,3,0,4};
    for(int i=0;i<7;i++){
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
    bubble(arr,7);
    for(int i=0;i<7;i++){
        cout<<arr[i]<<"\t";
    }
    return 0;
}