#include<bits/stdc++.h>
using namespace std;

// question :-
// wo row return kar jisme max 1s ho aur agar 1 se jydaa waise rows hain to low index wala return kar {saare rows sorted hain}

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (ROW WITH MAXIMUM 1s - BRUTE FORCE COUNT):
   - Problem:
     Hume ek 2D binary matrix `mat` di gayi hai jisme sirf 0s aur 1s hain.
     Hume aisi row ka index return karna hai jisme sabse zyada 1s hon.
     Agar ek se zyada rows me barabar aur highest count ke 1s hain, 
     toh sabse pehli (smallest index) row ko return karna hai.
     Agar matrix me kahin bhi 1 na ho (pura matrix 0s ka ho), toh -1 return karna standard hota hai.

   - Brute Force Counting Intuition:
     Matrix ko row-by-row linearly scan karo:
     - Har row `i` ke shuru me ek counter `count_1s = 0` banao.
     - Us row ke har column `j` par jao aur values ko add karo (`count_1s += nums[i][j]`).
       Kyunki array sirf 0s aur 1s contain karta hai, direct addition se 1s ka exact count mil jata hai 
       (bina kisi `if (nums[i][j] == 1)` condition ke).
     - Compare karo: Agar current row ka count pichle `max_1s` se strictly bada hai (`count_1s > max_1s`), 
       toh naya record update kar do aur index store kar lo.

   - Strict Inequality (`count_1s > max_1s`) Ka Logic:
     Agar matrix me multiple rows aisi hain jinme barabar highest 1s hain (jaise row 2 me bhi 4 ones hain 
     aur row 4 me bhi 4 ones hain), strict `>` ensure karta hai ki baad wali rows pehle record ko 
     overwrite na kar sakein. Isse hamesha smallest (first) row index preserved rehta hai.

   - Note on `max_1s` Initialization:
     `max_1s = -1` rakhne se agar kisi row me 0 ones bhi honge (e.g. saari rows zeroes hain), toh wo row 0 ko 
     max maan kar index 0 return kar dega. Agar question me purely "at least one 1 hona chahiye warna -1" rule ho, 
     toh `max_1s = 0` initialize karke check `count_1s > max_1s` lagana standard rehta hai (jisse pure 0 matrix par index -1 hi rahe).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int max_1s = -1; int index = -1;`:
     Global trackers. `max_1s` ab tak dekhe gaye maximum ones store karta hai, 
     aur `index` us winning row ka index hold karta hai.
   - `for(int i = 0; i < nums.size(); i++)`:
     Outer loop har row ko sequentially index 0 se N-1 tak process karta hai.
   - `int count_1s = 0;`:
     Har nayi row ke shuru hote hi counter reset kiya taaki sirf current row ke 1s count hon.
   - `for(int j = 0; j < nums[0].size(); j++) count_1s += nums[i][j];`:
     Inner loop row ke har column element ko sum karta hai (0s se sum badalta nahi, 1s se sum +1 hota hai).
   - `if(count_1s > max_1s)`:
     Strict condition check. Agar current row ne previous maximum record toda:
     - `max_1s = count_1s;` -> Naya record lock kiya.
     - `index = i;` -> Winning row ka index update kiya.
     Agar count barabar aaya (`count_1s == max_1s`), toh skip ho jayega (first occurrence rule intact).
   - `return index;`:
     Saari rows check karne ke baad overall winning index return ho jata hai.

======================================================================
3. DETAILED DRY RUN:

   Input Matrix (5 rows, 5 columns):
   Row 0: [0, 0, 1, 1, 1]
   Row 1: [0, 0, 0, 0, 0]
   Row 2: [0, 1, 1, 1, 1]
   Row 3: [0, 0, 0, 0, 0]
   Row 4: [0, 1, 1, 1, 1]

   Initial State:
   max_1s = -1, index = -1

   -------------------------------------------------------------------
   --- Row 0 ---
   Elements: 0 + 0 + 1 + 1 + 1
   count_1s = 3
   Check: count_1s > max_1s (3 > -1) -> TRUE!
   Action: max_1s = 3, index = 0
   State: max_1s = 3, index = 0

   --- Row 1 ---
   Elements: 0 + 0 + 0 + 0 + 0
   count_1s = 0
   Check: count_1s > max_1s (0 > 3) -> FALSE.
   State: max_1s = 3, index = 0

   --- Row 2 ---
   Elements: 0 + 1 + 1 + 1 + 1
   count_1s = 4
   Check: count_1s > max_1s (4 > 3) -> TRUE! (Naya highest record mil gaya)
   Action: max_1s = 4, index = 2
   State: max_1s = 4, index = 2

   --- Row 3 ---
   Elements: 0 + 0 + 0 + 0 + 0
   count_1s = 0
   Check: count_1s > max_1s (0 > 4) -> FALSE.
   State: max_1s = 4, index = 2

   --- Row 4 ---
   Elements: 0 + 1 + 1 + 1 + 1
   count_1s = 4
   Check: count_1s > max_1s (4 > 4) -> FALSE! (Tie breaker: strict `>` hone se update nahi hua)
   State: max_1s = 4, index = 2 (Pehla index 2 retain raha)

   Loop Ends.
   Function returns index = 2.
   Output: "The maximum 1s are at index 2"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = number of rows (`nums.size()`), M = number of columns (`nums[0].size()`).
     * Outer loop N baar chalta hai.
     * Har row ke andar inner loop M baar chalta hai.
     * Total matrix elements visited = N * M.
     * Overall Time Complexity: O(N * M).
     * (Note: Agar har row sorted ho, toh har row me pehla 1 dhundhne ke liye Binary Search 
       ya Pointer Staircase use karke ise O(N * log M) ya O(N + M) me optimize kiya ja sakta hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Matrix ko in-place read kiya gaya hai, koi extra array ya dynamic storage allocate nahi hui.
     * Sirf standard scalar variables (`max_1s`, `index`, `count_1s`, `i`, `j`) use hue hain.
======================================================================
*/

int row_with_max_1s(vector <vector<int>> &nums){
    int max_1s = -1;     // ye chk krta hai ki kya currnt row ke total no. of 1s kya wo maximum se bada hai 
    int index = -1;      // ye wo index hota hai jisme ki max 1s ho

    for(int i = 0; i < nums.size(); i++){
        int count_1s = 0;    // ye current row mein kitne 1s hain wo dekhta hai
        for(int j = 0; j < nums[0].size(); j++){
            count_1s += nums[i][j];
        }
        if(count_1s > max_1s){    // count_1s = max_1s nahi kiya kyuki agar 1 se jyada rows mein same no. of highest 1s hain to us case mein chote index wale ko hi return karna hai 
            max_1s = count_1s;
            index = i;
        }
    }

    return index;
}

int main(){
    vector<vector<int>> mat = {
    {0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1}
};

    cout<<"The maximum 1s are at index "<<row_with_max_1s(mat);
}