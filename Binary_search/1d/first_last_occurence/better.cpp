#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIRST & LAST OCCURRENCE USING LB & UB):
   - Problem: Sorted array me target ka first aur last occurrence index find 
     karna hai in O(log N) time.
   
   - Core Intuition (Lower Bound & Upper Bound ka direct relation):
     Sorted array me duplicates hamesha saath-saath (contiguous block me) hote hain:
       Example: [2, 4, 6, 6, 6, 6, 17]
                       ^        ^  ^
                     first    last  UB
     
     * First Occurrence:
       Lower Bound kya dhundhta hai? Pehla element jahan `nums[i] >= target`.
       Agar target array me present hai, toh pehla element jo `>= target` hoga, 
       woh KHUD target hi hoga! Isliye:
       `First Occurrence = lower_bound(target)`.
     
     * Last Occurrence:
       Upper Bound kya dhundhta hai? Pehla element jahan `nums[i] > target` (Strictly greater).
       Array sorted hai, toh target se strictly bade number se theek pehle wala index (ek piche) 
       hamesha target ka aakhri occurrence hi hoga! Isliye:
       `Last Occurrence = upper_bound(target) - 1`.

   - TARGET ABSENT CHECK & UNDEFINED BEHAVIOR (Short-Circuit Evaluation):
     Target array me nahi hai, iske do scenarios hote hain:
     1. Target array ke saare elements se bada hai:
        Lower bound loop khatam hone par default `n` (yaani `nums.size()`) return karega.
     2. Target array ke range ke andar hai par exist nahi karta (jaise target = 5):
        Lower bound 5 se bada pehla number dhundh lega (e.g. 6 at index 3), 
        lekin `nums[3] != 5`.

     Condition check: `if (lower == nums.size() || nums[lower] != target)`
     * SHORT-CIRCUIT EVALUATION:
       C++ me `||` (OR operator) left-to-right evaluate hota hai.
       Agar left condition `lower == nums.size()` TRUE ho jati hai, 
       toh compiler right condition `nums[lower] != target` ko CHECK BHI NAHI KARTA!
     * KYUN YEH CRITICAL HAI?
       Agar tum sirf `if (nums[lower] != target)` likhoge, aur target sabse bada nikla, 
       toh `lower = n` hoga. `nums[n]` access karna matlab **Out-of-Bounds Memory Access**, 
       jo C++ me **Undefined Behavior (UB)** create karta hai (crash/segmentation fault).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int lower = lower_(nums, target);` :
     Pehla index dhundha jahan value `>= target` ho.
   - `int upper = upper_(nums, target);` :
     Pehla index dhundha jahan value `> target` ho.
   - `if (lower == nums.size() || nums[lower] != target)` :
     Safety guard + existence check:
     * `lower == nums.size()` -> Target sabse bada tha, out-of-bounds jane se bacha liya.
     * `nums[lower] != target` -> Target array me tha hi nahi (lower bound ne usse bada koi number pakad liya).
     * Dono me se koi bhi baat sach hui toh target absent hai -> return `{-1, -1}`.
   - `return {lower, upper - 1};` :
     Agar target present hai, toh `lower` exact pehla index hai aur `upper - 1` exact aakhri index hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Flow):

   Array:
   Indices:   0   1   2   3   4   5   6   7   8   9
   Elements: [2,  3,  4,  6,  6,  6,  6,  6, 17, 19]
   n = 10

   -------------------------------------------------------------------
   CASE 1: Target Present (target = 6)
   -------------------------------------------------------------------
   Step 1: Find Lower Bound (first index with val >= 6)
           lower_(nums, 6) -> binary search narrows down to index 3 (val = 6).
           lower = 3.

   Step 2: Find Upper Bound (first index with val > 6)
           upper_(nums, 6) -> binary search narrows down to index 8 (val = 17).
           upper = 8.

   Step 3: Verification Check:
           lower == 10 (3 == 10) -> FALSE
           nums[lower] != 6 (nums[3] != 6 => 6 != 6) -> FALSE
           Toh target successfully present hai!

   Step 4: Result Formulation:
           first = lower = 3
           last  = upper - 1 = 8 - 1 = 7
           Returns: {3, 7}  (Indices 3, 4, 5, 6, 7 par 6 maujood hai)

   -------------------------------------------------------------------
   CASE 2: Target NOT Present [In Range] (target = 5)
   -------------------------------------------------------------------
   Step 1: lower_(nums, 5) -> Pehla element >= 5 index 3 par hai (nums[3] = 6).
           lower = 3.
   Step 2: Verification:
           lower == 10 (3 == 10) -> FALSE
           nums[3] != 5 (6 != 5) -> TRUE!
           Condition trigger hui -> return {-1, -1}.

   -------------------------------------------------------------------
   CASE 3: Target NOT Present [Out of Range / Too Large] (target = 25)
   -------------------------------------------------------------------
   Step 1: lower_(nums, 25) -> Koi element >= 25 nahi mila. Default return `ans = 10` (n).
           lower = 10.
   Step 2: Verification:
           lower == nums.size() (10 == 10) -> TRUE!
           Short-circuit triggers! `nums[10]` check hi nahi hua (Saved from crash!).
           Immediately return {-1, -1}.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * `lower_()` : O(log2 N)
     * `upper_()` : O(log2 N)
     * Target verification & return: O(1)
     * Total Time Complexity: O(log2 N) + O(log2 N) = O(log2 N).
       (Linear search ke O(N) ke muqable exponentially fast!)

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard variable pointers use kiye hain, 
       koi recursion stack ya extra auxiliary data structures use nahi hue.
======================================================================
*/

int lower_(vector <int>& nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();

    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ans=mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
    }
    return ans;
}

int upper_(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>target){
            ans=mid;
            high=mid-1;
        }
        else if(nums[mid]<=target){
            low=mid+1;
        }
    }
    return ans;
}

pair<int,int> first_last(vector <int> &nums,int target){
    int lower=lower_(nums,target);
    int upper=upper_(nums,target);
    if(lower==nums.size() || nums[lower]!=target){
        return {-1,-1};
    }
    else{
        return {lower,upper-1};
    }
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    cout<<"The first occurence of "<<n<<" is "<<res.first<<" and last occurence is "<<res.second;
    return 0;
}


/*

Undefined Behavior (Important Concept) :-

------> If i just write              if(nums[lower]!=target)        instead of      if(lower==nums.size() || nums[lower]!=target)    

Undefined Behavior means:

Program may crash

Program may print random values

Program may seem to work today and fail tomorrow

Compiler is allowed to do anything

*/