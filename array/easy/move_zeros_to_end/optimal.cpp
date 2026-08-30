// Here, i am going to use a two - pointer approach
// Step - 1 :- i am gonna traverse whole array nums and find the first ever occurence of zeero and name that index as j
// Step - 2 :- Then i am gonna traverse from next index from j till end of nums and swap ny=ums[i] and nums[j]
// "i" iterate over whole array but ist reacts when it reaches a non-zero number
// "j" always point o number zero only
// Example :- nums = [2, 3, 0, 6, 0, 0, 7, 0]
// From step - 1 :- j = 2
// In step - 2 :- i from index 3 to nums.size, so in this example it will be total 5 iterations { 8 - 3 = 5}

// Iteration 1 :- i = 3 and j = 2 swap ----> [2, 3, 6, 0, 0, 0, 7, 0]
// Iteration 2 :- i = 4 and j = 3 No swap
// Iteration 3 :- i = 5 and j = 3 No swap
// Iteration 4 :- i = 6 and j = 3 Swap ----> [2, 3, 6, 7, 0, 0, 0, 0]
// Iteartion 5 :- i = 7 and j = 4 No swap

#include<bits/stdc++.h>
using namespace std;

void move_zeros_to_end(vector <int> &nums){
    int n = nums.size();
    int j = -1;  // Just default value nothing special

    // Finding first occurence of zero :-
    for(int i = 0; i < nums.size(); i++){
        if(nums[i] == 0){
            j = i;
            break;
        }
    }

    if(j == -1){     // Even after traversal if i dont find any zero in nums that means there are no zeros in nums so directly return
        return;
    }

    // Traversing and swapping :-
    for(int i = j+1; i < nums.size(); i++){
        if(nums[i] != 0){
            swap(nums[i], nums[j]);
            j++;    // Move counter ahead
        }
    }
}

int main(){
    int n;
    cin>>n;
    vector <int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    cout<<"Before moving zeros to end :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    cout<<endl;

    move_zeros_to_end(nums);

    cout<<"After moving zeros to end :-"<<endl;
    for(int i = 0; i < n; i++){
        cout<<nums[i]<<" ";
    }
    return 0;
}

// Time complexity :- O(j) + O(N-j)  ----> O(N) ----> As, O(j) for traversal in findinh first occurence of 0 that is j, then traversing from i = j+1 till N {so, N-j}
// Space complexity :- O(1)  ----> As, no extra space is used