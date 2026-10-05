#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (REMOVE OUTERMOST PARENTHESES):
   - Problem:
     Hume ek valid parentheses string 's' di gayi hai. Ye string alag-alag
     "primitive" valid substrings se milkar bani hai.
     Hume har primitive substring ke sabse bahar wale (outermost) '(' aur ')'
     ko hatana hai aur bachi hui string ko join karke return karna hai.
     
     Example: "(()())" -> Outermost hatane par bachega "()()"
     
   - Intuition (Depth / Level Counting):
     Har bracket ka ek nesting level ya depth hota hai.
     - Pehla '(' jo primitive group shuru karta hai, wo Level 0 par khada hota hai.
     - Aakhri ')' jo us primitive group ko finish karta hai, wo wapas Level 0 par le aata hai.
     
     Humara Goal:
     Hume sirf aur sirf wahi brackets 'ans' string me jodte jana hai jo Level > 0 par hain!
     Level 0 wale brackets "SUPREME" (outermost) hote hain, unhe skip karna hai.
     
   - Variable 'count' ka magic:
     'count' tracks the current nesting depth.
     
     1. Jab ch == '(' aaye:
        - Agar abhi count == 0 hai, matlab ye kisi naye primitive block ka 
          PEHLA (outermost) opening bracket hai. Isko ans me NAHI daalna!
        - Agar abhi count > 0 hai, matlab hum already kisi block ke andar hain. 
          Ye inner bracket hai, isliye isko ans me DAALNA hai!
        - Iske baad count ko 1 se badha do (count++).
        
     2. Jab ch == ')' aaye:
        - Outermost closing bracket wo hota hai jo count ko wapas 0 bana de.
        - Isliye hum PEHLE hi count-- kar dete hain.
        - Agar count-- karne ke baad bhi count > 0 hai, matlab ye inner closing bracket tha, 
          isko ans me DAALNA hai!
        - Agar count-- karne par count == 0 ban gaya, matlab ye outermost closing bracket tha, 
          isko skip kar do (ans me mat daalo)!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - string ans = ""; int count = 0; :
     'ans' resultant string banayega aur 'count' nesting depth ko 0 se track karega.
     
   - if (ch == '(') :
     - if (count > 0) ans += ch;
       Check kiya ki kya hum already kisi outer bracket ke andar hain.
       Agar count > 0 hai, tabhi ans me add karo.
       Agar count == 0 tha, toh ye supreme opening bracket tha, isliye ans me add nahi hua!
     - count++;
       Chahe supreme ho ya inner, depth ko 1 level aage badhana zaroori hai.
       
   - else (ch == ')') :
     - count--;
       Pehle hi balance ko 1 se kam kiya taaki check kar sakein ki hum ground level (0) 
       par gire ya abhi bhi kisi bracket ke andar hain.
     - if (count > 0) ans += ch;
       Agar count abhi bhi > 0 hai, iska matlab hum outer boundary ke andar hain, 
       toh ')' ko ans me append karo.
       Agar count 0 ho gaya, toh ye supreme closing bracket tha, add mat karo!

======================================================================
3. DETAILED DRY RUN:

   Input: s = "(()())"
   Length = 6
   Initial: ans = "", count = 0

   -------------------------------------------------------------------
   Index 0: ch = '('
   - Check: count > 0 ? (0 > 0) -> FALSE (Supreme Opening, Skip!)
   - Action: ans = ""
   - Update: count++ => count = 1

   Index 1: ch = '('
   - Check: count > 0 ? (1 > 0) -> TRUE (Inner Opening, Keep!)
   - Action: ans = "("
   - Update: count++ => count = 2

   Index 2: ch = ')'
   - Pre-update: count-- => count = 1
   - Check: count > 0 ? (1 > 0) -> TRUE (Inner Closing, Keep!)
   - Action: ans = "()"

   Index 3: ch = '('
   - Check: count > 0 ? (1 > 0) -> TRUE (Inner Opening, Keep!)
   - Action: ans = "()("
   - Update: count++ => count = 2

   Index 4: ch = ')'
   - Pre-update: count-- => count = 1
   - Check: count > 0 ? (1 > 0) -> TRUE (Inner Closing, Keep!)
   - Action: ans = "()()"

   Index 5: ch = ')'
   - Pre-update: count-- => count = 0
   - Check: count > 0 ? (0 > 0) -> FALSE (Supreme Closing, Skip!)
   - Action: ans = "()()" (No change)

   Loop Ends.
   Returned String: "()()"

   -------------------------------------------------------------------
   For full main() example: "(()())(())(()(()))"
   - Block 1: "(()())"     -> becomes "()()"
   - Block 2: "(())"       -> becomes "()"
   - Block 3: "(()(()))"   -> becomes "()(())"
   Final Output: "()()()()(())"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(N) where N is the length of string 's'.
     * Hum string ke har character ko sirf ek baar traverse kar rahe hain.
     * Har character par sirf O(1) operations (conditions aur string append) ho rahe hain.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) extra operational space.
       Sirf ek integer counter 'count' aur loop variable use ho raha hai.
     * Output Space: O(N) result string 'ans' ko store karne ke liye.
======================================================================
*/

string remove_outermost_parentheses(string s){
    string ans = "";
    int count = 0;     // ye signify kar raha ki COUNT JAB JAB INCREASE -> DECREASE HOTE HOTE 0 AAYEGA TAB TAB "SUPREME OPENING TAG AAYEGA JISE KI ELIMINATE KARNA HAI"

    for(char ch : s){
        if(ch == '('){

            // sabse pehle ye check karunga ki kahi ye jo hai SUPREME OPENING BRACKET TO NAHI USKA TARIKA HAI KI :- SUPREME OPNING BRACKET KE LIYE HAMESHA count = 0 HOGA
            // lekin kyuki mujhe SUPREME OPENING - CLOSING BRACKETS KE ANDAR KE () PRINT KARNE HAIN ISLIYE MEIN count > 0 chk karunga jo ki true hone pe ye batayega ki abhi jo "(" hai wo actually mein print hone wala hai
            if(count > 0){
                ans += ch;
            }
            count++;   // ye to hamesha hi karunga kyuki bhale hi "(" SUPREME OPENING BRACKET ho ya NORMAL PRINT HONE WALA BRACKET count update karte hue har step mein chk to karna hi hai
        }
        else{    // condition of ch = ')'
            // pehle hi count-- kar raha hu taaki SUPREME OPENING BRACKET wala khali ho to pehle hi close ho jaye
            count--;
            if(count > 0){
                ans += ch;
            }
        }
    }
    return ans;
}

int main(){
    string s = "(()())(())(()(()))";
    cout<<"String after removing parentheses :-"<<endl;
    cout<<remove_outermost_parentheses(s);
    return 0;
}