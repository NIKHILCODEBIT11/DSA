#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (GENERATE PARENTHESES - CLASSIC BACKTRACKING):
   - Problem:
     Given an integer 'n', generate all combinations of well-formed parentheses.
     For n pairs, the resulting strings will always have length 2 * n, with exactly
     n opening '(' brackets and n closing ')' brackets.

   - Backtracking Philosophy (Choose, Explore, Unchoose):
     Instead of generating all 2^(2n) random strings and validating them afterward,
     we construct ONLY valid prefixes on the fly using a shared string buffer passed
     by reference (string &curr):
     
     1. Choose:
        Append the desired bracket to 'curr' (push_back).
     2. Explore:
        Make the recursive call to explore all paths starting with this prefix.
     3. Unchoose (Backtrack):
        Remove the bracket we just added (pop_back), restoring 'curr' to its 
        exact previous state so subsequent branches operate on clean data.

   - Invariant Rules:
     - Choice 1 (Opening Bracket):
       Can place '(' whenever open < n.
     - Choice 2 (Closing Bracket):
       Can place ')' only when close < open. If close == open, adding ')' would 
       create an unmatched closing bracket (e.g., ")(" or "())"), which is invalid.
     - Base Case:
       When open == n && close == n, all 2n positions are filled validly.
       Push 'curr' into 'result' and return.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- generateparenthesis(n, open, close, curr, result) ---
   - if(open == n && close == n):
     Base case hit: exactly n '(' and n ')' placed. 'curr' is guaranteed balanced.
     Save to 'result' and return.
   - if(open < n):
     Opening bracket quota remains.
     1. curr.push_back('(');                         -> Choose
     2. generateparenthesis(n, open + 1, close, ...); -> Explore
     3. curr.pop_back();                             -> Unchoose (Backtrack)
   - if(close < open):
     Unmatched opening brackets exist to close.
     1. curr.push_back(')');                         -> Choose
     2. generateparenthesis(n, open, close + 1, ...); -> Explore
     3. curr.pop_back();                             -> Unchoose (Backtrack)

   --- main() ---
   - string curr = ""; vector<string> result;:
     Single reusable string buffer and result accumulator.
   - generateparenthesis(4, 0, 0, curr, result);:
     Starts backtracking with 0 open, 0 close brackets placed.

======================================================================
3. DETAILED DRY RUN (for n = 2):

   Target: 2 pairs -> length 4. (open limit = 2, close limit = 2)

   Call 1: gen(open=0, close=0, curr="")
     - open < 2 -> curr.push('(') [curr="("]
     - Call 2: gen(open=1, close=0, curr="(")
         - open < 2 -> curr.push('(') [curr="(("]
         - Call 3: gen(open=2, close=0, curr="((")
             - open < 2 is False (2 < 2)
             - close < open (0 < 2) -> curr.push(')') [curr="(()"]
             - Call 4: gen(open=2, close=1, curr="(()")
                 - open < 2 is False
                 - close < open (1 < 2) -> curr.push(')') [curr="(())"]
                 - Call 5: gen(open=2, close=2, curr="(())")
                     - open==2 && close==2 -> Ans 1: "(())" saved -> return
                 - curr.pop_back() [curr restored to "(()"]
             - curr.pop_back() [curr restored to "(("]
         - curr.pop_back() [curr restored to "("]
         - close < open (0 < 1) -> curr.push(')') [curr="()"]
         - Call 6: gen(open=1, close=1, curr="()")
             - open < 2 (1 < 2) -> curr.push('(') [curr="()("]
             - Call 7: gen(open=2, close=1, curr="()(")
                 - open < 2 is False
                 - close < open (1 < 2) -> curr.push(')') [curr="()()"]
                 - Call 8: gen(open=2, close=2, curr="()()")
                     - open==2 && close==2 -> Ans 2: "()()" saved -> return
                 - curr.pop_back() [curr restored to "()("]
             - curr.pop_back() [curr restored to "()"]
             - close < open (1 < 1) is False -> returns
         - curr.pop_back() [curr restored to "("]
     - curr.pop_back() [curr restored to ""]
     - close < open (0 < 0) is False -> finished.

   Final Results for n = 4 generates exactly 14 valid strings:
   "(((())))", "((()()))", "((())())", "((()))()", "(()(()))",
   "(()()())", "(()())()", "(())(())", "(())()()", "()((()))",
   "()(()())", "()(())()", "()()(())", "()()()()"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * The number of valid parentheses combinations of length 2n is given by the
       nth Catalan Number: C(n) = (1 / (n + 1)) * (2n choose n).
     * Asymptotically, C(n) is bounded by O(4^n / (n^(1.5))).
     * Each valid combination takes O(2n) time to copy into the result vector.
     * Total Time Complexity: O( (4^n / sqrt(n)) ).
     * For n = 4, C(4) = 14 combinations; total operations are negligible (< 1ms).

   - Space Complexity (SC):
     * Auxiliary Stack Space: O(2n) = O(n).
       Maximum depth of recursion tree is 2n (one frame per placed character).
     * Working Buffer Memory: O(2n) = O(n) for the shared 'curr' string.
     * Output Space: O(C(n) * 2n) to store all generated strings in 'result'.
