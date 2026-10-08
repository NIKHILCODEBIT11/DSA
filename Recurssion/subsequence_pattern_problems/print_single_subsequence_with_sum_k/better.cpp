#include<bits/stdc++.h>
using namespace std;
/*
======================================================================
1. INTUITION & THOUGHT PROCESS (PRINT ONLY ONE SUBSEQUENCE WITH SUM K):
   - Problem:
     Pehle wale question me hume sum = k wale SAARE subsequences print karne the.
     Lekin is question me hume SIRF PEHLA (ANY ONE) valid subsequence print karna hai,
     aur uske baad bache hue saare combinations ko ignore karna hai.

   - Global Flag Approach (Your Code):
     1. Ek global boolean variable `flag = false` rakha.
     2. Recursion poora 2^n tree explore karta rahega standard pick/not-pick se.
     3. Jaise hi pehla match milta hai (`sum == k && flag == false`):
        - `flag = true` mark ho gaya.
        - Wo subsequence print ho gaya.
     4. Aage chalte hue baaki valid subsequences (`(2 )`) base case par aayenge zaroor,
        lekin kyunki `flag == true` ho chuka hai, `flag == false` wali condition fail ho jayegi
        aur wo print nahi honge!

   - Optimization Insight (Early Pruning via Boolean Return):
     Abhi wale code me `flag` lagane se output toh ek hi aata hai, lekin recursion tree
     khatam nahi hota — wo 2^n calls poori explore karta hai.
     Agar function ka return type `bool` kar dein:
       - `if (call == true) return true;`
     Toh jaise hi pehla answer milega, recursion wahi se seedha terminate ho jayega
     aur bache hue aadhe se zyada tree ko explore karne ka time bach jayega!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - bool flag = false; :
     Global state tracker. False ka matlab abhi tak koi valid subsequence print nahi hua.
   - if(index == n) :
     Base case: Array poori traverse ho chuki hai.
   - if(sum == k && flag == false) :
     Pehla valid match pakda!
     `flag = true;` karte hi darwaza band ho gaya, ab koi doosra subsequence print nahi ho sakta.
   - ds.push_back(arr[index]); sum += arr[index]; :
     PICK choice: Element add kiya aur sum update kiya.
   - ds.pop_back(); sum -= arr[index]; :
     BACKTRACK: Element nikala aur sum wapas subtract kiya.
   - print_single_subsequence_with_sum_k(index + 1, ...); :
     NOT PICK choice: Element ko bina liye aage explore kiya.

======================================================================
3. DETAILED DRY RUN (arr = {1, 2, 1}, k = 2, n = 3):

   Initial: flag = false, ds = {}, sum = 0

   --- Step 1: index 0 (arr[0] = 1) -> PICK 1 ---
   ds = {1}, sum = 1
   Call index 1

   --- Step 2: index 1 (arr[1] = 2) -> PICK 2 ---
   ds = {1, 2}, sum = 3
   Call index 2

   --- Step 3: index 2 (arr[2] = 1) -> PICK 1 ---
   ds = {1, 2, 1}, sum = 4
   Call index 3 (Base Case):
     index == 3, sum (4) != 2 -> No print -> return

   Backtrack: ds = {1, 2}, sum = 3
   Not Pick 1 -> Call index 3:
     index == 3, sum (3) != 2 -> No print -> return

   Backtrack: ds = {1}, sum = 1
   --- Step 4: index 1 -> NOT PICK 2 ---
   Call index 2 (with ds = {1}, sum = 1)

   --- Step 5: index 2 (arr[2] = 1) -> PICK 1 ---
   ds = {1, 1}, sum = 2
   Call index 3 (Base Case):
     index == 3, sum (2) == 2 AND flag == false -> TRUE!
     flag = true; (FLAG AB TRUE HO CHUKA HAI!)
     PRINT: (1  1 )
     return

   --- Step 6: Remaining Tree (Flag Protection) ---
   Aage jakar jab `arr[1] = 2` akele pick hoga:
   ds = {2}, sum = 2, index = 3 par aayega:
     Check: sum == 2 (True), lekin flag == false -> FALSE (kyunki flag true hai)!
     Print block skip ho gaya!
   
   Final Output on Screen:
   (1  1 )

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(n * 2^n).
     * Kyunki flag sirf print hone se rokta hai, recursive tree poora 2^n nodes tak
       traverse hota hi hai.
   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n).
     * Working Buffer Memory: O(n) for vector 'ds'.
     * Total Space Complexity: O(n).
======================================================================
*/

// is case mein bhale hi pehla wala subsequence jiska sum 2 hai wo print ho raha lekin phir bhi recursion to complete ho hi rahi agar mujhe pehla match milte hi recursion rokna hai to uske liye better_2.cpp dekho


bool flag = false;   // global variable use kar raha isko avoid karke function all karte hue hi kiase karenge ye optimal.cpp mein hai
void print_single_subsequence_with_sum_k(int index, vector <int> &ds, vector <int> &arr, int sum, int n, int k){
    if(index == n){
        if(sum == k && flag == false){
            flag = true;
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
    print_single_subsequence_with_sum_k(index + 1, ds, arr, sum, n, k);

    ds.pop_back();
    sum -= arr[index];
    print_single_subsequence_with_sum_k(index + 1, ds, arr, sum, n, k);

}

int main() {
    vector<int> arr = {1, 2, 1};
    vector<int> ds;
    int k = 2;
    int sum = 0;

    // Root Node: index 0, khali jhola
    print_single_subsequence_with_sum_k(0, ds, arr, sum, arr.size(), k);

    return 0;
}