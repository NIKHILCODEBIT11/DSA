#include <iostream>
using namespace std;

void pascals_triangle_row(int row) {
    int n = row - 1;
    long long ans = 1; // Use long long to avoid intermediate integer overflow
    cout << ans << " ";
    for (int i = 0; i < n; i++) {
        ans = ans * (n - i);
        ans = ans / (i + 1);
        cout << ans << " ";
    }
    cout << "\n";
}

void pascals_triangle(int total_rows) {
    for (int i = 1; i <= total_rows; i++) {
        pascals_triangle_row(i); // Pass current row index `i`
    }
}

int main() {
    cout << "The pascal's triangle of 4 rows is:\n";
    pascals_triangle(4);
    return 0;
}

/*
====================================================================
                        THOUGHT PROCESS
====================================================================

1. CORE MATHEMATICAL OBSERVATION:
   - Pascal's Triangle ka har row combinations ko represent karta hai:
     Row n (0-indexed): nC0, nC1, nC2, ..., nCn
   - Har element ko independently nCr formula se nikalne par extra loops
     aur factorial calculation lagti hai (jo overflow aur slow execution degi).

2. RATIO / FORMULA DERIVATION (Next element previous element se kaise banega?):
   - Agla term:
     Term(i) = nCi
     Term(i-1) = nC(i-1)
   - Ratio:
     nCi / nC(i-1) = (n - i + 1) / i
   - Matlab:
     Current Term = Previous Term * (n - i + 1) / i
   - Code mein loop 0-indexed hai (i = 0 se n-1 tak):
     Isliye formula adapt hoke banta hai:
     ans = ans * (n - i) / (i + 1)

3. STEP-BY-STEP FLOW:
   - pascals_triangle(total_rows):
     Ek outer loop chalata hai 1 se lekar total_rows tak taaki har row
     ko sequentially print kar sakein.
   - pascals_triangle_row(row):
     - Pehla element hamesha 1 hota hai (nC0 = 1), isliye ans = 1 initialize
       karte hain aur seedhe print kar dete hain.
     - Fir loop chala kar previous value (ans) ko use karke next value
       calculate karte hain.
     - Pehle multiply karte hain, fir divide karte hain integer truncation
       se bachne ke liye.
     - 'long long' isliye use kiya taaki multiplication ke time number
       temporary overflow na ho.
     - Row khatam hone par newline print kar dete hain.

====================================================================
                TIME & SPACE COMPLEXITY ANALYSIS
====================================================================

TIME COMPLEXITY (TC):
- Row 1 print karne ke liye: 1 operation
- Row 2 print karne ke liye: 2 operations
- Row 3 print karne ke liye: 3 operations
- ...
- Row N print karne ke liye: N operations
- Total Operations = 1 + 2 + 3 + ... + N = N * (N + 1) / 2
- Overall Time Complexity: O(N^2), jahan N = total_rows.

SPACE COMPLEXITY (SC):
- Auxiliary Space: O(1) [Constant Space]
  Kyunki hum koi bhi array, vector ya matrix store nahi kar rahe hain.
  Values calculate hote hi on-the-fly print ho rahi hain.
- Call Stack Space: O(1)
  Kyunki recursive calls nahi hain, sirf iterative loops hain.
- Overall Space Complexity: O(1).
====================================================================
*/