======================================================================
*/

void generateparenthesis(int n, int open, int close, string &curr, vector<string> &result){
    if(open == n && close == n){
        result.push_back(curr);
        return;
    }

    // Choice 1: Opening bracket tabhi lagao jab limit bachi ho
    if(open < n){
        curr.push_back('(');
        generateparenthesis(n, open + 1, close, curr, result);
        curr.pop_back();
    }

    //Choice 2: Closing bracket tabhi lagao jab valid pair bane (close < open)
    if (close < open) {
        curr.push_back(')');                         // Choose
        generateparenthesis(n, open, close + 1, curr, result); // Explore
        curr.pop_back();                             // Unchoose (Backtrack)
    }
}

int main(){
    int n = 4;
    cout<<"All parentheses for n = "<<n<<" are :-"<<endl;
    string curr = "";
    vector <string> result;
    generateparenthesis(n, 0, 0, curr, result);
    for(string c : result){
        cout<<"' "<<c<<" '"<<'\t';
    }
    return 0;
}

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (GENERATE PARENTHESES - n = 2):
   - Problem:
     Hume n = 2 ke liye valid parentheses strings generate karni hain.
     Total length = 2 * n = 4 hogi (2 opening '(' aur 2 closing ')').

   - Rules:
     1. Open check: open < n tabhi '(' push karenge aur open + 1 karenge.
     2. Close check: close < open tabhi ')' push karenge aur close + 1 karenge.
     3. Base case: current.length() == 4 hote hi valid string result me push hogi.
     4. Backtracking: Har recursive call ke theek baad current.pop_back() 
        chalega taaki pichli state restore ho sake.

======================================================================
2. REFERENCE CODE (LINE NUMBERS KE SAATH):

void generate(int open, int close, int n, string &current) {
    // [L1] Base Case
    if(current.length() == 2 * n) {
        result.push_back(current);
        return;
    }

    // [L2] Open Check (Branch A)
    if(open < n) {
        current.push_back('(');
        generate(open + 1, close, n, current); // CALL A
        current.pop_back();                     // POP A
    }

    // [L3] Close Check (Branch B)
    if(close < open) {
        current.push_back(')');
        generate(open, close + 1, n, current); // CALL B
        current.pop_back();                     // POP B
    }

    // [L4] Function End
}

======================================================================
3. CALL-BY-CALL EXECUTION TRACE (n = 2):

Step 1: Initial Call
- State: open = 0, close = 0, current = ""
- [L1] 0 == 4 -> False
- [L2] open < 2 (0 < 2) -> True
  * current.push_back('(') -> current = "("
  * CALL A -> generate(1, 0, "(")
  * (Ye frame (0, 0) CALL A par pause ho gaya)

---
Step 2: Inside (1, 0)
- State: open = 1, close = 0, current = "("
- [L1] 1 == 4 -> False
- [L2] open < 2 (1 < 2) -> True
  * current.push_back('(') -> current = "(("
  * CALL A -> generate(2, 0, "((")
  * (Ye frame (1, 0) CALL A par pause ho gaya)

