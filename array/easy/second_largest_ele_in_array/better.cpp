// Here, i will perform 2 pass stratergy :-
// In first pass i will find "largest"
// In second pass i will set second_largest as INT_MIN and traverse whole array for checking { element > second_largest but element < largest}

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i =0; i<n ;i++){
        cin>>nums[i];
    }
    cout<<"Array is :-"<<endl;
    for(int i=0; i<n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    int largest = nums[0];
    // First pass
    for(int i = 0; i < n; i++){
        if(nums[i] > largest){
            largest = nums[i];
        }
    }

    // Second pass
    int second_largest = INT_MIN;
    for(int i = 0; i < n; i++){
        if(nums[i] > second_largest && nums[i] < largest){
            second_largest = nums[i];
        }
    }

    if(second_largest != INT_MIN){
        cout<<"The second largest element is "<<second_largest;
    }
    else{
        cout<<"No second largest element exists";
    }
    return 0;
}

// Time complexity :- O(2N) ----> As, it runs for 2 passes {N + N}