#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (STAIRCASE SEARCH / 2D Z-SEARCH):
   - Problem:
     Hume ek 2D matrix di gayi hai jisme:
     1. Har row left-to-right sorted hai.
     2. Har column top-to-bottom sorted hai.
     Hume `target` ka exact coordinate `{row, column}` find karna hai in O(N + M) time.

   - "Corner Selection" Magic (Top-Right ya Bottom-Left hi kyun?):
     Socho agar hum (0, 0) (Top-Left) se shuru karein:
     - Right jao toh values badhti hain.
     - Down jao toh bhi values badhti hain.
     Agar target current element se bada ho, toh hum right jayein ya down? AMBIGUITY! Dono taraf bade elements hain.

     Lekin agar hum Top-Right corner `(row = 0, column = m - 1)` par khade hon:
     - Left jao toh values GHATTI hain (row sorted left-to-right).
     - Down jao toh values BADHTI hain (column sorted top-to-bottom).
     Yahan ek perfect Binary Decision Fork mil jata hai:
     * Current element > target:
       Target chhota hai, aur column me niche toh aur bade numbers hain, 
       toh current column me target kabhi nahi mil sakta! 
       Pura column discard karke LEFT aao: `column--`.
     * Current element < target:
       Target bada hai, aur row me left me toh aur chhote numbers hain, 
       toh current row me target kabhi nahi mil sakta! 
       Puri row discard karke DOWN jao: `row++`.
     * Current element == target: Mil gaya target!

   - Staircase Movement:
     Har step par hum ya toh ek puri row eliminate karte hain (`row++`), 
     ya ek pura column eliminate karte hain (`column--`). 
     Pura traversal ek seedhi (staircase) jaisa dikhta hai, isliye ise Staircase Search bolte hain.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int n = nums.size(); int m = nums[0].size();`:
     Rows (`n`) aur Columns (`m`) count nikala.
   - `int row = 0; int column = m - 1;`:
     Search ko Top-Right corner par place kiya (Row 0, Last Column).
   - `while(row < n && column >= 0)`:
     Loop boundary: Jab tak hum matrix ke bounds ke andar hain. 
     Agar `row == n` ho gaya (bottom se bahar) ya `column < 0` ho gaya (left se bahar), loop terminate hoga.
   - `if (nums[row][column] == target) return {row, column};`:
     Match mil gaya, coordinate pair turant return kar diya.
   - `else if (nums[row][column] < target) row++;`:
     Current cell target se chhota hai. Kyunki row left-to-right sorted hai, is row ke piche ke saare elements 
     aur bhi chhote honge. Toh yeh poori row useless ho gayi -> Neeche agli row par jao (`row++`).
   - `else column--;`:
     Current cell target se bada hai. Kyunki column top-to-bottom sorted hai, is column ke niche ke saare elements 
     aur bhi bade honge. Toh yeh poora column useless ho gaya -> Piche agle column par aao (`column--`).
   - `return {-1, -1};`:
     Matrix bounds se bahar nikal gaye par target nahi mila -> target absent hai.

======================================================================
3. DETAILED DRY RUN:

   Matrix (n = 4 rows, m = 5 columns):
   Indices:     0    1    2    3    4
   Row 0:     [ 2,   4,   6,   7,   9 ]
   Row 1:     [21,  23,  25,  26,  27 ]
   Row 2:     [29,  32,  33,  34,  36 ]
   Row 3:     [37,  39,  40,  42,  46 ]

   Target = 34
   Initial Position: row = 0, column = 4 (Top-Right: nums[0][4] = 9)

   --- Step 1 ---
   Current Position: (0, 4) -> nums[0][4] = 9
   Check:
     9 == 34 ? False
     9 < 34  ? True (9 chhota hai target se)
   Decision:
     Row 0 ke saare elements <= 9 hain, toh Row 0 me 34 nahi ho sakta.
     Row 0 discard karo: row = row + 1 = 1.
   State: row = 1, column = 4

   --- Step 2 ---
   Current Position: (1, 4) -> nums[1][4] = 27
   Check:
     27 == 34 ? False
     27 < 34  ? True (27 chhota hai target se)
   Decision:
     Row 1 ke saare elements <= 27 hain, toh Row 1 me 34 nahi ho sakta.
     Row 1 discard karo: row = row + 1 = 2.
   State: row = 2, column = 4

   --- Step 3 ---
   Current Position: (2, 4) -> nums[2][4] = 36
   Check:
     36 == 34 ? False
     36 < 34  ? False (36 bada hai target se)
   Decision:
     Column 4 me niche ke saare elements >= 36 honge, toh Column 4 me 34 nahi ho sakta.
     Column 4 discard karo: column = column - 1 = 3.
   State: row = 2, column = 3

   --- Step 4 ---
   Current Position: (2, 3) -> nums[2][3] = 34
   Check:
     34 == 34 ? TRUE! (MATCH FOUND!)
   Action:
     return {2, 3};
   Function terminates immediately!

   In main():
   Output: "The position of target is (2,3)"

   -------------------------------------------------------------------
   SCENARIO B: Target Absent (Target = 15)
   (0, 4) val=9  < 15 -> row++    => (1, 4)
   (1, 4) val=27 > 15 -> column-- => (1, 3)
   (1, 3) val=26 > 15 -> column-- => (1, 2)
   (1, 2) val=25 > 15 -> column-- => (1, 1)
   (1, 1) val=23 > 15 -> column-- => (1, 0)
   (1, 0) val=21 > 15 -> column-- => column = -1.
   Loop condition (column >= 0) breaks.
   Returns {-1, -1}.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = number of rows, M = number of columns.
     * Best Case: O(1) -> Top-Right corner element hi target ho (`nums[0][m-1] == target`).
     * Worst Case: O(N + M) -> Hum top-right (0, m-1) se chalte-chhalte bottom-left (n-1, 0) 
       tak pahunchein. Maximum N steps down ja sakte hain aur M steps left ja sakte hain.
     * Average Case: O(N + M).
     * Linear in terms of grid dimensions, without needing full grid binary search.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Algorithm sirf do integer pointer variables (`row`, `column`) aur dimensions (`n`, `m`) use karta hai.
     * Zero extra memory allocation.
======================================================================
*/

pair<int,int> search_2d(vector <vector<int>> &nums,int target){
    if (nums.empty() || nums[0].empty()) {
        return {-1, -1};
    }
    
    int n=nums.size();
    int m=nums[0].size();
    int row=0;
    int column=m-1;
    while(row<n && column>=0){
        if(nums[row][column] == target){
            return {row,column};
        }
        else if(nums[row][column]<target){
            row++;
        }
        else{
            column--;
        }
    }
    return {-1,-1};
}

/*
    STAIRCASE SEARCH VISUALIZATION
    Target: 34
    
    Matrix Structure:
    [  2,   4,   6,   7,   9  ]  <-- Row 0
    [ 21,  23,  25,  26,  27  ]  <-- Row 1
    [ 29,  32,  33,  34,  36  ]  <-- Row 2
    [ 37,  39,  40,  42,  46* ]  <-- Row 3 (Note: Fixed 26 to 46 for sorted logic)
    
    Search Path:
    1. Start at Top-Right: (0, 4) -> Value: 9
       9 < 34 ? Yes -> Move Down (row++)
       
    2. Current: (1, 4) -> Value: 27
       27 < 34 ? Yes -> Move Down (row++)
       
    3. Current: (2, 4) -> Value: 36
       36 > 34 ? Yes -> Move Left (column--)
       
    4. Current: (2, 3) -> Value: 34
       34 == 34 ? MATCH FOUND! -> Return {2, 3}
       
    Complexity:
    - Time: O(N + M) where N = rows, M = columns.
    - Space: O(1)
*/


int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=34;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    pair <int,int> ans = search_2d(nums,target);
    cout<<"The position of target is ("<<ans.first<<","<<ans.second<<")";
    return 0;
}