#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (CAPACITY TO SHIP PACKAGES - OPTIMAL BINARY SEARCH):
   - Problem:
     Hume ek array `nums` (weights) aur ek limit `threshold_days` (D) di gayi hai.
     Hume ship ki aisi MINIMUM weight capacity nikalni hai taaki saare packages 
     order me load hokar `threshold_days` ke andar deliver ho jayein.

   - Monotonic Search Space (Binary Search on Answers):
     - Minimum possible capacity (`low`): `max_element(nums)`
       Agar capacity array ke sabse bhaari package se kam hui, toh wo package kabhi 
       ship me load hi nahi ho payega.
     - Maximum possible capacity (`high`): `accumulate(nums)` (Total sum of weights)
       Agar capacity total sum ke barabar kar de, toh saare packages Day 1 par hi 
       ek saath ship ho jayenge (Days taken = 1). Isse badi capacity lene ka koi faida nahi.
     - Search range: `[max_element ... sum_of_elements]`.

   - Monotonic Nature & Polarity Switch:
     - Jaise jaise ship ki capacity `mid` BADHTI hai, per day zyada packages load hote hain, 
       isliye total days required GHAT-te hain (Monotonic function).
     - Pattern of validity across search space:
       Capacity:    max   ...   C-1    C     C+1  ...   TotalSum
       Valid?     [ False ...  False | True  True ...   True   ]
     - Hume pehli valid capacity `C` (Smallest True) nikalni hai.
     - Binary Search ki Polarity Switch:
       * `low` shuru hota hai invalid side (days > threshold_days).
       * `high` shuru hota hai valid side (days <= threshold_days).
       * Jab `days_required(mid) <= threshold_days`:
         Capacity sufficient hai, par hume aur MINIMUM capacity chahiye, 
         toh left jao: `high = mid - 1`.
       * Jab `days_required(mid) > threshold_days`:
         Capacity bohot kam hai, din zyada lag rahe hain, capacity badhao: 
         `low = mid + 1`.
       * Jab loop break hota hai (`low > high`):
         `high` last INVALID capacity par rukta hai.
         `low` theek first VALID (MINIMUM required capacity) par rukta hai!
         Isliye seedhe `return low;` answer deta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `days_required(wts, capacity)` ---
   - `int load = 0, days = 1;` :
     Pehle din ki loading start ki (`days = 1`), aur current day ka initial load zero rakha.
   - `if (load + wts[i] > capacity)` :
     Agar agla package dalne se capacity exceed ho rahi hai:
     - `days += 1;` -> Pichla batch ship hua, naya din shuru.
     - `load = wts[i];` -> Overload karne wala package agle din ka pehla load bana.
   - `else load += wts[i];` :
     Capacity bachi hai, bina naya din shuru kiye usi ship me samaan add kiya.
   - `return days;` :
     Given capacity ke liye total kitne din lage deliver karne me.

   --- `final_capacity(nums, threshold_days)` ---
   - `int low = *max_element(...); int high = accumulate(...);` :
     Binary search boundaries set ki: lowest possible viable capacity se absolute maximum capacity tak.
   - `int mid = low + (high - low) / 2;` :
     Overflow-safe candidate capacity calculate ki.
   - `if (days_required(nums, mid) <= threshold_days) high = mid - 1;` :
     Target days ke andar delivery ho gayi (Valid)! 
     Par minimum capacity dhundhne ke liye left half explore kiya.
   - `else low = mid + 1;` :
     Days zyada lag gaye (Invalid), ship bohot chhota hai, capacity badhane ke liye right half gaye.
   - `return low;` :
     Polarity swap ke baad `low` directly minimum valid capacity ko point karta hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], threshold_days = 5
   low = max(nums) = 10
   high = sum(nums) = 55

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 10, high = 55
   mid = 10 + (55 - 10) / 2 = 32

   Call days_required(nums, capacity = 32):
     - Day 1: 1+2+3+4+5+6+7 = 28 (next is 8 -> 28+8=36 > 32)
     - Day 2: 8+9+10 = 27
     Total Days = 2
   Check: 2 <= 5 -> TRUE (Valid, par chhota capacity dhundho)
   Action: high = mid - 1 = 32 - 1 = 31
   State: low = 10, high = 31

   --- Iteration 2 ---
   low = 10, high = 31
   mid = 10 + (31 - 10) / 2 = 20

   Call days_required(nums, capacity = 20):
     - Day 1: 1+2+3+4+5 = 15 (next is 6 -> 21 > 20)
     - Day 2: 6+7 = 13 (next is 8 -> 21 > 20)
     - Day 3: 8+9 = 17 (next is 10 -> 27 > 20)
     - Day 4: 10
     Total Days = 4
   Check: 4 <= 5 -> TRUE (Valid!)
   Action: high = mid - 1 = 20 - 1 = 19
   State: low = 10, high = 19

   --- Iteration 3 ---
   low = 10, high = 19
   mid = 10 + (19 - 10) / 2 = 14

   Call days_required(nums, capacity = 14):
     - Day 1: 1+2+3+4 = 10 (next is 5 -> 15 > 14)
     - Day 2: 5+6 = 11 (next is 7 -> 18 > 14)
     - Day 3: 7
     - Day 4: 8
     - Day 5: 9
     - Day 6: 10
     Total Days = 6
   Check: 6 <= 5 -> FALSE (Too slow, deadline miss!)
   Action: low = mid + 1 = 14 + 1 = 15
   State: low = 15, high = 19

   --- Iteration 4 ---
   low = 15, high = 19
   mid = 15 + (19 - 15) / 2 = 17

   Call days_required(nums, capacity = 17):
     - Day 1: 1+2+3+4+5 = 15
     - Day 2: 6+7 = 13
     - Day 3: 8+9 = 17
     - Day 4: 10
     Total Days = 4
   Check: 4 <= 5 -> TRUE (Valid!)
   Action: high = mid - 1 = 17 - 1 = 16
   State: low = 15, high = 16

   --- Iteration 5 ---
   low = 15, high = 16
   mid = 15 + (16 - 15) / 2 = 15

   Call days_required(nums, capacity = 15):
     - Day 1: 1+2+3+4+5 = 15
     - Day 2: 6+7 = 13
     - Day 3: 8
     - Day 4: 9
     - Day 5: 10
     Total Days = 5
   Check: 5 <= 5 -> TRUE (Valid!)
   Action: high = mid - 1 = 15 - 1 = 14
   State: low = 15, high = 14

   --- Loop Terminate ---
   Condition: low <= high (15 <= 14) -> FALSE! Loop ends.

   Polarity Switch Summary:
   Capacity:     10 ... 14  |  15   16   17 ... 55
   Status:       No ... No  |  Yes  Yes  Yes ... Yes
                        ^       ^
                       high    low

   high = 14 (Last invalid capacity)
   low  = 15 (First valid / MINIMUM capacity)

   Return low -> 15.
   Output: "The minimum capacity of ship is 15"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Sum = sum of all weights, Max = max element in nums.
     * Initial boundary setup: `*max_element` takes O(N) aur `accumulate` takes O(N).
     * Binary Search space range = (Sum - Max + 1).
     * Binary search loop runs: O(log2(Sum - Max)) iterations.
     * Har iteration me `days_required()` N elements traverse karta hai: O(N).
     * Total Time Complexity: O(N) + O(N * log2(Sum - Max)) = O(N * log2(Sum - Max)).
     * Brute force O(N * (Sum - Max)) ke muqable yeh massively fast hai 
       (e.g., Sum - Max = 10^7 ke liye linear 10^7 checks lega jabki binary search sirf ~24 checks lega).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf scalar variables (`low`, `high`, `mid`, `load`, `days`) 
       use hue hain, koi extra array ya recursive stack use nahi hua.
======================================================================
*/

int days_required(vector <int> &wts,int capacity){      // 1    2   3   4   5   6   7   8   9   10      days=5
    int load=0,days=1;
    for(int i=0;i<wts.size();i++){
        if(load+wts[i]>capacity){
            days+=1;
            load=wts[i];
        }
        else{
            load+=wts[i];
        }
    }
    return days;
}

int final_capacity(vector<int> &nums,int threshold_days){
    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    while(low<=high){
        int mid=low+(high-low)/2;
        if(days_required(nums,mid)<=threshold_days){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;
}

int main(){
    vector <int> wts={1,2,3,4,5,6,7,8,9,10};
    int threshold_days=5;
    int capacity=final_capacity(wts,threshold_days);
    cout<<"The minimum capacity of ship is "<<capacity;
    return 0;
}