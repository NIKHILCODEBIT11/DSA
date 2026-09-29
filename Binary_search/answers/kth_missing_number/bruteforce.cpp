#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (K-TH MISSING POSITIVE NUMBER - LINEAR SHIFT LOGIC):
   - Problem:
     Hume ek strictly increasing sorted positive integers ka array `nums` diya hai 
     aur ek integer `k` diya hai. Hume k-th missing positive number nikalna hai 
     (positive numbers start from 1, 2, 3, 4, ...).

   - Core Intuition (The "Shift" Mental Model):
     Maan lo array completely EMPTY hota:
     - 1st missing number = 1
     - 2nd missing number = 2
     - k-th missing number = k
     Iska matlab, agar koi number array me present nahi hota, toh seedha answer `k` hota!

   - Ab actual numbers introduce karte hain:
     Har wo number jo array me present hai aur jo humare target missing boundary (`<= k`) 
     ke andar baitha hai, wo humare answer ko 1 step aage shift (dhakka) de deta hai!
     
     Example: k = 5
     - Normal missing sequence: [1, 2, 3, 4, 5] -> 5th missing number = 5.
     - Lekin agar array me '2' present hai:
       Number '2' missing nahi hai! Toh [1, 2, 3, 4, 5] me se ek slot bhar gaya.
       Hume abhi bhi 5 missing numbers chahiye, toh hume sequence ko ek step aage 
       badhana padega: [1, 3, 4, 5, 6]. 
       Toh candidate ban gaya: k + 1 = 6.
     - Agar '3' bhi present hai:
       '3' <= 6 hai, toh ek aur slot bhar gaya! Candidate ek aur aage shift hoga: k = 7.
     
   - Termination / Break Rule:
     Kyunki array STRICTLY INCREASING SORTED hai:
     - Jaise hi hume koi aisa element milta hai jo updated `k` se BADA hai (`nums[i] > k`), 
       iska matlab aage aane wale saare elements bhi `k` se bade hi honge!
     - Wo future elements kabhi bhi `<= k` nahi ho sakte, toh wo humare missing answer 
       ko aage shift nahi kar sakte.
     - Isliye wahi par `break` kar do! Current `k` hi humara final answer hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `for(int i = 0; i < nums.size(); i++)` :
     Array ke elements ko sequence me check kar rahe hain taaki missing boundary ko shift kar sakein.
   - `if (nums[i] <= k)` -> `k++;` :
     Agar array ka element current `k` ke barabar ya usse chhota hai, iska matlab 
     yeh element missing numbers ke pool me se ek jagah occupy kar raha hai. 
     Isliye requirement poori karne ke liye answer ko ek step aage shift kiya (`k++`).
   - `else break;` :
     Array sorted hai! Agar `nums[i] > k` ho gaya, toh aage ke saare elements bhi `> k` 
     hi honge. Wo current answer ko affect nahi kar sakte, isliye faltu iterations rokne 
     ke liye seedhe loop tod do.
   - `return k;` :
     Shift hone ke baad jo final value banti hai, wahi k-th missing positive number hoti hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [2, 3, 6, 7, 9, 12, 14], k = 5
   Natural missing numbers in reality:
   Positive stream: 1, [2], [3], 4, 5, [6], [7], 8, [9], 10, 11, [12], 13, [14]...
   Bracketed [] = present in array.
   Missing numbers list: 1, 4, 5, 8, 10, 11, 13...
   1st missing = 1
   2nd missing = 4
   3rd missing = 5
   4th missing = 8
   5th missing = 10 -> EXPECTED ANSWER = 10.

   Let's trace the code:
   Initial State: k = 5

   --- Step 1 (i = 0) ---
   nums[0] = 2
   Check: nums[0] <= k => 2 <= 5 ? -> TRUE
   Action: k++ => k becomes 6.
   Explanation: '2' present hai, toh candidate 5 se shift hokar 6 bana.

   --- Step 2 (i = 1) ---
   nums[1] = 3
   Check: nums[1] <= k => 3 <= 6 ? -> TRUE
   Action: k++ => k becomes 7.
   Explanation: '3' present hai, toh candidate 6 se shift hokar 7 bana.

   --- Step 3 (i = 2) ---
   nums[2] = 6
   Check: nums[2] <= k => 6 <= 7 ? -> TRUE
   Action: k++ => k becomes 8.
   Explanation: '6' present hai, toh candidate 7 se shift hokar 8 bana.

   --- Step 4 (i = 3) ---
   nums[3] = 7
   Check: nums[3] <= k => 7 <= 8 ? -> TRUE
   Action: k++ => k becomes 9.
   Explanation: '7' present hai, toh candidate 8 se shift hokar 9 bana.

   --- Step 5 (i = 4) ---
   nums[4] = 9
   Check: nums[4] <= k => 9 <= 9 ? -> TRUE
   Action: k++ => k becomes 10.
   Explanation: '9' present hai, toh candidate 9 se shift hokar 10 bana.

   --- Step 6 (i = 5) ---
   nums[5] = 12
   Check: nums[5] <= k => 12 <= 10 ? -> FALSE!
   Action: BREAK!
   Explanation: 12 is greater than 10. Kyunki array sorted hai, aage 14 bhi 10 se bada hi hoga.
   Loop terminates immediately.

   Return k = 10.
   Final Output: "The 5th missing number is 10" (Matches expected answer perfectly!).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Agar pehla hi element `k` se bada ho (e.g., nums = [10, 11], k = 2). 
       Loop pehle hi step pe break ho jayega.
     * Worst Case: O(N) -> Agar saare elements target missing boundary ke andar hon 
       (e.g., nums = [1, 2, 3, 4], k = 5), toh pura array traverse hoga.
     * Average Case: O(N).
     * Note: Is linear approach ko Binary Search se O(log N) me optimize kiya ja sakta hai 
       by computing missing count at each index: `missing_count = nums[mid] - (mid + 1)`.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard loop counter `i` use hua hai. 
       No extra memory, hashset ya vector allocated.
======================================================================
*/

int missing(vector <int>&nums,int k){               //  {2  3     7   12}         k=5
    for(int i=0;i<nums.size();i++){
        if(nums[i]<=k){
            k++;
        }
        else{
            break;
        }
    }
    return k;
}

//      TIME COMPLEXITY :-   O(N)
//      SPACE COMPLEXITY :-  O(1)

int main(){
    vector <int> nums={2,3,6,7,9,12,14};
    int n;
    cout<<"Enter missing value to be found :- ";
    cin>>n;
    cout<<"The "<<n<<"th missing number is "<<missing(nums,n);
    return 0;
}