#include<bits/stdc++.h>
using namespace std;

// ispe TLE aayega kyuki TC O(N +  M) ho raha hai

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (MEDIAN OF TWO SORTED ARRAYS - MERGE STEP):
   - Problem:
     Hume do sorted arrays `arr_1` aur `arr_2` diye gaye hain.
     Hume dono ko milakar banne wale combined sorted array ka MEDIAN nikalna hai.

   - Median Ka Basic Rule:
     Maan lo total elements N = (size1 + size2).
     - Agar N ODD (visham) hai:
       Exact center par sirf 1 element hota hai -> index `N / 2`.
       Median = merged[N / 2].
     - Agar N EVEN (sam) hai:
       Center par do elements hote hain -> index `(N / 2) - 1` aur `N / 2`.
       Median = dono middle elements ka average = (merged[(N/2) - 1] + merged[N/2]) / 2.0.

   - Core Intuition (Merge Sort Step):
     Kyunki dono arrays ALREADY SORTED hain, hume dobara pura sorting algorithm 
     (jaise O(N log N)) chalane ki zaroorat nahi hai.
     Hum Merge Sort ka classic **Two-Pointer Merge Step** use karte hain:
     - Ek pointer `i` rakha `arr_1` ke start par (index 0).
     - Ek pointer `j` rakha `arr_2` ke start par (index 0).
     - Har step par compare karo: jo chhota ho use `ans` vector me daal do aur 
       uska pointer ek aage badha do.
     - Jab ek array khatam ho jaye, toh doosre array ke bache hue saare elements 
       as it is `ans` ke peeche jod do.

   - Pair Return Karne Ka Logic:
     Function `pair<int, int>` return kar raha hai taaki:
     - Agar Even count ho: Dono middle elements `{ans[(N/2)-1], ans[N/2]}` return ho sakein.
     - Agar Odd count ho: Wahi center element do baar `{ans[N/2], ans[N/2]}` return ho sake.
     Isse `main()` function me ek hi uniform formula lag jata hai:
         `(m.first + m.second) / 2.0`
     (Odd ke case me: `(x + x) / 2.0 = 2x / 2.0 = x`, exact value aati hai!).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `vector<int> ans; int i = 0, j = 0;`:
     `ans` merged sorted array store karega. `i` aur `j` pointers hain jo dono arrays 
     ko sequentially scan karenge.
   - `for(i = 0, j = 0; i < arr_1.size() && j < arr_2.size();)`:
     Jab tak dono arrays me elements bache hain, loop chalega.
   - `if(arr_1[i] <= arr_2[j]) { ans.push_back(arr_1[i]); i++; }`:
     `arr_1` ka current element chhota ya barabar hai, toh use `ans` me daalo aur `i` aage badhao.
   - `else { ans.push_back(arr_2[j]); j++; }`:
     `arr_2` ka current element chhota hai, toh use `ans` me daalo aur `j` aage badhao.
   - `while(i < arr_1.size())`:
     Agar `arr_2` pehle exhaust (khatam) ho gaya, toh `arr_1` ke remaining elements copy karo.
   - `while(j < arr_2.size())`:
     Agar `arr_1` pehle exhaust ho gaya, toh `arr_2` ke remaining elements copy karo.
   - `if(ans.size() % 2 == 0) return {ans[(ans.size()/2)-1], ans[ans.size()/2]};`:
     Even size: Beech ke do elements return kiye.
   - `else return {ans[ans.size()/2], ans[ans.size()/2]};`:
     Odd size: Center element ko dono slots me return kiya.

