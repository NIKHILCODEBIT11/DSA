#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (STRING TO INTEGER - ATOI):
   - Problem:
     Ek string 's' ko 32-bit signed integer me convert karna hai (C/C++ ke
     standard atoi function ki tarah) aur boundary constraints ko handle karna hai.
     Rules:
     1. Leading spaces ko ignore karo.
     2. Optional '+' ya '-' sign identify karo.
     3. Saare valid continuous digits ko integer me convert karo.
     4. Pehle non-digit character (jaise alphabets/symbols) aate hi ruk jao.
     5. 32-bit integer overflow/underflow ko clamp karo:
        Agar number > INT_MAX (2147483647), return INT_MAX.
        Agar number < INT_MIN (-2147483648), return INT_MIN.

   - The Masterstroke: "Overflow Check Before Multiplication":
     Agar hum seedhe `result = result * 10 + digit` likhenge aur result already
     bada hua, toh 32-bit signed integer C++ me overflow ho jayega jo
     UNDEFINED BEHAVIOR deta hai.
     Isliye calculation karne se PEHLE check karte hain:
     - INT_MAX = 2147483647
     - INT_MAX / 10 = 214748364
     
     Case A: Agar `result > INT_MAX / 10`:
       Iska matlab agle step me result * 10 kam se kam 2147483650 banega jo
       2147483647 se strictly bada hai. 100% overflow hoga!
       
     Case B: Agar `result == INT_MAX / 10` (matlab result = 214748364):
       Ab agle step me `result * 10 = 2147483640` banega.
       Agar aane wali `digit > 7` hui (jaise 8 ya 9):
       Toh total `2147483648` ban jayega jo INT_MAX ki limit tod dega!
       (Negative ke liye INT_MIN = -2147483648 hota hai, digit 8 aane par
       clamp hokar seedhe INT_MIN ban jayega, isliye condition safe hai).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - while(i < n && s[i] == ' ') i++; :
     Pehle saare leading whitespaces ko skip kiya.
   - if(i == n) return 0; :
     Edge Case: String me sirf spaces the ya empty thi, seedha 0 return kiya.
   - int sign = 1; if(s[i] == '-') ... else if(s[i] == '+') ... :
     Sign reading. Ek baar sign check hone ke baad pointer 'i' ko 1 step aage badhaya.
   - while(i < n && isdigit(s[i])) :
     Jab tak valid numeric character mil raha hai, loop chalega.
     Pehla character jo digit nahi hoga (jaise space ya letter), loop turant break ho jayega.
   - int digit = s[i] - '0'; :
     Character ASCII code ko actual numeric value me badla ('5' - '0' = 5).
   - if(result > INT_MAX/10 || (result == INT_MAX/10 && digit > 7)) :
     Pre-emptive overflow check. Agar overflow ho raha hai, toh sign ke hisab se
     INT_MAX ya INT_MIN return karke function exit.
   - result = result * 10 + digit; :
     Base-10 number formation (e.g. 6 -> 60 + 5 = 65 -> 650 + 7 = 657).
   - return result * sign; :
     Constructed integer ko uske original positive ya negative sign ke saath return kiya.

