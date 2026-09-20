#include<bits/stdc++.h>
using namespace std;

/*
suppose nums :-
1 1 1 1 
1 0 0 1 
1 1 0 1 
1 1 1 1 

end result :-
1 0 0 1 
0 0 0 0 
0 0 0 0 
1 0 0 1 

To mein do extra vectors rakhunga :- row, col
row col - 0 0 0 0
 |
 0        1 1 1 1
 0        1 0 0 1
 0        1 1 0 1
 0        1 1 1 1

agar mein matrix mein jaha jaha 0 hai waha ke rowand col index ko 0 -> 1 kar du :-
row col - 0 1 1 0
 |
 0        1 1 1 1
 1        1 0 0 1
 1        1 1 0 1
 0        1 1 1 1

 ab agar mein jin jin row-index aur saath hi col-index ka value 1 hai, matrix mein un indexes ke elements ko 0 kar du :-
row col - 0 1 1 0
 |
 0        1 0 0 1
 1        0 0 0 0
 1        0 0 0 0
 0        1 0 0 1

Yaha pe mein do vectors banaunga row of size rows, col of size columns jisko mein elements 0 se initialize karunga
phir pure matrix mein traverse karunga aur jaha bhi mujhe 0 mile us element ke corresponding row-index and column-index ko mein row, col vectors mein 0 -> 1 kar dunga
phir final traversal karunga aur jis row -index OR col-index mein 1 hoga us element ko 0 kar dunga

*/
void set_matrix_zeroes(vector <vector<int>> &nums){
    int rows = nums.size();
    int columns = nums[0].size();

    vector <int> row(rows, 0);
    vector <int> col(columns, 0);

    // Traversing the whole matrix and finding row and column index where 0 is present:-
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            if(nums[i][j] == 0){
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    // Traversing the whole array and making all the elements as 0 where row and column index is 1
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < columns;j++){
            if(row[i] == 1 || col[j] == 1){
                nums[i][j] = 0;
            }
        }
    }
    
}

/*
====================================================================
           DETAILED DRY RUN & COMPLEXITY ANALYSIS (BETTER APPROACH)
====================================================================

INITIAL MATRIX:
Index:     j=0  j=1  j=2  j=3
i = 0  -> [ 1,   1,   1,   1 ]
i = 1  -> [ 1,   0,   0,   1 ]
i = 2  -> [ 1,   1,   0,   1 ]
i = 3  -> [ 1,   1,   1,   1 ]

Dimensions: rows = 4, columns = 4

Tracking Arrays Initialized to 0:
row array (size 4): [ 0,  0,  0,  0 ]  (index: 0, 1, 2, 3)
col array (size 4): [ 0,  0,  0,  0 ]  (index: 0, 1, 2, 3)

--------------------------------------------------------------------
PHASE 1: FINDING ZEROES & MARKING TRACKER ARRAYS
--------------------------------------------------------------------
Iterate i: 0 -> 3, j: 0 -> 3

- i = 0: Sabhi elements 1 hain. (No action)
- i = 1:
    * j = 0: nums[1][0] = 1 (No action)
    * j = 1: nums[1][1] == 0  --> row[1] = 1, col[1] = 1
    * j = 2: nums[1][2] == 0  --> row[1] = 1, col[2] = 1
    * j = 3: nums[1][3] = 1 (No action)
- i = 2:
    * j = 0: nums[2][0] = 1 (No action)
    * j = 1: nums[2][1] = 1 (No action)
    * j = 2: nums[2][2] == 0  --> row[2] = 1, col[2] = 1
    * j = 3: nums[2][3] = 1 (No action)
- i = 3: Sabhi elements 1 hain. (No action)

Phase 1 ke baad Tracker Arrays:
row = [ 0, 1, 1, 0 ]   -> (Matlab Row 1 aur Row 2 pure 0 banenge)
col = [ 0, 1, 1, 0 ]   -> (Matlab Col 1 aur Col 2 pure 0 banenge)

--------------------------------------------------------------------
PHASE 2: UPDATING MATRIX USING TRACKER ARRAYS
--------------------------------------------------------------------
Condition: if (row[i] == 1 || col[j] == 1) -> nums[i][j] = 0;

- Row 0 (row[0] = 0):
    * j = 0: row[0]=0, col[0]=0 -> 1 (unchanged)
    * j = 1: col[1]=1           -> becomes 0
    * j = 2: col[2]=1           -> becomes 0
    * j = 3: row[0]=0, col[3]=0 -> 1 (unchanged)
    Result: [ 1, 0, 0, 1 ]

- Row 1 (row[1] = 1):
    * row[1] == 1 hai, toh poori row ke saare elements 0 ho jayenge!
    Result: [ 0, 0, 0, 0 ]

- Row 2 (row[2] = 1):
    * row[2] == 1 hai, toh poori row ke saare elements 0 ho jayenge!
    Result: [ 0, 0, 0, 0 ]

- Row 3 (row[3] = 0):
    * j = 0: row[3]=0, col[0]=0 -> 1 (unchanged)
    * j = 1: col[1]=1           -> becomes 0
    * j = 2: col[2]=1           -> becomes 0
    * j = 3: row[3]=0, col[3]=0 -> 1 (unchanged)
    Result: [ 1, 0, 0, 1 ]

FINAL OUTPUT MATRIX:
1  0  0  1
0  0  0  0
0  0  0  0
1  0  0  1

*/

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

/*
====================================================================
                     COMPLEXITY ANALYSIS
====================================================================

1. TIME COMPLEXITY (TC):
   - Phase 1 (Traverse to mark): O(rows * columns)
   - Phase 2 (Traverse to update): O(rows * columns)
   - Total Time Complexity: O(2 * (rows * columns)) = O(N * M)
   (Pehle wale O(N^3) brute-force se bohot fast hai)

2. SPACE COMPLEXITY (SC):
   - row tracking vector: O(N) space
   - col tracking vector: O(M) space
   - Total Auxiliary Space: O(N + M)
====================================================================
*/