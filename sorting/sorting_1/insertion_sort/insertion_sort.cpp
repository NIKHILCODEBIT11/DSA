#include<bits/stdc++.h>
using namespace std;

void insertion_sort(int arr[], int n){
    // 3  5   2  7  1  9
    for(int i = 0; i < n; i++){
        int j = i;
        while( j>0 && arr[j] < arr[j-1] ){
            swap(arr[j], arr[j-1]);
            j--;
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
    insertion_sort(arr, n);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}


/*
 * ============================================================================
 * TIME & SPACE COMPLEXITY ANALYSIS :-
 * ============================================================================
 * 
 * WORST CASE  : O(n^2) --- Occurs when array is sorted in reverse order.
 *                          The inner while loop runs (i) times for each element.
 * 
 * AVERAGE CASE: O(n^2) --- Occurs when array elements are randomly ordered.
 * 
 * BEST CASE   : O(n)   --- Occurs when array is already sorted.
 *                          The outer for-loop runs (n) times, but the while loop
 *                          condition (arr[j] < arr[j-1]) fails immediately on the
 *                          first check without entering the loop body.
 * 
 * SPACE COMPLEXITY: O(1) -- In-place sorting algorithm (no extra space required).
 * ============================================================================
 */