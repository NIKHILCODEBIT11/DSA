#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BINARY EXPONENTIATION - POW(X, N)):
   - Problem:
     Hume x^n (x raised to the power n) calculate karna hai jahan:
     * x ek floating-point double value hai.
     * n ek 32-bit signed integer hai jo positive, zero, ya negative ho sakta hai.

   - Brute Force Kyun Fail Hota Hai?
     Agar hum loop chala kar x ko n baar multiply karein:
       result = result * x; (n times)
     Toh Time Complexity O(N) hogi.
     Jab n = 2147483647 (INT_MAX) aayega, toh loop 2 billion baar chalega aur Time Limit Exceeded (TLE) de dega.

   - Binary Exponentiation (Divide and Conquer Intuition):
     Power ko aadha karte jao:
     - Agar n EVEN hai:
       x^8 = (x^4) * (x^4)
       Hume x^4 ko do baar calculate karne ki zaroorat nahi hai.
       Ek baar x^4 nikaal lo (`half = solve(x, n/2)`), fir `half * half` kar do!
     - Agar n ODD hai:
       x^9 = (x^4) * (x^4) * x
       Ek extra x multiply ho jayega: `half * half * x`.
     - Base Case:
       Kisi bhi number ki power 0 hamesha 1.0 hoti hai (x^0 = 1.0).

     Is tarah har step par power aadhi (n / 2) hoti rehti hai, toh total steps O(N) ke badle sirf O(log2 N) lagenge!

   - The INT_MIN Overflow Trap (`long long N = n`):
     32-bit signed integer ki range hoti hai:
       -2147483648 (INT_MIN) se lekar +2147483647 (INT_MAX).
     Notice karo: INT_MIN ka absolute positive counterpart (+2147483648) 32-bit signed int me fit hi nahi hota!
     Agar hum seedhe `n = -n;` likhte jab n = INT_MIN ho, toh integer overflow ho jata (Undefined Behavior in C++).
     Isliye `long long N = n;` me store karna mandatory hai taaki `-N` bina kisi overflow ke safely compute ho sake.

   - Negative Power Handling:
     x^(-n) = (1/x)^n.
     Isliye agar N < 0 ho, toh hum base ko invert kar dete hain (`x = 1.0 / x`) aur power ko positive bana dete hain (`N = -N`).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `solve(double x, long long n)` ---
   - `if(n == 0) return 1.0;`:
     Base Case: x^0 = 1.0.
   - `double half = solve(x, n/2);`:
     Recursive leap of faith. x^(n/2) ko sirf EK baar compute kiya taaki redundant calculations na hon.
   - `if(n % 2 == 0) return half * half;`:
     Even power logic: x^n = (x^(n/2))^2.
   - `else return half * half * x;`:
     Odd power logic: x^n = (x^(n/2))^2 * x.

   --- `myPow(double x, int n)` ---
   - `long long N = n;`:
     INT_MIN (-2147483648) overflow guard.
   - `if(N < 0)`:
     Negative exponent handler:
     `x = 1.0 / x;` -> Inverts the base.
     `N = -N;`      -> Makes the power strictly positive without overflow.
   - `return solve(x, N);`:
     Positive power ke saath recursive helper ko call kiya.

======================================================================
3. DETAILED DRY RUN:

   Base: x = 2.0, Exponent: n = 10
   N = 10 (N > 0) -> Call solve(2.0, 10)

   -------------------------------------------------------------------
   Recursion Tree (Top to Bottom Calls):
   solve(2.0, 10)
     -> solve(2.0, 5)
       -> solve(2.0, 2)
         -> solve(2.0, 1)
           -> solve(2.0, 0) => BASE CASE: returns 1.0

   Unwinding (Bottom to Top Returns):
   - At n = 1 (ODD):
     half = solve(2.0, 0) = 1.0
     return half * half * x = 1.0 * 1.0 * 2.0 = 2.0

   - At n = 2 (EVEN):
     half = solve(2.0, 1) = 2.0
     return half * half = 2.0 * 2.0 = 4.0

   - At n = 5 (ODD):
     half = solve(2.0, 2) = 4.0
     return half * half * x = 4.0 * 4.0 * 2.0 = 32.0

   - At n = 10 (EVEN):
     half = solve(2.0, 5) = 32.0
     return half * half = 32.0 * 32.0 = 1024.0

   Final Return: 1024.0
   Total recursive calls: sirf 5 calls for n = 10!

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(log2 N) where N is the magnitude of the exponent n.
     * Har recursive call me N ki value aadhi ho rahi hai (N -> N/2 -> N/4 -> ... -> 0).
     * Maximum 32 recursive calls lagengi jab n = 2147483647 ho.

   - Space Complexity (SC):
     * Auxiliary Space: O(log2 N).
     * Recursion Call Stack depth log2(N) levels tak hi jaati hai.
     * Koi auxiliary heap data structure allocate nahi hota.
======================================================================
*/

double solve(double x, long long n){
    if(n == 0){
        return 1.0;
    }
    double half = solve(x, n/2);
    if(n%2 == 0){
        return half*half;
    }
    else{
        return half*half*x;
    }
}

double myPow(double x, int n) {
    long long N = n;
    if(N < 0){
        x = 1.0/x;
        N = -N;
    }
    return solve(x, N);
}

int main(){
    double x = 67.6;
    int n = 8;
    
    cout<<"answer is "<<myPow(x, n);
    return 0;
}

