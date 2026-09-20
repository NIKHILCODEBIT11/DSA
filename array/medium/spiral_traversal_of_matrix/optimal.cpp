#include<bits/stdc++.h>
using namespace std;

// kisis bhi step mein confusion ho to do type ke matrix imagine kar 1 * n and n * 1 kyuki m * n wali to hogi hi edge case 1 * n aur n * 1 mein hai
/*
========================================================================================
                          SPIRAL TRAVERSAL (6 x 6 MATRIX)
========================================================================================

    [1] ---->  [2] ---->  [3] ---->  [4] ---->  [5] ---->  [6]
                                                             |
     ^                                                       v
     |                                                       |
   [20]       [21] ----> [22] ----> [23] ----> [24]         [7]
     ^                                           |           |
     |         ^                                 v           v
     |         |                                 |           |
   [19]      [32]       [33] ----> [34]        [25]         [8]
     ^         ^                     |           |           |
     |         |                     v           v           v
     |         |                     |           |           |
   [18]      [31]       [36] <---- [35]        [26]         [9]
     ^         ^                                 |           |
     |         |                                 v           v
     |         |                                 |           |
   [17]      [30] <---- [29] <---- [28] <----  [27]        [10]
     ^                                                       |
     |                                                       v
     |                                                       |
   [16] <---- [15] <---- [14] <---- [13] <---- [12] <---- [11]

========================================================================================
TRAVERSAL ORDER & BOUNDARY TRANSITIONS:
----------------------------------------------------------------------------------------
• LAYER 1 (Outer Ring):
  - Top Row    (L -> R) : 1  -> 2  -> 3  -> 4  -> 5  -> 6   [top++    => top = 1]
  - Right Col  (T -> B) : 7  -> 8  -> 9  -> 10 -> 11        [right--  => right = 4]
  - Bottom Row (R -> L) : 12 -> 13 -> 14 -> 15 -> 16        [bottom-- => bottom = 4]
  - Left Col   (B -> T) : 17 -> 18 -> 19 -> 20              [left++   => left = 1]

• LAYER 2 (Middle Ring):
  - Top Row    (L -> R) : 21 -> 22 -> 23 -> 24              [top++    => top = 2]
  - Right Col  (T -> B) : 25 -> 26 -> 27                    [right--  => right = 3]
  - Bottom Row (R -> L) : 28 -> 29 -> 30                    [bottom-- => bottom = 3]
  - Left Col   (B -> T) : 31 -> 32                          [left++   => left = 2]

• LAYER 3 (Inner Core):
  - Top Row    (L -> R) : 33 -> 34                          [top++    => top = 3]
  - Right Col  (T -> B) : 35                                [right--  => right = 2]
  - Bottom Row (R -> L) : 36                                [bottom-- => bottom = 2]
  - Left Col   (B -> T) : [left <= right check fails: 2 <= 2 is true, but bottom (2) >= top (3) is false]
                          => Loop exits cleanly!
========================================================================================
FINAL OUTPUT:
1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
========================================================================================
*/

// ============================================================================
// COMPLETE DRY RUN OF SPIRAL TRAVERSAL ACROSS ALL MATRIX ARCHITECTURES
// ============================================================================
// 4 PRIMARY BOUNDARIES:
// - top    : tracks the uppermost unprocessed row index
// - bottom : tracks the lowermost unprocessed row index
// - left   : tracks the leftmost unprocessed column index
// - right  : tracks the rightmost unprocessed column index
//
// 4 SEQUENTIAL STEPS PER ITERATION:
// 1. Move Left -> Right across row 'top', then top++
// 2. Move Top -> Bottom down col 'right', then right--
// 3. Guard (top <= bottom): Move Right -> Left across row 'bottom', then bottom--
// 4. Guard (left <= right): Move Bottom -> Top up col 'left', then left++
// ============================================================================


