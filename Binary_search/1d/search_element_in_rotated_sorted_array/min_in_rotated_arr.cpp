#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND MINIMUM IN ROTATED SORTED ARRAY):
   - Problem:
     Ek sorted array jo rotate ho chuka hai (unique elements), usme sabse chhota 
     element (minimum) find karna hai in O(log N) time.

   - Core Observation:
     Sorted array ko rotate karne par array do sorted halves me split ho jata hai.
     Minimum element hamesha "Pivot Point" hota hai (jahan drop/inflection point hota hai).
     
   - Golden Binary Search Rule:
     Kisi bhi `mid` par, kam se kam ek half HAMESHA SORTED hoga:
     1. Agar Left Half sorted hai (`nums[low] <= nums[mid]`):
        Toh is pure left half ka sabse chhota element kaun hoga?
        Obvious baat hai: `nums[low]`!
        Isliye `nums[low]` ko apne global answer `mn` ke saath compare karke update kar lo.
        Kyunki left half ka minimum humne already consider kar liya, ab left half me kuch 
        aur dekhne ki zaroorat nahi bachi! Isliye left half ko discard karo aur pivot dhundhne 
        right half jao: `low = mid + 1`.

     2. Agar Right Half sorted hai (`nums[mid] < nums[high]`):
        Toh is right half ka sabse chhota element kaun hoga?
        `nums[mid]`!
        Isliye `nums[mid]` ko `mn` se compare karke save kar lo.
        Ab right half ka minimum mil chuka hai, toh right half ko discard karo aur 
        left half me search space le jao: `high = mid - 1`.

   - Optimization (Search Space Already Sorted Check):
     Agar kisi iteration me `nums[low] <= nums[high]` mil jaye, iska matlab bacha hua 
     sub-array bilkul bhi rotated nahi hai (poori tarah sorted hai).
     Toh bache hue hisse ka minimum seedha `nums[low]` hi hoga!
     Usko `mn` se compare karo aur seedha `break` kar do! Bina kisi aur loop ke turant answer mil jayega.

   - BUG IN GIVEN CODE (Right-sorted block):
     Right-sorted ke andar likha hai:
         if(nums[low] < mn) { mn = min(mn, nums[mid]); }
     Yeh condition `nums[low] < mn` be-matlab aur buggy hai (kyunki left part to unsorted tha).
     Right half sorted hai, toh simple standard statement hona chahiye:
         mn = min(mn, nums[mid]);
         high = mid - 1;

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int mn = INT_MAX;`:
     Answer ko maximum possible integer se initialize kiya taaki pehli comparison me 
     chhota element asani se assign ho sake.
   - `if (nums[low] <= nums[high])`:
     OPTIMIZATION SHORTCUT! Agar current active window already sorted hai, toh sabse 
     chhota element `nums[low]` hi hoga. `mn = min(mn, nums[low]);` karke direct loop break kar do.
   - `if (nums[low] <= nums[mid])`:
     Left half sorted hai -> Is half ka sabse chhota element `nums[low]` hai.
     `mn = min(mn, nums[low]);` kiya aur left half eliminate kiya: `low = mid + 1;`.
   - `else`:
     Right half sorted hai -> Is half ka sabse chhota element `nums[mid]` hai.
     `mn = min(mn, nums[mid]);` kiya aur right half eliminate kiya: `high = mid - 1;`.
   - `return mn;`:
     Search space khatam hone ke baad global minimum return ho jayega.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0    1    2    3    4    5
   Elements: [6,   7,   2,   3,   4,   5]
   n = 6

   Initial State:
   low = 0, high = 5, mn = INT_MAX

   --- Iteration 1 ---
   low = 0, high = 5
   mid = (0 + 5) / 2 = 2
   nums[low] = nums[0] = 6
   nums[mid] = nums[2] = 2
   nums[high] = nums[5] = 5

   1. Check Fully Sorted Shortcut:
      nums[low] <= nums[high] => (6 <= 5) -> FALSE (Window rotated hai).
   2. Identify Sorted Half:
      nums[low] <= nums[mid] => (6 <= 2) -> FALSE!
      => Left part unsorted hai, matlab RIGHT HALF [2..5] SORTED HAI!
   3. Process Right Sorted Half:
      Right half ka minimum element `nums[mid]` (2) hai.
      mn = min(INT_MAX, nums[mid]) = min(INT_MAX, 2) = 2.
      Right half eliminate karo: high = mid - 1 = 2 - 1 = 1.
   State: low = 0, high = 1, mn = 2

   --- Iteration 2 ---
   low = 0, high = 1
   mid = (0 + 1) / 2 = 0
   nums[low] = nums[0] = 6
   nums[mid] = nums[0] = 6
   nums[high] = nums[1] = 7

   1. Check Fully Sorted Shortcut:
      nums[low] <= nums[high] => (6 <= 7) -> TRUE! 
      (Active window [6, 7] already 100% sorted hai!)
   2. Action:
      mn = min(mn, nums[low]) = min(2, 6) = 2.
      break; (Poora binary search yahin khatam, faltu steps bacha liye!)

   Final Output: 2.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Agar array pehle se fully sorted ho (jaise [1, 2, 3, 4, 5]), 
       `nums[low] <= nums[high]` pehli hi step me true hokar break kar dega.
     * Worst Case: O(log2 N) -> Search space har iteration me aadhi (N/2) hoti hai.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer pointers (`low`, `high`, `mid`, `mn`) 
       use hue hain, memory consumption constant hai.
======================================================================
*/

int rotated_min(vector <int>&nums){
    int low=0,high=nums.size()-1,mn=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        
        if(nums[low] <= nums[high]){
            mn = min(mn, nums[low]);
            break;
        }

        // Left-sorted
        if(nums[low]<=nums[mid]){
            if(mn>nums[low]){
                mn=nums[low];
            }
            low=mid+1;
        }

        // Right-sorted
        else {
            mn = min(mn, nums[mid]);
            high = mid - 1; // Right discard karo, left search space me jao
        }
    }
    return mn;
}

int main(){
    vector <int> nums={6,7,2,3,4,5};
    int res=rotated_min(nums);
    cout<<"The minimum in rotated array is "<<res;
    return 0;
}