#include <iostream>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (OPTIMIZED LINEAR SCAN UP TO SQRT(N)):
   - Problem:
     Hume ek non-negative integer `n` ka integer square root (floor value) calculate karna hai.
     Agar `n` perfect square nahi hai (jaise 39), toh greatest integer `ans` return karna hai 
     jiska square `<= n` ho (matlab floor value, jaise floor(sqrt(39)) = 6).

   - Key Improvement Over Previous Codes:
     Pichle codes me loop condition `i <= n` thi, jisse loop bina wajah N tak chalta tha.
     Yahan loop condition seedhe `i * i <= n` kar di gayi hai!
     - Intuition: Hume aage jane ki zaroorat hi nahi hai jab number ka square `n` ko cross kar jaye.
     - Jaise hi pehla aisa `i` aayega jiska square `> n` ho, loop condition automatically FALSE 
       ho jayegi aur loop wahi ruk jayega!
     - Result: Extra iterations eliminate ho gaye bina kisi explicit `break` statement ke.

   - `long long` Usage (Integer Overflow Protection):
     Loop variable ko `long long i` banaya gaya hai. 
     Agar standard `int i` hota aur `n` integer ki max limit ke kareeb hota, 
     toh `i * i` calculate karte waqt 32-bit signed integer overflow ho kar negative ban sakta tha. 
     `long long` use karne se product safe rehta hai (up to ≈ 9 * 10^18).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n < 0) return -1;` :
     Guard clause. Negative numbers ka real square root possible nahi hai.
   - `int ans = 0;` :
     Clean initialization. Default answer 0 set kiya (handles n = 0 perfectly).
   - `for (long long i = 0; i * i <= n; i++)` :
     Condition check: Jab tak `i` ka square `n` ke barabar ya chhota hai, tab tak loop chalega.
     Jaise hi `i * i > n` hoga, loop naturally terminate ho jayega.
   - `ans = i;` :
     Har valid candidate jo condition pass karega, wo latest floor value ban jayega. 
     Aakhri valid value hi humara final answer hogi.
   - `return ans;` :
     Loop rukne ke baad maximum valid integer `ans` return ho jayega.

======================================================================
3. DETAILED DRY RUN:

   Input: n = 39
   Initial State: ans = 0

   -------------------------------------------------------------------
   STEP-BY-STEP TRACE:
   -------------------------------------------------------------------
   i = 0: 0 * 0 = 0   <= 39 -> TRUE  | ans = 0
   i = 1: 1 * 1 = 1   <= 39 -> TRUE  | ans = 1
   i = 2: 2 * 2 = 4   <= 39 -> TRUE  | ans = 2
   i = 3: 3 * 3 = 9   <= 39 -> TRUE  | ans = 3
   i = 4: 4 * 4 = 16  <= 39 -> TRUE  | ans = 4
   i = 5: 5 * 5 = 25  <= 39 -> TRUE  | ans = 5
   i = 6: 6 * 6 = 36  <= 39 -> TRUE  | ans = 6  <-- Maximum valid floor sqrt
   i = 7: 7 * 7 = 49  <= 39 -> FALSE | Condition fails, loop terminates immediately!

   Loop Terminated at i = 7.
   Total iterations executed: Only 7 (compared to 40 in previous code!).
   Returns ans = 6.
   Output: "The sqrt of the number is 6"

   -------------------------------------------------------------------
   BOUNDARY CASES:
   - n = 0:
     i = 0: 0 * 0 <= 0 -> TRUE  | ans = 0
     i = 1: 1 * 1 <= 0 -> FALSE | loop exits. Returns 0 (Correct).
   - n = 1:
     i = 0: 0 * 0 <= 1 -> TRUE  | ans = 0
     i = 1: 1 * 1 <= 1 -> TRUE  | ans = 1
     i = 2: 2 * 2 <= 1 -> FALSE | loop exits. Returns 1 (Correct).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(sqrt(N)) in all non-negative cases.
     * Kyun? Kyunki loop sirf `i = 0` se lekar `i = floor(sqrt(n)) + 1` tak hi chal raha hai.
       For n = 39, loop sirf 7 steps chala. For n = 10^6, loop sirf 1000 steps chalega 
       (pichle code ke 10^6 steps ke muqable bohot fast).
   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf do primitive scalar variables (`ans`, `i`) 
       use hue hain. Extra memory bilkul constant hai.
======================================================================
*/

int sqrt_of_a_number(int n) {
    if (n < 0) return -1;

    int ans = 0;
    for (long long i = 0; i * i <= n; i++) {
        ans = i;
    }
    return ans;
}

int main() {
    int n = 39;
    cout << "The sqrt of the number is " << sqrt_of_a_number(n) << "\n";
    return 0;
}