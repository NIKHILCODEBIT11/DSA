#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (GENERATE ALL BINARY STRINGS OF LENGTH N):
   - Problem:
     Hume ek integer 'n' diya gaya hai (e.g., n = 3).
     Hume 'n' length ki saari possible binary strings ('0' aur '1' se bani)
     generate karke ek vector 'result' me store karni hain.

   - Core Logic: Two Choices at Every Position:
     Array/String ke har index (0 se lekar n - 1) par exactly do choices hain:
     1. Choice 1: Current position par '0' daalo -> ds.push_back('0')
        Explore karo: agle index ke liye call lagao -> generate_sequences(index + 1, ...)
        Backtrack (Undo): '0' hatao -> ds.pop_back()
     2. Choice 2: Current position par '1' daalo -> ds.push_back('1')
        Explore karo: agle index ke liye call lagao -> generate_sequences(index + 1, ...)
        Backtrack (Undo): '1' hatao -> ds.pop_back()

   - Base Case:
     Jab `index == n` pahunchte hain, iska matlab string ki length 'n' complete
     ho chuki hai. Current string 'ds' ko 'result' vector me push karo aur return ho jao.

   - Total Generated Strings:
     Har index par 2 options hain (0 ya 1).
     Toh n length ke liye total 2^n binary strings banti hain (e.g., 2^3 = 8 strings).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- generate_sequences(index, ds, result, n) ---
   - if(index == n):
     Base case: 'ds' ki length 'n' ho chuki hai.
     `result.push_back(ds);` karke return ho jao.
   - ds.push_back('0'); :
     CHOICE 1: String ke end me '0' jod diya.
   - generate_sequences(index + 1, ds, result, n); :
     EXPLORE: Left branch me '0' ke sath aage ke indices explore kiye.
   - ds.pop_back(); :
     BACKTRACK: Aakhri '0' hata diya taaki state restore ho sake.
   - ds.push_back('1'); :
     CHOICE 2: String ke end me '1' jod diya.
   - generate_sequences(index + 1, ds, result, n); :
     EXPLORE: Right branch me '1' ke sath aage ke indices explore kiye.
   - ds.pop_back(); :
     BACKTRACK: Aakhri '1' hata diya.

======================================================================
3. DETAILED DRY RUN (n = 3):

   Root Call: F(index=0, ds="")

   --- LEVEL 0: Index 0 par '0' rakha ---
   ds = "0" -> Call F(1, "0")

      --- LEVEL 1: Index 1 par '0' rakha ---
      ds = "00" -> Call F(2, "00")

         --- LEVEL 2: Index 2 par '0' rakha ---
         ds = "000" -> Call F(3, "000")
           - index == 3 -> Result me push: "000" -> return
         Backtrack: ds.pop_back() -> ds = "00"

         --- LEVEL 2: Index 2 par '1' rakha ---
         ds = "001" -> Call F(3, "001")
           - index == 3 -> Result me push: "001" -> return
         Backtrack: ds.pop_back() -> ds = "00"

      Backtrack: ds.pop_back() -> ds = "0"

      --- LEVEL 1: Index 1 par '1' rakha ---
      ds = "01" -> Call F(2, "01")

         --- LEVEL 2: Index 2 par '0' rakha ---
         ds = "010" -> Call F(3, "010")
           - index == 3 -> Result me push: "010" -> return
         Backtrack: ds.pop_back() -> ds = "01"

         --- LEVEL 2: Index 2 par '1' rakha ---
         ds = "011" -> Call F(3, "011")
           - index == 3 -> Result me push: "011" -> return
         Backtrack: ds.pop_back() -> ds = "01"

      Backtrack: ds.pop_back() -> ds = "0"

   Backtrack: ds.pop_back() -> ds = ""

   --- LEVEL 0: Index 0 par '1' rakha ---
   ds = "1" -> Call F(1, "1")

      --- LEVEL 1: Index 1 par '0' rakha ---
      ds = "10" -> Call F(2, "10")

         --- LEVEL 2: Index 2 par '0' rakha ---
         ds = "100" -> Call F(3, "100")
           - index == 3 -> Result me push: "100" -> return
         Backtrack: ds.pop_back() -> ds = "10"

         --- LEVEL 2: Index 2 par '1' rakha ---
         ds = "101" -> Call F(3, "101")
           - index == 3 -> Result me push: "101" -> return
         Backtrack: ds.pop_back() -> ds = "10"

      Backtrack: ds.pop_back() -> ds = "1"

      --- LEVEL 1: Index 1 par '1' rakha ---
      ds = "11" -> Call F(2, "11")

         --- LEVEL 2: Index 2 par '0' rakha ---
         ds = "110" -> Call F(3, "110")
           - index == 3 -> Result me push: "110" -> return
         Backtrack: ds.pop_back() -> ds = "11"

         --- LEVEL 2: Index 2 par '1' rakha ---
         ds = "111" -> Call F(3, "111")
           - index == 3 -> Result me push: "111" -> return
         Backtrack: ds.pop_back() -> ds = "11"

      Backtrack: ds.pop_back() -> ds = "1"

   Backtrack: ds.pop_back() -> ds = ""

   Console Output:
   000 001 010 011 100 101 110 111 

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Total leaves in recursion tree = 2^n.
     * Total recursive calls = 2^0 + 2^1 + ... + 2^n = 2^(n+1) - 1 = O(2^n).
     * Base case me string 'ds' ko 'result' vector me copy karne me O(n) lagta hai.
     * Total Time Complexity: O(n * 2^n).

   - Space Complexity (SC):
     * Auxiliary Recursion Stack Space: O(n) (Maximum depth = n).
     * Working Buffer Memory: O(n) for string 'ds'.
     * Output Storage: O(n * 2^n) to store 2^n strings of size n in 'result'.
     * Total Auxiliary Space (excluding output): O(n).
======================================================================
*/

void generate_sequences(int index, string &ds, vector <string> &result, int n){
    if(index == n){
        result.push_back(ds);
        return;
    }

    ds.push_back('0');
    generate_sequences(index + 1, ds, result, n);
    ds.pop_back();

    ds.push_back('1');
    generate_sequences(index + 1, ds, result, n);
    ds.pop_back();
}

int main(){
    string ds = "";
    vector <string> result;
    int n = 3;
    generate_sequences(0, ds, result, n);
    for(auto ans : result){
        cout<<ans<<" ";
    }
    return 0;
}