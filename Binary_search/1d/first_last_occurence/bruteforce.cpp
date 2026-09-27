// Yaha pe mein normal linear search kar raha
#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (LINEAR SEARCH FOR OCCURRENCES):
   - Problem: Ek array me target element ka sabse pehla index (`first`) 
     aur sabse aakhri index (`last`) find karna hai.
   - Core Idea (Single Pass Linear Traversal):
     Array ko left se right ek baar traverse karo (index 0 se n-1):
     * `first`: Hume sirf tab update karna hai jab target pehli baar dikhe.
       Iska track kaise rakhein? `first` ko shuru me `-1` set kar do. 
       Jab bhi `nums[i] == target` ho aur `first == -1` ho, tab `first = i` set kar do. 
       Uske baad chahe target dobara 10 baar aaye, `first != -1` rahega isliye wo update nahi hoga.
     * `last`: Jab bhi target dobara ya pehli baar dikhe, `last = i` update karte jao. 
       Kyunki loop left-to-right chal raha hai, toh target ka aakhri occurrence 
       loop ke end tak `last` me store ho chuka hoga.
   - Agar target array me exist hi nahi karta:
     `if(nums[i] == target)` kabhi trigger nahi hoga, aur default `{-1, -1}` return ho jayega.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int first = -1, last = -1;` :
     Initialization step. Agar element array me nahi mila, toh -1 reflect karega ki element absent hai.
   - `for(int i = 0; i < n; i++)` :
     Pura array 0 se n-1 tak linearly scan kar rahe hain.
   - `if(nums[i] == target)` :
     Match mil gaya! Ab do kaam karne hain:
     * `if(first == -1) first = i;` -> Check karta hai ki kya yeh target ka pehla encounter hai. 
       Agar `first` abhi bhi -1 hai, matlab yehi pehla index hai, isko freeze kar do.
     * `last = i;` -> Bina kisi condition ke har match par update karo, taaki jab aakhri 
       match aaye toh uska index automatically `last` me save ho jaye.
   - `return {first, last};` :
     C++ `std::pair<int, int>` me first aur last occurrence return kar diya.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Step-by-Step Flow):

   Array:
   Indices:   0   1   2   3   4   5   6   7   8   9
   Elements: [2,  3,  4,  6,  6,  6,  6,  6, 17, 19]
   n = 10
   Target = 6

   Initial State:
   first = -1, last = -1

   -------------------------------------------------------------------
   LOOP EXECUTION:
   -------------------------------------------------------------------
   i = 0: nums[0] = 2  != 6 -> No change  | first = -1, last = -1
   i = 1: nums[1] = 3  != 6 -> No change  | first = -1, last = -1
   i = 2: nums[2] = 4  != 6 -> No change  | first = -1, last = -1

   i = 3: nums[3] = 6  == 6 (Match!)
          - first == -1 ? TRUE  => first = 3  (Pehla encounter lock ho gaya)
          - last = 3
          State: first = 3, last = 3

   i = 4: nums[4] = 6  == 6 (Match!)
          - first == -1 ? FALSE => first remains 3
          - last = 4 (Overwrite)
          State: first = 3, last = 4

   i = 5: nums[5] = 6  == 6 (Match!)
          - first == -1 ? FALSE => first remains 3
          - last = 5 (Overwrite)
          State: first = 3, last = 5

   i = 6: nums[6] = 6  == 6 (Match!)
          - first == -1 ? FALSE => first remains 3
          - last = 6 (Overwrite)
          State: first = 3, last = 6

   i = 7: nums[7] = 6  == 6 (Match!)
          - first == -1 ? FALSE => first remains 3
          - last = 7 (Overwrite)
          State: first = 3, last = 7

   i = 8: nums[8] = 17 != 6 -> No change  | first = 3, last = 7
   i = 9: nums[9] = 19 != 6 -> No change  | first = 3, last = 7

   Loop Ends.
   Returns: {3, 7}
   Output: "The first occurence of 6 is 3 and last occurence is 7"

   -------------------------------------------------------------------
   EDGE CASE: Target Not Present (target = 100)
   - Pure loop me `nums[i] == 100` kabhi true nahi hoga.
   - `first` aur `last` dono -1 hi rahenge.
   - Returns: {-1, -1}.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(N) in all cases (Best, Average, Worst).
     * Kyun? Kyunki loop break nahi hota; chahe target pehle index par hi kyun na mil jaye, 
       aakhri occurrence confirm karne ke liye pura array index n-1 tak traverse karna padta hai.
   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf do variables (`first`, `last`) aur ek loop variable `i` use hua hai.
     * Total Space: O(1) extra space.
======================================================================
*/

pair <int, int> first_last_occurence(vector<int> &nums, int target){
    int n = nums.size();
    int first = -1, last = -1;
    for(int i = 0; i < n;i++){
        if(nums[i] == target){
            if(first == -1){
                first = i;
            }
            last = i;
        }
    }
    return {first, last};
}

int main(){
    vector <int> nums={2,3,4,6,6,6,6,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last_occurence(nums,n);
    cout<<"The first occurence of "<<n<<" is "<<res.first<<" and last occurence is "<<res.second;
    return 0;
}