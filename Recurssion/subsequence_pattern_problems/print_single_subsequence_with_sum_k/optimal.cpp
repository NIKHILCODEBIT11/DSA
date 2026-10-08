#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (EARLY PRUNING VIA BOOLEAN RETURN):
   - Problem:
     Hume array 'arr' me se koi bhi EK aisa subsequence print karna hai 
     jiska sum exactly 'k' ke barabar ho. 
     Jaise hi pehla valid subsequence mil jaye, aage ki saari recursive
     calls turant terminate ho jani chahiye (time waste bachane ke liye).

   - Core Technique: "Boolean Flagged Recursion"
     * Base case me agar sum == k match ho gaya -> print karo aur `return true` karo.
     * Agar sum != k hai -> `return false` karo.
     * Pick branch ko call karte hi uske result ko check karo:
         if (call(index + 1) == true) return true;
       Iska matlab: "Agar mere left child ko answer mil gaya, toh main turant 
       apne parent ko true bhej kar exit kar jaunga. Na main pop_back karunga, 
       na main Not-Pick branch ko explore karunga!"
     * Not-pick branch tabhi execute hoti hai jab Pick branch se false aaye.

   - Total Work Saved:
     Global flag approach me poora 2^n tree traverse hota tha.
     Yahan jaise hi pehla solution milta hai, baaki bacha hua poora 
     subtree bypass ho jata hai!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- print_single_subsequence_with_sum_k(...) ---
   - if(index == n):
     Base case:
     - if(sum == k): Found answer! Print 'ds' and return true.
     - return false: Dead end, target not met.
   - ds.push_back(arr[index]); sum += arr[index]; :
     PICK: Include current element in running subset.
   - if(print_single_subsequence_with_sum_k(index + 1, ...) == true) return true; :
     EARLY EXIT GUARD 1: Left branch succeeded. Propagate true up the stack immediately.
   - ds.pop_back(); sum -= arr[index]; :
     BACKTRACK: Only executes if Pick branch returned false!
   - if(print_single_subsequence_with_sum_k(index + 1, ...) == true) return true; :
     EARLY EXIT GUARD 2: Right branch succeeded. Propagate true up the stack immediately.
   - return false; :
     Neither choice led to sum == k.

======================================================================
3. DETAILED CALL-BY-CALL DRY RUN (arr = {1, 2, 1}, k = 2, n = 3):

   --- Step 1: Root Call ---
   F(index=0, sum=0, ds={})
   * Pick arr[0]=1 -> ds={1}, sum=1
   * Calls F(1, sum=1, ds={1})

   --- Step 2: Inside F(1, sum=1) ---
   * Pick arr[1]=2 -> ds={1, 2}, sum=3
   * Calls F(2, sum=3, ds={1, 2})

   --- Step 3: Inside F(2, sum=3) ---
   * Pick arr[2]=1 -> ds={1, 2, 1}, sum=4
   * Calls F(3, sum=4, ds={1, 2, 1})
     - index == 3, sum (4) != 2 -> returns false!

   * Back in F(2, sum=3):
     - Pick call returned false.
     - Backtrack: pop 1 -> ds={1, 2}, sum=3.
     - Not Pick arr[2]=1: Calls F(3, sum=3, ds={1, 2})
       - index == 3, sum (3) != 2 -> returns false!
     - Dono branches false -> F(2, sum=3) returns false!

   --- Step 4: Back in F(1, sum=1) ---
   * Pick branch returned false.
   * Backtrack: pop 2 -> ds={1}, sum=1.
   * Not Pick arr[1]=2: Calls F(2, sum=1, ds={1})

   --- Step 5: Inside F(2, sum=1) ---
   * Pick arr[2]=1 -> ds={1, 1}, sum=2
   * Calls F(3, sum=2, ds={1, 1})
     - index == 3, sum (2) == 2 -> MATCH FOUND!
     - PRINTS: (1  1 )
     - Returns TRUE!

   --- Step 6: THE EARLY EXIT CASCADE (Chain Reaction) ---
   * Control returns to F(2, sum=1):
     - Pick call evaluated to TRUE:
       `if(print_single(...) == true) return true;`
     - Turant returns TRUE! (Not-pick branch completely skipped!)
   * Control returns to F(1, sum=1):
     - Not-pick call evaluated to TRUE:
       `if(print_single(...) == true) return true;`
     - Turant returns TRUE!
   * Control returns to F(0, sum=0):
     - Pick call evaluated to TRUE:
       `if(print_single(...) == true) return true;`
     - Turant returns TRUE!
   * Back in main():
     - Entire recursion stops!
     - Index 0 ka Not-Pick branch (jahan arr[1]=2 akele banta) KABHI RUN HI NAHI HUA!

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(k) / O(n) jab pehla hi path target sum de de.
     * Worst Case: O(n * 2^n) jab target sum exist hi na kare ya bilkul 
       aakhri leaf par mile.
     * Average Case: Significantly faster than standard 2^n because the entire 
       remaining recursion tree is discarded immediately upon the first success.

   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n) maximum depth.
     * Working Buffer Memory: O(n) for the shared vector 'ds'.
     * Total Space Complexity: O(n).
======================================================================
*/

bool print_single_subsequence_with_sum_k(int index, vector<int> &ds, vector<int> &arr, int sum, int n, int k){
    // Base Case
    if(index == n){
        if(sum == k){
            cout << "(";
            for(int num : ds){
                cout << num << "\t";
            }
            cout << ")\n";
            return true; // Match mil gaya! True bhej kar sabko roko!
        }
        return false;   // Target match nahi hua
    }

    // --- CHOICE 1: PICK ---
    ds.push_back(arr[index]);
    sum += arr[index];

    // Agar pick karne se aage answer mil gaya, toh yahin se return true!
    if(print_single_subsequence_with_sum_k(index + 1, ds, arr, sum, n, k) == true){
        return true; // Aage kuch bhi mat chalao, seedha exit!
    }

    // --- BACKTRACK ---
    ds.pop_back();
    sum -= arr[index];

    // --- CHOICE 2: NOT PICK ---
    // Agar pick karne se answer nahi mila, tabhi not-pick try karo
    if(print_single_subsequence_with_sum_k(index + 1, ds, arr, sum, n, k) == true){
        return true; // Yahan se answer mil gaya toh bhi exit!
    }

    // Agar na pick se mila na not-pick se, toh false return karo
    return false;
}

int main() {
    vector<int> arr = {1, 2, 1};
    vector<int> ds;
    int k = 2;
    int sum = 0;

    print_single_subsequence_with_sum_k(0, ds, arr, sum, arr.size(), k);

    return 0;
}