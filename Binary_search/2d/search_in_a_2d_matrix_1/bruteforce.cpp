#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SEARCH IN 2D MATRIX - BRUTE FORCE):
   - Problem:
     Hume ek 2D matrix di gayi hai aur ek `target` value di hai.
     Hume check karna hai ki target matrix ke kisi bhi cell me exist karta hai ya nahi.
     Agar present hai toh `true` return karo, warna `false`.

   - Brute Force Thinking (Current Approach):
     Bina matrix ke sorted structure ka fayda uthaye, sabse straightforward tarika 
     yeh hai ki pure matrix ke har ek cell par traverse kiya jaye:
     - Nested loop lagao: Outer loop har row `i` ko visit karega, 
       aur inner loop us row ke har column `j` ko visit karega.
     - Har cell `nums[i][j]` ko target se compare karo.
     - Jaise hi match mil jaye (`nums[i][j] == target`), turant `true` return karke function exit kar do 
       (aage scan karne ki zaroorat nahi hai).
     - Agar pura matrix scan ho gaya aur loop normally khatam ho gaya, 
       iska matlab target matrix me maujood nahi hai -> return `false`.

   - Redundant Code Clarification:
     Tumne comment me bilkul sahi identify kiya:
     `else { continue; }` likhna completely redundant (faltu) hai kyunki agar `if` 
     condition false hoti hai, toh loop automatically agle iteration par chala hi jata hai.

   - Sorting Property Ignored:
     Notice karo matrix sorted hai:
     - Har row left se right sorted hai.
     - Har row ka pehla element pichli row ke aakhri element se bada hai (except last row typo in sample).
     Is sorted property ka use karke is brute force O(N * M) ko Binary Search se 
     O(log(N * M)) me optimize kiya ja sakta hai (Flattened 1D mapping ya row-finding BS).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - for(int i = 0; i < nums.size(); i++) :
     Outer loop index 0 se leke total rows - 1 tak ek-ek row ko pick karta hai.
   - for(int j = 0; j < nums[0].size(); j++) :
     Inner loop current row `i` ke har column `j` par jata hai.
   - if(nums[i][j] == target) return true; :
     Early Exit! Target milte hi bina pura matrix scan kiye seedha `true` return kar diya.
   - return false; :
     Dono nested loops khatam hone ke baad bhi match nahi mila, matlab target absent hai.
   - cout << boolalpha; (In main):
     C++ stream manipulator jo boolean output ko integer format (1 / 0) ke badle 
     readable text format ("true" / "false") me print karwata hai.

======================================================================
3. DETAILED DRY RUN:

   Matrix (4 rows, 5 columns):
   Row 0: [ 2,  4,  6,  7,  9]
   Row 1: [21, 23, 25, 26, 27]
   Row 2: [29, 32, 33, 34, 36]
   Row 3: [37, 39, 40, 42, 26]

   Target = 33

   -------------------------------------------------------------------
   --- Row 0 (i = 0) ---
   j = 0: nums[0][0] = 2  != 33
   j = 1: nums[0][1] = 4  != 33
   j = 2: nums[0][2] = 6  != 33
   j = 3: nums[0][3] = 7  != 33
   j = 4: nums[0][4] = 9  != 33
   (Row 0 complete, target not found)

   --- Row 1 (i = 1) ---
   j = 0: nums[1][0] = 21 != 33
   j = 1: nums[1][1] = 23 != 33
   j = 2: nums[1][2] = 25 != 33
   j = 3: nums[1][3] = 26 != 33
   j = 4: nums[1][4] = 27 != 33
   (Row 1 complete, target not found)

   --- Row 2 (i = 2) ---
   j = 0: nums[2][0] = 29 != 33
   j = 1: nums[2][1] = 32 != 33
   j = 2: nums[2][2] = 33 == 33 (MATCH FOUND!)
          Action: return true;
          Function exits immediately!

   In main():
   Output: "The target value of 33 is present : true"

   -------------------------------------------------------------------
   SCENARIO B: Target Missing (e.g., target = 100)
   - i = 0 se 3, j = 0 se 4 (Total 20 cells check honge).
   - Kisi bhi cell par condition match nahi hogi.
   - Loops terminate -> return false.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = number of rows (nums.size()), M = number of columns (nums[0].size()).
     * Best Case: O(1) -> Target pehle hi cell par mil jaye (nums[0][0] == target).
     * Worst Case: O(N * M) -> Target aakhri cell par ho ya matrix me exist hi na kare.
     * Average Case: O(N * M).
     * Pura 2D grid cell-by-cell scan hota hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra memory, dynamic vectors ya data structures allocate nahi hue.
     * Sirf standard loop variables (i, j) use ho rahe hain.
======================================================================
*/


// I am given a sorted array and have to search a target and if it is present return true or else return false

// BRUTEFORCE :-

bool search_2d(vector <vector<int>> &nums,int target){
    for(int i=0;i<nums.size();i++){
        for(int j=0;j<nums[0].size();j++){
            if(nums[i][j]==target){
                return true;
            }
            // else{            This is redundant as if block so no need
            //     continue;
            // }
        }
    }
    return false;
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=33;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    cout<<"The target value of "<<target<<" is present : "<<search_2d(nums,target);
    return 0;
}