/*
================================================================================
          DETAILED CONCEPTUAL EXPLANATION: BINARY EXPONENTIATION (POW(x, n))
================================================================================

1. KYUN ZAROORI HAI O(log n) APPROACH (DIVIDE & CONQUER):
--------------------------------------------------------------------------------
- Brute Force Approach:
  x ko n baar loop chala kar multiply karna O(n) time leta hai.
  Agar n = 2*10^9 (INT_MAX) ho, toh 2*10^9 operations honge.
  CP/LeetCode ka standard rule hai: 10^8 operations lagbhag 1 second lete hain.
  Toh 2*10^9 operations lene par code 20 seconds lega, jisse pakka TIME LIMIT
  EXCEEDED (TLE) aayega.

- Binary Exponentiation Ka Idea:
  Power ko har step par aadha (n/2) karte jao:
  Example: 2^10 = (2^5)^2 = ((2^2)^2 * 2)^2
  Har step par problem size aadhi hoti hai, isliye total steps log2(n) bante hain.
  Agar n = 2*10^9 bhi ho, toh log2(2*10^9) ≈ sirf 31 steps lagte hain!
  Code fractions of a millisecond mein execute ho jata hai.


2. VARIABLE 'half' MEIN RESULT STORE KARNE KA REASON:
--------------------------------------------------------------------------------
- Agar hum recursion mein likhein:
  return solve(x, n/2) * solve(x, n/2);
  Toh yeh Divide & Conquer nahi rehta, yeh Branching ban jata hai (jaise Fibonacci).
  Pehle half ke liye ek recursive tree banega, dusre half ke liye bilkul duplicate
  dusra tree banega. Time complexity wapas O(2^(log n)) = O(n) ho jayegi.

- Lekin jab hum likhte hain:
  double half = solve(x, n/2);
  return half * half;
  Toh subproblem sirf EK baar solve hoti hai aur uska answer memory mein hold hota hai.
  Phhir usi result ko square kar diya jata hai, jisse time strict O(log n) rehta hai.


3. ODD POWER KE LIYE 'half * half * x' KYUN HOTA HAI:
--------------------------------------------------------------------------------
- Computer programming mein integer division decimal part ko drop kar deta hai
  (Floor division):
  9 / 2 = 4 hota hai (4.5 nahi).
- Jab hum 3^9 calculate karte hain:
  Recursion call karega n = 4 ke liye, yani solve(3, 4) jo 81 dega.
- Jab function wapas aata hai:
  half * half = 81 * 81 = 3^4 * 3^4 = 3^8.
- Par hume calculate karna tha 3^9!
  Integer division ki wajah se ek power (x = 3) gayab ho gayi thi.
- Is missing power ko compensate karne ke liye:
  Odd case mein extra 'x' multiply kiya jata hai: (half * half * x) -> 3^8 * 3 = 3^9.


4. INT_MIN AUR OVERFLOW KA DEEP DIVE:
--------------------------------------------------------------------------------
- 32-bit signed integer memory mein 2's Complement format use karta hai.
- Range hoti hai: -2,147,483,648 se lekar +2,147,483,647 tak.
- Positive side par 1 number kam hota hai kyunki 0 positive bucket mein count hota hai.

- Ab dikkat kahan aati hai:
  LeetCode ka test case: x = 2.0, n = -2147483648 (INT_MIN).
  Negative power ko positive banane ke liye common instinct hota hai: n = -n;
  Lekin -(-2147483648) = +2147483648 hota hai.
  Ye value 32-bit int ki maximum capacity (+2147483647) se badi hai!

- Jab yeh overflow hota hai C++ mein:
  Binary wraparound hota hai aur +2147483648 wapas ghum kar -2147483648 ban jata hai.
  Toh n positive hone ke bajaye negative hi reh jata hai aur logic crash ho jata hai.
  Signed integer overflow C++ standards mein 'Undefined Behavior' (UB) hai.

- 'long long' Kyun Solve Karta Hai:
  'long long' 64-bit ka hota hai. Iski range ±9*10^18 hoti hai.
  Toh jab n ko pehle 'long long N = n' assign karte hain, tab memory ka size
  double ho jata hai. Ab N = -N karne par +2147483648 bina kisi issue ke
  fit ho jata hai.


5. NEGATIVE POWERS KO ENTRY POINT PAR HI CONVERT KARNE KA LOGIC:
--------------------------------------------------------------------------------
- Mathematics rule:
  x^(-n) = 1 / (x^n) = (1/x)^n.
  Example: 2^(-3) = (1/2)^3 = 0.5^3 = 0.125.

- Agar hum recursion ke andar negative numbers ko chalne dein:
  C++ mein negative odd number ka modulo negative hota hai:
  (-3) % 2 = -1 (1 nahi hota!).
  Negative numbers ki division rounding issues aur sign bit errors laati hai.

- Isliye standard practice yeh hai:
  Function shuru hote hi check karo:
  Agar power negative hai, toh base ko ulta kar do (x = 1.0 / x) aur power ko
  positive bana do (N = -N).
  Iske baad aage ka poora recursion normal positive integers ki tarah smooth chalta hai.


6. BASE CASE 'n == 0' PAR RETURN 1.0 HI KYUN:
--------------------------------------------------------------------------------
- Maths principle: Kisi bhi non-zero number ki power 0 hamesha 1 hoti hai (x^0 = 1).
- Agar base case n == 1 par return x rakhoge, toh agar kisi ne directly n = 0
  pass kiya (jaise 5^0), toh code crash ya galat result dega kyunki n = 0 handle
  hi nahi hua.
- n == 0 base case natural recursion terminal point hai:
  n = 1 par call aayegi -> solve(x, 0) call hoga -> wahan se 1.0 aayega ->
  odd rule lag kar 1.0 * 1.0 * x = x return ho jayega.
  Yani n == 0 rakhne se n = 0 aur n = 1 dono cases naturally solve ho jaate hain.
================================================================================
*/