---
Step 3: Inside (2, 0)
- State: open = 2, close = 0, current = "(("
- [L1] 2 == 4 -> False
- [L2] open < 2 (2 < 2) -> False (Open quota khatam)
- [L3] close < open (0 < 2) -> True
  * current.push_back(')') -> current = "(()"
  * CALL B -> generate(2, 1, "(()")
  * (Ye frame (2, 0) CALL B par pause ho gaya)

---
Step 4: Inside (2, 1)
- State: open = 2, close = 1, current = "(()"
- [L1] 3 == 4 -> False
- [L2] open < 2 (2 < 2) -> False
- [L3] close < open (1 < 2) -> True
  * current.push_back(')') -> current = "(())"
  * CALL B -> generate(2, 2, "(())")
  * (Ye frame (2, 1) CALL B par pause ho gaya)

---
Step 5: Inside (2, 2) [Leaf / Base Case]
- State: open = 2, close = 2, current = "(())"
- [L1] current.length() == 4 (4 == 4) -> True!
  * Ans 1 store hua: "(())"
  * return; (Frame pop)

---
Step 6: Return to (2, 1)
- Control wapas CALL B ke theek baad wali line par aaya:
  * POP B: current.pop_back() -> ')' hata -> current = "(()"
- Niche koi line nahi hai ([L4] End).
- Frame (2, 1) return (pop)!

---
Step 7: Return to (2, 0)
- Control wapas CALL B ke theek baad wali line par aaya:
  * POP B: current.pop_back() -> ')' hata -> current = "(("
- Niche koi line nahi hai ([L4] End).
- Frame (2, 0) return (pop)!

---
Step 8: Return to (1, 0) [Dhyan yahan do]
- (1, 0) kahan pause tha? CALL A par!
- Resume hua theek CALL A ke baad:
  * POP A: current.pop_back() -> '(' hata -> current = "("
- [L2] ka block ab finish hua.
- Program agle statement par badha -> [L3] if(close < open):
  * Yahan close = 0, open = 1
  * Condition: 0 < 1 -> True!
  * current.push_back(')') -> current = "()"
  * CALL B -> generate(1, 1, "()")
  * (Frame (1, 0) CALL B par pause ho gaya)

---
Step 9: Inside (1, 1)
- State: open = 1, close = 1, current = "()"
- [L1] 2 == 4 -> False
- [L2] open < 2 (1 < 2) -> True
  * current.push_back('(') -> current = "()("
  * CALL A -> generate(2, 1, "()(")
  * (Frame (1, 1) CALL A par pause)

---
Step 10: Inside (2, 1)
- State: open = 2, close = 1, current = "()("
- [L1] 3 == 4 -> False
- [L2] open < 2 (2 < 2) -> False
- [L3] close < open (1 < 2) -> True
  * current.push_back(')') -> current = "()()"
  * CALL B -> generate(2, 2, "()()")
  * (Frame (2, 1) CALL B par pause)

---
Step 11: Inside (2, 2) [Leaf / Base Case]
- State: open = 2, close = 2, current = "()()"
- [L1] current.length() == 4 -> True!
  * Ans 2 store hua: "()()"
  * return;

---
Step 12: Final Unwinding (All POPs to the root)
1. At (2, 1):
   * POP B: current.pop_back() -> current = "()("
   * [L4] End -> Return!
2. At (1, 1):
   * POP A: current.pop_back() -> current = "()"
   * [L3] check: close < open (1 < 1) -> False
   * [L4] End -> Return!
3. At (1, 0):
   * POP B: current.pop_back() -> current = "("
   * [L4] End -> Return!
4. At (0, 0):
   * POP A: current.pop_back() -> current = ""
   * [L3] check: close < open (0 < 0) -> False
   * [L4] End -> Return!

Saare frames stack se pop ho chuke hain, aur total do answers generate hue: "(())" aur "()()".

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC): O(4^n / sqrt(n))
   - Space Complexity (SC): O(2 * n) = O(n) recursion call stack depth
======================================================================
*/