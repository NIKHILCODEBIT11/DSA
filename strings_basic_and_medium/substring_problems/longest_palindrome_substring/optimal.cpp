#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (LONGEST PALINDROMIC SUBSTRING - EXPAND AROUND CENTER):
   - Problem:
     Hume ek string 's' di gayi hai. Hume us string ke andar sabse lamba 
     palindrome substring dhoondhna hai aur use return karna hai.

   - Brute Force Kyun Bekar Hai?
     Saare substrings generate karo O(N^2) aur har ek ko check karo O(N).
     Total Time Complexity = O(N^3), jo bade strings par TLE de dega.

   - Expand Around Center Intuition:
     Har palindrome string apne center ke around symmetric (aaine jaisi) hoti hai:
     - "racecar" ka center 'e' hai.
     - "noon" ka center do 'o' ke beech ka gap hai.
     
     Toh har character/position ko ek "Center" maano aur dono taraf 
     (left me piche aur right me aage) failte jao (expand out):
     Jab tak `s[left] == s[right]` match karta rahe, palindrome bada hota jayega!
     Jaise hi character mismatch ho ya boundary hit ho, ruk jao.

   - Do Tarah Ke Centers:
     1. Odd Length Palindrome:
        Center ek single character hota hai (e.g. "aba" me 'b').
        Isliye start expanding from: `left = i, right = i`.
     2. Even Length Palindrome:
        Center do adjacent characters ke beech hota hai (e.g. "abba" me 'b' aur 'b').
        Isliye start expanding from: `left = i, right = i + 1`.

   - Clean Substring Extraction:
     Hume bar-bar substring copy karne ki zaroorat nahi hai.
     Sirf do integer variables track karo:
     - `start`: Longest palindrome kahan se shuru hota hai.
     - `max_len`: Uski total lambai kitni hai.
     End me `s.substr(start, max_len)` se exact substring ek baar me mil jati hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - int max_len = 0; int start = 0; :
     Longest palindromic window ka starting index aur length track karne ke liye.
     (Note: `start = 0` initialize karna safe practice hai agar string size 1 ho).
   - auto expand = [&](int left, int right) { ... }; :
     Lambda function jo given center se outward expand karta hai jab tak 
     palindrome property satisfy hoti rahe.
   - while(left >= 0 && right < n && s[left] == s[right]) :
     Boundary checks aur symmetry matching. Jab tak dono characters identical hain, 
     palindrome valid hai.
   - int current_len = right - left + 1; :
     Current expanding palindrome ki length calculate ki.
   - if(current_len > max_len) { max_len = current_len; start = left; } :
     Agar naya palindrome ab tak ke record se lamba hai, toh naya max aur start point lock kiya.
   - left--; right++; :
     Center se ek kadam aur bahar ki taraf dono directions me expand kiya.
   - for(int i = 0; i < n; i++) :
     String ke har index ko potential center mankar Odd aur Even expansion run kiya.
   - return s.substr(start, max_len); :
     Sabse lambe palindrome ko directly slice karke return kar diya.

