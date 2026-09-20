#include<bits/stdc++.h>
using namespace std;

/*

====================================================================
                        THOUGHT PROCESS
====================================================================

1. DIMS KA KHEL:
   - Agar matrix 3x4 ki hai (3 rows, 4 columns).
   - Clockwise 90 degree ghumate hi wo khadi ho jayegi, size banega 4x3.
   - Nayi matrix 'ans' ka dimension hoga: [columns][rows].

2. ROWS TO COLUMNS KA LOGIC:
   - 90 deg clockwise ghumane par original matrix ki:
     * Pehli Row (Row 0)  -> Nayi matrix ka aakhri column (Col 2) banegi.
     * Dusri Row (Row 1)  -> Nayi matrix ka beech ka column (Col 1) banegi.
     * Teesri Row (Row 2) -> Nayi matrix ka pehla column (Col 0) banegi.

3. INDEX MAPPING KA FORMULA:
   - Left to right chalna (j = 0, 1, 2, 3) ab upar se neeche ja raha hai:
     * new_row = j
   - Top to bottom rows ab right to left columns ban rahi hain:
     * new_col = total_rows - 1 - i  (yani: n - 1 - i)
   - Final Assignment: ans[j][n - 1 - i] = nums[i][j]


====================================================================
                  DRY RUN (3x4 MATRIX PAR STEP-BY-STEP)
====================================================================

INPUT MATRIX (nums):
Row 0: [ 1,   2,   3,   4 ]
Row 1: [ 5,   6,   7,   8 ]
Row 2: [ 9,  10,  11,  12 ]

Total Rows (n) = 3
Total Columns = 4
Nayi Matrix (ans) ka Size = 4 Rows x 3 Columns

--------------------------------------------------------------------
LOOP 1: Jab i = 0 (Row 0 process ho rahi hai)
Target Column: n - 1 - i = 3 - 1 - 0 = Column 2
--------------------------------------------------------------------
- j = 0 -> nums[0][0] (1)  jayega ans[0][2] pe
- j = 1 -> nums[0][1] (2)  jayega ans[1][2] pe
- j = 2 -> nums[0][2] (3)  jayega ans[2][2] pe
- j = 3 -> nums[0][3] (4)  jayega ans[3][2] pe

Result: ans ka Column 2 ban gaya:
[ _, _, 1 ]
[ _, _, 2 ]
[ _, _, 3 ]
[ _, _, 4 ]

--------------------------------------------------------------------
LOOP 2: Jab i = 1 (Row 1 process ho rahi hai)
Target Column: n - 1 - i = 3 - 1 - 1 = Column 1
--------------------------------------------------------------------
- j = 0 -> nums[1][0] (5)  jayega ans[0][1] pe
- j = 1 -> nums[1][1] (6)  jayega ans[1][1] pe
- j = 2 -> nums[1][2] (7)  jayega ans[2][1] pe
- j = 3 -> nums[1][3] (8)  jayega ans[3][1] pe

Result: ans ka Column 1 ban gaya:
[ _, 5, 1 ]
[ _, 6, 2 ]
[ _, 7, 3 ]
[ _, 8, 4 ]

--------------------------------------------------------------------
LOOP 3: Jab i = 2 (Row 2 process ho rahi hai)
Target Column: n - 1 - i = 3 - 1 - 2 = Column 0
--------------------------------------------------------------------
- j = 0 -> nums[2][0] (9)   jayega ans[0][0] pe
- j = 1 -> nums[2][1] (10)  jayega ans[1][0] pe
- j = 2 -> nums[2][2] (11)  jayega ans[2][0] pe
- j = 3 -> nums[2][3] (12)  jayega ans[3][0] pe

Result: ans ka Column 0 ban gaya:
[  9, 5, 1 ]
[ 10, 6, 2 ]
[ 11, 7, 3 ]
[ 12, 8, 4 ]

--------------------------------------------------------------------
FINAL OUTPUT (ans):
[  9,  5,  1 ]
[ 10,  6,  2 ]
[ 11,  7,  3 ]
[ 12,  8,  4 ]
====================================================================
*/

