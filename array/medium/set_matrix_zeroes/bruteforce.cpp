#include<bits/stdc++.h>
using namespace std;

/*
Suppose ek matrix diya hua hai :-
nums :-
1 1 1 1 
1 0 0 1 
1 1 0 1 
1 1 1 1 

aur mujhe ye karna hai :-
1. jis position pe 0 aa raha hai us position ke corresponding row and column ke saare elemnts ko zero karna hai
2. Lekin suppose upar wale matrix mein (1,1){0-based indexing} mein zero hai to mujhe row-index 1 and column-index 1 ke saare elements ko zero banana padega
lekin uske baad nums kuch aisa dikhega :-
1 0 1 1 
0 0 0 0 
1 0 0 1 
1 0 1 1 
lekin iska matlab ye nahi ki ye jo naye zeroes bane unpe bhi mein rule 1 apply karunga 
RULE 1 SIRF ORIGINAL nums MEIN JITNE TRUE ZEROS HAIN UNPE HI LAGTA HAI

To rule 2 ke controversy kp hatae ke liye pehli baar jab traverse karunga har element se tab mein corresponding row and columns ke elements ko -1 se replace karunga
uske baad jab traversal khatam ho jayegi to ek baar aur traverse karunga full nums aur saare -1 wale elements ko zero bana dunga

*/

/*
DRY RUN :-

====================================================================
               DETAILED DRY RUN (AAPKE BHEJE HUE CODE KE LIYE)
====================================================================

INITIAL MATRIX:
Index:     j=0  j=1  j=2  j=3
i = 0  -> [ 1,   1,   1,   1 ]
i = 1  -> [ 1,   0,   0,   1 ]
i = 2  -> [ 1,   1,   0,   1 ]
i = 3  -> [ 1,   1,   1,   1 ]

Dimensions: rows = 4, cols = 4
--------------------------------------------------------------------

PHASE 1: MATRIX TRAVERSAL (i: 0 -> 3, j: 0 -> 3)
Dhundo kahan kahan nums[i][j] == 0 hai:

--------------------------------------------------------------------
[1] i = 0 (Row 0):
    - j = 0: nums[0][0] = 1 (kuch nahi hoga)
    - j = 1: nums[0][1] = 1 (kuch nahi hoga)
    - j = 2: nums[0][2] = 1 (kuch nahi hoga)
    - j = 3: nums[0][3] = 1 (kuch nahi hoga)
    Matrix state: Unchanged

--------------------------------------------------------------------
[2] i = 1 (Row 1):
    - j = 0: nums[1][0] = 1 (kuch nahi hoga)

    - j = 1: nums[1][1] == 0  --> ZERO MIL GAYA!
      Call -> mark_row(1, nums):
        * Row 1 ke non-zero elements ko -1 banayega:
        * nums[1][0] ban gaya -1
        * nums[1][1] pehle se 0 hai, touch nahi karega (if != 0 check)
        * nums[1][2] pehle se 0 hai, touch nahi karega
        * nums[1][3] ban gaya -1
      Call -> mark_col(1, nums):
        * Col 1 ke non-zero elements ko -1 banayega:
        * nums[0][1] ban gaya -1
        * nums[1][1] is 0, skip
        * nums[2][1] ban gaya -1
        * nums[3][1] ban gaya -1

      Abhi tak ka Matrix:
      [  1,  -1,   1,   1 ]
      [ -1,   0,   0,  -1 ]
      [  1,  -1,   0,   1 ]
      [  1,  -1,   1,   1 ]

    - j = 2: nums[1][2] == 0  --> PHIR SE ZERO MIL GAYA!
      Call -> mark_row(1, nums):
        * Row 1 mein ghumega:
        * nums[1][0] already -1 hai (condition nums != 0 true hai, rewrite -1)
        * nums[1][1] is 0, skip
        * nums[1][2] is 0, skip
        * nums[1][3] already -1 hai
      Call -> mark_col(2, nums):
        * Col 2 ke non-zero elements ko -1 banayega:
        * nums[0][2] ban gaya -1
        * nums[1][2] is 0, skip
        * nums[2][2] is 0, skip
        * nums[3][2] ban gaya -1

      Abhi tak ka Matrix:
      [  1,  -1,  -1,   1 ]
      [ -1,   0,   0,  -1 ]
      [  1,  -1,   0,   1 ]
      [  1,  -1,  -1,   1 ]

    - j = 3: nums[1][3] = -1 (!= 0, kuch nahi hoga)

--------------------------------------------------------------------
[3] i = 2 (Row 2):
    - j = 0: nums[2][0] = 1 (kuch nahi hoga)
    - j = 1: nums[2][1] = -1 (kuch nahi hoga)

    - j = 2: nums[2][2] == 0  --> PHIR SE ZERO MIL GAYA!
      Call -> mark_row(2, nums):
        * Row 2 ke non-zero elements ko -1 banayega:
        * nums[2][0] ban gaya -1
        * nums[2][1] already -1 hai
        * nums[2][2] is 0, skip
        * nums[2][3] ban gaya -1
      Call -> mark_col(2, nums):
        * Col 2 ke non-zero elements ko -1 banayega:
        * nums[0][2] already -1 hai
        * nums[1][2] is 0, skip
        * nums[2][2] is 0, skip
        * nums[3][2] already -1 hai

      Abhi tak ka Matrix:
      [  1,  -1,  -1,   1 ]
      [ -1,   0,   0,  -1 ]
      [ -1,  -1,   0,  -1 ]
      [  1,  -1,  -1,   1 ]

    - j = 3: nums[2][3] = -1 (!= 0, kuch nahi hoga)

--------------------------------------------------------------------
[4] i = 3 (Row 3):
    - j = 0: nums[3][0] = 1 (kuch nahi hoga)
    - j = 1: nums[3][1] = -1 (kuch nahi hoga)
    - j = 2: nums[3][2] = -1 (kuch nahi hoga)
    - j = 3: nums[3][3] = 1 (kuch nahi hoga)

====================================================================
PHASE 1 KHATAM HONE KE BAAD MATRIX KI HALAT:
[  1,  -1,  -1,   1 ]
[ -1,   0,   0,  -1 ]
[ -1,  -1,   0,  -1 ]
[  1,  -1,  -1,   1 ]
====================================================================

PHASE 2: CONVERTING -1 TO 0 (Final cleanup loop)

Loop poore matrix pe iterate karega:
if (nums[i][j] == -1) -> nums[i][j] = 0;

Step-by-step transformation:
- Row 0:
  nums[0][0] = 1
  nums[0][1] = -1  -> ban gaya 0
  nums[0][2] = -1  -> ban gaya 0
  nums[0][3] = 1

- Row 1:
  nums[1][0] = -1  -> ban gaya 0
  nums[1][1] = 0   -> unchanged
  nums[1][2] = 0   -> unchanged
  nums[1][3] = -1  -> ban gaya 0

- Row 2:
  nums[2][0] = -1  -> ban gaya 0
  nums[2][1] = -1  -> ban gaya 0
  nums[2][2] = 0   -> unchanged
  nums[2][3] = -1  -> ban gaya 0

- Row 3:
  nums[3][0] = 1
  nums[3][1] = -1  -> ban gaya 0
  nums[3][2] = -1  -> ban gaya 0
  nums[3][3] = 1

====================================================================
FINAL OUTPUT MATRIX:
1  0  0  1
0  0  0  0
0  0  0  0
1  0  0  1
====================================================================
*/

