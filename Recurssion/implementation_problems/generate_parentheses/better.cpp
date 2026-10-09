#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (GENERATE PARENTHESES - BACKTRACKING):
   - Problem:
     Hume ek integer 'n' diya hai. Hume 'n' pairs of valid parentheses
     ke saare possible combinations generate karke return karne hain.
     Valid parentheses ka matlab:
     1. Total length hamesha 2 * n hogi (n opening '(' aur n closing ')').
     2. Kisi bhi prefix me closing bracket ')' ka count opening bracket '('
        ke count se zyada nahi hona chahiye.

   - Brute Force vs Backtracking Intuition:
     Brute force me hum har position par '(' ya ')' laga kar 2^(2*n) combinations
     banate aur fir har ek ko validate karte (bohot slow aur TLE deta).

     Backtracking Intuition (Build Only Valid Prefixes):
     Hum string ko shuru se hi aise construct karenge ki koi invalid combination
     bane hi na! Do golden rules:
     
     Rule 1: Opening Bracket '(' kab add kar sakte hain?
     - Hum total 'n' opening brackets hi use kar sakte hain.
     - Toh condition: if(open < n) -> '(' add karo aur open+1 karo.

     Rule 2: Closing Bracket ')' kab add kar sakte hain?
     - Hum closing bracket tabhi laga sakte hain jab usko match karne ke liye
       already koi unclosed opening bracket maujood ho!
       Agar close == open hai, aur humne ')' laga diya, toh wo string invalid ho jayegi (e.g. ")(").
     - Toh condition: if(close < open) -> ')' add karo aur close+1 karo.

   - Base Case:
     Jab current string ki length 2 * n ho jaye (yani saare n pairs lag chuke hain),
     toh wo string 100% valid guarantee hoti hai. Use 'result' me push karo aur return karo.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `generate(result, open, close, n, current)` ---
   - `if(current.length() == 2*n)`:
     Base condition: Ek valid combination complete ho gaya. `result.push_back(current)` karke backtrack karo.
   - `if(open < n)`:
     Opening bracket quota check: Abhi aur '(' lagaye ja sakte hain.
     Recursive call: `generate(result, open + 1, close, n, current + '(')`.
   - `if(close < open)`:
     Validity invariant check: Closing brackets ka count opening se kam hona chahiye
     taaki har ')' ke liye ek corresponding '(' pehle se khada ho.
     Recursive call: `generate(result, open, close + 1, n, current + ')')`.

   --- `generateParenthesis(n)` ---
   - `vector<string> result;`:
     Saare valid combinations store karne ke liye container.
   - `generate(result, 0, 0, n, "");`:
     Recursion ko 0 open brackets, 0 close brackets, aur empty string ke saath trigger kiya.
   - `return result;`:
     Final saare generated valid combinations return kar diye.

======================================================================
3. DETAILED DRY RUN (for n = 2):

   n = 2 (Total length = 4, open limit = 2, close limit = 2)

   Call Tree:
   generate(open=0, close=0, current="")
     |
     |-- open < 2 -> add '(' -> generate(open=1, close=0, current="(")
           |
           |-- open < 2 -> add '(' -> generate(open=2, close=0, current="((")
           |     |
           |     |-- (open < 2 is False)
           |     |-- close < open (0 < 2) -> add ')' -> generate(open=2, close=1, current="(()")
           |           |
           |           |-- (open < 2 is False)
           |           |-- close < open (1 < 2) -> add ')' -> generate(open=2, close=2, current="(())")
           |                 |
           |                 |-- length == 4 -> RESULT ADDED: "(())" -> return
           |
           |-- close < open (0 < 1) -> add ')' -> generate(open=1, close=1, current="()")
                 |
                 |-- open < 2 (1 < 2) -> add '(' -> generate(open=2, close=1, current="()(")
                 |     |
                 |     |-- (open < 2 is False)
                 |     |-- close < open (1 < 2) -> add ')' -> generate(open=2, close=2, current="()()")
                 |           |
                 |           |-- length == 4 -> RESULT ADDED: "()()" -> return
                 |
                 |-- (close < open is False, 1 < 1 fails)

   Final Results for n = 2:
   ["(())", "()()"]

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Number of valid combinations for n pairs = nth Catalan Number:
       C(n) = (1 / (n + 1)) * (2n choose n)
     * For n = 4, C(4) = 14 valid strings.
     * Har valid string ko build aur copy karne me O(2 * n) time lagta hai.
     * Total Time Complexity: O( (4^n / sqrt(n)) * n ), mathematically bounded by O(4^n / sqrt(n)).
     * Yeh brute force 2^(2n) = 4^n ke blind validation se kaafi fast hai kyunki invalid branches
       shuru me hi prune ho jati hain.

   - Space Complexity (SC):
     * Auxiliary Space (Recursion Call Stack): O(2 * n) = O(n).
       Call stack maximum 2*n frames gehri jati hai.
     * Output Space: O(C(n) * 2n) saare valid combinations store karne ke liye.