======================================================================
3. DETAILED DRY RUN:

   Input: s = "   -657 with rong"
   Length n = 18

   Step 1: Skip Whitespaces
   - i = 0: ' ' -> i = 1
   - i = 1: ' ' -> i = 2
   - i = 2: ' ' -> i = 3
   - i = 3: '-' -> stop. (i = 3 < n, empty check passed).

   Step 2: Read Sign
   - s[3] == '-' -> sign = -1, i = 4.

   Step 3: Read Digits & Construct Number
   - Initial: result = 0

   --- Iteration 1 (i = 4, s[4] = '6') ---
   - isdigit('6') -> TRUE
   - digit = '6' - '0' = 6
   - Overflow Check:
     result (0) > INT_MAX/10 (214748364) -> FALSE
     result == INT_MAX/10 && digit > 7 -> FALSE
   - result = 0 * 10 + 6 = 6
   - i = 5

   --- Iteration 2 (i = 5, s[5] = '5') ---
   - isdigit('5') -> TRUE
   - digit = '5' - '0' = 5
   - Overflow Check: 6 > 214748364 -> FALSE
   - result = 6 * 10 + 5 = 65
   - i = 6

   --- Iteration 3 (i = 6, s[6] = '7') ---
   - isdigit('7') -> TRUE
   - digit = '7' - '0' = 7
   - Overflow Check: 65 > 214748364 -> FALSE
   - result = 65 * 10 + 7 = 657
   - i = 7

   --- Iteration 4 (i = 7, s[7] = ' ') ---
   - isdigit(' ') -> FALSE
   - Loop Terminates Immediately!
   (" with rong" completely ignored).

   Step 4: Final Return
   - return result * sign => 657 * (-1) = -657.
   Output: -657.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(N) where N is the length of string 's'.
     * String ko single pass me traverse kiya jata hai.
     * Whitespaces aur non-digits ke aate hi scanning ruk jati hai,
       maximum operations string length ke barabar hi honge.
   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Sirf standard integer scalar variables (i, n, sign, result, digit)
       use hue hain, koi auxiliary data structure allocate nahi hota.
======================================================================
*/

int myAtoi(string s) {
    // INT_MAX ki value for 32-bit int = 2147483647

    int i = 0, n = s.size();

    // whitespace skip karna 
    while(i < n && s[i] == ' '){
        i++;
    }
    // agar pura string hi whitespaces se bhara hai jaise '    '
    if(i == n){
        return 0;
    }

    // sign dekhna
    int sign = 1;
    if(s[i] == '-'){
        sign = -1;
        i++;
    }
    else if(s[i] == '+'){
        i++;
    }

    // digits and overflow
    int result = 0;
    while(i < n && isdigit(s[i])){
        int digit = s[i] - '0';

        // check for overlow before result * 10
        if(result > INT_MAX/10 || (result == INT_MAX/10 && digit > 7)){
            return (sign == 1) ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
        i++;
    }
    return result * sign;

}

int main(){
    string s = "   -657 with rong";
    cout<<"String ATOI :-"<<endl;
    cout<<myAtoi(s);
    return 0;
}

/*
3. Overflow Condition (INT_MAX / 10 aur digit > 7)
Yahi is question ka main trick hai.
32-bit signed integer ki maximum limit hoti hai:
INT_MAX = 2147483647

Agar result already bada ho chuka hai aur humne result * 10 kar diya, toh C++ me Integer Overflow 
runtime crash ho jayega. Isliye hume multiply karne se pehle hi check karna padta hai ki kya agla 
step safe hai ya nahi.

Iske 2 cases bante hain:

Case A: result > INT_MAX / 10
---> INT_MAX / 10 = 214748364 (integer division me aakhiri digit 7 chhoot jati hai).
---> Agar aapka result pehle se hi 214748365 ya usse bada hai, toh jab aap agle step me usko * 10 karenge, wo ban jayega 2147483650, jo pakka 2147483647 se bada hai — yaani guaranteed overflow! Chahe aane wali digit koi bhi ho (0 se 9).

Case B: result == INT_MAX / 10 && digit > 7
---> Agar aapka result theek 214748364 par baitha hai:
        Agle step me jab aap * 10 karenge, base banega 2147483640.
        Max limit hai 2147483647.
        Agar aane wali digit 7 tak hai (0, 1, ...., 7), toh number banega max 2147483647 — Safe!
        Lekin agar aane wali digit 8 ya 9 ho gayi, toh number ban jayega 2147483648 ya 2147483649 — Overflow!

End me:
return (sign == 1) ? INT_MAX : INT_MIN;

Agar overflow ho raha hai:
Positive number tha toh maximum limit return kar do: INT_MAX
Negative number tha toh minimum limit return kar do: INT_MIN
Aur agar loop normally bina overflow hue khatam ho gaya, toh aakhiri line:
return sign * result;
*/