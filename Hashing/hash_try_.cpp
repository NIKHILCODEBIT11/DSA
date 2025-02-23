#include<iostream>
using namespace std;
int main(){
    int arr[]={2,3,2,3,1,4,3,5,6,5,12,2,0,0};
    int k=arr[0];
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        if(k>arr[i]){
            continue;
        }
        else{
            k=arr[i];
        }
    }
    int hash[k+1]={0};
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
        hash[arr[i]]++;
    }
    int k_;
    do{
        if(k_==-1){
            break;
        }
        cout<<"Enter value whose value is needed :- ";
        cin>>k_;
        cout<<"The number of repetitions is :- "<<hash[k_]<<endl;
    }
    while(1);
    return 0;
}