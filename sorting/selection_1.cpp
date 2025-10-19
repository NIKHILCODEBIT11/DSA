#include<iostream>
using namespace std;

int main(){
    int arr[]={23,34,10,2,31};
    int size=sizeof(arr)/sizeof(arr[0]);

    for(int i=0;i<size-1;i++){
        int min=arr[i];
        for(int j=i;j<size;j++){
            if(arr[j]<min){
                arr[i]=arr[j];
                arr[j]=min;
                min=arr[i];
            }
        }
    }
    
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}