/*
How to define a matrix in c++ :- {fixed size}
SYNTAX :-
vector<Type> name(count, fill_value);

For a 1D vector where Type is int:
vector<int> nums(cols, 0);
// Type = int
// count = cols
// fill_value = 0

For a 2D matrix where Type is vector<int>:
vector<vector<int>> matrix(rows, vector<int>(cols, 0));
// Type = vector<int>
// count = rows
// fill_value = vector<int>(cols, 0)
iska matlab count = rows baar vector <int>(cols, 0) banega jaha couls baar 0 aa jyega har row pe

*/

void mark_row(int row, vector <vector<int>> &nums){
    int total_cols = nums[0].size();
    for(int i = 0;i < total_cols;i++){
        if(nums[row][i] != 0){
            nums[row][i] = -1;
        }
    }
}

void mark_col(int col, vector <vector<int>> &nums){
    int total_rows = nums.size();
    for(int i = 0;i < total_rows;i++){
        if(nums[i][col] != 0){
            nums[i][col] = -1;
        }
    }
}

void set_matrix_zeroes(vector <vector<int>> &nums){
    int rows = nums.size();
    int cols = nums[0].size();
    // traversing matrix element by element
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){

            // check if element is 0 then replace by -1
            if(nums[i][j] == 0){
                mark_row(i, nums);
                mark_col(j, nums);
            }
        }
    }

    // Traversing over the matrix to make the -1s as 0s
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){
            if(nums[i][j] == -1){
                nums[i][j] = 0;
            }
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

/*
====================================================================
               COMPLEXITY ANALYSIS (TC & SC)
====================================================================

Matrix Size: N x M (jahan N = rows aur M = cols)

1. TIME COMPLEXITY (TC):
   - Overall TC: O((N * M) * (N + M)) + O(N * M)
   - Worst-case TC: O((N * M) * (N + M))
     (Agar square matrix N x N ho, toh yeh lagbhag O(N^3) hoti hai)

   Breakdown:
   a) Traversal aur Marking Phase:
      - Bahar do nested loops poore matrix ko traverse karte hain: O(N * M)
      - Jab bhi koi element 0 milta hai, do functions call hote hain:
        * mark_row(): Poori row traverse karta hai -> O(M)
        * mark_col(): Poora column traverse karta hai -> O(N)
      - Dono milkar har 0 par O(N + M) ka kaam karte hain.
      - Worst-case scenario (agar matrix mein bohot saare zeroes hon):
        O((N * M) * (N + M))

   b) Replacement Phase (-1 se 0):
      - Ek aur nested loop pure matrix par ghumta hai: O(N * M)

--------------------------------------------------------------------

2. SPACE COMPLEXITY (SC):
   - Auxiliary Space: O(1)
   
   Breakdown:
   - Aapne koi extra data structure (jaise alag vector ya array) use nahi kiya hai.
   - Aap direct input matrix ke andar hi modify kar rahe hain.
   - Loop variables (i, j, rows, cols) constant space O(1) lete hain.
====================================================================
*/