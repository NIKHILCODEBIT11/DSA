#include<iostream>
#include<vector>

using namespace std;


int largest(vector <int> arr,int n){
    int large=arr[0];
    for(int i=1;i<n;i++){
        if(large<arr[i]){
            large=arr[i];
        }
        else{
            continue;
        }
    }
    return large;
}

int main(){
    vector <int> arr1={3,4,2,2,1,3,4,5,7,3,2};
    cout<<"The largest element is "<<largest(arr1,arr1.size())<<endl;
    return 0;
}