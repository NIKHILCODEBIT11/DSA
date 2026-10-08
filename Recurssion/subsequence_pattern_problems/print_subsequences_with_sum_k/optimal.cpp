#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SUBSEQUENCES WITH SUM K):
   - Problem:
     Hume ek array 'arr' di gayi hai (e.g. {1, 2, 1}) aur ek target 'k = 2'.
     Hume wo saare subsequences print karne hain jinka sum exactly 'k' ke barabar ho.

   - Pick / Not Pick + Rolling Sum:
     Ye standard subsequence generation ka hi extension hai.
     Farak bas itna hai ki hum har element ko pick/not-pick karte waqt 
     ek variable 'sum' ko track karte hain:
     
     1. Choice 1 (PICK):
        - Element ko jhole me daalo: `ds.push_back(arr[index])`
        - Current sum badhao: `sum += arr[index]`
        - Agle index par explore karo: `subsequences_with_sum_k(index + 1, ...)`
        
     2. Backtrack (UNDO):
        - Jhole se element nikalo: `ds.pop_back()`
        - Sum ko wapas restore karo: `sum -= arr[index]`
        
     3. Choice 2 (NOT PICK):
        - Bina is element ko liye agle index par explore karo:
          `subsequences_with_sum_k(index + 1, ...)`

   - Base Case & Filtering:
     Jab `index == n` pahunche:
     - Check karo: kya `sum == k` hai?
     - Agar HAAN: toh 'ds' ke andar jo numbers hain unka sum target match kar gaya! Print it!
     - Agar NAHI: toh chupchap return ho jao bina print kiye.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- subsequences_with_sum_k(index, ds, arr, n, sum, k) ---
   - if(index == n):
     Base case: Poori array scan ho chuki hai.
     - if(sum == k):
       Target sum match hua, valid subsequence print kiya.
     - return;
       Recursion stack unwind karne ke liye return.
   - ds.push_back(arr[index]); sum += arr[index]; :
     PICK: Element jhole me add hua aur rolling sum increase hua.
   - subsequences_with_sum_k(index + 1, ...); :
     EXPLORE: Picked element ke sath aage ke combinations check kiye.
   - ds.pop_back(); sum -= arr[index]; :
     BACKTRACK: Dono modifications undo kiye taaki Right Branch clean rahe.
   - subsequences_with_sum_k(index + 1, ...); :
     NOT PICK: Element ko chhodkar aage ke combinations check kiye.

======================================================================
3. DETAILED DRY RUN (arr = {1, 2, 1}, k = 2, n = 3):

   Initial: index = 0, ds = {}, sum = 0

   --- Level 0: arr[0] = 1 ---
   Pick 1: ds = {1}, sum = 1
   Call F(index=1, sum=1)

      --- Level 1: arr[1] = 2 ---
      Pick 2: ds = {1, 2}, sum = 3
      Call F(index=2, sum=3)

         --- Level 2: arr[2] = 1 ---
         Pick 1: ds = {1, 2, 1}, sum = 4
         Call F(index=3, sum=4)
           - index == 3, sum (4) != 2 -> No print -> return

         Backtrack: ds = {1, 2}, sum = 3
         Not Pick 1:
         Call F(index=3, sum=3)
           - index == 3, sum (3) != 2 -> No print -> return

      Backtrack: ds = {1}, sum = 1
      Not Pick 2:
      Call F(index=2, sum=1)

         --- Level 2: arr[2] = 1 ---
         Pick 1: ds = {1, 1}, sum = 2
         Call F(index=3, sum=2)
           - index == 3, sum (2) == 2 -> MATCH!
           - PRINT: (1  1 ) -> return

         Backtrack: ds = {1}, sum = 1
         Not Pick 1:
         Call F(index=3, sum=1)
           - index == 3, sum (1) != 2 -> No print -> return

   Backtrack: ds = {}, sum = 0
   Not Pick 1:
   Call F(index=1, sum=0)

      --- Level 1: arr[1] = 2 ---
      Pick 2: ds = {2}, sum = 2
      Call F(index=2, sum=2)

         --- Level 2: arr[2] = 1 ---
         Pick 1: ds = {2, 1}, sum = 3
         Call F(index=3, sum=3)
           - index == 3, sum (3) != 2 -> No print -> return

         Backtrack: ds = {2}, sum = 2
         Not Pick 1:
         Call F(index=3, sum=2)
           - index == 3, sum (2) == 2 -> MATCH!
           - PRINT: (2 ) -> return

      Backtrack: ds = {}, sum = 0
      Not Pick 2:
      Call F(index=2, sum=0)

         --- Level 2: arr[2] = 1 ---
         Pick 1: ds = {1}, sum = 1
         Call F(index=3, sum=1)
           - index == 3, sum (1) != 2 -> No print -> return

         Backtrack: ds = {}, sum = 0
         Not Pick 1:
         Call F(index=3, sum=0)
           - index == 3, sum (0) != 2 -> No print -> return

   Final Output:
   (1  1 )
   (2 )

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Har index par 2 options hain (Pick ya Not Pick).
     * Total recursive function calls: 2^n.
     * Base case me valid match hone par print karne me worst case O(n) lagta hai.
     * Total Time Complexity: O(n * 2^n).

   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n) (Maximum depth = n).
     * Working Buffer Memory: O(n) for the shared vector 'ds'.
     * Total Space Complexity: O(n).
======================================================================
*/

void subsequences_with_sum_k(int index, vector <int> &ds, vector <int> &arr, int n, int sum, int k){
    if(index == n){
        if(sum == k){
            cout<<"(";
            for(int num : ds){
                cout<<num<<"\t";
            }
            cout<<")";
        }
        return;
    }

    ds.push_back(arr[index]);
    sum += arr[index];
    subsequences_with_sum_k(index + 1, ds, arr, n, sum, k);

    ds.pop_back();
    sum -= arr[index];
    subsequences_with_sum_k(index + 1, ds, arr, n, sum, k);
}

int main() {
    vector<int> arr = {1, 2, 1};
    vector<int> ds;
    int k = 2;
    int sum = 0;

    // Root Node: index 0, khali jhola
    subsequences_with_sum_k(0, ds, arr, arr.size(), sum, k);

    return 0;
}