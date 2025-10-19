#include<iostream>
using namespace std;

int main(){
    int arr[]={22,33,3,43,21,2};
    int size=sizeof(arr)/sizeof(arr[0]);

    for(int i=0;i<size-1;i++){
        int min_index=i;

        for(int j=i+1;j<size;j++){
            if(arr[j]<arr[min_index]){
                int temp=arr[min_index];
                arr[min_index]=arr[j];
                arr[j]=temp;
            }
        }
    }

    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}