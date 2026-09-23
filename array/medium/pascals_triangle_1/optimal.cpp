/*

 * Pascal's Triangle (Row vs Column):
 *
 *               col 1  col 2  col 3  col 4  col 5  col 6
 *                 \      \      \      \      \      \
 * Row 1:           1
 *                 / \
 * Row 2:         1   1
 *               / \ / \
 * Row 3:       1   2   1
 *             / \ / \ / \
 * Row 4:     1   3   3   1
 *           / \ / \ / \ / \
 * Row 5:   1   4   6   4   1
 *         / \ / \ / \ / \ / \
 * Row 6: 1   5  10  10   5   1
 *
 * Cell: (row, col) => e.g., (5, 3) = 6

 * Formula: C(n, r) = n! / (r! * (n - r)!)
 * Relation: val[r][c] = val[r-1][c-1] + val[r-1][c]

Yaha pe bruteforce hai ki mein pehle pascal's traingle banau phir row and column traverse karte hue
element ko return karu
Lekin isse bhi acha tarika hai :-
BY OBSERVATION :-

Kisi bi row(n) column(r) ka element nikalna hai to mujhe bas p and c ka c use karna hai
For r and c as 1-based indexing :-

(n-1)c(r-1)

for example :- agar mujhe row 3rd aur column 2nd ka element nikalna hai to :-

(3-1)c(2-1) = 2c1 = 2

*/

#include<bits/stdc++.h>
using namespace std;

int pascals_traingle_element_search(int row, int column){
  int n = row-1;
  int c = column - 1;
  int ans = 1;
  int count = min(c, n-c);
  for(int i = 0;i < count;i++){
    ans = (ans * (n - i))/(i+1);
  }
  return ans;
}

int main(){
  cout<<"The value at row 4 and column 3 is "<<pascals_traingle_element_search(4,3);
  return 0;
}

/*
 * ============================================================================
 *                    THOUGHT PROCESS & INTUITION BREAKDOWN
 * ============================================================================
 *
 * 1. PROBLEM STATEMENT & MOTIVATION:
 *    - Pascal's Triangle ke kisi specific (row, col) coordinate ka element nikalna.
 *    - Bruteforce:
 *      Pura triangle generate karo O(N^2) time & space mein, fir cell access karo.
 *    - Optimized Approach (Combinatorics):
 *      Pascal triangle generate kiye bina directly mathematical formula se O(R) time
 *      aur O(1) extra space mein single element find out karna.
 *
 * ----------------------------------------------------------------------------
 * 2. WHY `n = row - 1` AND `c = column - 1`?
 *    - Mathematical Foundation:
 *      Standard binomial theorem aur Pascal's identity naturally 0-indexed hoti hai:
 *        Row 0: 0C0
 *        Row 1: 1C0, 1C1
 *        Row 2: 2C0, 2C1, 2C2
 *        ...
 *        Row N: NC0, NC1, ..., NCR
 *
 *    - Mapping 1-based indexing to 0-based Combinations:
 *      Jab input 1-based indexing mein diya jata hai:
 *        Given Row 1 => Represents n = 0
 *        Given Row 2 => Represents n = 1
 *        Given Row 4 => Represents n = 3  (i.e., row - 1)
 *
 *        Given Col 1 => Represents r = 0
 *        Given Col 3 => Represents r = 2  (i.e., col - 1)
 *
 *      Isliye (row, col) ka element nikalne ke liye hum calculate karte hain:
 *        Formula: (row - 1) C (col - 1)
 *
 * ----------------------------------------------------------------------------
 * 3. WHY USE `count = min(c, n - c)`?
 *    - Combinatorial Symmetry Property:
 *        nCr = nC(n - r)
 *      Pascal's triangle symmetrical hota hai (left half = right half).
 *
 *    - Optimization Advantage:
 *      Agar hume 10C8 calculate karna ho:
 *        Without symmetry: Loop 8 baar chalega (r = 8).
 *        With symmetry   : 10C8 = 10C(10 - 8) = 10C2.
 *                          Loop sirf 2 baar chalega (min(8, 2) = 2).
 *      Isse operations drastically kam ho jate hain aur time complexity O(min(r, n-r))
 *      par drop ho jati hai.
 *
 * ----------------------------------------------------------------------------
 * 4. WHY CALCULATE nCr ITERATIVELY INSTEAD OF FACTORIALS?
 *    - Factorial Problem:
 *      nCr = n! / (r! * (n - r)!)
 *      13! hi standard 32-bit integer ki limit cross kar deta hai. Factorial direct
 *      compute karne par turant integer overflow ho jayega, chahe final answer chhota ho.
 *
 *    - Cancelled Fraction Technique:
 *      nCr = [n * (n-1) * ... * (n - r + 1)] / [1 * 2 * ... * r]
 *      Example: 10C3 = (10 * 9 * 8) / (1 * 2 * 3)
 *
 *      Iteration 0: ans = 1 * 10 / 1 = 10
 *      Iteration 1: ans = 10 * 9 / 2 = 45
 *      Iteration 2: ans = 45 * 8 / 3 = 120
 *
 *    - Multiplication Before Division:
 *      Har step par pehle multiply `(ans * (n - i))` aur fir divide `/(i + 1)` karne se:
 *      1. Consecutive numbers ka product hamesha divisibility property satisfy karta hai,
 *         isliye kabhi precision loss (decimal cutoff) nahi hota.
 *      2. Division by zero prevent ho jata hai kyunki denominator `(i + 1)` hamesha >= 1 rehta hai.
 *
 * ----------------------------------------------------------------------------
 * 5. COMPLEXITY SUMMARY:
 *    - Time Complexity : O(min(column, row - column)) -> Extremely fast, linear in terms of column.
 *    - Space Complexity: O(1) -> Sirf constant variables use ho rahe hain.
 * ============================================================================
 */