#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (INDEX PARITY / EVEN-ODD PATTERN):
   - Problem:
     Sorted array me har element do baar (pairs me) aata hai, sirf ek 
     element single hai. Hume $O(\log N)$ time me single element find karna hai.

   - The Secret Pattern (Before vs After Single Element):
     Array ko do hisson me divide karke pairs ke indices observe karo:

     Example: [1, 1,  2,  3, 3,  4, 4]   (Single element = 2 at index 2)
     Indices:  0  1   2   3  4   5  6

     * BEFORE the single element (Left Half):
       Pairs start at EVEN index and end at ODD index:
       - Element 1: indices (0, 1) -> (Even, Odd)
       Is region me:
       Agar `mid` ODD hai -> pair ka pehla part peeche hoga: `nums[mid] == nums[mid - 1]`.
       Agar `mid` EVEN hai -> pair ka doosra part aage hoga: `nums[mid] == nums[mid + 1]`.

     * AFTER the single element (Right Half):
       Single element ke aane se saara alignment 1 index aage shift ho gaya!
       Ab pairs start at ODD index and end at EVEN index:
       - Element 3: indices (3, 4) -> (Odd, Even)
       - Element 4: indices (5, 6) -> (Odd, Even)

   - The Elimination Strategy:
     1. Agar `mid` par khade hokar (Even, Odd) pattern match kar raha hai:
        Iska matlab hum single element ke LEFT SIDE me hain.
        Single element pakka humare RIGHT me baitha hai!
        Toh left half ko discard karo: `low = mid + 1`.
     2. Agar (Even, Odd) pattern break ho gaya:
        Iska matlab hum single element ke RIGHT SIDE me hain (ya khud single element par hain).
        Toh right half discard karo: `high = mid - 1`.

   - Boundary Trimming Shortcut (`low = 1, high = n - 2`):
     Corner elements (`index 0` aur `index n-1`) ke dono neighbors nahi hote 
     (left ya right out-of-bounds ho jata hai).
     Unhe while loop se pehle hi check kar liya!
     Fayda: While loop ke andar `nums[mid - 1]` aur `nums[mid + 1]` bina kisi 
     boundary crash/segmentation fault ke freely check ho sakte hain!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n == 1) return nums[0];` :
     Single element array edge case (e.g. `[5]`).
   - `if (nums[0] != nums[1]) return nums[0];` :
     Agar pehla element hi unique nikla toh aage binary search ki zaroorat hi nahi.
   - `if (nums[n - 1] != nums[n - 2]) return nums[n - 1];` :
     Agar aakhri element unique nikla toh yahin se return.
   - `int low = 1, high = n - 2;` :
     Search space ko `1` se `n - 2` par restrict kar diya taaki mid kabhi 0 ya n-1 na bane.
   - `if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]) return nums[mid];` :
     Target check! Agar mid apne dono neighbors se alag hai, toh yahi single element hai.
   - `if ((mid % 2 == 1 && nums[mid] == nums[mid - 1]) || (mid % 2 == 0 && nums[mid] == nums[mid + 1]))` :
     Pattern Check: Hum single element ke left me hain ((Even, Odd) sequence intact hai).
     Eliminate left half -> `low = mid + 1;`.
   - `else` :
     Pattern broke! Hum single element ke right me hain.
     Eliminate right half -> `high = mid - 1;`.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0   1   2   3   4   5   6   7   8   9   10
   Elements: [2,  3,  3,  4,  4,  5,  5,  6,  6,  7,  7]
   n = 11

   -------------------------------------------------------------------
   PRE-CHECK (Edge Cases):
   - Check `n == 1`: 11 == 1 -> False
   - Check index 0: `nums[0] != nums[1]` => (2 != 3) -> TRUE!
   - Action: `return nums[0]` => Returns 2 immediately!
   -------------------------------------------------------------------

   LET'S DRY RUN WITH SINGLE ELEMENT IN THE MIDDLE:
   Array:
   Indices:   0   1   2   3   4   5   6   7   8
   Elements: [1,  1,  2,  2,  3,  4,  4,  5,  5]
   n = 9 (Single element = 3 at index 4)

   Pre-checks:
   - nums[0] != nums[1] (1 != 1) -> False
   - nums[8] != nums[7] (5 != 5) -> False
   low = 1, high = 7

   --- Iteration 1 ---
   low = 1, high = 7
   mid = (1 + 7) / 2 = 4
   nums[mid] = nums[4] = 3

   1. Check Match (Is mid the single element?):
      nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]
      => nums[4] != nums[3] && nums[4] != nums[5]
      => 3 != 2 && 3 != 4 -> TRUE && TRUE -> TRUE!
   2. Action:
      Element mil gaya! Return `nums[mid]` => Return 3.
   Finished in 1 iteration!

   -------------------------------------------------------------------
   ANOTHER WALKTHROUGH (Where mid lands in Left Half):
   Array: [1, 1, 2, 3, 3]
   Indices: 0, 1, 2, 3, 4
   Target Single = 2 at index 2.
   Pre-checks pass. low = 1, high = 3.

   --- Iteration 1 ---
   mid = (1 + 3) / 2 = 2
   nums[mid] = nums[2] = 2
   - Check match: nums[2] != nums[1] (2 != 1) && nums[2] != nums[3] (2 != 3) -> TRUE!
   - Returns 2.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Agar index 0 ya index n-1 par single element ho (Pre-checks pakad lenge), 
       ya pehla hi mid single element par land kar jaye.
     * Worst Case: O(log2 N) -> Binary search har iteration me search boundary ko aadhi karta hai.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer pointers (`low`, `high`, `mid`, `n`) 
       use hue hain, koi recursion call stack ya extra space nahi hai.
======================================================================
*/

int single_element(vector <int> &nums){
    int n = nums.size();

    // for single -sized element :- like {3}
    if(n == 1){
        return nums[0];
    }

    int low = 1;
    int high = n - 2;

    // Checking for index 0 element :-
    if(nums[0] != nums[1]){
        return nums[0];
    }

    // checking for index n-1 element :-
    if(nums[n-1] != nums[n-2]){
        return nums[n-1];
    }

    while(low <= high){
        int mid = (low+high)/2;

        // if mid is the single element check and return it
        if(nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]){
            return nums[mid];
        }

        // rest cases of elimination and all
        // single element on right half :-
        if((mid % 2 == 1 && nums[mid] == nums[mid - 1]) || (mid % 2 == 0 && nums[mid] == nums[mid + 1])){
            low = mid + 1;
        }
        // single element on left half
        else{
            high = mid - 1;
        }
        
    }
    // ye wali return statement kabhi use nahi hogi kyuki single element to hoga hi question mein diya gaya hai lekin kyuki ye function int return kar raha hai to saare loop if-else ke bahar bhi kuch to return karna hi padega
    return -1;
}

int main(){
    vector <int> nums = {2,3,3,4,4,5,5,6,6,7,7};
    cout<<"The single element is "<<single_element(nums);
    return 0;
}