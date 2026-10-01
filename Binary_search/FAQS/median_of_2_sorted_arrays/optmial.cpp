#include<bits/stdc++.h>
using namespace std;


/*

nums1:  ... [mid1 - 1] (l1)  |  [mid1] (r1) ...
nums2:  ... [mid2 - 1] (l2)  |  [mid2] (r2) ...
                             ^
                      Partition Line
*/


/*
======================================================================
1. INTUITION & THOUGHT PROCESS (OPTIMAL BINARY SEARCH ON PARTITION):
   - Problem:
     Do sorted arrays `nums1` aur `nums2` ka median O(log(min(n1, n2))) 
     time aur O(1) space me nikalna hai bina arrays ko merge kiye.

   - Core Partition Concept (Virtual Division):
     Agar dono arrays ko merge karke do barabar hisso me tod diya jaye:
     [----------- LEFT HALF -----------] | [----------- RIGHT HALF -----------]
     - Left half me total elements = `(n1 + n2 + 1) / 2` honge.
       (Odd size hone par `+ 1` ensure karta hai ki median hamesha left half me hi baithe).
     - Left half ka kuch hissa `nums1` se aayega (`mid1` elements) aur 
       bacha hua hissa `nums2` se aayega (`mid2 = left - mid1` elements).

   - Chhote Array Par Binary Search Kyun? (`if(n2 < n1) return med(nums2, nums1);`):
     1. Complexity: Binary search range `[0 ... n1]` hoti hai. Chhote array par 
        chalane se time O(log(min(n1, n2))) ho jata hai jo sabse optimal hai.
     2. Safety (Negative Index Protection): Agar bade array par binary search kiya, 
        toh ho sakta hai `mid1` itna bada ho jaye ki `mid2 = left - mid1` negative ban jaye! 
        Chhote array par chalane se `mid2` hamesha `>= 0` aur `<= n2` rehta hai.

   - Four Boundary Elements (l1, l2, r1, r2):
     Array 1:  ... nums1[mid1-1] (l1)  |  nums1[mid1] (r1) ...
     Array 2:  ... nums2[mid2-1] (l2)  |  nums2[mid2] (r2) ...

     Kyunki individual arrays sorted hain, `l1 <= r1` aur `l2 <= r2` already true hai.
     Partition tab VALID mana jayega jab:
         `l1 <= r2`  AND  `l2 <= r1`
     Matlab left half ka har element right half ke har element se chhota ya barabar ho!

   - Edge Cases via INT_MIN / INT_MAX:
     - Agar `mid1 == 0`: Matlab nums1 se left me 0 elements liye, toh `l1 = INT_MIN` 
       taaki comparison kabhi fail na ho.
     - Agar `mid1 == n1`: Matlab nums1 ke saare elements left me chale gaye, toh `r1 = INT_MAX`.
     Same logic applies to `l2` aur `r2`.

   - Binary Search Direction Rules:
     - Case 1: `l1 > r2`:
       Nums1 ka left element Array 2 ke right element se bada nikal gaya.
       Nums1 se left me zyada elements le liye hain, unhe kam karo -> `high = mid1 - 1`.
     - Case 2: `l2 > r1`:
       Nums2 ka left element Array 1 ke right element se bada hai. 
       Matlab nums2 se zyada elements le liye. Kyunki hum nums2 ko directly control nahi karte, 
       nums1 se zyada elements uthayenge (`low = mid1 + 1`), jisse automatically 
       `mid2 = left - mid1` kam ho jayega!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n2 < n1) return med(nums2, nums1);`:
     First argument ko hamesha smaller array banata hai taaki binary search fast aur safe rahe.
   - `int low = 0, high = n1;`:
     Binary search range: Chhote array se minimum 0 elements le sakte hain, 
     aur maximum saare `n1` elements le sakte hain.
   - `int left = (n1 + n2 + 1) / 2;`:
     Left partition ka fixed total size calculate kiya.
   - `int mid1 = (low + high) / 2;`:
     Nums1 se pick kiye jaane wale elements ka count.
   - `int mid2 = left - mid1;`:
     Nums2 se pick kiye jaane wale elements ka count.
   - `l1 = (mid1 > 0) ? nums1[mid1 - 1] : INT_MIN;`:
     Nums1 ke left side ka maximum element (agar koi element nahi liya toh -infinity).
   - `r1 = (mid1 < n1) ? nums1[mid1] : INT_MAX;`:
     Nums1 ke right side ka minimum element (agar sab left me le liye toh +infinity).
   - `l2 = (mid2 > 0) ? nums2[mid2 - 1] : INT_MIN;` / `r2 = (mid2 < n2) ? nums2[mid2] : INT_MAX;`:
     Nums2 ke left aur right boundary elements.
   - `if (l1 <= r2 && l2 <= r1)`:
     Valid partition condition hit!
     - Odd length `(n1 + n2) % 2 == 1`: Center element left partition ka maximum hoga -> `max(l1, l2)`.
     - Even length: Left max aur right min ka average -> `(max(l1, l2) + min(r1, r2)) / 2.0`.
   - `else if (l1 > r2) high = mid1 - 1;`:
     Nums1 se left me elements ghatao.
   - `else low = mid1 + 1;`:
     Nums1 se left me elements badhao (jisse Nums2 ke ghat sakein).

======================================================================
3. DETAILED DRY RUN:

   Input:
   nums1 = [2, 3, 4, 6]          (n1 = 4)
   nums2 = [3, 4, 7, 9, 22, 23]  (n2 = 6)
   n1 <= n2 (4 <= 6) -> No swap needed.
   Total n = 4 + 6 = 10 (EVEN)
   left = (4 + 6 + 1) / 2 = 11 / 2 = 5 elements

   Initial search space:
   low = 0, high = 4

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 0, high = 4
   mid1 = (0 + 4) / 2 = 2   (nums1 se 2 elements)
   mid2 = 5 - 2 = 3         (nums2 se 3 elements)

   Boundary Elements:
   nums1: [2, 3] | [4, 6]             -> l1 = nums1[1] = 3, r1 = nums1[2] = 4
   nums2: [3, 4, 7] | [9, 22, 23]     -> l2 = nums2[2] = 7, r2 = nums2[3] = 9

   Check Validity:
   1. l1 <= r2 ? (3 <= 9) -> TRUE
   2. l2 <= r1 ? (7 <= 4) -> FALSE! (7 bada hai 4 se)

   Decision:
   Kyunki l2 > r1 hai, nums2 se left side me elements kam karne padenge.
   Nums2 ko kam karne ke liye nums1 se elements badhao:
   low = mid1 + 1 = 2 + 1 = 3
   State updated: low = 3, high = 4

   -------------------------------------------------------------------
   --- Iteration 2 ---
   low = 3, high = 4
   mid1 = (3 + 4) / 2 = 3   (nums1 se 3 elements)
   mid2 = 5 - 3 = 2         (nums2 se 2 elements)

   Boundary Elements:
   nums1: [2, 3, 4] | [6]             -> l1 = nums1[2] = 4, r1 = nums1[3] = 6
   nums2: [3, 4] | [7, 9, 22, 23]     -> l2 = nums2[1] = 4, r2 = nums2[2] = 7

   Check Validity:
   1. l1 <= r2 ? (4 <= 7) -> TRUE
   2. l2 <= r1 ? (4 <= 6) -> TRUE

   BOTH TRUE! Valid partition mil gaya!

   Median Calculation (Total size 10 is EVEN):
   Left Max  = max(l1, l2) = max(4, 4) = 4
   Right Min = min(r1, r2) = min(6, 7) = 6

   Median = (Left Max + Right Min) / 2.0
          = (4 + 6) / 2.0 = 10 / 2.0 = 5.0

   Function returns 5.0.
   Output: "Median = 5"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(log2(min(N1, N2))).
     * Hum binary search sirf smaller array par run kar rahe hain jiska size min(N1, N2) hai.
     * Har step par search space aadhi ho rahi hai.
     * Array size 10^5 hone par bhi max 17-18 iterations me answer nikal aayega.
     * Yeh is problem ka mathematically most optimal time complexity solution hai.

   - Space Complexity (SC):
     * O(1) Auxiliary Space.
     * Koi extra memory, vector ya array allocate nahi hui. 
       Sirf standard integer pointers/variables (`low`, `high`, `mid1`, `mid2`, 
       `l1`, `l2`, `r1`, `r2`) use hue hain.
======================================================================
*/

