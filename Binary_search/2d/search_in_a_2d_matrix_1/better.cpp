#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SEARCH IN 2D MATRIX - ROW PRUNING + 1D BINARY SEARCH):
   - Problem:
     Hume ek matrix `nums` di gayi hai jisme har row left-to-right sorted hai, 
     aur ek `target` value search karni hai. Agar target exist karta hai 
     toh `true`, warna `false` return karna hai.

   - Brute Force O(N * M) ke comparison me Smart Thinking:
     Brute force me hum har single cell scan kar rahe the.
     Lekin row SORTED hai! Har row ka:
     - Pehla element (`nums[i][0]`) us row ka MINIMUM element hai.
     - Aakhri element (`nums[i][column - 1]`) us row ka MAXIMUM element hai.

   - Range Filtering / Row Pruning:
     Agar target kisi row `i` me maujood ho sakta hai, toh uski ek hi shart hai:
         `nums[i][0] <= target && target <= nums[i][column - 1]`
     - Agar target is range ke BAHAR hai:
       Toh us row ke andar dekhne ka koi matlab hi nahi hai! Seedhe agli row par jao (Instant skip).
     - Agar target is range ke ANDAR hai:
       Is row me target milne ka chance hai. Kyunki yeh single row already sorted array hai, 
       hum linear scan karne ke badle 1D Binary Search lagayenge jo sirf O(log M) time lega!

   - Key Observation & Further Optimization Note:
     Current code me hum rows ko linear loop `for(int i = 0; i < row; i++)` se check kar rahe hain, 
     jisse TC = O(N + log M) banti hai. 
     Agar pure matrix me pichli row ka aakhri element agli row ke pehle element se chhota ho (strictly sorted 2D matrix), 
     toh correct row select karne ke liye bhi Binary Search lagaya ja sakta hai, 
     ya pure matrix ko ek flattened virtual 1D array maan kar direct O(log(N * M)) me solve kiya ja sakta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - int row = nums.size(); int column = nums[0].size(); :
     Matrix ke grid bounds (N rows, M columns) store kiye.
   - for(int i = 0; i < row; i++) :
     Row-by-row iterate kiya dekhne ke liye ki target kis row ki range me belong karta hai.
   - if(nums[i][0] <= target && target <= nums[i][column - 1]) :
     THE RANGE FILTER! Check karta hai ki kya target current row ke min aur max bounds ke beech baitha hai.
     Agar false hai, toh andar ka pura while loop skip ho jata hai.
   - int low = 0; int high = column - 1; :
     Filtered valid row ke andar 1D Binary Search ke boundaries initialize kiye.
   - while(low <= high) :
     Us single row ke andar target search karne ke liye standard Binary Search.
     - if(nums[i][mid] == target) return true; -> Match milte hi turant true return karke exit.
     - if(nums[i][mid] < target) low = mid + 1; -> Target bada hai, right jao.
     - else high = mid - 1; -> Target chhota hai, left jao.
   - return false; :
     Agar koi aisi row nahi mili jisme target ho, ya range match hone par bhi 
     binary search me element nahi mila, toh final answer false hoga.

======================================================================
3. DETAILED DRY RUN:

   Matrix (4 rows, 5 columns -> column = 5):
   Row 0: [ 2,  4,  6,  7,  9]    -> Range: [2 ... 9]
   Row 1: [21, 23, 25, 26, 27]   -> Range: [21 ... 27]
   Row 2: [29, 32, 33, 34, 36]   -> Range: [29 ... 36]
   Row 3: [37, 39, 40, 42, 45]   -> Range: [37 ... 45]

   Target = 35

   -------------------------------------------------------------------
   --- Row 0 (i = 0) ---
   Check Range: nums[0][0] <= 35 && 35 <= nums[0][4]
                => 2 <= 35 && 35 <= 9 -> FALSE.
   Action: Skip Row 0 completely.

   --- Row 1 (i = 1) ---
   Check Range: nums[1][0] <= 35 && 35 <= nums[1][4]
                => 21 <= 35 && 35 <= 27 -> FALSE.
   Action: Skip Row 1 completely.

   --- Row 2 (i = 2) ---
   Check Range: nums[2][0] <= 35 && 35 <= nums[2][4]
                => 29 <= 35 && 35 <= 36 -> TRUE!
   Target is row 2 ki range me fall karta hai!
   Enter Binary Search on Row 2: [29, 32, 33, 34, 36]

   low = 0, high = 4
   - Iteration 1:
     mid = (0 + 4) / 2 = 2
     nums[2][2] = 33
     Compare: 33 == 35 -> False
              33 < 35  -> True => low = mid + 1 = 3
     State: low = 3, high = 4

   - Iteration 2:
     mid = (3 + 4) / 2 = 3
     nums[2][3] = 34
     Compare: 34 == 35 -> False
              34 < 35  -> True => low = mid + 1 = 4
     State: low = 4, high = 4

   - Iteration 3:
     mid = (4 + 4) / 2 = 4
     nums[2][4] = 36
     Compare: 36 == 35 -> False
              36 < 35  -> False => high = mid - 1 = 3
     State: low = 4, high = 3

   - Termination: low > high (4 > 3) -> Binary Search for Row 2 finished.
   (Target 35 was not found in Row 2).

   --- Row 3 (i = 3) ---
   Check Range: nums[3][0] <= 35 && 35 <= nums[3][4]
                => 37 <= 35 && 35 <= 45 -> FALSE.
   Action: Skip Row 3 completely.

   --- Loop Ends ---
   Return false.
   Output: "The target value of 35 is present : false"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = number of rows (`nums.size()`), M = number of columns (`nums[0].size()`).
     * Outer for-loop: Har row ke pehle aur aakhri element ko check karta hai -> O(N).
     * Inner Binary Search: Agar rows strictly non-overlapping ranges me hain, 
       toh target maximum sirf EK hi row ki range me fall karega.
       Isliye Binary Search poore code execution me maximum sirf EK baar chalega -> O(log M).
     * Total Time Complexity: O(N + log M).
     * Previous Brute Force O(N * M) ke comparison me bohot bada improvement hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Kisi extra memory structure, vector ya recursive stack ka use nahi hua.
     * Sirf standard local integer pointers/variables (`row`, `column`, `i`, `low`, `high`, `mid`) use hue hain.
======================================================================
*/


// I am given a sorted array and have to search a target and if it is present return true or else return false

// BINARYSEARCH :-

bool search_2d(vector <vector<int>> &nums,int target){
    int row=nums.size();
    int column=nums[0].size();
    for(int i=0;i<row;i++){
        if(nums[i][0] <= target && target <= nums[i][column-1]){     
            int low=0;
            int high=column-1;
                while(low<=high){
                    int mid=(low+high)/2;
                    if(nums[i][mid]==target){
                        return true;
                    }
                    if(nums[i][mid] < target){
                        low=mid+1;
                    }
                    else{
                        high=mid-1;
                    }
                }
                
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
    int target=35;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    cout<<"The target value of "<<target<<" is present : "<<search_2d(nums,target);
    return 0;
}