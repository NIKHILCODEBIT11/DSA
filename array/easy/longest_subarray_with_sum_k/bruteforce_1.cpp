/*
Consider an array [1,2,3,1,1,1,1,4,2,3]
and find longest subarray {continous part of array only} whose sum is k
like for k = 3
subarrays are :-
[1,2]
[3]
[1,1,1] ---> longest length 3 so return 3

Here, i am going to use 2-pointer approach where i will start from 0 to n and j will start from i to n
j will move finding subarrays whose sum is k and the length will be stored for each found subarray
*/

#include<bits/stdc++.h>
using namespace std;

int longest_subarray_with_sum_k(vector <int> &nums,int m){
    int n = nums.size();
    int longest = 0;
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            int sum = 0;

            // To find sum :-
            for(int k = i;k <= j;k++){
                sum += nums[k];
            }
            if(sum == m){
                    longest = max(longest, j-i+1);
            }

        }
    }
    return longest;
}

int main(){
    vector <int> nums = {1,2,3,1,1,1,1,4,2,3};
    int m = 3;
    cout<<"The length of longest subarray with sum "<<m<<" is "<<longest_subarray_with_sum_k(nums, m);
    return 0;
}

// TC :-approximately O(N^3), because the 2nd and 3rd loop wont run for size n as they will keep on reducing as i increases
// SC :- O(1)