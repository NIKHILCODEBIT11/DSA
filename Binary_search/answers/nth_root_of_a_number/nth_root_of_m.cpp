#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS:
   - Problem:
     Hume do numbers diye hain: target m aur power n.
     Hume ek aisa integer x nikalna hai jiske liye:
         x^n == m
     Agar aisa exact integer exist nahi karta, toh return karna hai -1.

   - Monotonic Search Space (Binary Search kyun lagega?):
     Possible answer hamesha 1 se lekar m ke beech hi hoga (range: 1 to m).
     Jaise jaise number badhega, uska power n bhi hamesha badhega:
     - Agar mid^n < m  -> Iska matlab mid chhota hai, hume bada number chahiye -> right jao (low = mid + 1).
     - Agar mid^n > m  -> Iska matlab mid bohot bada hai, chhota number chahiye -> left jao (high = mid - 1).
     - Agar mid^n == m -> Exact answer mil gaya!

   - pow() Function Kyun Use Nahi Kiya? (The Overflow & Precision Trap):
     1. Precision Problem: pow() doubles par kaam karta hai. Badi values me floating point
        inaccuracy ki wajah se result galat convert ho sakta hai.
     2. Integer Overflow: Agar mid = 100 aur n = 10 ho, toh 100^10 = 10^20 ban jayega.
        Yeh standard 64-bit long long (max limit ~ 9 * 10^18) ko bhi overflow kar dega!
     
     Solution (Step-by-Step Check with Early Break):
     Number ko loop me ek-ek karke n baar multiply karo.
     Jaise hi kisi step pe product m se bada ho jaye (ans > m), aage multiply karna
     bewakoofi hai. Wahi ruk jao aur seedhe return 2 kar do (too large).
     Isse overflow ka risk 0 ho jata hai!

   - 3-State Return Flags:
     power_calculation function 3 values deta hai:
     - Return 1: mid^n == m (Exact integer root mil gaya)
     - Return 0: mid^n < m  (mid chhota hai, aage badho)
     - Return 2: mid^n > m  (mid bada hai, peeche aao)

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- power_calculation(mid, m, n) ---
   - long long ans = 1; : Product track karne ke liye variable.
   - for(int i = 1; i < n + 1; i++) : mid ko n baar aapas me multiply karega.
   - ans = ans * mid; : Ek-ek karke multiply kiya.
   - if(ans > m) return 2; : EARLY EXIT. Jaise hi ans m se aage nikla, guaranteed hai
     ki aage chal kar bhi mid^n > m hi rahega. Isliye aage multiply kiye bina 2 return kiya.
   - if(ans == m) return 1; : Loop khatam hone ke baad exact target match ho gaya.
   - return 0; : Loop pura chalne ke baad bhi ans m se chhota reh gaya (mid^n < m).

   --- nth_root(m, n) ---
   - int low = 1, high = m; : Answer ki search boundary 1 se m tak set ki.
   - int mid = low + (high - low) / 2; : Safe midpoint calculation jo overflow nahi hota.
   - if(midn == 1) return mid; : Exact root match, return answer.
   - else if(midn == 0) low = mid + 1; : mid^n chhota hai, toh search space ko right half shift kiya.
   - else high = mid - 1; : mid^n bada hai (midn == 2), toh search space ko left half shift kiya.
   - return -1; : Agar loop low > high ho kar ruk gaya aur koi integer nahi mila, toh -1 return karo.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Input: m = 27, n = 3 (Target: 3rd root of 27 -> Expected Output: 3)
   Initial Boundary: low = 1, high = 27

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 27
   mid = 1 + (27 - 1) / 2 = 14

   Call: power_calculation(mid = 14, m = 27, n = 3)
     i = 1: ans = 1 * 14 = 14   (14 > 27 ? False)
     i = 2: ans = 14 * 14 = 196 (196 > 27 ? TRUE! -> Return 2 immediately)
   
   Action in nth_root():
     midn = 2 (14^3 > 27) -> Left jao
     high = mid - 1 = 13
   State updated: low = 1, high = 13

   --- Iteration 2 ---
   low = 1, high = 13
   mid = 1 + (13 - 1) / 2 = 7

   Call: power_calculation(mid = 7, m = 27, n = 3)
     i = 1: ans = 1 * 7 = 7    (7 > 27 ? False)
     i = 2: ans = 7 * 7 = 49   (49 > 27 ? TRUE! -> Return 2 immediately)

   Action in nth_root():
     midn = 2 (7^3 > 27) -> Left jao
     high = mid - 1 = 6
   State updated: low = 1, high = 6

   --- Iteration 3 ---
   low = 1, high = 6
   mid = 1 + (6 - 1) / 2 = 3

   Call: power_calculation(mid = 3, m = 27, n = 3)
     i = 1: ans = 1 * 3 = 3    (3 > 27 ? False)
     i = 2: ans = 3 * 3 = 9    (9 > 27 ? False)
     i = 3: ans = 9 * 3 = 27   (27 > 27 ? False)
     Loop ends!
     Check: ans == m (27 == 27) -> TRUE! -> Return 1

   Action in nth_root():
     midn = 1 (Exact match!)
     return mid -> return 3.

   Final Output: "The 3th root of 27 is 3"

   -------------------------------------------------------------------
   TRACE FOR NON-EXISTENT CASE: m = 20, n = 2 (No integer square root)
   - mid = 10 -> 10^2 = 100 > 20 -> high = 9
   - mid = 5  -> 5^2 = 25 > 20   -> high = 4
   - mid = 2  -> 2^2 = 4 < 20    -> low = 3
   - mid = 4  -> 4^2 = 16 < 20   -> low = 5
   - mid = 4, low = 5, high = 4  -> low > high (5 > 4) -> Loop Terminate!
   - Returns -1 (Correct).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Binary Search space [1, m] me travel karta hai, jisme lagte hain O(log2 m) steps.
     * Har step par power_calculation function maximum n steps tak chal sakta hai.
     * Total Worst Case Time Complexity: O(n * log2 m).
     * Note: early exit (ans > m) hone ki wajah se practical average time
       n se bohot kam steps me execute ho jata hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables (low, high, mid, ans, i)
       use hue hain. Extra memory bilkul constant hai.
