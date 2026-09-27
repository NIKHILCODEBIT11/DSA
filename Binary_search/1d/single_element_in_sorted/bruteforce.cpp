#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SINGLE ELEMENT IN SORTED ARRAY - LINEAR):
   - Problem:
     Ek sorted array di gayi hai jisme har element exactly 2 baar aata hai, 
     par sirf EK element aisa hai jo akela (single) aata hai. Hume wahi 
     single element find karke return karna hai.

   - Brute Force / Direct Neighbor Intuition:
     Kyunki array sorted hai, jo duplicate elements hain wo hamesha bagal-bagal 
     (adjacent neighbors) hi baithenge!
     Toh koi bhi element "Single" tabhi kehlayega jab wo apne aas-paas ke 
     dono padosiyon (left neighbor aur right neighbor) se ALAG ho!
     
     - Beech ke elements (index 1 to n-2):
       Single hone ki condition: `nums[i] != nums[i-1] && nums[i] != nums[i+1]`.
     - Corner Edge Cases (Corner elements ke 2 neighbors nahi hote):
       * Index 0 (Pehla element): Iska koi left neighbor nahi hai. 
         Toh yeh tabhi single hoga jab `nums[0] != nums[1]`.
       * Index n-1 (Aakhri element): Iska koi right neighbor nahi hai. 
         Toh yeh tabhi single hoga jab `nums[n-1] != nums[n-2]`.

   - EDGE CASE BUG ALERT (Size = 1):
     Agar array me sirf ek hi element ho, jaise `nums = {5}` (n = 1):
     Code seedha `i = 0` par jayega aur `nums[i+1]` yaani `nums[1]` access 
     karne ki koshish karega, jo ki **Out-of-Bounds Memory Access** ho jayega!
     Isliye function ke shuru me ek simple guard condition honi chahiye:
     `if (n == 1) return nums[0];`.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int n = nums.size();` :
     Vector ki total length nikali.
   - `if (i == 0)` :
     First element boundary check.
     Agar `nums[0] != nums[1]`, matlab pehla element duplicate nahi hai, 
     wahi single element hai -> return `nums[0]`.
   - `else if (i == n - 1)` :
     Last element boundary check.
     Agar `nums[n-1] != nums[n-2]`, matlab aakhri element duplicate nahi hai -> return `nums[n-1]`.
   - `else` :
     Middle elements (index 1 se n-2) ke liye general check:
     - `if (nums[i] == nums[i-1] || nums[i] == nums[i+1]) continue;` :
       Agar kisi bhi ek padosi se match ho gaya, toh yeh single nahi hai (duplicate pair ka part hai). 
       Aage badh jao.
     - `else return nums[i];` :
       Agar na left neighbor se match hua aur na right se, iska matlab yahi akela 
       (unique) element hai -> return `nums[i]`.

======================================================================
3. DETAILED DRY RUN (Step-by-Step Flow):

   Array:
   Indices:   0   1   2   3   4   5   6   7   8   9   10
   Elements: [2,  3,  3,  4,  4,  5,  5,  6,  6,  7,  7]
   n = 11

   -------------------------------------------------------------------
   STEP-BY-STEP ITERATIONS:
   -------------------------------------------------------------------
   i = 0:
   - Boundary condition hit: `i == 0`
   - Check: `nums[0] != nums[1]` => `2 != 3` -> TRUE!
   - Action: `return nums[0]` => Return 2.
   - Loop exits immediately on the very first iteration!

   -------------------------------------------------------------------
   ALTERNATIVE TEST CASE (Single element beech me ho):
   Array: [1, 1, 2, 2, 3, 4, 4]
   n = 7

   - i = 0: i == 0 -> nums[0] != nums[1] (1 != 1) -> FALSE.
   - i = 1: Middle element. nums[1] == nums[0] (1 == 1) -> TRUE -> continue.
   - i = 2: Middle element. nums[2] == nums[3] (2 == 2) -> TRUE -> continue.
   - i = 3: Middle element. nums[3] == nums[2] (2 == 2) -> TRUE -> continue.
   - i = 4:
     Middle element.
     nums[4] == nums[3] (3 == 2) -> FALSE
     nums[4] == nums[5] (3 == 4) -> FALSE
     Both matches FALSE! -> Else block triggers!
     return nums[4] => Return 3.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Agar single element pehle index (`i = 0`) par hi baitha ho.
     * Worst Case: O(N) -> Agar single element array ke bilkul aakhri index (`n - 1`) par ho.
       Linear scan hone ki wajah se pure N elements check karne pad sakte hain.
     * Average Case: O(N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard loop counter `i` aur integer `n` use hue hain.
       Koi extra auxiliary data structure ya memory allocation nahi hui.
======================================================================
*/

int single_element(vector <int> &nums){
    int n = nums.size();
    for(int i = 0; i < n; i++){
        if(i == 0){
            if(nums[i] != nums[i+1]){
                return nums[i];
            }
        }
        else if(i == n-1){
            if(nums[i] != nums[i-1]){
                return nums[i];
            }
        }
        else{
            if(nums[i] == nums[i-1] || nums[i] == nums[i+1]){
                continue;
            }
            else{
                return nums[i];
            }
        }
    }
}

int main(){
    vector <int> nums = {2,3,3,4,4,5,5,6,6,7,7};
    cout<<"The single element is "<<single_element(nums);
    return 0;
}