======================================================================
3. DETAILED DRY RUN:

   Input: s = "jfdhdjsracecarhf"
   Length n = 16

   Jab loop chalte hue index 10 ('e') par aayega:
   Target word "racecar":
   Indices:   7   8   9  10  11  12  13
   Chars:     r   a   c   e   c   a   r

   Call expand(10, 10) [Odd Length Expansion]:
   - Step 1: left = 10, right = 10 ('e' == 'e')
     current_len = 10 - 10 + 1 = 1.
     left becomes 9, right becomes 11.
   - Step 2: left = 9, right = 11 (s[9]='c' == s[11]='c')
     current_len = 11 - 9 + 1 = 3 ("cec").
     left becomes 8, right becomes 12.
   - Step 3: left = 8, right = 12 (s[8]='a' == s[12]='a')
     current_len = 12 - 8 + 1 = 5 ("aceca").
     left becomes 7, right becomes 13.
   - Step 4: left = 7, right = 13 (s[7]='r' == s[13]='r')
     current_len = 13 - 7 + 1 = 7 ("racecar").
     current_len (7) > max_len -> max_len = 7, start = 7.
     left becomes 6, right becomes 14.
   - Step 5: left = 6 ('s'), right = 14 ('h') -> s[6] != s[14] ('s' != 'h').
     Condition fails! While loop breaks.

   Pure loop me "racecar" (length 7) se lamba koi palindrome nahi milega.

   Final Extraction:
   s.substr(start = 7, max_len = 7) => "racecar".
   Output: "The longest palindrome is :- racecar"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Total Centers = 2 * N - 1 (N odd centers + N-1 even centers).
     * Har center se expansion worst case me O(N) dur tak ja sakta hai 
       (jaise string "aaaaa" ho).
     * Total Time Complexity: O(N * N) = O(N^2).
     * Brute Force O(N^3) ke comparison me bohot fast hai aur interview standard optimal solution hai.
       (Note: Linear time O(N) ke liye Manacher's Algorithm use hota hai, par interviews me Expand Around Center best balance maana jata hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra table (DP matrix) ya reverse string allocate nahi hui.
     * Sirf standard integer trackers (max_len, start, left, right, current_len) use hue hain.
======================================================================
*/

string longest_palindrome(string s){
    int max_len = 0;
    int start;
    int n = s.size();

    auto expand = [&](int left, int right){
        while(left >= 0 && right <n && s[left] == s[right]){
            int current_len = right - left + 1;
            if(current_len > max_len){
                max_len = current_len;
                start = left;
            }
            left--;
            right++;
        }
    };

    for(int i = 0; i < n; i++){
        expand(i, i);     // odd length palindrome ke liye
        expand(i, i+1);    // even length palindrome ke liye
    }

    return s.substr(start, max_len);
}

int main(){
    string s = "jfdhdjsracecarhf";
    cout<<"The longest palindrome is :- "<<longest_palindrome(s);
    return 0;
}

/*

================================================================================
DOUBT 1: auto expand = [&](int left, int right) { ... };
Yeh syntax kya hai aur iska actual kaam kya hota hai?
================================================================================

QUESTION:
C++ mein normal function banane ke bajaye function ke andar yeh 
"auto expand = [&](int left, int right)" likhne ka kya matlab hai?

ANSWER:
Isko C++ mein Lambda Function (Anonymous Local Function) kehte hain.

1. "auto expand =":
   Iska matlab hai hum ek chhota local tool/helper bana rahe hain jiska naam 
   humne "expand" rakha hai. Yeh tool sirf is function ke andar hi zinda rahega.

2. "[&]" (Capture by Reference - Sabse Important):
   Normal functions apne bahar ke variables ko nahi dekh sakte jab tak unhe 
   pass na kiya jaye.
   Lekin yeh "[&]" symbol expand ko yeh taqat deta hai ki woh apne bahar 
   baithe variables jaise "start", "max_len", aur "s" ko directly padh bhi 
   sakta hai aur MODIFY (change) bhi kar sakta hai.
   Agar hum yeh nahi lagate, toh hume har baar expand mein 
   expand(left, right, s, start, max_len, n) itne lambe parameters bhejne padte.

3. "(int left, int right)":
   Yeh do ungliyon (pointers) ke coordinates hain jahan se matching shuru karni hai.

4. Aakhiri semicolon ";":
   Kyunki yeh ek variable assignment jaisa hai (jaise int x = 5;), isliye 
   curly bracket band hone ke baad semicolon ";" lagana syntax ka rule hai.


================================================================================
DOUBT 2: expand(i, i) aur expand(i, i+1) se Odd aur Even length kaise aate hain?
================================================================================

QUESTION:
Ek jagah dono mein 'i' diya aur doosri jagah 'i, i+1' diya, isse Odd aur Even 
ka faisla kaise hota hai?

ANSWER:
Yeh poora khel is baat ka hai ki tumhara mirror shuru kitne letters se ho raha hai.
Rule: Palindrome jab dono taraf phailta hai, toh har kadam par hamesha 
2 letters naye judte hain (1 left se, 1 right se).

Case A: expand(i, i) -> Odd Kyun?
- Yahan tum dono ungliyan EK HI letter par rakhte ho (Shuruat hui 1 letter se).
- Shuruat: 1 letter (Odd).
- Phir expand hua: 1 + 2 = 3 letters (Odd).
- Phir expand hua: 3 + 2 = 5 letters (Odd).
- Odd number mein 2 jodte rahoge, toh answer hamesha ODD hi aayega (1, 3, 5, 7...).
- Example: String "aba" mein agar 'b' par khade hokar dono ungliyan rakho, 
  toh pehle 1 letter ('b') match hua, phir expand hoke 3 letters ("aba") match huye.

Case B: expand(i, i+1) -> Even Kyun?
- Yahan tum ungliyan DO ALAG bagal wale letters par rakhte ho (Shuruat hui 2 letters se).
- Shuruat: 2 letters (Even).
- Phir expand hua: 2 + 2 = 4 letters (Even).
- Phir expand hua: 4 + 2 = 6 letters (Even).
- Even number mein 2 jodte rahoge, toh answer hamesha EVEN hi aayega (2, 4, 6, 8...).
- Example: String "abba" mein dono beech wale 'b' aur 'b' par ungli rakhi, 
  toh pehle 2 letters ("bb") match huye, phir expand hoke 4 letters ("abba") match huye.


================================================================================
DOUBT 3: Khali ek hi (Odd ya Even) lene se kaam kyun nahi chal sakta?
================================================================================

QUESTION:
Agar main sirf expand(i, i) chalaun ya sirf expand(i, i+1) chalaun, 
toh problem kya aayegi?

ANSWER:
Duniya mein palindromes do tarah ke hote hain.
Agar tum ek hi check lagaoge, toh doosre type ke sare palindromes code 
ke haath se chhoot jayenge aur answer galat aayega.

Problem 1 (Agar sirf Odd chalaya):
Input: "cbbd"
Yahan answer "bb" (length 2 - even) hona chahiye.
Lekin code hamesha 1 letter ke center se dhoondhega (1, 3, 5...), 
usko do same letters ka center kabhi milega hi nahi.
Result: Code "bb" ko chhod dega aur sirf single letter "c" ya "b" de dega. Test case fail.

Problem 2 (Agar sirf Even chalaya):
Input: "aba"
Yahan answer "aba" (length 3 - odd) hona chahiye.
Lekin code hamesha do letters ke jode se shuru karega.
Index 0 aur 1 ("ab") match nahi huye.
Index 1 aur 2 ("ba") match nahi huye.
Result: Code ko lagega koi palindrome hai hi nahi. "aba" miss ho gaya. Test case fail.


================================================================================
DOUBT 4: s = "aba" mein jab i = 1 tha, toh expand(1, 2) se "bab" kyun nahi bana?
================================================================================

QUESTION:
String "aba" mein jab i = 1 par even check expand(1, 2) call hua, 
toh left-- aur right++ hoke pura "aba" pakad mein kyun nahi aaya?

ANSWER:
Kyunki left-- aur right++ tak pahunchne ke liye darwaza paar karna padta hai, 
aur darwaza pehli hi line mein band ho gaya!

Code ka order dhyan se samjho:
while(left >= 0 && right < n && s[left] == s[right])

Yahan pehle check hota hai:
Kya s[left] barabar hai s[right] ke?

Jab i = 1 par expand(1, 2) call hua:
- left = 1 (letter hai 'b')
- right = 2 (letter hai 'a')
- Darwaze par guard ne pucha: Kya 'b' aur 'a' barabar hain?
- Jawab mila: NAHI (False).

Kyunki yeh false ho gaya, while loop ke andar execution gaya hi nahi!
Na length count hui, na left-- hua, na right++ hua.
While loop ne pehle hi kadam par function ko bahar phenk diya.
Expansion sirf tabhi aage badhta hai jab shuruati letters match karein.


================================================================================
DOUBT 5: Indexing aur Formula (right - left + 1)
================================================================================

QUESTION:
Length nikaalne ke liye "right - left + 1" mein yeh "+1" kyun lagaya jata hai?

ANSWER:
Array aur string ki indexing 0 se shuru hoti hai.
Jab tum do indices ke beech ke elements ginte ho, toh agar tum sirf 
(right - left) karoge toh ek letter chhoot jata hai.

Example:
String: "r a c e c a r"
Indices: 0 1 2 3 4 5 6
Maan lo left = 2 (letter 'c') aur right = 4 (letter 'c').
Hamare letters hain: index 2, index 3, index 4 (Total 3 letters: "cec").

Agar sirf minus karein:
right - left = 4 - 2 = 2 (Galat! Letters toh 3 hain).

Isliye:
right - left + 1 = 4 - 2 + 1 = 3 (Ekdum sahi!).
Yeh standard formula hai dono ends ko include karke total count nikaalne ka.


================================================================================
DOUBT 6: C++ substr() vs Python Slicing s[0:4]
================================================================================

QUESTION:
s.substr(start, max_len) ka exact matlab kya hota hai aur yeh Python ke 
s[0:4] se kaise alag hai?

ANSWER:
Dono languages do alag rules use karti hain:

Python Slicing: s[start : stop]
- Yahan doosra number "ending index" hota hai (jo include nahi hota).
- Example: s[0:4] ka matlab hai index 0 se shuru karo aur index 4 se pehle 
  (yani 3 tak) ruk jao -> Total 4 letters aate hain.

C++ substr(): s.substr(starting_index, total_count)
- Yahan doosra number ending index NAHI hota.
- Doosra number seedha GINTI (kitne letters kaatne hain) hota hai.
- Example: s.substr(2, 7) ka matlab hai:
  "Index 2 par khade ho jao, aur wahan se aage gin ke 7 letters utha lo."
Isliye hamare code mein humne "start" (kahan se shuru karna hai) aur 
"max_len" (kitne letters kaatne hain) pass kiya.


================================================================================
DOUBT 7: int start; bina initialize kiye chhodne se kya dikkat aayegi?
================================================================================

QUESTION:
Code mein "int max_len = 0;" toh kar diya, lekin "int start;" ko koi value 
nahi di, isse code crash kyun ho sakta hai?

ANSWER:
C++ mein local variables ko agar koi value na do, toh unme 0 nahi baithta, 
unme GARBAGE VALUE (koi bhi ulti-seedhi random memory value, jaise -492813 ya 
892347) baith jati hai.

Maan lo string empty aayi: s = "" (n = 0).
For loop chalega hi nahi (0 < 0 false).
Toh aakhiri line chalegi: s.substr(start, max_len).
Kyunki start ko kisi ne touch nahi kiya, usme wahi garbage value padi hogi.
Program string se bolega: "Memory ke index -492813 se character uthao!"
Computer turant Segmentation Fault dekar crash ho jayega.
Isliye hamesha "int start = 0;" likhna safe programming hoti hai.
================================================================================
*/