======================================================================
*/

int power_calculation(int mid,int m,int n){
    long long ans=1;
    for(int i=1;i<n+1;i++){
        ans=ans*mid;
        if(ans>m){     // The case where ans > m suppose i have to find 10th root of 27 and after some iterations i got ans=3 where mid^n starts coming close to m, but 3^10 is already large than 27 then no use of moving ahead
            return 2;
        }
    }
    if(ans==m){         // The case where ans matches to target m
        return 1;
    }
    return 0;
}
int nth_root(int m,int n){
    int low=1,high=m;
    while(low<=high){
        int mid=low+(high-low)/2;
        
        int midn=power_calculation(mid,m,n);        // It calculates    (m)^n
        if(midn==1){
            return mid;
        }
        else if(midn==0){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}


/*
GOAL:
-----
Find the integer n-th root of a given number m.
That is, find an integer x such that:
    x^n == m
If no such integer exists, return -1.

APPROACH:
---------
We use Binary Search because:
- The possible answer range is from 1 to m
- If x^n < m, we need a larger x
- If x^n > m, we need a smaller x
This monotonic behavior allows binary search.

There are two main parts:

1) func(mid, m, n):
-------------------
This helper function compares mid^n with m safely.

- We compute mid^n step-by-step using a loop instead of pow()
  to avoid floating-point inaccuracies and overflow.
- While multiplying, we check:
    - If ans > m:
        We immediately stop because further multiplication
        will only increase the value (mid >= 1).
        Hence mid^n will definitely be greater than m.
        We return 2 (mid is too large).
    - If ans == m:
        We found the exact n-th root, return 1.
- If the loop ends and ans < m:
    mid^n is smaller than m, return 0.

Return values meaning:
    1 -> mid^n == m (perfect root found)
    0 -> mid^n < m  (mid is too small)
    2 -> mid^n > m  (mid is too large)

2) nth_root(m, n):
------------------
- We perform binary search in the range [1, m].
- For each mid, we call func(mid, m, n).
- Based on the result:
    - If func returns 1, mid is the answer.
    - If func returns 0, move right (low = mid + 1).
    - If func returns 2, move left (high = mid - 1).
- If binary search finishes without finding a match,
  return -1 (no integer n-th root exists).

WHY ans > m CHECK IS IMPORTANT:
-------------------------------
- Prevents unnecessary computations
- Avoids integer overflow
- Improves performance
- Allows early termination when mid is too large

TIME & SPACE COMPLEXITY:
------------------------
Time Complexity:
    O(n * log m)
    - log m from binary search
    - n from power calculation

Space Complexity:
    O(1) (constant extra space)
*/


int main(){
    int target,n;
    cout<<"Enter target value :- ";
    cin>>target;
    cout<<"Enter n :- ";
    cin>>n;
    cout<<"The "<<n<<"th root of "<<target<<" is "<<nth_root(target,n);
    return 0;
}


