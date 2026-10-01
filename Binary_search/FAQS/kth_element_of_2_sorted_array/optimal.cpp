#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (K-TH ELEMENT OF TWO SORTED ARRAYS):
   - Problem:
     Do sorted arrays `nums1` aur `nums2` ko bina actually merge kiye, 
     unka combined `k`-th element (1-based index) find karna hai 
     O(log(min(n1, n2))) time aur O(1) auxiliary space me.

   - Median Problem Se Kya Difference Hai?
     Median me hum total elements ko theek aadhe me todte the (`left = (n1 + n2 + 1) / 2`).
     K-th element me hume specific `k` elements left partition me chahiye!
     Toh humara left partition target seedhe `left = k` ho jata hai.
     Jab partition valid ho jayega (`l1 <= r2` && `l2 <= r1`), toh left partition 
     ke andar exactly pehle `k` smallest elements honge. Unka sabse bada element 
     yaani `max(l1, l2)` hi humara k-th element hoga!

   - THE MOST CRITICAL PART: Boundary Adjustment for `low` and `high`:
     Median me `low = 0` aur `high = n1` hamesha safe tha, lekin K-th element me 
     kuch edge cases runtime crash / logic fail kar sakte hain agar limits adjust na hon:

     1. `low = max(0, k - n2)`:
        - Socho: `k = 7`, `n1 = 6`, `n2 = 5`.
        - Agar hum `low = 0` rakhte, iska matlab "nums1 se 0 elements lo".
        - Toh `mid1 = 0` hone par `mid2 = k - mid1 = 7 - 0 = 7`.
        - Lekin `nums2` ka size toh sirf 5 hai! 7 elements kahan se aayenge?
          `mid2 > n2` ho jayega aur negative/out-of-bounds index hit hoga!
        - Isliye `nums2` se maximum `n2` elements hi aa sakte hain.
          Bache hue `(k - n2)` elements toh nums1 se lene hi padenge (majboori hai).
        - Isliye minimum elements from nums1 = `max(0, k - n2)`.

     2. `high = min(k, n1)`:
        - Socho: `k = 4`, `n1 = 8`, `n2 = 6`.
        - Hume total hi 4 elements partition ke left me chahiye.
        - Agar hum `high = n1 = 8` rakhte, toh hum nums1 se 5 ya 8 elements lene 
          ki koshish kar sakte the, jabki pure left side me total hi 4 slots hain!
        - Isliye nums1 se maximum utne hi elements le sakte hain jitna `k` ya `n1` me se chhota ho.
        - Maximum elements from nums1 = `min(k, n1)`.

   - Cross Conditions (`l1 <= r2` && `l2 <= r1`):
     - `l1 <= r2` aur `l2 <= r1` TRUE hote hi `max(l1, l2)` return karo.
     - Agar `l1 > r2`, nums1 se elements kam karo -> `high = mid1 - 1`.
     - Agar `l2 > r1`, nums1 se elements badhao (taaki nums2 se kam hon) -> `low = mid1 + 1`.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (n2 < n1) return kth_element(nums2, nums1, k);`:
     Binary search hamesha smaller array par run karta hai taaki search range minimum ho.
   - `int low = max(0, k - n2);`:
     Ensures `mid2` kabhi bhi `n2` se bada na ho sake (Bade array ke size overflow se bachav).
   - `int high = min(k, n1);`:
     Ensures hum kabhi bhi `k` se zyada elements pick na karein (Slot overflow se bachav).
   - `int left = k;`:
     Left partition me total exactly `k` elements hone chahiye.
   - `int mid1 = (low + high) / 2;`:
     Nums1 se kitne elements pick kiye.
   - `int mid2 = left - mid1;`:
     Nums2 se kitne elements pick kiye (`k - mid1`).
   - `l1`, `r1`, `l2`, `r2` with `INT_MIN` / `INT_MAX`:
     Boundary guards jo array ke ends (0 ya n) par hone par comparisons ko fail hone se bachate hain.
   - `if (l1 <= r2 && l2 <= r1) return max(l1, l2);`:
     Valid partition! Left partition ka highest element hi exact k-th smallest element hai.
   - `else if (l1 > r2) high = mid1 - 1;`:
     Nums1 ka left element bada hai, nums1 ke elements ghatao.
   - `else low = mid1 + 1;`:
     Nums2 ka left element bada hai, nums1 ke elements badhao (jisse nums2 ke kam hon).

======================================================================
3. DETAILED DRY RUN:

   Input:
   nums1 = [2, 3, 4, 6]          (n1 = 4)
   nums2 = [3, 4, 7, 9, 22, 23]  (n2 = 6)
   k = 8
   Total elements = 4 + 6 = 10.
   Merged Sorted Array mentally: [2, 3, 3, 4, 4, 6, 7, 9, 22, 23]
   Indices (1-based):             1  2  3  4  5  6  7  8   9   10
   8th element must be: 9

   Check initial boundaries:
   n1 <= n2 (4 <= 6) -> OK (nums1 is smaller).
   low  = max(0, k - n2) = max(0, 8 - 6) = max(0, 2) = 2.
          (Kyunki nums2 me total 6 hi hain, nums1 se at least 2 elements lene hi honge!)
   high = min(k, n1) = min(8, 4) = 4.
   left = k = 8.

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 2, high = 4
   mid1 = (2 + 4) / 2 = 3   (nums1 se 3 elements)
   mid2 = left - mid1 = 8 - 3 = 5 (nums2 se 5 elements)

   Partitions:
     nums1: [2, 3, 4]       | [6]           => l1 = 4, r1 = 6
     nums2: [3, 4, 7, 9, 22]| [23]          => l2 = 22, r2 = 23

   Cross Checks:
     l1 <= r2 ?  4 <= 23 -> TRUE
     l2 <= r1 ? 22 <= 6  -> FALSE! (22 bada hai 6 se)

   Decision:
     l2 > r1 hai. Nums2 se elements kam karne hain.
     Nums1 se elements badhao:
     low = mid1 + 1 = 3 + 1 = 4.
   State: low = 4, high = 4.

   -------------------------------------------------------------------
   --- Iteration 2 ---
   low = 4, high = 4
   mid1 = (4 + 4) / 2 = 4   (nums1 se 4 elements)
   mid2 = left - mid1 = 8 - 4 = 4 (nums2 se 4 elements)

   Partitions:
     nums1: [2, 3, 4, 6]    | []            => l1 = 6, r1 = INT_MAX (all in left)
     nums2: [3, 4, 7, 9]    | [22, 23]      => l2 = 9, r2 = 22

   Cross Checks:
     l1 <= r2 ?  6 <= 22      -> TRUE
     l2 <= r1 ?  9 <= INT_MAX -> TRUE

   BOTH TRUE! Valid Partition Found!

   Result:
     max(l1, l2) = max(6, 9) = 9.
   Function returns 9.0 (as double/int).
   Output: "Kth element = 9" (Matches expected answer!).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O(log2(min(N1, N2))).
     * Hum binary search hamesha strictly smaller array ke boundaries par chalate hain.
     * Search space har step me aadhi hoti hai: (high - low + 1) / 2.
     * Worst case operations: <= log2(min(N1, N2)).
     * Yeh linear merge O(k) ya O(N1 + N2) se exponentially fast hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra array, dynamic vector ya call stack allocate nahi hota.
     * Sirf fixed scalar variables (`n1`, `n2`, `low`, `high`, `mid1`, `mid2`, 
       `l1`, `l2`, `r1`, `r2`, `left`) use hote hain.
======================================================================
*/


double kth_element(vector <int>&nums1,vector <int>&nums2, int k){
    int n1=nums1.size();
    int n2=nums2.size();
    if(n2<n1){     // Mein ye isliye kar raha hu kyuki mein actually chote wale array ke elements ko select karta hua jaunga jaise ki agar n1 chota hai to pehle n1 se 1 element lunga aur chk karunga agar nahi hua to phir 2 element lunga aur ck karunga agar wo bhi nahi hua to phir n1 se 3 elements lunga .......
        return kth_element(nums2,nums1, k);
    }

    // int low=0;    // ye batata hai ki mein chote array se ek bhi element select nahi karunga pehle
    int low = max(0, k - n2);  // suppose k = 7 hai aur nums1 ka size hain 6 and nus2 ka size hai 5 TO AGAR low = 0 HOGA TO US CASE MEIN SAARE ELEMENTS nums2 SE HI HONGE LEKIN nums2 MEIN BHI 5 HI HAI AUR K = 7 HAI

    // int high=n1;    // ye batata hai ki end tak bhi nahi hua to mein chote array ke saare elements le lunga
    int high = min(k, n1);  //  k = 4 n1 = 8 is case mein agar high = n1 hota to mein 8 elemnt le sakta LEKIN JAB k HI 4 HAI TO MEIN nums1 SE 8 ELEMENTS KAISE HI LU
    
    int left=k;    // itne elements honge left side mein 
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
            return max(l1, l2);
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

    int k = 8;
    cout << "Kth element = " << kth_element(a, b, k);
    return 0;
}