// ============================================================================
// TYPE 1: SINGLE ROW MATRIX (1 x 4)
// Matrix: [ [10, 20, 30, 40] ]
// Initial State: top = 0, bottom = 0, left = 0, right = 3, ans = []
// ============================================================================
//
// [ITERATION 1]
// -> Check while (top <= bottom && left <= right):
//    (0 <= 0 && 0 <= 3) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 0):
//    for (i = 0; i <= 3; i++)
//      i = 0: push nums[0][0] = 10
//      i = 1: push nums[0][1] = 20
//      i = 2: push nums[0][2] = 30
//      i = 3: push nums[0][3] = 40
//    State: ans = [10, 20, 30, 40]
//    top++ executes -> top = 1
//
// -> Step 2 (Top -> Bottom down col 'right' = 3):
//    for (i = top; i <= bottom; i++) -> for (i = 1; i <= 0; i++)
//    Condition (1 <= 0) is FALSE. Loop executes 0 times.
//    right-- executes -> right = 2
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 1 <= 0 -> FALSE!
//    CRITICAL BEHAVIOR: Entire Step 3 block is completely skipped.
//    WHY THIS MATTERS: If this guard did not exist, the reverse loop
//    for (i = 2; i >= 0; i--) would run on row bottom = 0, re-adding
//    elements 30, 20, 10 in reverse. The guard prevents this duplication.
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 0 <= 2 -> TRUE. Enter guard block.
//    for (i = bottom; i >= top; i--) -> for (i = 0; i >= 1; i--)
//    Condition (0 >= 1) is FALSE. Loop executes 0 times.
//    left++ executes -> left = 1
//
// -> Check while (top <= bottom && left <= right):
//    (1 <= 0 && 1 <= 2) -> (FALSE && TRUE) -> FALSE.
//    Loop terminates immediately.
//
// FINAL OUTPUT (Type 1): [10, 20, 30, 40]


// ============================================================================
// TYPE 2: SINGLE COLUMN MATRIX (4 x 1)
// Matrix:
// [ [1],
//   [2],
//   [3],
//   [4] ]
// Initial State: top = 0, bottom = 3, left = 0, right = 0, ans = []
// ============================================================================
//
// [ITERATION 1]
// -> Check while (top <= bottom && left <= right):
//    (0 <= 3 && 0 <= 0) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 0):
//    for (i = 0; i <= 0; i++)
//      i = 0: push nums[0][0] = 1
//    State: ans = [1]
//    top++ executes -> top = 1
//
// -> Step 2 (Top -> Bottom down col 'right' = 0):
//    for (i = top; i <= bottom; i++) -> for (i = 1; i <= 3; i++)
//      i = 1: push nums[1][0] = 2
//      i = 2: push nums[2][0] = 3
//      i = 3: push nums[3][0] = 4
//    State: ans = [1, 2, 3, 4]
//    right-- executes -> right = -1
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 1 <= 3 -> TRUE. Enter guard block.
//    for (i = right; i >= left; i--) -> for (i = -1; i >= 0; i--)
//    Condition (-1 >= 0) is FALSE. Loop executes 0 times.
//    bottom-- executes -> bottom = 2
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 0 <= -1 -> FALSE!
//    CRITICAL BEHAVIOR: Entire Step 4 block is completely skipped.
//    WHY THIS MATTERS: Notice that top = 1 and bottom = 2.
//    If this guard did not exist, the upward loop
//    for (i = 2; i >= 1; i--) would run on col left = 0, re-adding
//    elements nums[2][0] = 3 and nums[1][0] = 2.
//    The check (0 <= -1) blocks this completely.
//
// -> Check while (top <= bottom && left <= right):
//    (1 <= 2 && 0 <= -1) -> (TRUE && FALSE) -> FALSE.
//    Loop terminates immediately.
//
// FINAL OUTPUT (Type 2): [1, 2, 3, 4]


// ============================================================================
// TYPE 3: RECTANGULAR MATRIX WITH ROWS < COLS (2 x 3)
// Matrix:
// [ [1, 2, 3],
//   [4, 5, 6] ]
// Initial State: top = 0, bottom = 1, left = 0, right = 2, ans = []
// ============================================================================
//
// [ITERATION 1]
// -> Check while (top <= bottom && left <= right):
//    (0 <= 1 && 0 <= 2) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 0):
//    for (i = 0; i <= 2; i++)
//      i = 0: push nums[0][0] = 1
//      i = 1: push nums[0][1] = 2
//      i = 2: push nums[0][2] = 3
//    State: ans = [1, 2, 3]
//    top++ executes -> top = 1
//
// -> Step 2 (Top -> Bottom down col 'right' = 2):
//    for (i = 1; i <= 1; i++)
//      i = 1: push nums[1][2] = 6
//    State: ans = [1, 2, 3, 6]
//    right-- executes -> right = 1
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 1 <= 1 -> TRUE. Enter guard block.
//    for (i = right; i >= left; i--) -> for (i = 1; i >= 0; i--) on row bottom = 1
//      i = 1: push nums[1][1] = 5
//      i = 0: push nums[1][0] = 4
//    State: ans = [1, 2, 3, 6, 5, 4]
//    bottom-- executes -> bottom = 0
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 0 <= 1 -> TRUE. Enter guard block.
//    for (i = bottom; i >= top; i--) -> for (i = 0; i >= 1; i--)
//    Condition (0 >= 1) is FALSE. Loop executes 0 times.
//    left++ executes -> left = 1
//
// -> Check while (top <= bottom && left <= right):
//    (1 <= 0 && 1 <= 1) -> (FALSE && TRUE) -> FALSE.
//    Loop terminates immediately.
//
// FINAL OUTPUT (Type 3): [1, 2, 3, 6, 5, 4]


