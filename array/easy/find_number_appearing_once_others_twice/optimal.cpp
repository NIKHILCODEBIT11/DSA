// Here, i am going to use xor as, xor(n,n) = 0 {xxor of same numbers give 0} and xor(n,0) = n
#include<bits/stdc++.h>
using namespace std;

int appear_once_not_twice(vector <int> &nums){
    int n = nums.size();
    int ans = 0;
    for(auto num : nums){
        ans ^= num;
    }
    return ans;
}

int main(){
    vector <int> nums = {1,2,1,3,2,4,4};
    cout<<"The number appearing only once is "<<appear_once_not_twice(nums);
    return 0;
}

// TC :- O(N)
// SC :- O(1)