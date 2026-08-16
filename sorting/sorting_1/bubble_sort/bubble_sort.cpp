#include<bits/stdc++.h>
using namespace std;

void bubble_sort(int arr[], int n){
    for(int i = n-1; i >= 1; i--){

        // Now i am doing OPTIMIZATION FOR TIME COMPLEXITY BEST CASE :-
        bool didswap = false;
        for(int j = 0; j <= i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                didswap = true;
            }
        }
        if( !didswap ){
            break;
        }
    }
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
    bubble_sort(arr, n);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}

// Time complexity :-
// WORST and AVERAGE :-  O(n^2)
// BEST :- O(n)  -------> Explaination :- If the array is already sorted then there is no need of checking internal for loop after 1st time due to whihc i have used a variable didswap