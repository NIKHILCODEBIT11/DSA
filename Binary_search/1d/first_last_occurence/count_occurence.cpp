#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (COUNT OCCURRENCES IN A SORTED ARRAY):
   - Problem:
     Ek sorted array di gayi hai. Hume kisi target element ki total frequency 
     (wo array me kitni baar aaya hai) count karke batani hai.

   - Brute Force Approach:
     Array ko 0 se n-1 tak linearly traverse karo aur count++ karte jao.
     Time Complexity: O(N). Par kyunki array SORTED hai, linear search karna 
     sorted property ko waste karna hoga.

   - Core Intuition (The Mathematical Formula):
     Sorted array me kisi bhi number ke saare duplicates ek continuous block 
     (saath-saath) me baithe hote hain.
     Example: [2, 3, 4, 6, 17, 17, 17, 19]
                           ^       ^
                         first    last
                         (idx 4) (idx 6)

     Agar hume target ka:
       - First occurrence index mil jaye (`first`)
       - Last occurrence index mil jaye (`last`)
     Toh total elements count karne ke liye loop chalane ki koi zaroorat nahi hai!
     Seedha standard range formula use hota hai:
         Total Count = (last - first + 1)
     Yahan: (6 - 4 + 1) = 3 occurrences!

   - Edge Case (Target Absent):
     Agar target array me exist hi nahi karta, toh `first` ki value `-1` hogi.
     Aise case me formula apply kiye bina seedha `return 0;` karna zaroori hai, 
     warna galat arithmetic ho sakti hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `first_()` Function ---
   - Pehla occurrence dhundhne ke liye binary search:
     Jab `nums[mid] == target` mil jaye, toh `first = mid;` save karte hain 
     aur `high = mid - 1;` karke left side explore karte hain taaki pehla 
     index pakad sakein. Missing hone par `-1` return karta hai.

   --- `last_()` Function ---
   - Aakhri occurrence dhundhne ke liye binary search:
     Jab `nums[mid] == target` mil jaye, toh `last = mid;` save karte hain 
     aur `low = mid + 1;` karke right side explore karte hain taaki aakhri 
     index pakad sakein.

   --- `first_last()` Function ---
   - Early Exit Optimization:
     Pehle `first_(nums, target)` call hota hai. Agar `first == -1` aa gaya, 
     toh turant `{-1, -1}` return kar diya. `last_()` call hi nahi hota 
     (bina wajah ka ek O(log N) bacha liya).

   --- `count_()` Function ---
   - `if (res.first == -1) return 0;`:
     Target exist nahi karta toh count seedhe 0.
   - `return res.second - res.first + 1;`:
     Inclusive boundary formula laga kar total frequency direct O(1) me calculate kar li.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0   1   2   3   4    5    6    7
   Elements: [2,  3,  4,  6, 17,  17,  17,  19]
   n = 8
   Target = 17

   -------------------------------------------------------------------
   STEP 1: Find First Occurrence -> first_(nums, 17)
   -------------------------------------------------------------------
   Initial: low = 0, high = 7, first = -1

   [Call 1]
   low = 0, high = 7 -> mid = 3
   nums[3] = 6
   6 < 17 -> low = mid + 1 = 4

   [Call 2]
   low = 4, high = 7 -> mid = 5
   nums[5] = 17 == 17 (Match!)
   Action: first = 5, high = mid - 1 = 4

   [Call 3]
   low = 4, high = 4 -> mid = 4
   nums[4] = 17 == 17 (Match!)
   Action: first = 4, high = mid - 1 = 3

   Condition (low <= high): 4 <= 3 -> FALSE. Loop stops.
   first = 4.

   -------------------------------------------------------------------
   STEP 2: Find Last Occurrence -> last_(nums, 17)
   -------------------------------------------------------------------
   Initial: low = 0, high = 7, last = -1

   [Call 1]
   low = 0, high = 7 -> mid = 3
   nums[3] = 6
   6 < 17 -> low = mid + 1 = 4

   [Call 2]
   low = 4, high = 7 -> mid = 5
   nums[5] = 17 == 17 (Match!)
   Action: last = 5, low = mid + 1 = 6

   [Call 3]
   low = 6, high = 7 -> mid = 6
   nums[6] = 17 == 17 (Match!)
   Action: last = 6, low = mid + 1 = 7

   [Call 4]
   low = 7, high = 7 -> mid = 7
   nums[7] = 19
   19 > 17 -> high = mid - 1 = 6

   Condition (low <= high): 7 <= 6 -> FALSE. Loop stops.
   last = 6.

   -------------------------------------------------------------------
   STEP 3: Frequency Calculation in count_()
   -------------------------------------------------------------------
   res = {first = 4, last = 6}
   res.first != -1
   Count = res.second - res.first + 1
         = 6 - 4 + 1
         = 3.

   Final Output: "The total number of occurences of 17 is 3".

   -------------------------------------------------------------------
   EDGE CASE: Target Absent (target = 5)
   - `first_(nums, 5)` returns -1.
   - `first_last()` detects `first == -1` -> immediately returns `{-1, -1}`.
   - `count_()` detects `res.first == -1` -> immediately returns 0.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Case 1: Target Present:
       `first_()` takes O(log2 N) + `last_()` takes O(log2 N) + Math formula O(1)
       = 2 * log2 N => O(log N).
     * Case 2: Target Absent:
       Only `first_()` executes => 1 * log2 N => O(log N).
       (Linear search ke O(N) ke muqable dramatically fast).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Pure iterative binary search use hua hai. 
       Koi recursion stack ya auxiliary array use nahi kiya gaya.
======================================================================
*/

int first_(vector<int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int first=-1,last=-1;              //      int first,last=-1;     Writing like this is wrong         
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            high=mid-1;
            first=mid;
        }
        else{
            high=mid-1;
        }
    }
    return first;
}

int last_(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int last=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            last=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return last;
}

pair <int,int> first_last(vector <int>&nums,int target){
    int first=first_(nums,target);
    if(first==-1){
        return {-1,-1};
    }
    int last=last_(nums,target);
    return {first,last};
}

int count_(vector<int> &nums,int target){
    pair <int,int> res=first_last(nums,target);
    if(res.first==-1){
        return 0;
    }
    else{
        return res.second-res.first+1;          //      Count       =       (last-first+1)
    }
}
int main(){
    vector <int> nums={2,3,4,6,17,17,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    int count=count_(nums,n);
    cout<<"The total number of occurences of "<<n<<" is "<<count;
    return 0;
}