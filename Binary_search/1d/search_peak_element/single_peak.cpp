#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND PEAK ELEMENT IN AN ARRAY):
   - Problem:
     Hume ek array `nums` diya hai jisme hume ek "Peak Element" dhundhna hai.
     Peak element ka matlab: aisa element jo apne dono bagal wale padosiyo 
     (left neighbor aur right neighbor) se strictly bada ho (`nums[i-1] < nums[i] > nums[i+1]`).
     Array ke boundaries ke bahar imaginary -infinity maana jata hai:
     - Index 0 peak banega agar `nums[0] > nums[1]`.
     - Index n-1 peak banega agar `nums[n-1] > nums[n-2]`.

   - Unsorted Array Me Binary Search Kaise Lag Sakta Hai? (Mountain Analogy):
     Binary Search sirf sorted array par nahi, balki kisi bhi aisi problem par lag sakta hai 
     jahan hum kisi condition ke basis par ek pure half ko eliminate kar sakein!
     Array ko ek pahaad (mountain) ki tarah socho:
     - Case 1: `nums[mid - 1] < nums[mid] > nums[mid + 1]` -> Yeh choti (peak) hai! Direct return karo.
     - Case 2: `nums[mid] < nums[mid + 1]` (Increasing Slope / Chadhai):
       Hum pahaad ke chadhte hue slope par khade hain. Peak pakka RIGHT side me hi hoga 
       (kyunki aage badhne par number badh rahe hain, chahe baad me gir jayein ya array end tak badhte rahein).
       Isliye left half ko eliminate karke right jao: `low = mid + 1`.
     - Case 3: `nums[mid] > nums[mid + 1]` (Decreasing Slope / Dhalan):
       Hum utarte hue slope par hain. Peak pakka LEFT side me hoga (kyunki piche chadhai thi).
       Isliye right half ko eliminate karke left jao: `high = mid - 1`.

   - Boundary Protection Trick (`low = 1`, `high = n - 2`):
     Har step par `nums[mid - 1]` aur `nums[mid + 1]` check karna hota hai.
     Agar `mid = 0` ho jaye toh `mid - 1` segmentation fault dega.
     Agar `mid = n - 1` ho jaye toh `mid + 1` out-of-bounds crash karega.
     Isliye:
     - Index 0 aur Index n-1 ko hum loop shuru hone se PEHLE hi alag se check karke handle kar lete hain.
     - Binary search ko hum strictly `[1 ... n - 2]` ke safe zone me chalate hain.
     - Isse `mid - 1` aur `mid + 1` hamesha 100% valid memory par access hote hain!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (nums.size() == 1) return nums[0];`:
     Single element array: Bahar -infinity hone ki wajah se akela element hi peak hota hai.
   - `else if (nums[0] > nums[1]) return nums[0];`:
     Leftmost boundary check: Agar pehla element dusre se bada hai, wahi peak hai.
   - `else if (nums[nums.size() - 1] > nums[nums.size() - 2]) return nums[nums.size() - 1];`:
     Rightmost boundary check: Agar aakhri element second-last se bada hai, wahi peak hai.
   - `int low = 1; int high = nums.size() - 2;`:
     Safe search boundary: Range ko 1 se n-2 tak restrict kiya taaki koi out-of-bounds access na ho.
   - `if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return nums[mid];`:
     Peak condition hit! Element apne dono padosiyo se bada hai -> answer mil gaya.
   - `else if (nums[mid] < nums[mid + 1]) low = mid + 1;`:
     Increasing slope (chadhai): Peak right half me lie karega, left side discard karo.
   - `else high = mid - 1;`:
     Decreasing slope (dhalan): Peak left half me lie karega, right side discard karo.
   - `return -1;`:
     Array boundaries par -infinity hone ki wajah se kam se kam ek peak exist karega hi karega.
     Yeh line mathematically unreachable hai, par function ke return type `int` ko satisfy karne ke liye safe fallback hai.

======================================================================
3. DETAILED DRY RUN:

   Array:
   Indices:   0   1   2    3    4   5   6   7   8
   Elements: [2,  3,  4,  12,  13,  7,  6,  4,  3]
   n = 9

   -------------------------------------------------------------------
   PRE-CHECKS (Edge Cases):
   -------------------------------------------------------------------
   1. nums.size() == 1 ? (9 == 1) -> FALSE.
   2. nums[0] > nums[1] ? (2 > 3) -> FALSE.
   3. nums[8] > nums[7] ? (3 > 4) -> FALSE.
   None of boundaries are peaks. Proceed to Binary Search in range [1 ... 7].

   -------------------------------------------------------------------
   BINARY SEARCH EXECUTION:
   -------------------------------------------------------------------
   Initial Range: low = 1, high = 7

   --- Iteration 1 ---
   low = 1, high = 7 (1 <= 7 -> True)
   mid = (1 + 7) / 2 = 4
   nums[mid - 1] = nums[3] = 12
   nums[mid]     = nums[4] = 13
   nums[mid + 1] = nums[5] = 7

   Peak Check:
     nums[4] > nums[3] && nums[4] > nums[5]
     => 13 > 12 && 13 > 7 -> TRUE && TRUE -> TRUE!
   Action:
     Peak condition satisfied!
     return nums[mid] => return 13.
   Function terminates immediately!

   Output: "The single peak element is 13"

   -------------------------------------------------------------------
   SECONDARY DRY RUN (Multiple Iterations Walkthrough, e.g. Peak at Index 2):
   Array: [1, 2, 8, 4, 3] (n = 5)
   low = 1, high = 3
   - Iteration 1:
     mid = (1 + 3) / 2 = 2
     nums[1]=2, nums[2]=8, nums[3]=4
     8 > 2 && 8 > 4 -> TRUE -> returns 8.
   If mid had landed on slope [1, 2, 3, 4, 5]:
     nums[mid] < nums[mid + 1] would drive search rightward to catch the rising peak.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Edge case checks (size, first, last element): O(1).
     * Binary Search loop: Har iteration me search boundary `[low ... high]` aadhi ho rahi hai (N/2).
     * Best Case: O(1) -> Agar index 0, n-1, ya pehla calculate hua `mid` hi peak ho.
     * Worst Case: O(log2 N) -> Search space shrinks from N to 1.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra array, vector ya recursion call stack use nahi hua.
     * Sirf do pointers (`low`, `high`) aur ek scalar variable (`mid`) memory me ban rahe hain.
======================================================================
*/

int single(vector <int>&nums){
    int low=1;
    int high=nums.size()-2;

    if(nums.size()==1){
        return nums[0];
    }
    // Checking for first and last index
    else if(nums[0]>nums[1]){
        return nums[0];
    }
    else if(nums[nums.size()-1]>nums[nums.size()-2]){
        return nums[nums.size()-1];
    }
    else{
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1]){
                return nums[mid];
            }
            else{
                if(nums[mid]<nums[mid+1]){
                    low=mid+1;
                }
                else{
                    high=mid-1;
                }
            }
        }
    }
    return -1;      // This line will never never be executed but just to respect return type of function it is written.
}

int main(){
    vector <int> nums={2,3,4,12,13,7,6,4,3};
    int res=single(nums);
    cout<<"The single peak element is "<<res;
    return 0;
}