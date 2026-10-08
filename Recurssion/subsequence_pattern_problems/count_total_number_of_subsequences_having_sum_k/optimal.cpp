#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (COUNT SUBSEQUENCES WITH SUM K):
   - Problem:
     Hume di gayi array 'arr' me se aise subsequences ka total COUNT nikalna hai
     jinka sum exactly 'k' ke barabar ho.
     Elements ko print nahi karna, sirf total number of ways (ginti) return karni hai.

   - Kyun koi data structure (ds) pass nahi kiya?
     Jab sirf count chahiye hota hai, tab elements ko store karne ki zaroorat nahi hoti.
     Hume sirf yeh track karna hai ki elements ko pick/not-pick karke current 'sum' kya ban raha hai.
     Isse vector creation aur push/pop ka extra memory overhead bach jata hai.

   - Counting via Recursion (Base Case & Combination):
     * Jab index == n pahunchte hain (array traverse ho chuki hai):
       - Agar sum == k match ho gaya -> return 1 (ek valid subsequence mil gaya).
       - Agar sum != k hai -> return 0 (yeh rasta invalid hai).
     * Har state par do recursive branches hain:
       - left: element ko PICK karke aage se kitne valid combinations mile.
       - right: element ko NOT PICK karke aage se kitne valid combinations mile.
     * Dono branches ke answers ko add karke upar bhejna hai: return left + right;

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- total_number_of_subsequences(index, arr, n, sum, k) ---
   - if(index == n):
     Base case:
     - if(sum == k) return 1; : Target match hua, return 1 to parent frame.
     - return 0; : Target match nahi hua, return 0 to parent frame.
   - sum += arr[index]; :
     PICK choice: Element ko current running sum me add kiya.
   - int left = total_number_of_subsequences(index + 1, ...); :
     Call left branch (Pick). Is stack frame ka apna alag 'left' variable hai.
   - sum -= arr[index]; :
     BACKTRACK: Sum ko restore kiya taaki Not Pick branch clean state me chale.
   - int right = total_number_of_subsequences(index + 1, ...); :
     Call right branch (Not Pick). Is stack frame ka apna alag 'right' variable hai.
   - return left + right; :
     Dono branches se mile counts ko sum karke parent frame ko return kiya.

======================================================================
3. DETAILED DRY RUN (arr = {1, 1, 1}, k = 2, n = 3):

   Initial: index = 0, sum = 0

   --- Level 0: arr[0] = 1 ---
   Pick 1 -> sum = 1
   Call F(index=1, sum=1)

      --- Level 1: arr[1] = 1 ---
      Pick 1 -> sum = 2
      Call F(index=2, sum=2)

         --- Level 2: arr[2] = 1 ---
         Pick 1 -> sum = 3
         Call F(index=3, sum=3)
           - index == 3, sum (3) != 2 -> returns 0

         Backtrack: sum = 2
         Not Pick 1 -> Call F(index=3, sum=2)
           - index == 3, sum (2) == 2 -> returns 1

         Level 2 Result: left = 0, right = 1 -> returns (0 + 1) = 1

      Level 1 (Pick branch) receives: left = 1
      Backtrack: sum = 1
      Not Pick 1 -> Call F(index=2, sum=1)

         --- Level 2: arr[2] = 1 ---
         Pick 1 -> sum = 2
         Call F(index=3, sum=2)
           - index == 3, sum (2) == 2 -> returns 1

         Backtrack: sum = 1
         Not Pick 1 -> Call F(index=3, sum=1)
           - index == 3, sum (1) != 2 -> returns 0

         Level 2 Result: left = 1, right = 0 -> returns (1 + 0) = 1

      Level 1 receives: right = 1
      Level 1 Result: left = 1, right = 1 -> returns (1 + 1) = 2

   Level 0 (Pick branch) receives: left = 2
   Backtrack: sum = 0
   Not Pick 1 -> Call F(index=1, sum=0)

      --- Level 1: arr[1] = 1 ---
      Pick 1 -> sum = 1
      Call F(index=2, sum=1)

         --- Level 2: arr[2] = 1 ---
         Pick 1 -> sum = 2
         Call F(index=3, sum=2)
           - index == 3, sum (2) == 2 -> returns 1

         Backtrack: sum = 1
         Not Pick 1 -> Call F(index=3, sum=1)
           - index == 3, sum (1) != 2 -> returns 0

         Level 2 Result: left = 1, right = 0 -> returns (1 + 0) = 1

      Level 1 receives: left = 1
      Backtrack: sum = 0
      Not Pick 1 -> Call F(index=2, sum=0)

         --- Level 2: arr[2] = 1 ---
         Pick 1 -> sum = 1
         Call F(index=3, sum=1)
           - index == 3, sum (1) != 2 -> returns 0

         Backtrack: sum = 0
         Not Pick 1 -> Call F(index=3, sum=0)
           - index == 3, sum (0) != 2 -> returns 0

         Level 2 Result: left = 0, right = 0 -> returns (0 + 0) = 0

      Level 1 receives: right = 0
      Level 1 Result: left = 1, right = 0 -> returns (1 + 0) = 1

   Level 0 receives: right = 1
   Level 0 Result: left = 2, right = 1 -> returns (2 + 1) = 3

   Console Output:
   The total number of sequences that can be formed are 3

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Har index par exactly 2 branches banti hain (Pick and Not Pick).
     * Total recursive calls = 2^0 + 2^1 + ... + 2^n = 2^(n+1) - 1 = O(2^n).
     * Har base case par O(1) operations hote hain.
     * Total Time Complexity: O(2^n).

   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n).
       Maximum call stack depth 'n' tak hi jaati hai (index 0 se lekar index n tak).
     * Koi extra heap array ya vector use nahi hua hai, isliye auxiliary data space O(1) hai.
     * Total Space Complexity: O(n).
======================================================================
*/

int total_number_of_subsequences(int index, vector <int> &arr, int n, int sum, int k){
    if(index == n){
        if(sum == k){
            return 1;
        }
        return 0;
    }

    sum += arr[index];
    int left = total_number_of_subsequences(index + 1, arr, n, sum, k);

    sum -= arr[index];
    int right = total_number_of_subsequences(index + 1, arr, n, sum, k);

    return left + right;
}

int main() {
    vector<int> arr = {1, 1, 1};
    int sum = 0;
    int k = 2;
    // Root Node: index 0, khali jhola
    int ans = total_number_of_subsequences(0, arr, arr.size(), sum, k);
    cout<<"The total number of sequences that can be formed are "<<ans;

    return 0;
}

