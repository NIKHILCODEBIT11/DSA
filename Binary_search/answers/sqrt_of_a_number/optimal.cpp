#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BINARY SEARCH ON ANSWERS - SQRT):
   - Problem:
     Hume integer `n` ka integer square root (floor value) calculate karna hai 
     in O(log N) time bina kisi built-in function ke.

   - Monotonic Search Space (Binary Search on Answer kyun laga?):
     Socho agar hum answer range ko dekhein:
     Range: 1, 2, 3, 4, ... , n
     Har number ka square check karo:
     1*1 <= n  -> YES
     2*2 <= n  -> YES
     ...
     ans*ans <= n -> YES  (Last YES)
     (ans+1)*(ans+1) <= n -> NO (First NO)
     (ans+2)*(ans+2) <= n -> NO

     Yeh pattern hamesha [YES, YES, YES, ..., NO, NO, NO] hota hai!
     Yeh ek **Monotonic function** hai.
     Jab bhi condition monotonically change hoti hai, wahan Binary Search 
     lagakar last YES ya first NO dhundha ja sakta hai.

   - The Overflow Prevention Trick (`mid <= n / mid`):
     - Agar hum `mid * mid <= n` likhein, toh agar `mid` bada hua (jaise $10^5$), 
       toh `mid * mid` 32-bit int overflow kar jayega.
     - Isko mathematically transform kiya:
       $$mid \cdot mid \le n \iff mid \le \frac{n}{mid}$$
       Kyunki `mid >= 1` (handled `n = 0` separately), yeh division 100% safe hai 
       aur product overflow ka khatra zero ho jata hai!

   - Why Returning `high` Works (Opposite Polarity Concept):
     Jab Binary Search terminate hota hai (`low > high` condition par):
     - `low` hamesha boundary cross karke pehle "NO" (invalid zone: square > n) par khada hota hai.
     - `high` hamesha peeche aakar aakhri "YES" (valid zone: square <= n) par khada hota hai.
     Isliye alag se `ans` variable na rakh kar seedha `return high;` karna bhi 100% mathematically correct hai!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n < 0) return -1;` :
     Negative number check.
   - `if (n == 0) return 0;` :
     Zero handling. Yeh `mid <= n / mid` me Divide-by-Zero (`mid = 0`) exception se bachata hai.
   - `int low = 1, high = n;` :
     Possible answer search space set kiya (1 se n).
   - `int mid = low + (high - low) / 2;` :
     Standard overflow-safe midpoint calculation.
   - `if (mid <= n / mid)` :
     Valid candidate! Iska square `<= n` hai.
     `ans = mid;` save kiya aur aur bada candidate dhundhne ke liye right side move kiya: `low = mid + 1;`.
   - `else` :
     Number ka square `n` se bada hai (`mid * mid > n`).
     Yeh aur iske aage ke saare numbers reject ho gaye -> search range left shrink ki: `high = mid - 1;`.
   - `return ans;` (ya `return high;`) :
     Final largest integer floor value return ho jati hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Input: n = 28  (Expected floor(sqrt(28)) = 5, kyunki 5*5 = 25 <= 28 aur 6*6 = 36 > 28)
   Initial State:
   low = 1, high = 28, ans = 1

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 28
   mid = 1 + (28 - 1) / 2 = 14
   Condition Check: mid <= n / mid
   => 14 <= 28 / 14 => 14 <= 2 -> FALSE! (14*14 = 196 > 28)
   Action:
     high = mid - 1 = 13
   State: low = 1, high = 13, ans = 1

   --- Iteration 2 ---
   low = 1, high = 13
   mid = 1 + (13 - 1) / 2 = 7
   Condition Check: mid <= n / mid
   => 7 <= 28 / 7 => 7 <= 4 -> FALSE! (7*7 = 49 > 28)
   Action:
     high = mid - 1 = 6
   State: low = 1, high = 6, ans = 1

   --- Iteration 3 ---
   low = 1, high = 6
   mid = 1 + (6 - 1) / 2 = 3
   Condition Check: mid <= n / mid
   => 3 <= 28 / 3 => 3 <= 9 -> TRUE! (3*3 = 9 <= 28)
   Action:
     ans = mid = 3 (Candidate saved)
     low = mid + 1 = 4 (Right jao aur bada number dhundhne)
   State: low = 4, high = 6, ans = 3

   --- Iteration 4 ---
   low = 4, high = 6
   mid = 4 + (6 - 4) / 2 = 5
   Condition Check: mid <= n / mid
   => 5 <= 28 / 5 => 5 <= 5 -> TRUE! (5*5 = 25 <= 28)
   Action:
     ans = mid = 5 (Better candidate saved)
     low = mid + 1 = 6
   State: low = 6, high = 6, ans = 5

   --- Iteration 5 ---
   low = 6, high = 6
   mid = 6 + (6 - 6) / 2 = 6
   Condition Check: mid <= n / mid
   => 6 <= 28 / 6 => 6 <= 4 -> FALSE! (6*6 = 36 > 28)
   Action:
     high = mid - 1 = 5
   State: low = 6, high = 5, ans = 5

   --- Termination ---
   low <= high (6 <= 5) -> FALSE!
   Notice the pointers at termination:
   low = 6  (First invalid answer: 6*6 = 36 > 28)
   high = 5 (Last valid answer: 5*5 = 25 <= 28)
   ans = 5
   
   Whether you return `ans` or `high`, both give 5!

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(log2 N) in all cases.
     * Search space har step me aadhi ho rahi hai: N -> N/2 -> N/4 -> ... -> 1.
       For n = 10^9, binary search maximum 30 iterations me khatam ho jayega!
   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables (`low`, `high`, `mid`, `ans`) 
       use hue hain. Memory bilkul constant hai.
======================================================================
*/

int sqrt_of_a_number(int n){
    if (n < 0) return -1; // Edge case: negative numbers
    if (n == 0) return 0; // Handled separately to allow safe division starting at 1

    int ans=1;
    int low=1,high=n;
    while(low<=high){
        // long long mid=(low+high)/2;             // It is useful but even long long has capacity til     9*(10)^18    for which i should use :-
        int mid=low+(high-low)/2;

        // if(mid*mid<=n){                  // It is useful but even long long has capacity til     9*(10)^18    for which i should use :-
        if(mid<=n/mid){    
            ans=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return ans;         // I can also return    "high"
}

int main(){
    int n;
    cout<<"Enter value :- ";
    cin>>n;
    cout<<"The floor value of sqrt of "<<n<<" is "<<sqrt_of_a_number(n);
    return 0;
}

// Explaination for returning "high"

/*

Instead of returning "ans" i can also return "high" as "high" is the first index which has possible answer and "low" is the
first index where answer is not possible.


EXPLAINATION :-

After binary search ends,
high points to the largest value that satisfies the condition
and low points to the first value that violates it.

So returning high gives the same result as ans.

n = 10
floor(sqrt(10)) = 3

Binary search trace
low	high	mid	mid*mid <= 10	action
0	10	5	❌ (25 > 10)	high = 4
0	4	2	✅ (4 ≤ 10)	low = 3
3	4	3	✅ (9 ≤ 10)	low = 4
4	4	4	❌ (16 > 10)	high = 3

*/