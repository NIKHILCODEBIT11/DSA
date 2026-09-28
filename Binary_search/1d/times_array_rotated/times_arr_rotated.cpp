#include<bits/stdc++.h>
using namespace std;

//      Similar concept like of finding "MINIMUM" and simply returning the index of that "MINIMUM"

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (ROTATION COUNT KA SECRET):
   - Problem:
     Ek sorted array (unique elements) ko right-rotate kiya gaya hai `k` baar.
     Hume batana hai ki array kitni baar rotate hui hai.

   - The Golden Observation:
     Maan lo original array tha:
       [2, 3, 4, 5, 6, 7]  -> Minimum element 2 kahan hai? Index 0 par! (Rotation = 0)
     1 Baar rotate karo:
       [7, 2, 3, 4, 5, 6]  -> Minimum element 2 kahan hai? Index 1 par! (Rotation = 1)
     2 Baar rotate karo:
       [6, 7, 2, 3, 4, 5]  -> Minimum element 2 kahan hai? Index 2 par! (Rotation = 2)

     Notice the pattern:
     "Number of times the array has been rotated == INDEX OF THE MINIMUM ELEMENT!"
     Matlab pichla wala problem (Find Minimum) aur yeh problem 100% same hain, 
     bas pichli baar hum minimum element ki VALUE return kar rahe the, 
     aur is baar hume minimum element ka INDEX return karna hai!

   - BUG ALERT IN GIVEN CODE (Right-sorted block):
     Right-sorted block me likha hai:
         mn = min(mn, nums[mid]);
         index = mid;
     Problem: Agar `mn` pehle se `nums[mid]` se chhota hua (yaani `nums[mid]` naya minimum NAHI hai), 
     tab bhi `index = mid` bina check kiye execute ho jayega! Isse `index` galat update ho sakta hai.
     Sahi tarika:
         if (nums[mid] < mn) {
             mn = nums[mid];
             index = mid;
         }

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int mn = INT_MAX, index = -1;`:
     Answer aur candidate index ko initialize kiya.
   - `if (nums[low] <= nums[high])`:
     Short-circuit optimization! Agar bachi hui active window already sorted hai, 
     toh is window ka sabse chhota element `nums[low]` hoga. Agar wo current `mn` se chhota hai, 
     toh `index = low` set karo aur loop break karke bahar aa jao.
   - `if (nums[low] <= nums[mid])`:
     Left half sorted hai -> Is half ka sabse chhota candidate `nums[low]` at index `low` hai.
     Agar `nums[low] < mn`, toh update `mn = nums[low]` aur `index = low`.
     Left half ko consider kar liya, toh use discard karke right half explore karo: `low = mid + 1`.
   - `else`:
     Right half sorted hai -> Is half ka sabse chhota candidate `nums[mid]` at index `mid` hai.
     Agar `nums[mid] < mn`, toh update `mn = nums[mid]` aur `index = mid`.
     Right half discard karke left half explore karo: `high = mid - 1`.
   - `return index;`:
     Minimum element ka index hi total number of rotations hota hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0    1    2    3    4    5
   Elements: [6,   7,   2,   3,   4,   5]
   n = 6

   Initial State:
   low = 0, high = 5, mn = INT_MAX, index = -1

   --- Iteration 1 ---
   low = 0, high = 5
   mid = (0 + 5) / 2 = 2
   nums[low] = nums[0] = 6
   nums[mid] = nums[2] = 2
   nums[high] = nums[5] = 5

   1. Check Fully Sorted Shortcut:
      nums[low] <= nums[high] (6 <= 5) -> FALSE.
   2. Identify Sorted Half:
      nums[low] <= nums[mid] (6 <= 2) -> FALSE!
      => Left half rotated/unsorted hai.
      => Pakka RIGHT HALF [2..5] SORTED HAI!
   3. Process Right Sorted Half:
      Right half ka minimum candidate = nums[mid] = nums[2] = 2.
      Kya nums[mid] < mn? (2 < INT_MAX) -> TRUE!
      Action:
        mn = 2
        index = mid = 2
        Right half eliminate karo -> high = mid - 1 = 1
   State: low = 0, high = 1, mn = 2, index = 2

   --- Iteration 2 ---
   low = 0, high = 1
   mid = (0 + 1) / 2 = 0
   nums[low] = nums[0] = 6
   nums[mid] = nums[0] = 6
   nums[high] = nums[1] = 7

   1. Check Fully Sorted Shortcut:
      nums[low] <= nums[high] (6 <= 7) -> TRUE! (Window [6, 7] already fully sorted!)
   2. Action:
      Kya nums[low] < mn? (6 < 2) -> FALSE (2 already chhota hai).
      break; (Loop finished early!)

   Loop Ends.
   Returns: index = 2.
   Output: "The number of times array is rotated is 2" (Correct! [2,3,4,5,6,7] ko 2 baar rotate kiya gaya tha).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Array pehle se fully sorted ho (0 rotations), 
       toh first step me hi `nums[low] <= nums[high]` break kar dega.
     * Worst Case: O(log2 N) -> Binary search har iteration me search boundary ko 
       aadhi karta hai. For N = 6, maximum 3 steps.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables (`low`, `high`, `mid`, `mn`, `index`) 
       use hue hain. Koi recursion stack frame ya extra data structure nahi hai.
======================================================================
*/

int times(vector <int> &nums){
    int low=0,high=nums.size()-1,mn=INT_MAX;
    int index=-1;

    while(low<=high){
        int mid=(low+high)/2;

        // One condition :-     If array is already sorted writing below line because then this code can be used even though rotation is done or not.
        if(nums[low]<=nums[high]){
            if(mn>nums[low]){
                mn=nums[low];
                index=low;
            }
            break;
        }
        
        // left-rotated
        if(nums[low]<=nums[mid]){
            if(mn>nums[low]){
                mn=nums[low];
                index=low;
            }
            low=mid+1;
        }

        // Right-sorted
        else {
            mn = min(mn, nums[mid]);
            index = mid;
            high = mid - 1; // Right discard karo, left search space me jao
        }
    }
    return index;
}


int main(){
    vector <int> nums={6,7,2,3,4,5};
    int res=times(nums);
    cout<<"The number of times array is rotated is "<<res;
    return 0;
}