======================================================================
3. DETAILED DRY RUN:

   Input:
   arr_1 = [2, 3, 4, 6]          (size = 4)
   arr_2 = [3, 4, 7, 9, 22, 23]  (size = 6)
   Total elements = 4 + 6 = 10 (EVEN)
   Expected Median indices in merged array: (10/2) - 1 = 4  aur  10/2 = 5.

   --- Step 1: Two Pointers Merging ---
   Initial: i = 0, j = 0, ans = []

   Step 1: arr_1[0]=2 <= arr_2[0]=3 -> ans=[2], i=1, j=0
   Step 2: arr_1[1]=3 <= arr_2[0]=3 -> ans=[2, 3], i=2, j=0
   Step 3: arr_1[2]=4 >  arr_2[0]=3 -> ans=[2, 3, 3], i=2, j=1
   Step 4: arr_1[2]=4 <= arr_2[1]=4 -> ans=[2, 3, 3, 4], i=3, j=1
   Step 5: arr_1[3]=6 >  arr_2[1]=4 -> ans=[2, 3, 3, 4, 4], i=3, j=2
   Step 6: arr_1[3]=6 <= arr_2[2]=7 -> ans=[2, 3, 3, 4, 4, 6], i=4, j=2

   Yahan `i = 4 == arr_1.size()`, loop break!

   --- Step 2: Remaining Elements Copy ---
   `arr_2` me elements bache hain (j = 2 se j = 5):
   - j=2: ans.push_back(7)  -> ans=[2, 3, 3, 4, 4, 6, 7]
   - j=3: ans.push_back(9)  -> ans=[2, 3, 3, 4, 4, 6, 7, 9]
   - j=4: ans.push_back(22) -> ans=[2, 3, 3, 4, 4, 6, 7, 9, 22]
   - j=5: ans.push_back(23) -> ans=[2, 3, 3, 4, 4, 6, 7, 9, 22, 23]

   Final `ans` vector (size = 10):
   Index: 0  1  2  3  4  5  6  7   8   9
   Value: 2  3  3  4  4  6  7  9  22  23

   --- Step 3: Median Extraction ---
   ans.size() = 10 (10 % 2 == 0 -> TRUE, EVEN case)
   Left mid index  = (10 / 2) - 1 = 4  -> ans[4] = 4
   Right mid index = 10 / 2 = 5        -> ans[5] = 6
   Returns pair: {4, 6}

   In main():
   m = {4, 6}
   Formula: (m.first + m.second) / 2.0 = (4 + 6) / 2.0 = 10 / 2.0 = 5.0
   Output: "The median value is 5"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = arr_1.size(), M = arr_2.size().
     * Merge step dono arrays ke har element ko exactly ek baar traverse karta hai.
     * Total iterations = N + M.
     * Overall Time Complexity: O(N + M).

   - Space Complexity (SC):
     * Auxiliary Space: O(N + M).
     * Kyunki humne merged elements store karne ke liye `ans` vector banaya hai 
       jiska size (N + M) hai.
     * (Note: Isko bina extra space O(1) memory me sirf counter track karke, 
       aur even optimal Binary Search se O(log(min(N, M))) me optimize kiya ja sakta hai).
======================================================================
*/

pair<int,int> med(vector <int>&arr_1,vector <int> &arr_2){
    vector <int> ans;
    int i,j;
    for(i=0,j=0;i<arr_1.size() && j<arr_2.size();){
        if(arr_1[i]<=arr_2[j]){
            ans.push_back(arr_1[i]);
            i++;
        }
        else{
            ans.push_back(arr_2[j]);
            j++;
        }
    }

    // ye tab hi chalega jab arr_1 mein kuch elements bach gaye honge
    while(i<arr_1.size()){
        ans.push_back(arr_1[i]);
        i++;
    }

    // ye tab hi chalega jab arr_2 mein kuch elements bach gaye honge
    while(j<arr_2.size()){
        ans.push_back(arr_2[j]);
        j++;
    }


    if(ans.size()%2==0){
        return {ans[(ans.size()/2)-1],ans[ans.size()/2]};
    }
    else{
        return {ans[(ans.size()/2)],ans[(ans.size()/2)]};
    }
}

int main(){
    vector <int> arr_1={2,3,4,6};
    vector <int> arr_2={3,4,7,9,22,23};

    pair <int,int> m=med(arr_1,arr_2);
    cout<<"The median value is "<<(m.first+m.second)/2.0;
    return 0;
}