// ============================================================================
// TYPE 4: RECTANGULAR MATRIX WITH ROWS > COLS (3 x 2)
// Matrix:
// [ [1, 2],
//   [3, 4],
//   [5, 6] ]
// Initial State: top = 0, bottom = 2, left = 0, right = 1, ans = []
// ============================================================================
//
// [ITERATION 1]
// -> Check while (top <= bottom && left <= right):
//    (0 <= 2 && 0 <= 1) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 0):
//    for (i = 0; i <= 1; i++)
//      i = 0: push nums[0][0] = 1
//      i = 1: push nums[0][1] = 2
//    State: ans = [1, 2]
//    top++ executes -> top = 1
//
// -> Step 2 (Top -> Bottom down col 'right' = 1):
//    for (i = 1; i <= 2; i++)
//      i = 1: push nums[1][1] = 4
//      i = 2: push nums[2][1] = 6
//    State: ans = [1, 2, 4, 6]
//    right-- executes -> right = 0
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 1 <= 2 -> TRUE. Enter guard block.
//    for (i = 0; i >= 0; i--) on row bottom = 2
//      i = 0: push nums[2][0] = 5
//    State: ans = [1, 2, 4, 6, 5]
//    bottom-- executes -> bottom = 1
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 0 <= 0 -> TRUE. Enter guard block.
//    for (i = bottom; i >= top; i--) -> for (i = 1; i >= 1; i--) on col left = 0
//      i = 1: push nums[1][0] = 3
//    State: ans = [1, 2, 4, 6, 5, 3]
//    left++ executes -> left = 1
//
// -> Check while (top <= bottom && left <= right):
//    (1 <= 1 && 1 <= 0) -> (TRUE && FALSE) -> FALSE.
//    Loop terminates immediately.
//
// FINAL OUTPUT (Type 4): [1, 2, 4, 6, 5, 3]


// ============================================================================
// TYPE 5: SQUARE MATRIX (3 x 3)
// Matrix:
// [ [1, 2, 3],
//   [4, 5, 6],
//   [7, 8, 9] ]
// Initial State: top = 0, bottom = 2, left = 0, right = 2, ans = []
// ============================================================================
//
// [ITERATION 1: OUTER LAYER]
// -> Check while (top <= bottom && left <= right):
//    (0 <= 2 && 0 <= 2) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 0):
//    for (i = 0; i <= 2; i++)
//      i = 0: push nums[0][0] = 1
//      i = 1: push nums[0][1] = 2
//      i = 2: push nums[0][2] = 3
//    State: ans = [1, 2, 3]
//    top++ executes -> top = 1
//
// -> Step 2 (Top -> Bottom down col 'right' = 2):
//    for (i = 1; i <= 2; i++)
//      i = 1: push nums[1][2] = 6
//      i = 2: push nums[2][2] = 9
//    State: ans = [1, 2, 3, 6, 9]
//    right-- executes -> right = 1
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 1 <= 2 -> TRUE. Enter guard block.
//    for (i = 1; i >= 0; i--) on row bottom = 2
//      i = 1: push nums[2][1] = 8
//      i = 0: push nums[2][0] = 7
//    State: ans = [1, 2, 3, 6, 9, 8, 7]
//    bottom-- executes -> bottom = 1
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 0 <= 1 -> TRUE. Enter guard block.
//    for (i = 1; i >= 1; i--) on col left = 0
//      i = 1: push nums[1][0] = 4
//    State: ans = [1, 2, 3, 6, 9, 8, 7, 4]
//    left++ executes -> left = 1
//
// [ITERATION 2: CENTER ELEMENT]
// -> Check while (top <= bottom && left <= right):
//    (1 <= 1 && 1 <= 1) -> TRUE. Enter loop.
//
// -> Step 1 (Left -> Right across row 'top' = 1):
//    for (i = 1; i <= 1; i++)
//      i = 1: push nums[1][1] = 5
//    State: ans = [1, 2, 3, 6, 9, 8, 7, 4, 5]
//    top++ executes -> top = 2
//
// -> Step 2 (Top -> Bottom down col 'right' = 1):
//    for (i = 2; i <= 1; i++)
//    Condition (2 <= 1) is FALSE. Loop executes 0 times.
//    right-- executes -> right = 0
//
// -> Step 3 Guard Check: if (top <= bottom)
//    Check: 2 <= 1 -> FALSE!
//    Step 3 is skipped. Center element is not re-processed.
//
// -> Step 4 Guard Check: if (left <= right)
//    Check: 1 <= 0 -> FALSE!
//    Step 4 is skipped.
//
// -> Check while (top <= bottom && left <= right):
//    (2 <= 1 && 1 <= 0) -> (FALSE && FALSE) -> FALSE.
//    Loop terminates immediately.
//
// FINAL OUTPUT (Type 5): [1, 2, 3, 6, 9, 8, 7, 4, 5]
// ============================================================================

