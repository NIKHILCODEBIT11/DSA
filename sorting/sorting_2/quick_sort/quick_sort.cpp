#include<bits/stdc++.h>
using namespace std;

int partition(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low;
    int j = high;

    while(i < j){
        while(i <= high && arr[i] <= pivot){
            i++;
        }
        while(j >= low && arr[j] > pivot){
            j--;
        }
        if(i < j){
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    return j;
}

void quick_sort(int arr[], int low, int high){
    if(low < high){    // This condition checks that i sort only for array with more than 1 elements 
        int partition_indx = partition(arr, low, high);
        quick_sort(arr, low, partition_indx-1);
        quick_sort(arr, partition_indx+1, high);
    }
    // else{   ---------->This is redundant
    //     return;
    // }
    // In C++, when a void function reaches the end of its body without a return statement, it automatically returns to the caller.
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i =0; i<n ;i++){
        cin>>arr[i];
    }
    cout<<"Before sorting :-"<<endl;
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"After sorting :-"<<endl;
    quick_sort(arr, 0, n-1);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}

// Time complexity :- O(N*logN)
// Space complexity :- O(1)