// Here, for a given number "N" i have to store "N" numbers in array of size "N-1", so 1 number will be missing
// Here, i am gonna use hashing
// i will construct a hashmap of size {N+1} each element initialized to 0 and traverse over the array nums
// and will update the index j in hashmap if nums[i] == j
// Example :- N = 5 so nums = [2,3,4,5] ----> 1 is missing
// Hashmap = [0,0,0,0,0,0]
// Now iterating over nums and updating the index of the element in hashmap encountered in nums to 1
// After complete iteration :- hashmap = [0,0,1,1,1,1] since 0th index is not to be checked as numbers were written in nums from 1 to N
// So, missing number is 1 as in hashmap index 1 is still 0

#include<bits/stdc++.h>
using namespace std;

int find_missing_number(vector <int> &nums, int N){
    int n = nums.size();   // or else int n = N-1
    vector <int> hashmap(N+1);
    for(int i = 0;i < n; i++){
        hashmap[nums[i]] = 1;
    }

    for(int i = 1;i < N+1;i++){
        if(hashmap[i] == 0){
            return i;
        }
    }
}

int main(){
    int n = 7;     // Value of n
    vector <int> nums = {1,2,3,5,6,7};      // Array of size n -1 
    cout<<"The missing number is "<<find_missing_number(nums, n);
    return 0;
}

// TC :- O(N) + O(N)
// SC :- O(N)