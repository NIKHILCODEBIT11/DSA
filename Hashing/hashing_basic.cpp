#include<iostream>
using namespace std;

int count(int,int arr[]);

int main(){
    int n,n_;
    cout<<"Enter the number of items in array :- ";
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cout<<"Enter value at "<<i<<"th index :- ";
        cin>>arr[i];
    }
    arr[n-1]=-1;        // Passing -1 as last element, luckily if the user doesn't input -1 in array then i can pass array only without specifying number of elements in it
    cout<<endl<<"Enter the number whose count is needed :- ";
    cin>>n_;
    cout<<"The count of "<<n_<<" is "<<count(n_,arr);
    return 0;
}

int count(int n,int arr[]){
    int count_ = 0;
    // for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){       Here, i am getting error as when i just use sizeof(arr), then it is making arr as a pointer   {AS NAME OF ARRAY ITSELF ACTS AS A POINTER} , so to correct this i will have to use a different approach
    //     if(arr[i]==n){
    //         count_++;
    //     }
    // }
    int i=0;
    while(arr[i]!=-1){
        if(arr[i]==n){
            count_++;
        }
        i++;
    }
    return count_;
}