vector <vector<int>> rotate_matrix_by_90_deg(vector <vector<int>> &nums){
    int n = nums.size();
    int rows = nums.size();
    int columns = nums[0].size();
    // Rotated matrix will have dimensions: columns x rows
    vector<vector<int>> ans(columns, vector<int>(rows));

    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            ans[j][rows-i-1] = nums[i][j];
        }
    }
    return ans;
}

void printMatrix(const vector<vector<int>> &mat) {
    for (const auto &row : mat) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << "\n";
    }

    /*
    1. const vector<vector<int>> &mat
    & (Reference): Agar sirf vector<vector<int>> mat likhte, toh function call hote hi poori 
    2D matrix ki ek duplicate copy memory mein banti. & lagane ka matlab hai: "Copy mat bana, 
    original matrix ka direct address/reference use kar." Memory aur time dono bachta hai.

    const: Reference pass karne par dar rehta hai ki function ke andar galti se koi value modify 
    na ho jaye. const compiler ko bolta hai: "Yeh matrix strictly read-only hai, isme koi 
    chhed-chhaad nahi hogi."

    2. for (const auto &row : mat)
    . Yeh C++11 ka Range-based for loop (for-each loop) hai.
    . Normal loop mein index chalana padta hai: for(int i = 0; i < mat.size(); i++).
    . Range-based loop seedha elements uthata hai: "Matrix ke andar jitni rows hain, ek-ek karke 
     row naam ke dabbe mein daalo."
    . auto: Compiler khud samajh jata hai ki mat ke andar ka element ek 1D vector (vector<int>) hai. Type ka lamba naam nahi likhna padta.
     const ... &: Phir wahi baat — puri row ko copy karne ke bajaye uska reference uthata hai bina modify kiye.

    3. for (int val : row)
    Ab row ek normal 1D vector hai (jaise {1, 2, 3, 4}).
    Yeh loop uss row ke har ek number ko ek-ek karke val mein copy karta hai.

    4. \t
    Tab character. Elements ke beech mein 3-4 spaces ka gap de deta hai taaki 2-digit aur 1-digit numbers table ki tarah ek line mein align dikhein.
    */
}

int main() {
    // 3 x 4 matrix
    vector<vector<int>> mat = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "Original Matrix (3x4):\n";
    printMatrix(mat);

    vector<vector<int>> rotated = rotate_matrix_by_90_deg(mat);

    cout << "\nRotated Matrix by 90 Deg Clockwise (4x3):\n";
    printMatrix(rotated);

    return 0;
}

/*
====================================================================
               COMPLEXITY ANALYSIS (TC & SC)
====================================================================

Matrix Size:
- Rows = M (yahan 3)
- Columns = N (yahan 4)
- Total Elements = M * N (yahan 12)

--------------------------------------------------------------------
1. TIME COMPLEXITY (TC): O(M * N)
--------------------------------------------------------------------
- Outer loop 'i' chalta hai 0 se M-1 tak  -> M times
- Inner loop 'j' chalta hai 0 se N-1 tak  -> N times
- Loop ke andar ka operation:
    ans[j][n - 1 - i] = nums[i][j];
  Yeh ek constant time O(1) operation hai.

Total operations = M * N
Isliye Time Complexity = O(M * N)
(Agar square matrix N x N hoti, toh TC = O(N^2))

--------------------------------------------------------------------
2. SPACE COMPLEXITY (SC): O(M * N)
--------------------------------------------------------------------
- Nayi matrix 'ans' banayi hai of size N x M:
    vector<vector<int>> ans(columns, vector<int>(rows));
- Yeh memory mein M * N elements store karne ke liye extra jagah leti hai.
- Iske alawa sirf 3-4 integer variables use hue hain (n, rows, columns, i, j) jo O(1) hain.

Auxiliary / Extra Space = O(M * N)
Total Space Complexity  = O(M * N)

Note:
- Rectangular matrix (M != N) ko rotate karne ke liye dimensions change hoti hain,
  isliye extra matrix O(M * N) lena zaroori ho jata hai.
- Square matrix (N x N) hoti toh in-place (Transpose + Reverse) karke 
  SC ko O(1) kiya ja sakta tha.
====================================================================
*/