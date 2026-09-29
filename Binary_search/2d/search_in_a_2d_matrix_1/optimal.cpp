#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FLATTENED 2D MATRIX BINARY SEARCH - CORRECTED MAPPING):
   - Problem:
     Hume ek 2D matrix di gayi hai jisme har row sorted hai aur agla row pichle row 
     ke aakhri element se bada hai (strictly sorted order). Hume `target` ko search karna hai 
     aur boolean (`true`/`false`) return karna hai.

   - Code Correction Notice:
     Pichle code me jo formula bug tha (`row = mid / m` jabki `m` number of rows tha), 
     is code me tune variables redefine karke bilkul sahi kar diya hai:
       `int n = nums.size();`    -> n = Total Rows
       `int m = nums[0].size();` -> m = Total Columns (Width)
       `row = mid / m;`          -> Correct! (Divided by column width)
       `column = mid % m;`       -> Correct! (Modulo by column width)

   - Core Virtual 1D Flattening Intuition:
     Pure matrix me total `n * m` elements hain.
     Agar hum matrix ke har row ko horizontally ek straight line me bichha dein:
     - 0 se lekar `(n * m - 1)` tak ka ek perfectly sorted 1D array ban jata hai.
     - Kisi bhi linear 1D index `mid` ko 2D coordinates `(row, column)` me convert karne ka rule:
       * Har row me `m` elements hote hain.
       * `mid` tak pahunchte-pahunchte kitni poori rows cross ho chuki hain? -> `mid / m`
       * Aakhri row me hum kis column offset par hain? -> `mid % m`
     - Is mathematical index translation ki wajah se bina koi naya array banaye hum pure 
       matrix par single 1D Binary Search chala sakte hain!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int n = nums.size(); int m = nums[0].size();`:
     Grid boundaries initialize kiye (`n` rows, `m` columns).
   - `int low = 0; int high = n * m - 1;`:
     Virtual 1D array ke search boundaries define kiye: index 0 se leke last element tak.
   - `while(low <= high)`:
     Standard binary search loop jo search space valid rehne tak chalega.
   - `int mid = (low + high) / 2;`:
     Middle element ka virtual 1D index nikal liya.
   - `int row = mid / m; int column = mid % m;`:
     1D coordinate ko 2D cell `nums[row][column]` me convert kiya.
   - `if (nums[row][column] == target) return true;`:
     Target exact match ho gaya -> early success return.
   - `else if (nums[row][column] <= target) low = mid + 1;`:
     Target bada hai, right half me search continue karo (`low = mid + 1`).
     *(Note: Kyunki upar == target check ho chuka hai, yahan strictly `<` likhna clean rehta hai).*
   - `else high = mid - 1;`:
     Target chhota hai, left half me search continue karo (`high = mid - 1`).
   - `return false;`:
     Search space khatam ho gayi aur element nahi mila -> element absent hai.

======================================================================
3. DETAILED DRY RUN:

   Input Matrix: n = 4 (rows), m = 5 (columns)
   Total elements = 4 * 5 = 20
   Virtual 1D Range: 0 to 19

   Row 0: [ 2,  4,  6,  7,  9]    (Virtual 0..4)
   Row 1: [21, 23, 25, 26, 27]   (Virtual 5..9)
   Row 2: [29, 32, 33, 34, 36]   (Virtual 10..14)
   Row 3: [37, 39, 40, 42, 45]   (Virtual 15..19)  [Assuming last row valid]

   Target = 35
   Initial: low = 0, high = 19

   --- Iteration 1 ---
   low = 0, high = 19 (0 <= 19 -> True)
   mid = (0 + 19) / 2 = 9
   Coordinate calculation:
     row = 9 / 5 = 1
     column = 9 % 5 = 4
   Cell inspected: nums[1][4] = 27
   Compare:
     27 == 35 -> False
     27 <= 35 -> True (Target bada hai)
   Action: low = mid + 1 = 9 + 1 = 10
   State: low = 10, high = 19

   --- Iteration 2 ---
   low = 10, high = 19 (10 <= 19 -> True)
   mid = (10 + 19) / 2 = 14
   Coordinate calculation:
     row = 14 / 5 = 2
     column = 14 % 5 = 4
   Cell inspected: nums[2][4] = 36
   Compare:
     36 == 35 -> False
     36 <= 35 -> False (Target chhota hai)
   Action: high = mid - 1 = 14 - 1 = 13
   State: low = 10, high = 13

   --- Iteration 3 ---
   low = 10, high = 13 (10 <= 13 -> True)
   mid = (10 + 13) / 2 = 11
   Coordinate calculation:
     row = 11 / 5 = 2
     column = 11 % 5 = 1
   Cell inspected: nums[2][1] = 32
   Compare:
     32 == 35 -> False
     32 <= 35 -> True (Target bada hai)
   Action: low = mid + 1 = 11 + 1 = 12
   State: low = 12, high = 13

   --- Iteration 4 ---
   low = 12, high = 13 (12 <= 13 -> True)
   mid = (12 + 13) / 2 = 12
   Coordinate calculation:
     row = 12 / 5 = 2
     column = 12 % 5 = 2
   Cell inspected: nums[2][2] = 33
   Compare:
     33 == 35 -> False
     33 <= 35 -> True (Target bada hai)
   Action: low = mid + 1 = 12 + 1 = 13
   State: low = 13, high = 13

   --- Iteration 5 ---
   low = 13, high = 13 (13 <= 13 -> True)
   mid = (13 + 13) / 2 = 13
   Coordinate calculation:
     row = 13 / 5 = 2
     column = 13 % 5 = 3
   Cell inspected: nums[2][3] = 34
   Compare:
     34 == 35 -> False
     34 <= 35 -> True (Target bada hai)
   Action: low = mid + 1 = 13 + 1 = 14
   State: low = 14, high = 13

   --- Termination ---
   Condition check: low <= high (14 <= 13) -> FALSE!
   Loop ends.
   Function returns false.
   Output: "The target value of 35 is present : false"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Virtual array size = N * M.
     * Binary search har step par search range aadhi karta hai: (N * M) -> (N * M)/2 -> ... -> 1.
     * Total Steps = log2(N * M) = log2(N) + log2(M).
     * Best Case: O(1) (Pehla mid hi target mil jaye).
     * Worst / Average Case: O(log(N * M)).
     * Matrix search ke liye yeh theoretically most optimal time complexity hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Pure constant memory footprint. Koi extra array ya dynamic memory allocate nahi ki gayi.
     * Sirf standard integer variables (`low`, `high`, `mid`, `row`, `column`, `n`, `m`) use hue hain.
======================================================================
*/

// yaha pe mein sach mein 2d matrix ko flatten karke 1d mein nahi change kar raha balki mein bas imagine kar raha 

bool search_2d(vector <vector<int>> &nums,int target){
    int low=0;
    int n=nums.size();
    int m=nums[0].size();
    int high=n*m-1;
    while(low<=high){
        int mid=(low+high)/2;
        int row=mid/m;
        int column=mid%m;
        if(nums[row][column]==target){
            return true;
        }
        else if(nums[row][column]<target){
            low=mid+1;
        }
        else{
            high=mid-1;
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