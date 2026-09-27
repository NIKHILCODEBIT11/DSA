#include<bits/stdc++.h>
#include<vector>

using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS:
   - Problem: Hume ek sorted array `nums` me ek `target` element dhundhna hai aur uska index return karna hai. Agar nahi mila toh -1 return karna hai.
   - Brute Force: Ek loop chalao index 0 se n-1 tak (Linear Search). Time lagega O(N).
   - Core Intuition (Binary Search):
     Array already sorted hai! Yeh sabse bada clue hai.
     Agar tum dictionary me koi word dhundhte ho, toh pehle page se shuru nahi karte; tum dictionary ko beech se kholte ho.
     - Beech ka word agar target se chhota hai -> Iska matlab target hamesha right half me hi hoga. Left half ko dekhne ki bhi zaroorat nahi.
     - Beech ka word agar target se bada hai -> Iska matlab target hamesha left half me hoga. Right half ko discard kar do.
     - Beech ka word barabar hai -> Mil gaya element!
   - Har comparison ke baad humara search space aadha (half) ho jata hai (N -> N/2 -> N/4 -> ... -> 1).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int low = 0, high = n - 1;`:
     Search space boundary set kar rahe hain. Abhi target index 0 se leke n-1 ke beech kahin bhi ho sakta hai.
   - `while(low <= high)`:
     Jab tak search boundary valid hai (yaani kam se kam 1 element bacha hai check karne ko), tab tak loop chalega.
     Jab `low > high` ho jata hai, matlab search space khatam ho gaya aur element pure array me kahin nahi tha.
   - `int mid = (low + high) / 2;`:
     Current search range ka exact middle index calculate kiya.
     *(Note: Extreme large values ke case me integer overflow se bachne ke liye standard practice `low + (high - low) / 2` hoti hai).*
   - `if (nums[mid] == target) return mid;`:
     Direct hit! Target mil gaya, uska index return karke function exit.
   - `else if (nums[mid] < target)` -> `low = mid + 1;`:
     Middle element target se chhota hai. Kyunki array sorted hai, `mid` aur uske piche ke saare elements target se chhote hi honge.
     Isliye left side ko eliminate karke apni search range right side shift ki: `low = mid + 1`.
   - `else` -> `high = mid - 1;`:
     Middle element target se bada hai (`nums[mid] > target`). Toh `mid` aur uske aage ke saare elements target se bade honge.
     Isliye right side ko eliminate karke search range left side shift ki: `high = mid - 1`.
   - `return -1;`:
     Pura loop khatam ho gaya par element nahi mila, toh -1 return karo.

======================================================================
3. DETAILED DRY RUN:
   Input: nums = [2, 3, 5, 6, 17, 19], n = 6
   Target: 17

   Initial State:
   low = 0, high = 5

   --- Iteration 1 ---
   Check Condition: low <= high (0 <= 5) -> TRUE
   mid = (0 + 5) / 2 = 2
   nums[mid] = nums[2] = 5
   Compare:
     nums[mid] == 17 ? (5 == 17) -> FALSE
     nums[mid] < 17  ? (5 < 17)  -> TRUE
   Action:
     Target right side me hai.
     low = mid + 1 = 2 + 1 = 3
   Boundary updated: low = 3, high = 5

   --- Iteration 2 ---
   Check Condition: low <= high (3 <= 5) -> TRUE
   mid = (3 + 5) / 2 = 4
   nums[mid] = nums[4] = 17
   Compare:
     nums[mid] == 17 ? (17 == 17) -> TRUE
   Action:
     Element mil gaya! Return mid -> Return 4.
   Loop stops, function exits with answer = 4.

   --- Edge Case Walkthrough (Target not present, e.g., target = 4) ---
   Iter 1: low=0, high=5 -> mid=2 (nums[2]=5). 5 > 4 -> high = mid - 1 = 1.
   Iter 2: low=0, high=1 -> mid=0 (nums[0]=2). 2 < 4 -> low = mid + 1 = 1.
   Iter 3: low=1, high=1 -> mid=1 (nums[1]=3). 3 < 4 -> low = mid + 1 = 2.
   Iter 4: low=2, high=1 -> Condition (low <= high) -> (2 <= 1) -> FALSE.
   Loop terminates -> returns -1 (Correct).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Target pehli hi koshish me array ke middle index par mil jaye.
     * Worst Case: O(log N) -> Target array ke extreme ends par ho ya array me ho hi nahi.
       Kyun? Har step me range aadhi ho rahi hai: N -> N/2 -> N/4 -> ... -> 1.
       Toh total steps = log2(N). For N = 6, maximum 3-4 steps lagenge.
     * Average Case: O(log N).

   - Space Complexity (SC):
     * O(1) (Auxiliary / Extra Space) -> Sirf 4 integer variables (`n`, `low`, `high`, `mid`) use kiye hain. 
       Koi extra dynamic memory ya recursive stack use nahi hua.
======================================================================
*/

int search(vector <int>& nums,int target){
    int n=nums.size();
    int low=0;
    int high=n-1;

    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={2,3,5,6,17,19};
    int n;
    cout<<"Enter target : ";
    cin>>n;
    int res=search(nums,n);
    if(res!=-1){
        cout<<"The target is at index "<<res;
    }
    else{
        cout<<"No occurence";
    }
    return 0;
}