vector <int> spiral_traversal_of_matrix(vector <vector<int>> &nums){
    int rows = nums.size();
    int columns = nums[0].size();
    vector <int> ans;
    int left = 0, right = columns - 1;
    int top = 0, bottom = rows - 1;

    while(top <= bottom && left <= right){
        // RIGHT -> BOTTOM -> LEFT -> TOP

        // LEFT -> RIGHT
        for(int i = left;i <= right;i++){
            ans.push_back(nums[top][i]);
        }
        top++;
        
        // TOP -> BOTTOM
        for(int i = top;i <= bottom;i++){
            ans.push_back(nums[i][right]);
        }
        right--;

        //RIGHT -> LEFT
        if(top <= bottom){     // Is case mein 1 * n marix imagine kar aur saath hi n* 1 imagine kar problem dikhegi n * 1 mein, agar maine top <= bottom use kiya but usme bhi left <= right work karegi aur 1 * n mein dono ki logic clear hai
            for(int i = right;i >= left;i--){
                ans.push_back(nums[bottom][i]);
            }
            bottom--;
        }

        // BOTTOM -> TOP
        if(left <= right){    // Is case mein 1 * n marix imagine kar aur saath hi n* 1 imagine kar problem dikhegi 1 * n mein, agar maine left <= right use kiya but usme bhi top <= bottom work karegi aur n * 1 mein dono ki logic clear hai  
            for(int i = bottom;i >= top;i--){
                ans.push_back(nums[i][left]);
            }
            left++;
        }
        
    }

    return ans;
}

int main(){
    vector<vector<int>> nums = {
    { 1,  2,  3,  4,  5,  6},
    {20, 21, 22, 23, 24,  7},
    {19, 32, 33, 34, 25,  8},
    {18, 31, 36, 35, 26,  9},
    {17, 30, 29, 28, 27, 10},
    {16, 15, 14, 13, 12, 11}
    };

    vector <int> ans = spiral_traversal_of_matrix(nums);

    for(int x : ans){
        cout<<x<<" ";
    }

    return 0;
}

// ============================================================================
// COMPLEXITY ANALYSIS: SPIRAL MATRIX TRAVERSAL
// ============================================================================
// Let:
//   m = Number of rows    (nums.size())
//   n = Number of columns (nums[0].size())
//   Total elements = m * n
// ============================================================================

// ----------------------------------------------------------------------------
// 1. TIME COMPLEXITY (TC): O(m * n)
// ----------------------------------------------------------------------------
// - Har ek element matrix ke andar exactly EK hi baar process hota hai.
// - Pointers (top, bottom, left, right) progressively shrink hote rehte hain:
//     * Row 'top' traverse hui    -> top++
//     * Col 'right' traverse hui  -> right--
//     * Row 'bottom' traverse hui -> bottom--
//     * Col 'left' traverse hui   -> left++
// - Kisi bhi cell ko dobara re-visit nahi kiya jata.
// - Total operations direct proportional hain matrix ke total elements ke:
//     * For m x n matrix    : O(m * n)
//     * For n x n (Square) : O(n^2)

// ----------------------------------------------------------------------------
// 2. SPACE COMPLEXITY (SC)
// ----------------------------------------------------------------------------
// A. Auxiliary Space (Extra Memory used by algorithm logic):
//    -> O(1)
//    - Algorithm ko run karne ke liye koi extra data structure nahi lagta.
//    - Koi auxiliary visited 2D matrix, hash map ya recursion stack nahi hai.
//    - Sirf 4 integer pointers use hote hain:
//        int left, right, top, bottom;
//      jo memory mein constant extra space O(1) lete hain.
//
// B. Output Space (To store and return the result):
//    -> O(m * n)
//    - Function vector<int> return karta hai jisme saare m * n elements
//      spiral order mein store hote hain.
//
// TOTAL SPACE COMPLEXITY:
//    - If including output vector : O(m * n)
//    - If excluding output vector : O(1)
// ============================================================================