======================================================================
*/

void generate(vector <string> &result, int open, int close, int n, string current){
    if(current.length() == 2*n){
        result.push_back(current);
        return;
    }

    if(open < n){
        generate(result, open+1, close, n, current+'(');
    }

    if(close < open){
        generate(result, open, close+1, n, current+')');
    }
}

vector<string> generateParenthesis(int n) {
    vector <string> result;
    generate(result, 0, 0, n, "");
    return result;
        
}

int main(){
    int n = 4;
    cout<<"All parentheses for n = "<<n<<" are :-"<<endl;
    vector <string> ans = generateParenthesis(n);
    for(string c : ans){
        cout<<"' "<<c<<" '"<<'\t';
    }
    return 0;
}

/*
================================================================================
          COMPLETE STEP-BY-STEP EXECUTION TRACE (PASS-BY-VALUE, n = 3)
================================================================================

Code ki 2 lines:
- Line A: generate(result, open + 1, close, n, current + '(');  (Condition: open < 3)
- Line B: generate(result, open, close + 1, n, current + ')');  (Condition: close < open)

--------------------------------------------------------------------------------
Step 1
- Active Call: Call 1
- Values: open = 0, close = 0, current = ""
- Line A check: open < 3 (0 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "("
- Trigger: Call 2 chalu hui. (Call 1 yahin pause ho gaya Line A par).

--------------------------------------------------------------------------------
Step 2
- Active Call: Call 2
- Values: open = 1, close = 0, current = "("
- Line A check: open < 3 (1 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "(("
- Trigger: Call 3 chalu hui. (Call 2 pause hua Line A par).

--------------------------------------------------------------------------------
Step 3
- Active Call: Call 3
- Values: open = 2, close = 0, current = "(("
- Line A check: open < 3 (2 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "((("
- Trigger: Call 4 chalu hui. (Call 3 pause hua Line A par).

--------------------------------------------------------------------------------
Step 4
- Active Call: Call 4
- Values: open = 3, close = 0, current = "((("
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (0 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "((()"
- Trigger: Call 5 chalu hui. (Call 4 pause hua Line B par).

--------------------------------------------------------------------------------
Step 5
- Active Call: Call 5
- Values: open = 3, close = 1, current = "((()"
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (1 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "((())"
- Trigger: Call 6 chalu hui. (Call 5 pause hua Line B par).

--------------------------------------------------------------------------------
Step 6
- Active Call: Call 6
- Values: open = 3, close = 2, current = "((())"
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (2 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "((()))"
- Trigger: Call 7 chalu hui. (Call 6 pause hua Line B par).

--------------------------------------------------------------------------------
Step 7
- Active Call: Call 7
- Values: open = 3, close = 3, current = "((()))"
- Base check: current.length() == 6 -> True!
- Action: result.push_back("((()))") -> Answer #1 Saved!
- Action: return; chala.
- Result: Call 7 khatam ho gaya aur memory se delete!

--------------------------------------------------------------------------------
Step 8 (Wapsi shuru)
- Active Call: Call 6
- Values: open = 3, close = 2, current = "((())"
- Status: Call 6 ki Line B poori ho gayi. Aage koi code nahi hai.
- Action: Call 6 khatam, return to Call 5.

--------------------------------------------------------------------------------
Step 9
- Active Call: Call 5
- Values: open = 3, close = 1, current = "((()"
- Status: Line B poori ho gayi. Aage koi code nahi hai.
- Action: Call 5 khatam, return to Call 4.

--------------------------------------------------------------------------------
Step 10
- Active Call: Call 4
- Values: open = 3, close = 0, current = "((("
- Status: Line B poori ho gayi. Aage koi code nahi hai.
- Action: Call 4 khatam, return to Call 3.

--------------------------------------------------------------------------------
Step 11 (Call 3 par naya branch)
- Active Call: Call 3
- Values: open = 2, close = 0, current = "(("  (Dhyan do: iska apna current bilkul fresh "((" hi hai!)
- Status: Iski Line A (open < 3) complete ho chuki hai.
- Line B check: close < open (0 < 2) -> True
- Action: current + ')' kiya -> nayi string bani "(()"
- Trigger: Call 8 chalu hui. (Call 3 pause hua Line B par).

--------------------------------------------------------------------------------
Step 12
- Active Call: Call 8
- Values: open = 2, close = 1, current = "(()"
- Line A check: open < 3 (2 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "(()("
- Trigger: Call 9 chalu hui. (Call 8 pause hua Line A par).

--------------------------------------------------------------------------------
Step 13
- Active Call: Call 9
- Values: open = 3, close = 1, current = "(()("
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (1 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "(()()"
- Trigger: Call 10 chalu hui. (Call 9 pause hua Line B par).

--------------------------------------------------------------------------------
Step 14
- Active Call: Call 10
- Values: open = 3, close = 2, current = "(()()"
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (2 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "(()())"
- Trigger: Call 11 chalu hui. (Call 10 pause hua Line B par).

--------------------------------------------------------------------------------
Step 15
- Active Call: Call 11
- Values: open = 3, close = 3, current = "(()())"
- Base check: current.length() == 6 -> True!
- Action: result.push_back("(()())") -> Answer #2 Saved!
- Action: return; chala.
- Result: Call 11 destroy!

--------------------------------------------------------------------------------
Step 16
- Active Call: Call 10 -> Line B khatam -> Destroy.
- Active Call: Call 9 -> Line B khatam -> Destroy.
- Control wapas: Call 8 par pahuncha.

--------------------------------------------------------------------------------
Step 17 (Call 8 ka doosra branch)
- Active Call: Call 8
- Values: open = 2, close = 1, current = "(()"
- Status: Line A complete ho chuki thi.
- Line B check: close < open (1 < 2) -> True
- Action: current + ')' kiya -> nayi string bani "(())"
- Trigger: Call 12 chalu hui. (Call 8 pause hua Line B par).

--------------------------------------------------------------------------------
Step 18
- Active Call: Call 12
- Values: open = 2, close = 2, current = "(())"
- Line A check: open < 3 (2 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "(())("
- Trigger: Call 13 chalu hui. (Call 12 pause hua Line A par).

--------------------------------------------------------------------------------
Step 19
- Active Call: Call 13
- Values: open = 3, close = 2, current = "(())("
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (2 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "(())()"
- Trigger: Call 14 chalu hui. (Call 13 pause hua Line B par).

--------------------------------------------------------------------------------
Step 20
- Active Call: Call 14
- Values: open = 3, close = 3, current = "(())()"
- Base check: current.length() == 6 -> True!
- Action: result.push_back("(())()") -> Answer #3 Saved!
- Action: return; chala.
- Result: Call 14 destroy!

--------------------------------------------------------------------------------
Step 21
- Active Call: Call 13 -> Khatam.
- Active Call: Call 12 -> Line B check: close < open (2 < 2) -> False -> Khatam.
- Active Call: Call 8 -> Khatam.
- Active Call: Call 3 -> Khatam.
- Control wapas seedha kahan gira? Call 2 par!

--------------------------------------------------------------------------------
Step 22 (Call 2 par Main Turning Point)
- Active Call: Call 2
- Values: open = 1, close = 0, current = "(" (Iska apna current abhi bhi wahi purana "(" hai!)
- Status: Iski Line A se Call 3 gayi thi, jo poori khatam ho chuki hai.
- Line B check: close < open (0 < 1) -> True
- Action: current + ')' kiya -> nayi string bani "()"
- Trigger: Call 15 chalu hui. (Call 2 pause hua Line B par).

--------------------------------------------------------------------------------
Step 23
- Active Call: Call 15
- Values: open = 1, close = 1, current = "()"
- Line A check: open < 3 (1 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "()("
- Trigger: Call 16 chalu hui. (Call 15 pause hua Line A par).

--------------------------------------------------------------------------------
Step 24
- Active Call: Call 16
- Values: open = 2, close = 1, current = "()("
- Line A check: open < 3 (2 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "()(("
- Trigger: Call 17 chalu hui. (Call 16 pause hua Line A par).

--------------------------------------------------------------------------------
Step 25
- Active Call: Call 17
- Values: open = 3, close = 1, current = "()(("
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (1 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "()(()"
- Trigger: Call 18 chalu hui.

--------------------------------------------------------------------------------
Step 26
- Active Call: Call 18
- Values: open = 3, close = 2, current = "()(()"
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (2 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "()(())"
- Trigger: Call 19 chalu hui.

--------------------------------------------------------------------------------
Step 27
- Active Call: Call 19
- Values: open = 3, close = 3, current = "()(())"
- Base check: current.length() == 6 -> True!
- Action: result.push_back("()(())") -> Answer #4 Saved!
- Action: return; chala -> Call 19 destroy!

--------------------------------------------------------------------------------
Step 28
- Active Call: Call 18 -> Khatam.
- Active Call: Call 17 -> Khatam.
- Control wapas gira: Call 16 par!

--------------------------------------------------------------------------------
Step 29 (Call 16 ka aakhri rasta)
- Active Call: Call 16
- Values: open = 2, close = 1, current = "()("
- Status: Line A complete ho chuki thi.
- Line B check: close < open (1 < 2) -> True
- Action: current + ')' kiya -> nayi string bani "()()"
- Trigger: Call 20 chalu hui. (Call 16 pause hua Line B par).

--------------------------------------------------------------------------------
Step 30
- Active Call: Call 20
- Values: open = 2, close = 2, current = "()()"
- Line A check: open < 3 (2 < 3) -> True
- Action: current + '(' kiya -> nayi string bani "()()("
- Trigger: Call 21 chalu hui.

--------------------------------------------------------------------------------
Step 31
- Active Call: Call 21
- Values: open = 3, close = 2, current = "()()("
- Line A check: open < 3 (3 < 3) -> False
- Line B check: close < open (2 < 3) -> True
- Action: current + ')' kiya -> nayi string bani "()()()"
- Trigger: Call 22 chalu hui.

--------------------------------------------------------------------------------
Step 32
- Active Call: Call 22
- Values: open = 3, close = 3, current = "()()()"
- Base check: current.length() == 6 -> True!
- Action: result.push_back("()()()") -> Answer #5 Saved!
- Action: return; chala -> Call 22 destroy!

--------------------------------------------------------------------------------
Step 33 (Sab khatam)
- Call 21 -> return.
- Call 20 -> Line B check: close < open (2 < 2) -> False -> return.
- Call 16 -> return.
- Call 15 -> Line B check: close < open (1 < 1) -> False -> return.
- Call 2 -> return.
- Call 1 -> Line B check: close < open (0 < 0) -> False -> return.

Poora program complete! Saari 22 calls execute hone ke baad result vector mein yeh 5 answers bache:
1. "((()))"
2. "(()())"
3. "(())()"
4. "()(())"
5. "()()()"
================================================================================
*/

/*
for n = 2 :-
                  generate(open=0, close=0, "")
                                   |
                         (open < 2 -> add '(')
                                   |
                      generate(open=1, close=0, "(")
                        /                       \
        (open < 2 -> add '(')             (close < open -> add ')')
                      /                           \
     generate(open=2, close=0, "((")      generate(open=1, close=1, "()")
                 |                                      |
         (close < open -> ')')                  (open < 2 -> '(')
                 |                                      |
     generate(open=2, close=1, "(()")     generate(open=2, close=1, "()(")
                 |                                      |
         (close < open -> ')')                  (close < open -> ')')
                 |                                      |
     generate(open=2, close=2, "(())")    generate(open=2, close=2, "()()")
            [Length = 4 -> SAVE]                 [Length = 4 -> SAVE]
*/