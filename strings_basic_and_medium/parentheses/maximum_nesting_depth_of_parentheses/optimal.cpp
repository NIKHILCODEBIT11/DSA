#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (MAXIMUM NESTING DEPTH OF PARENTHESES):
   - Problem:
     Hume ek string di gayi hai jisme parentheses '(' aur ')' ke alawa 
     numbers, operators, ya characters bhi ho sakte hain (Valid Parentheses String - VPS).
     Hume batana hai ki string me kisi bhi point par parentheses ka 
     MAXIMUM NESTING LEVEL (depth) kitna gehra gaya hai.

   - Real-Life Analogy (Lift ya Basement Floor):
     Socho ground floor Level 0 hai:
     - Har baar jab '(' aata hai: Hum lift se 1 floor neeche (gehraai me) 
       ja rahe hain -> Depth 1 badh gayi (`count++`).
     - Har baar jab ')' aata hai: Hum wapas 1 floor upar aa rahe hain -> 
       Depth 1 kam ho gayi (`count--`).
     - Baaki characters (digits, operators '+', '-', etc.): Ye lift ke andar ke log hain, 
       inse floor ki gehraai par koi farak nahi padta (`continue`).
     - Goal: Lift sabse gehre kaunse floor par gayi? 
       Wo hum `max_depth = max(max_depth, count)` se record karte chalenge.

   - '(' par hi `max_depth` kyun update karte hain?
     Kyunki peak hamesha open bracket ke time hi banta hai! 
     Jab naya '(' khulta hai, tab gehraai badhti hai. 
     ')' aane par toh gehraai hamesha kam hi hoti hai, toh tab maximum 
     record tootne ka koi sawal hi nahi banta.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - int count = 0; int max_depth = 0; :
     `count` current live nesting depth track karta hai, aur `max_depth` 
     ab tak ka overall highest record store karta hai.
   - for(char ch : s) :
     Puri string ko left-to-right linearly scan kiya.
   - if (ch == '(') :
     - count++; 
       Naya bracket khula, nesting depth 1 level badh gayi.
     - max_depth = max(max_depth, count);
       Kya abhi tak ki sabse gehri nesting me pahuche hain? Agar haan, toh record update kiya.
   - else if (ch == ')') :
     - count--;
       Bracket close hua, nesting depth 1 level kam ho gayi.
   - else continue; :
     Non-bracket characters ko ignore karke aage badh gaye.
   - return max_depth; :
     String finish hone ke baad overall maximum nesting depth return kar di.

======================================================================
3. DETAILED DRY RUN:

   Input: s = "(()())(())(()(()))"
   Initial: count = 0, max_depth = 0

   Block 1: "(()())"
   - ch = '(': count = 1, max_depth = max(0, 1) = 1
   - ch = '(': count = 2, max_depth = max(1, 2) = 2
   - ch = ')': count = 1
   - ch = '(': count = 2, max_depth = max(2, 2) = 2
   - ch = ')': count = 1
   - ch = ')': count = 0

   Block 2: "(())"
   - ch = '(': count = 1, max_depth = max(2, 1) = 2
   - ch = '(': count = 2, max_depth = max(2, 2) = 2
   - ch = ')': count = 1
   - ch = ')': count = 0

   Block 3: "(()(()))"
   - ch = '(': count = 1, max_depth = max(2, 1) = 2
   - ch = '(': count = 2, max_depth = max(2, 2) = 2
   - ch = ')': count = 1
   - ch = '(': count = 2, max_depth = max(2, 2) = 2
   - ch = '(': count = 3, max_depth = max(2, 3) = 3  <-- NEW PEAK RECORD!
   - ch = ')': count = 2
   - ch = ')': count = 1
   - ch = ')': count = 0

   Loop Ends.
   Returned Value: 3
   Output: "The maximum nesting depth of parentheses is :- 3"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(N) where N is the length of string 's'.
     * Pure string ko ek single pass me visit kiya jata hai.
     * Har character par strictly O(1) operations (comparison, increment/decrement) ho rahe hain.
   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra stack, array ya heap memory allocate nahi hoti.
     * Sirf do standard integer variables (`count`, `max_depth`) use hue hain.
======================================================================
*/

int maximum_nesting_depth_of_parentheses(string s) {
        int count = 0;
        int max_depth = 0;
        for(char ch : s){
            if(ch == '('){
                count++;
                max_depth = max(max_depth, count);    // yaha pe lagane se mujhe "(" open bracket ka count milega YE ISLIYE KIYA KYUKI AGAR string valid parentheses ki naa ho matlab open "(" to ho lekin close ")" na ho us case mein count of open pata chale
                // lekin agar sring valid hai tab iska mtlab hai jitne open "(" haiin utne hi close bhi hain tab bhi agar mein max_depth ko "(" aane pe update karu tab bhi chalega
            }
            else if(ch == ')'){
                count--;
            }
            else{
                continue;
            }
        }
        return max_depth;
}

int main(){
    string s = "(1+(2*3)+((8)/4))+1";
    cout<<"The maximum nesting depth of parentheses is :-"<<maximum_nesting_depth_of_parentheses(s);
    return 0;
}