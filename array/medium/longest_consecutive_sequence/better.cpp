/*
Yaha pe mein sabse pehle array ko sort kar lunga jisse saare consecutive elements paas-paas aa jaye
phir puri array traverse karunga 0 -> N
aur check karunga ki agar nums[i] - 1 == last_smaller hai :-
    count update kar dunga kyuki maine sequence ke 2 numbers ka pata laga liya
aur agar nums[i] redudant value aa rahi jaisa 2 in [1,1,1,2,2,2,3,3,4] :-
    us case mein kuch bhi nahi karna 
aur agar subsequence khatam ho gaya matlab pehli if aur else if ko chod ke niche pahuchega :-
    jaha count = 1 reset karunga aur last_smaller = nums[i] karunga
*/

/*
Is input array ka size n = 14 hai.
Sorting ke baad array ka roop:
Index:    0   1   2   3   4   5   6   7   8   9   10   11   12   13
nums:   { 1,  1,  1,  2,  2,  2,  3,  3,  4, 100, 100, 101, 101, 102 }

====================================================================================================
DRY RUN:
Initial State:
* n = 14
* longest = 1
* count = 0
* last_smaller = INT_MIN
====================================================================================================

PASS 0:
* Loop variable: i = 0
* Current element: nums[0] = 1
* Conditions check:
    - nums[0] - 1 == last_smaller -> (1 - 1 == INT_MIN) -> False
    - nums[0] == last_smaller     -> (1 == INT_MIN)     -> False
    - nums[0] != last_smaller     -> (1 != INT_MIN)     -> True (Nayi streak start hui)
* Actions:
    - count = 1
    - last_smaller = 1
    - longest = max(1, 1) = 1
* State at end of Pass 0:
    [i = 0, nums[i] = 1, last_smaller = 1, count = 1, longest = 1]

PASS 1:
* Loop variable: i = 1
* Current element: nums[1] = 1
* Conditions check:
    - nums[1] - 1 == last_smaller -> (1 - 1 == 1) -> False
    - nums[1] == last_smaller     -> (1 == 1)     -> True (Duplicate mila)
* Actions:
    - continue execute hua (koi variable update nahi hua)
* State at end of Pass 1:
    [i = 1, nums[i] = 1, last_smaller = 1, count = 1, longest = 1]

PASS 2:
* Loop variable: i = 2
* Current element: nums[2] = 1
* Conditions check:
    - nums[2] == last_smaller     -> (1 == 1)     -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 2:
    [i = 2, nums[i] = 1, last_smaller = 1, count = 1, longest = 1]

PASS 3:
* Loop variable: i = 3
* Current element: nums[3] = 2
* Conditions check:
    - nums[3] - 1 == last_smaller -> (2 - 1 == 1) -> True (Consecutive element mila)
* Actions:
    - count++ => count = 2
    - last_smaller = 2
    - longest = max(1, 2) = 2
* State at end of Pass 3:
    [i = 3, nums[i] = 2, last_smaller = 2, count = 2, longest = 2]

PASS 4:
* Loop variable: i = 4
* Current element: nums[4] = 2
* Conditions check:
    - nums[4] == last_smaller     -> (2 == 2)     -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 4:
    [i = 4, nums[i] = 2, last_smaller = 2, count = 2, longest = 2]

PASS 5:
* Loop variable: i = 5
* Current element: nums[5] = 2
* Conditions check:
    - nums[5] == last_smaller     -> (2 == 2)     -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 5:
    [i = 5, nums[i] = 2, last_smaller = 2, count = 2, longest = 2]

PASS 6:
* Loop variable: i = 6
* Current element: nums[6] = 3
* Conditions check:
    - nums[6] - 1 == last_smaller -> (3 - 1 == 2) -> True (Consecutive element mila)
* Actions:
    - count++ => count = 3
    - last_smaller = 3
    - longest = max(2, 3) = 3
* State at end of Pass 6:
    [i = 6, nums[i] = 3, last_smaller = 3, count = 3, longest = 3]

PASS 7:
* Loop variable: i = 7
* Current element: nums[7] = 3
* Conditions check:
    - nums[7] == last_smaller     -> (3 == 3)     -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 7:
    [i = 7, nums[i] = 3, last_smaller = 3, count = 3, longest = 3]

PASS 8:
* Loop variable: i = 8
* Current element: nums[8] = 4
* Conditions check:
    - nums[8] - 1 == last_smaller -> (4 - 1 == 3) -> True (Consecutive element mila)
* Actions:
    - count++ => count = 4
    - last_smaller = 4
    - longest = max(3, 4) = 4
* State at end of Pass 8:
    [i = 8, nums[i] = 4, last_smaller = 4, count = 4, longest = 4]

PASS 9:
* Loop variable: i = 9
* Current element: nums[9] = 100
* Conditions check:
    - nums[9] - 1 == last_smaller -> (100 - 1 == 4) -> False
    - nums[9] == last_smaller     -> (100 == 4)     -> False
    - nums[9] != last_smaller     -> (100 != 4)     -> True (Gap aa gaya, nayi streak)
* Actions:
    - count = 1
    - last_smaller = 100
    - longest = max(4, 1) = 4
* State at end of Pass 9:
    [i = 9, nums[i] = 100, last_smaller = 100, count = 1, longest = 4]

PASS 10:
* Loop variable: i = 10
* Current element: nums[10] = 100
* Conditions check:
    - nums[10] == last_smaller    -> (100 == 100)   -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 10:
    [i = 10, nums[i] = 100, last_smaller = 100, count = 1, longest = 4]

PASS 11:
* Loop variable: i = 11
* Current element: nums[11] = 101
* Conditions check:
    - nums[11] - 1 == last_smaller -> (101 - 1 == 100) -> True (Consecutive element mila)
* Actions:
    - count++ => count = 2
    - last_smaller = 101
    - longest = max(4, 2) = 4
* State at end of Pass 11:
    [i = 11, nums[i] = 101, last_smaller = 101, count = 2, longest = 4]

PASS 12:
* Loop variable: i = 12
* Current element: nums[12] = 101
* Conditions check:
    - nums[12] == last_smaller    -> (101 == 101)   -> True (Duplicate mila)
* Actions:
    - continue execute hua
* State at end of Pass 12:
    [i = 12, nums[i] = 101, last_smaller = 101, count = 2, longest = 4]

PASS 13:
* Loop variable: i = 13
* Current element: nums[13] = 102
* Conditions check:
    - nums[13] - 1 == last_smaller -> (102 - 1 == 101) -> True (Consecutive element mila)
* Actions:
    - count++ => count = 3
    - last_smaller = 102
    - longest = max(4, 3) = 4
* State at end of Pass 13:
    [i = 13, nums[i] = 102, last_smaller = 102, count = 3, longest = 4]

====================================================================================================
FINAL OUTPUT:
Loop khatam hua. 
Sabse badi sequence bani: {1, 2, 3, 4}
Return value: longest = 4
====================================================================================================
*/
#include<bits/stdc++.h>
using namespace std;