double med(vector <int>&nums1,vector <int>&nums2){
    int n1=nums1.size();
    int n2=nums2.size();
    if(n2<n1){     // Mein ye isliye kar raha hu kyuki mein actually chote wale array ke elements ko select karta hua jaunga jaise ki agar n1 chota hai to pehle n1 se 1 element lunga aur chk karunga agar nahi hua to phir 2 element lunga aur ck karunga agar wo bhi nahi hua to phir n1 se 3 elements lunga .......
        return med(nums2, nums1);
    }

    int low=0;    // ye batata hai ki mein chote array se ek bhi element select nahi karunga pehle    
    int high=n1;    // ye batata hai ki end tak bhi nahi hua to mein chote array ke saare elements le lunga

    int left= (n1 + n2 + 1)/2;    // itne elements honge left side mein 
    while(low<=high){
        int mid1=(low+high)/2;     // iska matlab hai ki mein chote array se kitne elements lu jaise ki suppose n1 = 4 smallest array to phir low = 0 and high = 4 tab mid1 = 2 ho jayega matlab n1 se 2 elements lo
        int mid2=left-mid1;          //iska matlab hai ki left side mein jo "left" no. of elements hone hain unme se "mid1" no chote array se honge aur "mid2" no bade array se honge
        int l1,l2,r1,r2;
        if(mid1>0){
            l1=nums1[mid1-1];
        }
        else{
            l1=INT_MIN;
        }

        if(mid1<n1){
            r1=nums1[mid1];
        }
        else{
            r1=INT_MAX;
        }

        l2 = (mid2 > 0) ? nums2[mid2 - 1] : INT_MIN;
        r2 = (mid2 < n2) ? nums2[mid2]     : INT_MAX;

        if(l1<=r2 && l2<=r1){
            if((n1+n2)%2==1){
                return max(l1,l2);
            }
            else{
                return (max(l1,l2)+min(r1,r2))/2.0;
            }
        }
        else if (l1 > r2) {   // iska simple matlab hai partition ke left side mein chote array ka jo last element hai agar wo r2 se bada hai iska matlab nujhe chote array ka wo element partition ke dusre side yaani right bhejna padega to agar pehle left side meiin 3 element the tab abhi wo 2 karne padenge iske liye high = mid - 1 hi karna padega taaki right ka search space kam ho
            high = mid1 - 1;    // iska matlab l1 ko chota karna hai par kyuki nums1 pehle se hi sorted hai to l1 chota karne ke liye nums1 ko hi move karke l1 number hi badalna padega uske liye CHOTA KARNA MATLAB nums1 KO AAGE SHIFT KARNA TAAKI NAYA l1 JO HO WO PICHLE l1 SE CHOTA HO JOKI achieve kiya ja sakta hai high ko piche lake taaki mid1 jo hai wo piche aa sake
        }
        // else mein wo case hai jab l2 > r1 ho
        else {                // iska simple matlab hai partition ke left side mein bade array ka jo last element hai agar wo r1 se bada hai iska matlab nujhe bade array ka wo element partition ke dusre side yaani right bhejna padega LEKIN MEIN MOVEMENT SIRF CHOTE ARRAY PE KAR SAKTA HU isliye mein bade array se 3 elements ko ghata ke 2 element karne ke badle chote array pe jo 2 elemnt hai unhe 3 karunga isse automatically mid2 ghatega aur bade array ke left side mein kam elements rahenge 
            low = mid1 + 1;    // iska matlab l2 ghatane ke liye mujhe nums2 chedna padega jo ki mein nahi kar sakta kyuki mein sirf nums1 pe hi change kar sakta hu to l2 ghatane ka matlab nums2 ko right shift karna {taaki l2 wali elemnt partition ke baad chali jaye aur partition se pehle wala naya l2 pichle l2 se chota ho jaye} aur kyuki nums2 nahi ched sakta isliye mein l2 ghatane ke badle r1 badhaunga iske liye nums1 ko left shift karna padega matlab r2 ko partition ke us taraf le jaunga jis wajah se jo naya r2 hoga wo pichle r2 se bada hoga uske liye mujhe left side nums1 shift karne ka matlab left partition for nums1 ka size badhana jiske liye mujhe low = mid + 1 karna padega
        }
    }
    
    return 0.0; // Fallback to avoid compiler warning / UB
}

int main() {
    vector<int> a = {2, 3, 4, 6};
    vector<int> b = {3, 4, 7, 9, 22, 23};

    cout << "Median = " << med(a, b);
    return 0;
}