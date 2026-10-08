#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (PRINT ALL SUBSEQUENCES - PICK / NOT PICK PATTERN):
   - Problem:
     Hume ek array 'arr' di gayi hai (e.g. {3, 1, 2}). Hume iske saare 
     possible subsequences print karne hain.
     Subsequence ka matlab: array ke elements ka koi bhi subset jisme elements 
     ka relative order maintain rahe (contiguous hona zaroori nahi hai).

   - Core Logic: "The Pick / Not Pick (Include / Exclude) Choice":
     Array ke har element ke paas exactly do choices hoti hain:
     1. Choice 1 (PICK / TAKE):
        Element ko apne jhole ('ds') me daal lo (`ds.push_back(arr[index])`).
        Agle index ke liye explore karo: `print_subsequence(index + 1, ...)`.
     2. Backtrack & Choice 2 (NOT PICK / LEAVE):
        Jhole se us element ko bahar nikaal do (`ds.pop_back()`), taaki jhola 
        wapas pehle jaisa ho sake!
        Ab bina us element ke agle index ke liye explore karo: `print_subsequence(index + 1, ...)`.

   - Base Case:
     Jab `index == n` ho jaye, iska matlab hum array ke aakhri element ke baad 
     pahunch gaye hain (saare elements par decision liya ja chuka hai).
     Ab jhole ('ds') me jo bhi elements hain, wahi humara ek complete 
     subsequence banate hain. Unhe print karo aur return karke backtrack karo.

   - Total Subsequences:
     Har ek element ke paas 2 options hain (Pick ya Not Pick).
     Toh n elements ke liye total 2 * 2 * ... (n times) = 2^n subsequences bante hain.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- print_subsequence(index, ds, n, arr) ---
   - if(index == n):
     Base case: Array khatam ho gayi. 'ds' ke saare elements print karo aur return.
   - ds.push_back(arr[index]); :
     PICK CHOICE: Current element ko subsequence me include kiya.
   - print_subsequence(index + 1, ds, n, arr); :
     EXPLORE (LEFT BRANCH): Current element ko rakh kar aage ke elements explore kiye.
   - ds.pop_back(); :
     BACKTRACK (UNDO): Aakhri daala hua element hata diya taaki next branch clean rahe.
   - print_subsequence(index + 1, ds, n, arr); :
     NOT PICK CHOICE (RIGHT BRANCH): Current element ko bina liye aage explore kiya.

======================================================================
3. DETAILED DRY RUN (arr = {3, 1, 2}, n = 3):

   Initial Call: F(index=0, ds={})

   --- LEVEL 0: Index 0 (Element = 3) ---
   Pick 3: ds.push_back(3) -> ds = {3}
   Call F(1, {3})

      --- LEVEL 1: Index 1 (Element = 1) ---
      Pick 1: ds.push_back(1) -> ds = {3, 1}
      Call F(2, {3, 1})

         --- LEVEL 2: Index 2 (Element = 2) ---
         Pick 2: ds.push_back(2) -> ds = {3, 1, 2}
         Call F(3, {3, 1, 2})
           - index == 3 -> PRINT: (3  1  2 ) -> return

         Backtrack: ds.pop_back() -> 2 hata -> ds = {3, 1}
         Not Pick 2:
         Call F(3, {3, 1})
           - index == 3 -> PRINT: (3  1 ) -> return

      Backtrack: ds.pop_back() -> 1 hata -> ds = {3}
      Not Pick 1:
      Call F(2, {3})

         --- LEVEL 2: Index 2 (Element = 2) ---
         Pick 2: ds.push_back(2) -> ds = {3, 2}
         Call F(3, {3, 2})
           - index == 3 -> PRINT: (3  2 ) -> return

         Backtrack: ds.pop_back() -> 2 hata -> ds = {3}
         Not Pick 2:
         Call F(3, {3})
           - index == 3 -> PRINT: (3 ) -> return

   Backtrack: ds.pop_back() -> 3 hata -> ds = {}
   Not Pick 3:
   Call F(1, {})

      --- LEVEL 1: Index 1 (Element = 1) ---
      Pick 1: ds.push_back(1) -> ds = {1}
      Call F(2, {1})

         --- LEVEL 2: Index 2 (Element = 2) ---
         Pick 2: ds.push_back(2) -> ds = {1, 2}
         Call F(3, {1, 2})
           - index == 3 -> PRINT: (1  2 ) -> return

         Backtrack: ds.pop_back() -> 2 hata -> ds = {1}
         Not Pick 2:
         Call F(3, {1})
           - index == 3 -> PRINT: (1 ) -> return

      Backtrack: ds.pop_back() -> 1 hata -> ds = {}
      Not Pick 1:
      Call F(2, {})

         --- LEVEL 2: Index 2 (Element = 2) ---
         Pick 2: ds.push_back(2) -> ds = {2}
         Call F(3, {2})
           - index == 3 -> PRINT: (2 ) -> return

         Backtrack: ds.pop_back() -> 2 hata -> ds = {}
         Not Pick 2:
         Call F(3, {})
           - index == 3 -> PRINT: ( ) -> return (Empty Subsequence)

   Output sequence:
   (3  1  2 )
   (3  1 )
   (3  2 )
   (3 )
   (1  2 )
   (1 )
   (2 )
   ( )

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Har index par 2 recursive calls banti hain (Pick aur Not Pick).
     * Total recursive calls = 2^0 + 2^1 + 2^2 + ... + 2^n = 2^(n+1) - 1 = O(2^n).
     * Base case me vector 'ds' ke elements ko print karne me O(n) time lagta hai.
     * Total Time Complexity: O(n * 2^n).

   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n).
       Maximum tree depth 'n' tak hi jati hai (index 0 se index n).
     * Working Buffer Memory: O(n) for the shared vector 'ds'.
     * Total Space Complexity: O(n).
======================================================================
*/

void print_subsequence(int index, vector <int> &ds, int n, vector <int> &arr){
    if(index == n){
        cout<<"(";
        for(int num : ds){
            cout<<num<<"\t";
        }
        cout<<")";
        return;
    }

    ds.push_back(arr[index]);
    print_subsequence(index + 1, ds, n, arr);

    ds.pop_back();
    print_subsequence(index + 1, ds, n, arr);
}

int main() {
    vector<int> arr = {3, 1, 2};
    vector<int> ds;
    
    // Root Node: index 0, khali jhola
    print_subsequence(0, ds, arr.size(), arr);

    return 0;
}