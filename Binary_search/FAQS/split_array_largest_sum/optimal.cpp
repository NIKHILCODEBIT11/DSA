#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SPLIT ARRAY LARGEST SUM / PAINTER'S PARTITION / BOOK ALLOCATION):
   - Problem:
     Hume ek array `nums` diya hai jise contiguous subarrays me split karna hai
     (at most `k` parts me, ya `k` painters/students me baantna hai).
     Har split ka sum nikalo, unme jo MAXIMUM sum bane, use hume MINIMIZE
     karna hai ("Minimize the Maximum Subarray Sum").

   - Concept: "Binary Search on Answer Space"
     Array khud sorted nahi hai, par jo humara ANSWER hai (maximum allowed sum per block/painter),
     uski range ek MONOTONIC order follow karti hai:
       Allowed Max Sum:  49 ... 70 ... 71  |  72 ... 172
       Subarrays needed: >k ... >k ...  k  | <=k ...  1
     - Agar allowed sum bohot chhota hoga, toh bohot saare tukde ban jayenge (> k).
     - Agar allowed sum bada kar doge, toh kam tukde banenge (<= k).
     - Is transition boundary par hume pehla aisa minimum sum dhundhna hai jo <= k blocks me fit ho jaye.

   - Search Space Boundaries:
     - `low = *max_element(nums.begin(), nums.end())`:
       Kisi bhi ek subarray ko kam se kam array ka sabse bada single element toh lena hi padega.
       Agar max element 49 hai, toh koi bhi block sum 49 se chhota ho hi nahi sakta!
     - `high = accumulate(nums.begin(), nums.end(), 0)`:
       Worst case: Agar k = 1 ho (sirf 1 hi block bane), toh pura array ek hi chunk me aayega,
       iska sum saare elements ka total sum hoga.

   - Polarity Shift & Return `low`:
     - Jab `size_of_array(nums, mid) <= k`:
       `mid` capacity me kaam ho gaya! Ye ek possible answer ho sakta hai. Lekin hume
       MINIMUM maximum sum chahiye, isliye aur chhota capacity limit try karne left aayenge: `high = mid - 1`.
     - Jab `size_of_array(nums, mid) > k`:
       Capacity bohot chhoti hai, tukde `k` se zyada ban gaye (invalid). Capacity badhani padegi -> `low = mid + 1`.
     - Jab loop end hota hai (`low > high`):
       `high` invalid range par chala jata hai aur `low` pehle valid minimum answer par rukta hai.
       Isliye hum seedhe `return low;` karte hain!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `size_of_array(nums, size)` Helper Function ---
   - `int array_block = 1; int array_elements = 0;`:
     Pehle block se shuru kiya. `array_elements` current block ka running sum track karta hai.
   - `if (array_elements + nums[i] > size)`:
     Agar current element jodte hi block ka sum allowed limit `size` se bada ho jaye:
     - Naya block shuru karo: `array_block++`.
     - Naye block ka pehla element current element ban jayega: `array_elements = nums[i]`.
   - `else array_elements += nums[i];`:
     Agar limit ke andar hai, toh isi block me jodte jao.
   - `return array_block;`:
     Given limit `size` ke hisab se total kitne contiguous blocks bane, wo return kiya.

   --- `splitArray(nums, k)` Main BS Function ---
   - `int low = *max_element(...); int high = accumulate(...);`:
     Valid capacity range `[max_element, sum_of_all]` set ki.
   - `int mid = low + (high - low) / 2;`:
     Test capacity candidate select kiya.
   - `if (size_of_array(nums, mid) <= k) high = mid - 1;`:
     Current capacity valid hai, isse bhi chhota limit check karne left half jao.
   - `else low = mid + 1;`:
     Capacity kam pad rahi hai (tukde > k ban rahe hain), capacity badhao -> right half jao.
   - `return low;`:
     Final minimum valid largest sum return kiya.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [25, 46, 28, 49, 24], k = 4
   Total elements = 5
   low = max(nums) = 49
   high = sum(nums) = 25 + 46 + 28 + 49 + 24 = 172

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 49, high = 172
   mid = 49 + (172 - 49) / 2 = 49 + 61 = 110

   Call size_of_array(nums, size = 110):
     - Block 1: 25 + 46 + 28 = 99 (99 + 49 > 110, so Block 1 ends)
     - Block 2: 49 + 24 = 73
     Total blocks needed = 2.
   Check: blocks <= k (2 <= 4) -> TRUE!
   Action: high = mid - 1 = 110 - 1 = 109
   State: low = 49, high = 109

   --- Iteration 2 ---
   low = 49, high = 109
   mid = 49 + (109 - 49) / 2 = 49 + 30 = 79

   Call size_of_array(nums, size = 79):
     - Block 1: 25 + 46 = 71 (71 + 28 > 79 -> end)
     - Block 2: 28 + 49 = 77 (77 + 24 > 79 -> end)
     - Block 3: 24
     Total blocks needed = 3.
   Check: blocks <= k (3 <= 4) -> TRUE!
   Action: high = mid - 1 = 79 - 1 = 78
   State: low = 49, high = 78

   --- Iteration 3 ---
   low = 49, high = 78
   mid = 49 + (78 - 49) / 2 = 49 + 14 = 63

   Call size_of_array(nums, size = 63):
     - Block 1: 25 (25 + 46 > 63 -> end)
     - Block 2: 46 (46 + 28 > 63 -> end)
     - Block 3: 28 (28 + 49 > 63 -> end)
     - Block 4: 49 (49 + 24 > 63 -> end)
     - Block 5: 24
     Total blocks needed = 5.
   Check: blocks <= k (5 <= 4) -> FALSE!
   Action: low = mid + 1 = 63 + 1 = 64
   State: low = 64, high = 78

   --- Iterations Continue... ---
   Binary search narrows down the boundary:
   At mid = 71:
     - Block 1: 25 + 46 = 71
     - Block 2: 28 (28 + 49 > 71)
     - Block 3: 49 (49 + 24 > 71)
     - Block 4: 24
     Total blocks = 4 (<= 4 -> TRUE) -> high moves down.
   At mid = 70:
     Blocks needed = 5 (> 4 -> FALSE) -> low moves up to 71.

   Final state when low > high:
   high = 70 (Last invalid capacity where blocks > 4)
   low  = 71 (First valid capacity where blocks <= 4)

   Function returns low = 71.
   Output: "The maximum size of subarray is :-71"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Range = sum(nums) - max(nums).
     * Binary Search loop iterations: O(log2(sum - max + 1)).
     * Har iteration me `size_of_array()` pura array linearly scan karta hai: O(N).
     * Overall Time Complexity: O(N * log2(sum - max)).
     * For N = 10^5 and sum = 10^9, total operations ≈ 10^5 * 30 ≈ 3 * 10^6,
       jo standard 1 second limit (< 10^8) me easily pass ho jata hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Sirf standard integer variables (`low`, `high`, `mid`, `array_block`, 
       `array_elements`) use hue hain. Zero extra dynamic memory overhead.
======================================================================
*/

int size_of_array(vector <int> &nums, int size){
    int array_block = 1; int array_elements = 0;
    for(int i = 0; i < nums.size(); i++){
        if(array_elements + nums[i] > size){
            array_block++;
            array_elements = nums[i];
        }
        else{
            array_elements += nums[i];
        }
    }
    return array_block;
}

int splitArray(vector<int>& nums, int k) {
    int n = nums.size();
    int low = *max_element(nums.begin(), nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);
    while(low <= high){
        int mid = low + (high - low)/2;
        if(size_of_array(nums, mid) <= k){
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int assigned_painters=4;
    cout<<"The maximum size of subarray is :-"<<splitArray(nums,assigned_painters);
    return 0;
}