int longest_consecutive_subsequence(vector <int> &nums){
    int n = nums.size();
    int longest = 1;
    int count = 0;
    int last_smaller = INT_MIN;

    // sorting array
    sort(nums.begin(), nums.end());

    // Traversing :-
    for(int i = 0;i < n;i++){
        if(nums[i] - 1 == last_smaller){
            count++;
            last_smaller = nums[i];
        }
        else if(nums[i] == last_smaller){
            continue;
        }
        else if(nums[i] != last_smaller){
            count = 1;
            last_smaller = nums[i];
        }
        longest = max(longest, count);
    }
    return longest;
}

int main(){
    vector <int> nums = {100, 102, 100, 101, 101, 4, 3, 2, 3, 2, 1, 1, 1, 2};
    cout<<"The length of longest subsequence is "<<longest_consecutive_subsequence(nums);
    return 0;
}

/*
TC :- 
Sorting Approach (Jo code aapne use kiya)
Time Complexity (TC): O(N log N)
    Array ko sort karne ke liye: O(N log N)
    Array ko ek baar linear traverse karne ke liye: O(N)
    Total TC: O(N log N) + O(N) = O(N log N)

Space Complexity (SC): O(1) ya O(log N)
    Hum koi alag data structure (like set/map) use nahi kar rahe, isliye auxiliary space O(1) hai.
    C++ me std::sort (Introsort) internally recursion stack use karta hai, jo worst-case me O(\log N) space leta hai.
*/