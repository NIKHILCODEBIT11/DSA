// Here, only bruteforce exists
// Traverse the whole array and find the first ever occurence of given value k in array and return it's index and if the number k doesn't exist simply return -1

#include<bits/stdc++.h>
using namespace std;

int linear_search(vector <int>&nums, int k){
    int n = nums.size();

    for(int i = 0; i < n; i++){
        if(nums[i]==k){
            return i;
        }
    }

    return -1;    // If no value is matched to k from nums
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    int k;
    cout<<"Enter value to be searched :- ";
    cin>>k;
    cout<<"Before linear search :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;
    int l = linear_search(nums, k);
    if(l==-1){
        cout<<"Value "<<k<<" is not found";
    }
    else{
        cout<<"The value "<<k<<" is in index "<<l;
    }
    return 0;
}

// Time complexity :- O(N) ----> For worst case i traverse whole vector but still not found the number
// Space commplexity :- O(1) ----> As, no extra space is required