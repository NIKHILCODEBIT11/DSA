#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
1. KYU YE APPROACH SIRF (N x N) MATRIX MEIN HI WORK KARTI HAI?
================================================================================

A. In-Place Swap ka Index Out-of-Bounds Issue:
   - Transpose ka formula hota hai: swap(nums[i][j], nums[j][i]).
   - Square Matrix (N x N) mein:
     Agar matrix 4x4 hai, toh row indices (0 se 3) aur column indices (0 se 3)
     dono identical hote hain. Agar (0, 3) valid hai, toh (3, 0) bhi 100% valid
     hoga. Koi crash nahi hoga.
   - Non-Square Matrix (M x N, maan lo 3x4):
     Rows = 3 (indices: 0, 1, 2)
     Cols = 4 (indices: 0, 1, 2, 3)
     Jab loop coordinate (0, 3) par pahuchega, code execute karega:
     swap(nums[0][3], nums[3][0])
     Yahan nums[3][0] ka matlab hai Row 3 — jo exist hi nahi karti!
     Result: Segmentation Fault / Out of bounds memory crash.

B. Dimension Mismatch (Size Change):
   - Kisi bhi R x C matrix ko rotate karoge toh uske dimensions C x R ban jate hain.
   - N x N matrix rotate hone ke baad bhi N x N rehta hai, isliye bina memory
     allocate kiye usi dabbe ke andar elements swap ho sakte hain.
   - 3x4 matrix rotate hoke 4x3 banega. Ek 3x4 vector container ko bina naya
     vector banaye ya resize kiye direct elements swap karke shape nahi badal sakte.

--------------------------------------------------------------------------------
M x N MATRIX KE LIYE KYA KARNA PADEGA?
--------------------------------------------------------------------------------
- In-place swap + row reverse approach M x N par fail ho jata hai.
- Solution: Ek naya matrix banana padega jiska size (Cols x Rows) ho.
- Formula:
  Original matrix ke element (i, j) ko seedha target position par daal do:
  rotated[j][rows - 1 - i] = nums[i][j];
- Time Complexity: O(M * N)
- Space Complexity: O(M * N) (kyunki naya matrix lagta hai)
================================================================================
*/


/*
================================================================================
2. THOUGHT PROCESS (90 DEGREE CLOCKWISE ROTATION)
================================================================================

Goal: Matrix ko 90 degree clockwise turn karna hai bina kisi extra space ke (O(1) Aux Space).

Pattern Observation:
Original 4x4 matrix ko dhyan se dekho:
- 1st Row [ 1,  2,  3,  4]  --> Rotated matrix ka Last Column ban jata hai.
- 2nd Row [ 5,  6,  7,  8]  --> Rotated matrix ka 3rd Column ban jata hai.
- 3rd Row [ 9, 10, 11, 12]  --> Rotated matrix ka 2nd Column ban jata hai.
- 4th Row [13, 14, 15, 16]  --> Rotated matrix ka 1st Column ban jata hai.

Problem:
Agar hum ek element ko directly uski nayi jagah bhejenge, toh wahan ka
purana element overwrite ho jayega. 4 elements ki cycle handle karna thoda
tricky aur error-prone ho jata hai.

Clever 2-Step Mathematical Trick:
Puri rotation ko do basic operations mein tod do:

Step 1: Transpose (Rows ko Columns bana do)
        - Isse (i, j) ban jayega (j, i).
        - 1st Row ban gayi 1st Column, 2nd Row ban gayi 2nd Column...
        - Notice: Columns toh ban gaye, lekin order ulta hai! Pehli row ko
          aakhri column banna tha, par wo pehla column ban gayi.

Step 2: Reverse Each Row (Horizontal Mirror Flip)
        - Har row ko pakad ke ulta kar do (reverse).
        - Isse 1st column chala jayega last column mein, 2nd ban jayega 3rd, etc.
        - Result: Perfectly rotated by 90 degrees clockwise!

Summary Formula:
90 deg Clockwise = Transpose + Reverse each row
(Note: Agar 90 deg Anti-Clockwise karna hota toh: Transpose + Reverse each column)
================================================================================
*/


