#include<bits/stdc++.h>

using namespace std;

int second_largest(vector <int> arr,int n){
    int large=arr[0];
    int second_large=arr[0];
    
    for(int i=1;i<n;i++){
        if(large<arr[i]){
            second_large=large;
            large=arr[i];
        }
        else if(arr[i]>second_large && arr[i]!=large){
            second_large=arr[i];
        }
    }

    return second_large;
}

int main(){
    vector <int> arr1={2,3,4,2,3,1,7,5,6,9};
    cout<<"The second largest element is "<<second_largest(arr1,arr1.size());
    return 0;
}