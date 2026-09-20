#include<bits/stdc++.h>
using namespace std;

/*
====================================================================
               THOUGHT PROCESS (KOD KA LOGIC KAISE SOCHA GAYA)
====================================================================

1. Problem aur Goal:
   - Hamara goal matrix ke har us row aur column ko 0 banana hai jisme 0 exist karta hai.
   - Better approach mein humne do extra vectors liye the: row[rows] aur col[columns].
   - Interviewer ki requirement: Auxiliary space O(1) hona chahiye (koi extra vector nahi lena).

2. Idea (Matrix ki boundary ko hi dummy arrays banana):
   - Matrix ke pehle row (nums[0][..]) ko hum column-tracker bana sakte hain.
   - Matrix ke pehle col (nums[..][0]) ko hum row-tracker bana sakte hain.

3. The Overlap Problem (Corner Cell nums[0][0]):
   - nums[0][0] row 0 aur column 0 dono ka part hai.
   - Agar nums[0][0] ko 0 kiya jaye, toh hume kaise pata chalega ki yeh Row 0 ke liye 0 hua ya Col 0 ke liye?
   - Is clash ko resolve karne ke liye:
     * nums[0][0] ko sirf 0th ROW ka marker banaya gaya.
     * 0th COLUMN ke liye ek alag simple variable le liya: `col0 = 1`.

4. Loop Order kaisa hona chahiye?
   - Step 1: Poora matrix traverse karke boundary markers (nums[i][0], nums[0][j], aur col0) set karenge.
   - Step 2: Inner submatrix (index 1 se rows-1, cols-1) ko update karenge.
     (Important: Inner matrix ko pehle update karna zaroori hai taaki row 0 aur col 0 ke markers pehle hi overwrite na ho jayein!)
   - Step 3: Last mein 0th row ko update karenge nums[0][0] ke basis par.
   - Step 4: Sabse aakhri mein 0th col ko update karenge col0 ke basis par.

====================================================================
         DETAILED LINE-BY-LINE DRY RUN (GIVEN 4x4 MATRIX)
====================================================================

INITIAL MATRIX:
Indices:    j=0  j=1  j=2  j=3
i = 0  -> [  1,   1,   1,   1  ]
i = 1  -> [  1,   0,   0,   1  ]
i = 2  -> [  1,   1,   0,   1  ]
i = 3  -> [  1,   1,   1,   1  ]

Initial variables:
rows = 4, columns = 4, col0 = 1

--------------------------------------------------------------------
PHASE 1: MARKING PHASE (i: 0 -> 3, j: 0 -> 3)
--------------------------------------------------------------------

- i = 0 (Row 0):
  * nums[0][0]=1, nums[0][1]=1, nums[0][2]=1, nums[0][3]=1
  * Koi 0 nahi mila -> No action.

- i = 1 (Row 1):
  * j = 0: nums[1][0] = 1 (No action)
  * j = 1: nums[1][1] == 0:
      -> nums[i][0] = 0  => nums[1][0] = 0 (Row 1 marked)
      -> j != 0 hai, toh nums[0][j] = 0 => nums[0][1] = 0 (Col 1 marked)
  * j = 2: nums[1][2] == 0:
      -> nums[i][0] = 0  => nums[1][0] = 0 (Row 1 already marked)
      -> j != 0 hai, toh nums[0][j] = 0 => nums[0][2] = 0 (Col 2 marked)
  * j = 3: nums[1][3] = 1 (No action)

- i = 2 (Row 2):
  * j = 0: nums[2][0] = 1 (No action)
  * j = 1: nums[2][1] = 1 (No action)
  * j = 2: nums[2][2] == 0:
      -> nums[i][0] = 0  => nums[2][0] = 0 (Row 2 marked)
      -> j != 0 hai, toh nums[0][j] = 0 => nums[0][2] = 0 (Col 2 already marked)
  * j = 3: nums[2][3] = 1 (No action)

- i = 3 (Row 3):
  * nums[3][0]=1, nums[3][1]=1, nums[3][2]=1, nums[3][3]=1
  * Koi 0 nahi mila -> No action.

Phase 1 khatam hone par Matrix:
Row 0 markers: [ 1,  0,  0,  1 ]
Row 1 marker:  [ 0,  0,  0,  1 ]
Row 2 marker:  [ 0,  1,  0,  1 ]
Row 3 marker:  [ 1,  1,  1,  1 ]
col0 = 1 (kyunki j == 0 par koi 0 nahi tha)

--------------------------------------------------------------------
PHASE 2: INNER MATRIX RESOLUTION (i: 1 -> 3, j: 1 -> 3)
--------------------------------------------------------------------
Condition check: if (nums[i][0] == 0 || nums[0][j] == 0) -> nums[i][j] = 0

* For i = 1:
  nums[1][0] == 0 hai, isliye row 1 ke saare inner cells 0 honge:
  nums[1][1] = 0
  nums[1][2] = 0
  nums[1][3] = 0

* For i = 2:
  nums[2][0] == 0 hai, isliye row 2 ke saare inner cells 0 honge:
  nums[2][1] = 0
  nums[2][2] = 0
  nums[2][3] = 0

* For i = 3:
  nums[3][0] == 1 hai (row marked nahi hai), ab columns check honge:
  - j = 1: nums[0][1] == 0 hai -> nums[3][1] = 0
  - j = 2: nums[0][2] == 0 hai -> nums[3][2] = 0
  - j = 3: nums[0][3] == 1 aur nums[3][0] == 1 -> nums[3][3] = 1 (unchanged)

Phase 2 khatam hone par Matrix:
[ 1,  0,  0,  1 ]  <- (Abhi Row 0 resolve nahi hui)
[ 0,  0,  0,  0 ]
[ 0,  0,  0,  0 ]
[ 1,  0,  0,  1 ]

--------------------------------------------------------------------
PHASE 3: 0th ROW RESOLUTION
--------------------------------------------------------------------
Condition check: if (nums[0][0] == 0)
- Hamare case mein nums[0][0] == 1 hai.
- Iska matlab Row 0 mein koi original 0 nahi tha.
- So, Row 0 untouched rahegi: [ 1, 0, 0, 1 ].

--------------------------------------------------------------------
PHASE 4: 0th COLUMN RESOLUTION
--------------------------------------------------------------------
Condition check: if (col0 == 0)
- Hamare case mein col0 == 1 hai.
- Iska matlab Column 0 mein koi original 0 nahi tha.
- So, Col 0 bhi untouched rahega.

====================================================================
FINAL OUTPUT MATRIX:
1  0  0  1
0  0  0  0
0  0  0  0
1  0  0  1

====================================================================
COMPLEXITY RECAP:
- Time Complexity: O(2 * (N * M)) = O(N * M)
- Space Complexity: O(1) Auxiliary Space
====================================================================

*/
void set_matrix_zeroes(vector <vector<int>> &nums){
    int n = nums.size();
    int rows = nums.size();
    int columns = nums[0].size();
    int col0 = 1;
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            if(nums[i][j] == 0){
                // first row ko zero karo
                nums[i][0] = 0;

                // mark the jth column :-
                if(j != 0){
                    nums[0][j] = 0;
                }
                else{
                    col0 = 0;
                }
            }
        }
    }

    for(int i = 1;i < rows;i++){
        for(int j = 1;j < columns;j++){
            // check for row and column 
            if(nums[i][j] != 0){
                // check for row and column
                if(nums[i][0] == 0 || nums[0][j] == 0){
                    nums[i][j] = 0;
                }
            }
        }
    }

    // Checking for 0th row and 0th column based on FIRST ELEMENT ONLY :-
    if(nums[0][0] == 0){
        for(int j = 0;j < columns;j++){
            nums[0][j] = 0;
        }
    }
    if(col0 == 0){
        for(int i = 0;i < rows;i++){
            nums[i][0] = 0;
        }
    }
}

int main(){
    vector<vector<int>> matrix = {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 1}
    };

    // Print the matrix
    cout<<"Before setting to zeroes :-"<<endl;
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
    cout<<endl;

    set_matrix_zeroes(matrix);

    // Print the matrix
    cout<<"After setting to zeroes :-"<<endl;
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}