/*
================================================================================
3. DETAILED DRY RUN (ON 4 x 4 MATRIX)
================================================================================

Initial Matrix:
Row 0: [  1,   2,   3,   4 ]
Row 1: [  5,   6,   7,   8 ]
Row 2: [  9,  10,  11,  12 ]
Row 3: [ 13,  14,  15,  16 ]

--------------------------------------------------------------------------------
PHASE 1: TRANSPOSE MATRIX
Loop conditions:
- i chalta hai 0 se rows - 2 tak
- j hamesha i + 1 se start hota hai (taaki diagonal chhoot jaye aur double swap na ho)

-- Jab i = 0 --
* j = 1: swap(nums[0][1], nums[1][0]) -> swap(2, 5)
* j = 2: swap(nums[0][2], nums[2][0]) -> swap(3, 9)
* j = 3: swap(nums[0][3], nums[3][0]) -> swap(4, 13)

Matrix state:
[  1,   5,   9,  13 ]
[  2,   6,   7,   8 ]
[  3,  10,  11,  12 ]
[  4,  14,  15,  16 ]

-- Jab i = 1 --
* j = 2: swap(nums[1][2], nums[2][1]) -> swap(7, 10)
* j = 3: swap(nums[1][3], nums[3][1]) -> swap(8, 14)

Matrix state:
[  1,   5,   9,  13 ]
[  2,   6,  10,  14 ]
[  3,   7,  11,  12 ]
[  4,   8,  15,  16 ]

-- Jab i = 2 --
* j = 3: swap(nums[2][3], nums[3][2]) -> swap(12, 15)

Transposed Matrix final state:
[  1,   5,   9,  13 ]
[  2,   6,  10,  14 ]
[  3,   7,  11,  15 ]
[  4,   8,  12,  16 ]

--------------------------------------------------------------------------------
PHASE 2: REVERSE EACH ROW
Loop har row (i = 0 se 3) par chalega aur puri row ko flip karega:

* Row 0 flip: [  1,   5,   9,  13 ]  ==>  [ 13,   9,   5,   1 ]
* Row 1 flip: [  2,   6,  10,  14 ]  ==>  [ 14,  10,   6,   2 ]
* Row 2 flip: [  3,   7,  11,  15 ]  ==>  [ 15,  11,   7,   3 ]
* Row 3 flip: [  4,   8,  12,  16 ]  ==>  [ 16,  12,   8,   4 ]

--------------------------------------------------------------------------------
FINAL ROTATED MATRIX (90 DEGREE CLOCKWISE):
[ 13,   9,   5,   1 ]
[ 14,  10,   6,   2 ]
[ 15,  11,   7,   3 ]
[ 16,  12,   8,   4 ]

Complexity Analysis:
- Transpose Step: O(N^2 / 2) swaps
- Reverse Step: O(N * (N / 2)) swaps
- Total Time Complexity: O(N^2)
- Total Space Complexity: O(1) Auxiliary Space
================================================================================
*/

void transpose_matrix(vector <vector<int>> &nums){
    int rows = nums.size();
    int columns = nums[0].size();

    for(int i = 0;i < rows - 1;i++){
        for(int j = i+1;j < columns;j++){
            swap(nums[i][j], nums[j][i]);
        }
    }
}

void reverse_each_row(vector <vector<int>> &nums){
    int rows = nums.size();
    for(int i = 0;i < rows;i++){
        reverse(nums[i].begin(), nums[i].end());
    }
}

void rotate_matrix_by_90_deg(vector <vector<int>> &nums){
    transpose_matrix(nums);
    reverse_each_row(nums);
}

void printMatrix(const vector <vector<int>> &nums){
    for(const auto &row : nums){
        for(const int val : row){
            cout<<val<<"\t";
        }
        cout<<"\n";
    }
}

int main() {
    // 4 x 4 matrix
    vector<vector<int>> mat = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    cout << "Original Matrix (3x4):\n";
    printMatrix(mat);

    rotate_matrix_by_90_deg(mat);

    cout << "\nRotated Matrix by 90 Deg Clockwise (4x3):\n";
    printMatrix(mat);

    return 0;
}

