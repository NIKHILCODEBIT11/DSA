/*
Suppose nums = [102, 4, 100, 1, 101, 3, 2, 1, 1]
ab mujhe longest consecutive sequence nikalna hai 
jaise ki subsequences hain :-
[100, 101, 102] ----------> Length = 3
[1, 2, 3, 4] -------. Length = 4
longest length = 4

======================================================================
DRY RUN: nums = {102, 4, 100, 1, 101, 3, 2, 1, 1}, size n = 9
======================================================================

PASS 0: i = 0, nums[0] = 102
----------------------------------------------------------------------
* x = 102, count = 1
* while linear_search(nums, 102 + 1 = 103):
    -> 103 array me dhunda: NOT FOUND (false)
    -> while loop exit.
* longest = max(1, 1) = 1

PASS 1: i = 1, nums[1] = 4
----------------------------------------------------------------------
* x = 4, count = 1
* while linear_search(nums, 4 + 1 = 5):
    -> 5 array me dhunda: NOT FOUND (false)
    -> while loop exit.
* longest = max(1, 1) = 1

PASS 2: i = 2, nums[2] = 100
----------------------------------------------------------------------
* x = 100, count = 1
* Iteration 1:
    -> linear_search(nums, 100 + 1 = 101): FOUND at index 4 (true)
    -> x update hua: x = 101
    -> count increment: count = 2
* Iteration 2:
    -> linear_search(nums, 101 + 1 = 102): FOUND at index 0 (true)
    -> x update hua: x = 102
    -> count increment: count = 3
* Iteration 3:
    -> linear_search(nums, 102 + 1 = 103): NOT FOUND (false)
    -> while loop exit.
* Sequence mili: [100 -> 101 -> 102] (length = 3)
* longest = max(1, 3) = 3

PASS 3: i = 3, nums[3] = 1
----------------------------------------------------------------------
* x = 1, count = 1
* Iteration 1:
    -> linear_search(nums, 1 + 1 = 2): FOUND at index 6 (true)
    -> x update hua: x = 2
    -> count increment: count = 2
* Iteration 2:
    -> linear_search(nums, 2 + 1 = 3): FOUND at index 5 (true)
    -> x update hua: x = 3
    -> count increment: count = 3
* Iteration 3:
    -> linear_search(nums, 3 + 1 = 4): FOUND at index 1 (true)
    -> x update hua: x = 4
    -> count increment: count = 4
* Iteration 4:
    -> linear_search(nums, 4 + 1 = 5): NOT FOUND (false)
    -> while loop exit.
* Sequence mili: [1 -> 2 -> 3 -> 4] (length = 4)
* longest = max(3, 4) = 4

PASS 4: i = 4, nums[4] = 101
----------------------------------------------------------------------
* x = 101, count = 1
* Iteration 1:
    -> linear_search(nums, 101 + 1 = 102): FOUND at index 0 (true)
    -> x = 102, count = 2
* Iteration 2:
    -> linear_search(nums, 102 + 1 = 103): NOT FOUND (false)
* longest = max(4, 2) = 4

PASS 5: i = 5, nums[5] = 3
----------------------------------------------------------------------
* x = 3, count = 1
* Iteration 1:
    -> linear_search(nums, 3 + 1 = 4): FOUND at index 1 (true)
    -> x = 4, count = 2
* Iteration 2:
    -> linear_search(nums, 4 + 1 = 5): NOT FOUND (false)
* longest = max(4, 2) = 4

PASS 6: i = 6, nums[6] = 2
----------------------------------------------------------------------
* x = 2, count = 1
* Iteration 1:
    -> linear_search(nums, 2 + 1 = 3): FOUND at index 5 (true)
    -> x = 3, count = 2
* Iteration 2:
    -> linear_search(nums, 3 + 1 = 4): FOUND at index 1 (true)
    -> x = 4, count = 3
* Iteration 3:
    -> linear_search(nums, 4 + 1 = 5): NOT FOUND (false)
* longest = max(4, 3) = 4

PASS 7: i = 7, nums[7] = 1
----------------------------------------------------------------------
* x = 1, count = 1
* Fir se 1 se leke 4 tak search karega (same as Pass 3)
* count banega: 4
* longest = max(4, 4) = 4

PASS 8: i = 8, nums[8] = 1
----------------------------------------------------------------------
* x = 1, count = 1
* Fir se 1 se leke 4 tak search karega (duplicate element check)
* count banega: 4
* longest = max(4, 4) = 4

======================================================================
FINAL RESULT:
Loop complete. Sabse lamba consecutive streak mila = 4 (Sequence: 1, 2, 3, 4)
======================================================================
*/



#include<bits/stdc++.h>
using namespace std;

bool linear_search(vector <int> &nums, int x){
    for(int i = 0;i < nums.size();i++){
        if(nums[i] == x){
            return true;
        }
    }
    return false;
}

int longest_consecutive_sequnce(vector <int> &nums){
    int n = nums.size();
    int longest = 1;

    // for(int i = 0;i < n;i++){
    //     int count = 1;
    //     for(int j = 0;j < n;j++){
    //         if(nums[j] == (nums[i] + count)){
    //             count++;
    //         }
    //     }
    //     longest = max(longest, count);
    // }

    // return longest;

    /*
    Upar wale code ki dikkat hai ki :-- inner loop sirf ek hi baar run ho raha hai
    ex :- {3,2,1} ---> longest hona chahiye 3

    magar :-
    Take the outer loop iteration where nums[i] = 1 (at index i = 1):
    Initialized: count = 1. Looking for nums[i] + count ---> 1 + 1 = 2.
    Inner loop starts (j = 0 to 2):
        j = 0: nums[0] = 3.
            s 3 == 2? No. count stays 1. (Notice: we just passed 3!)
        j = 1: nums[1] = 1.
            Is 1 == 2? No. count stays 1.
        j = 2: nums[2] = 2.
            Is 2 == 2? Yes! count increments to 2

    Inner loop ends.
    Result for 1: count = 2 (only detected 1 and 2).
    */

    for(int i = 0;i < n;i++){
        int count = 1;
        int x = nums[i];
        
        while(linear_search(nums, nums[i] + 1) == true){
            // nums[i] = nums[i] + 1;     now i am using x because using this line makes the array nums modify as using assignment operator in nums[i]
            x = x +1;
            count++;
        }

        longest = max(longest, count);
    }
    return longest;
}

int main(){
    vector <int> nums = {102, 4, 100, 1, 101, 3, 2, 1, 1};
    cout<<"The length of longest subsequence is "<<longest_consecutive_sequnce(nums);
    return 0;
}

/*
TC :- approx. O(N**2) ---> As, outer for loop runs for N times and inside linear_search in worst case runs for O(N) times each time
SC :- O(1)
*/