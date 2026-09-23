#include<bits/stdc++.h>
using namespace std;

void pascals_triangle_row_print(int row){
    int n = row - 1;

    int ans = 1;
    cout<<ans<<" ";
    for(int i = 0;i < n;i++){
        ans = (ans * (n - i));
        ans = ans/(i+1);
        cout<<ans<<" ";
    }
}

int main(){
  cout<<"The 4th row in pascal's triangle looks like :-"<<endl;
  pascals_triangle_row_print(4);
  return 0;
}

/*
 * ============================================================================
 *               PASCAL'S TRIANGLE: PRINTING AN ENTIRE ROW
 *                     THOUGHT PROCESS & MATHEMATICAL INTUITION
 * ============================================================================
 *
 * 1. PROBLEM OBJECTIVE:
 *    - Given a 1-based row number 'row', print all elements of that row.
 *    - Example: row = 4  --> Output: 1 3 3 1
 *
 * ----------------------------------------------------------------------------
 * 2. BRUTE FORCE VS OPTIMAL THINKING:
 *    - Brute Force:
 *        Pura Pascal's Triangle generate karo (2D matrix) aur di gayi row print karo.
 *        Time: O(N^2), Space: O(N^2).
 *
 *    - Naive Combinatorics:
 *        Hume pata hai row 'n' ke elements hote hain:
 *        nC0, nC1, nC2, ..., nCn
 *        Agar har ek element ke liye independent nCr function chalayein:
 *        Time: O(N * r) ~ O(N^2).
 *
 *    - Optimal Approach (Current Solution):
 *        Observe karo ki consecutive elements ke beech ek direct mathematical ratio hai.
 *        Pichle element ko use karke agla element O(1) time mein derive karo.
 *        Time: O(N), Space: O(1).
 *
 * ----------------------------------------------------------------------------
 * 3. WHY `int n = row - 1`?
 *    - Pascal's identity naturally 0-indexed hoti hai:
 *        Row 1 (1-based) => n = 0 (Elements: 0C0)
 *        Row 2 (1-based) => n = 1 (Elements: 1C0, 1C1)
 *        Row 4 (1-based) => n = 3 (Elements: 3C0, 3C1, 3C2, 3C3)
 *    - Isliye row number ko seedhe binomial power 'n' mein map karne ke liye
 *      n = row - 1 kiya gaya.
 *
 * ----------------------------------------------------------------------------
 * 4. THE MATHEMATICAL RELATION (RECURRENCE):
 *    - Term at index i:
 *        T(i) = nCi
 *    - Next term at index (i + 1):
 *        T(i + 1) = nC(i + 1)
 *
 *    - Ratio nikalte hain:
 *        T(i + 1) / T(i) = [n! / ((i+1)! * (n - i - 1)!)] / [n! / (i! * (n - i)!)]
 *                        = (n - i) / (i + 1)
 *
 *    - Iska matlab:
 *        Next Term = Current Term * (n - i) / (i + 1)
 *
 * ----------------------------------------------------------------------------
 * 5. STEP-BY-STEP DRY RUN (row = 4 => n = 3):
 *    - Start:
 *        ans = 1 (har row ka pehla element hamesha 1 hota hai: nC0 = 1).
 *        Print -> 1
 *
 *    - Loop i = 0 to 2 (i < 3):
 *        Iteration 0 (i = 0):
 *          ans = (1 * (3 - 0)) / (0 + 1) = 3 / 1 = 3
 *          Print -> 3
 *
 *        Iteration 1 (i = 1):
 *          ans = (3 * (3 - 1)) / (1 + 1) = (3 * 2) / 2 = 3
 *          Print -> 3
 *
 *        Iteration 2 (i = 2):
 *          ans = (3 * (3 - 2)) / (2 + 1) = (3 * 1) / 3 = 1
 *          Print -> 1
 *
 *    - Final Output: 1 3 3 1
 *
 * ----------------------------------------------------------------------------
 * 6. COMPLEXITY ANALYSIS:
 *    - Time Complexity : O(N) -> Loop runs exactly (row - 1) times.
 *    - Space Complexity: O(1) -> Sirf do variables ('n' aur 'ans') use ho rahe hain.
 * ============================================================================
 */