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

Better than bruteforce_1 because :-

*/

#include<bits/stdc++.h>
using namespace std;

int longest_subarray_with_sum_k(vector <int> &nums,int m){
    int n = nums.size();
    int longest = 0;
    for(int i = 0;i < n;i++){
        int sum = 0;
        for(int j = i;j < n;j++){
            sum+= nums[j];
            if(sum == m){
                longest = max(longest, j-i+1);
                // Removed sum = 0 from here see explaination below
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

// TC :-approximately O(N^2), because i removed 3rd loop and did same in 2nd for loop only
// SC :- O(1)

/*
================================================================================
                    DOUBTS & CLARIFICATIONS SUMMARY
================================================================================

DOUBT 1: Why can't I write `sum = 0;` inside `if (sum == m)`?
--------------------------------------------------------------------------------
REASON:
- The variable `sum` must track the cumulative sum from index `i` to `j`.
- The formula `j - i + 1` calculates the subarray length from `i` all the way to `j`.
- If you reset `sum = 0`, on the next iteration (`j + 1`), `sum` will only hold 
  the value of `nums[j + 1]` instead of the actual subarray sum.
- If `nums[j + 1] == m`, the code runs `longest = max(longest, (j + 1) - i + 1)`, 
  attributing the full span `i...j+1` to the sum `m`, which is mathematically false!

EXAMPLE:
    nums = [1, 2, 3],  m = 3,  i = 0
    - j = 0: sum = 1
    - j = 1: sum = 1 + 2 = 3 (matches m!) -> you set sum = 0
    - j = 2: sum = 0 + 3 = 3 (matches m again!)
      Formula executes: longest = max(longest, 2 - 0 + 1) = 3
      This incorrectly claims [1, 2, 3] sums to 3!


DOUBT 2: Why not just use `break;` as soon as `sum == m`?
--------------------------------------------------------------------------------
REASON:
It depends strictly on the types of numbers present in the array:

CASE A: Array has ZEROS (>= 0) -> `break;` FAILS!
- Adding zeros does not increase the sum, but it DOES increase the length.
- If you break immediately, you miss longer valid subarrays.

EXAMPLE:
    nums = [1, 2, 0, 0],  m = 3,  i = 0
    - At j = 1: subarray [1, 2]       -> sum = 3, length = 2
    - If you break now, you record length = 2.
    - If you don't break:
        * At j = 2: [1, 2, 0]       -> sum = 3, length = 3
        * At j = 3: [1, 2, 0, 0]    -> sum = 3, length = 4 (LONGEST!)
    -> Breaking causes you to miss the true maximum length 4.

CASE B: Array has NEGATIVE NUMBERS -> `break;` FAILS!
- Sum can exceed `m` and later be reduced back down by a negative value.
- Breaking on `sum >= m` misses valid longer windows.

EXAMPLE:
    nums = [1, 2, 5, -5],  m = 3,  i = 0
    - [1, 2]         has sum = 3 (length 2)
    - [1, 2, 5, -5]  also has sum = 3 (length 4)

CASE C: Array is STRICTLY POSITIVE (> 0) -> `break;` WORKS!
- Every element is at least 1.
- Once sum reaches `m`, adding any next element guarantees sum > m.
- Here, and ONLY here, breaking immediately on `sum >= m` is safe and faster.

================================================================================
*/