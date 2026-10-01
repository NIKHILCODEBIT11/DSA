#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FIND PEAK ELEMENT IN AN ARRAY):
   - Problem:
     Hume ek array `nums` diya hai aur hume ek "Peak Element" return karna hai.
     Peak Element ki property:
     Wo apne left neighbor aur right neighbor dono se strictly BADA hota hai:
     `nums[i] > nums[i - 1]` && `nums[i] > nums[i + 1]`.

   - Real-Life Analogy (Mountain Peak):
     Socho tum ek pahad par chadh rahe ho aur tumhare aage-piche dhalan (slope) hai:
     - Agar aage wala rasta upar ja raha hai (`nums[mid] < nums[mid + 1]`), 
       iska matlab pahad ki choti (peak) tumhare aage (right side) hi hogi.
     - Agar piche wala rasta upar tha aur aage rasta niche gir raha hai (`nums[mid] < nums[mid - 1]`), 
       matlab tum choti cross kar chuke ho, choti piche (left side) reh gayi hai.
     - Agar tumhare piche aur aage dono taraf dhalan niche hai (`nums[mid] > nums[mid - 1]` 
       && `nums[mid] > nums[mid + 1]`), badhai ho, tum choti (peak) par hi khade ho!

   - Edge Cases Ko Pehle Handle Karne Ka Genius Reason:
     Index `0` ka koi left neighbor nahi hota, aur index `n - 1` ka koi right neighbor nahi hota.
     Agar hum direct Binary Search range `[0 ... n - 1]` par chalate, toh `mid - 1` aur 
     `mid + 1` check karte waqt Out-Of-Bounds (Runtime Error) aa jata.
     Isliye:
     1. Size = 1 check kar liya -> wahi a अकेला element peak hai.
     2. Index 0 check kar liya -> agar `nums[0] > nums[1]`, peak mil gaya.
     3. Index n-1 check kar liya -> agar `nums[n - 1] > nums[n - 2]`, peak mil gaya.
     4. Iske baad safe hokar search space sirf internal elements par set kiya:
        `low = 1` aur `high = n - 2`. Ab `mid - 1` aur `mid + 1` hamesha valid rahenge!

   - LeetCode Standard Note:
     LeetCode problem 162 me peak ka *INDEX* return karne bola jata hai (`return mid;`), 
     jabki tumhare code me peak ki *VALUE* return ho rahi hai (`return nums[mid];`). 
     Dono ka core logic 100% same hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n == 1) return nums[0];`:
     Single element array me wahi akele peak hota hai.
   - `if (nums[0] > nums[1]) return nums[0];`:
     Left boundary check: Agar array starting se hi girna shuru ho raha hai, 
     toh 0th element hi peak hai.
   - `if (nums[n - 1] > nums[n - 2]) return nums[n - 1];`:
     Right boundary check: Agar array lagataar badhta hi ja raha hai, 
     toh aakhri element hi peak hai.
   - `int low = 1, high = n - 2;`:
     Boundaries shrink kar di taaki `mid - 1` aur `mid + 1` kabhi out-of-bounds na jayein.
   - `if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) return nums[mid];`:
     Current element apne dono neighbors se bada hai -> Peak found!
   - `else if (nums[mid] < nums[mid - 1]) high = mid - 1;`:
     Left neighbor bada hai, yaani hum decreasing slope par hain. 
     Peak left side me guarantee exist karegi -> Left half jao.
   - `else if (nums[mid] < nums[mid + 1]) low = mid + 1;`:
     Right neighbor bada hai, yaani hum increasing slope par hain. 
     Peak right side me guarantee exist karegi -> Right half jao.
   - `return -1;`:
     Unreachable code, safe fallback (kyunki kisi bhi finite array me at least ek peak zaroor hota hai).

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [1, 2, 3, 4, 5, 6, 9, 8, 7]
   n = 9
   Indices: 0  1  2  3  4  5  6  7  8
   Values:  1  2  3  4  5  6  9  8  7

   --- Edge Cases Check ---
   1. n == 1 ? (9 == 1) -> FALSE.
   2. nums[0] > nums[1] ? (1 > 2) -> FALSE.
   3. nums[8] > nums[7] ? (7 > 8) -> FALSE.
   Safe search range: low = 1, high = n - 2 = 7.

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 7
   mid = 1 + (7 - 1) / 2 = 4
   nums[mid] = nums[4] = 5

   Neighbors of mid:
     Left neighbor:  nums[mid - 1] = nums[3] = 4
     Right neighbor: nums[mid + 1] = nums[5] = 6

   Checks:
     1. nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        5 > 4 (True) && 5 > 6 (False) -> Overall FALSE.
     2. nums[mid] < nums[mid-1]
        5 < 4 -> FALSE.
     3. nums[mid] < nums[mid+1]
        5 < 6 -> TRUE!
   Action:
     Increasing slope par hain, peak right side me hai.
     low = mid + 1 = 4 + 1 = 5.
   State updated: low = 5, high = 7.

   --- Iteration 2 ---
   low = 5, high = 7
   mid = 5 + (7 - 5) / 2 = 6
   nums[mid] = nums[6] = 9

   Neighbors of mid:
     Left neighbor:  nums[mid - 1] = nums[5] = 6
     Right neighbor: nums[mid + 1] = nums[7] = 8

   Checks:
     1. nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        9 > 6 (True) && 9 > 8 (True) -> TRUE!
   Action:
     Peak mil gaya!
     Return nums[mid] => return 9.
   Loop terminates immediately, returns 9.

   Final Output: "The peak element is 9"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Array size 1 ho, ya boundary elements (0th / (n-1)th) peak hon, 
       ya pehla hi `mid` peak element nikal jaye.
     * Worst Case: O(log2 N) -> Har step par search space theek aadha (N/2) ho raha hai.
     * Average Case: O(log2 N).
     * Linear search O(N) ke muqable log2(N) operations me peak guaranteed mil jata hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables (`n`, `low`, `high`, `mid`) 
       use hue hain. Koi extra memory, data structure ya call stack allocate nahi hua.
======================================================================
*/

int single_peak(vector <int> &nums){
    int n = nums.size();

    // for single element array 
    if(n == 1){
        return nums[0]; 
    }
    
    // checking for 0th index element or first element
    if(nums[0] > nums[1]){
        return nums[0];
    }

    // checking for (n-1)th index element or last element
    if(nums[n - 1] > nums[n - 2]){
        return nums[n - 1];
    }

    int low = 1;
    int high = n - 2;

    while(low <= high){
        int mid = low + (high - low)/2;
        
        // checking if mid is the peak :-
        if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]){
            return nums[mid];
        }

        else if(nums[mid] < nums[mid - 1]){
            high = mid - 1;
        }

        else if(nums[mid] < nums[mid + 1]){
            low = mid + 1;
        }
    }

    return - 1;   // ye kabhi bhi execute nahi hoga kyuki har baar ek peak element to kam se kam hoga hi aur is ode mein deal hi single peak se kar raha hu, agar array ke andar nahi hoga to obviously index 0 ya n-1 wala koi zarur peak hoga

}

int main(){
    vector <int> nums = {1,2,3,4,5,6,9,8,7};
    cout<<"The peak element is "<<single_peak(nums);
    return 0;
}