#include<bits/stdc++.h>
using namespace std;

// Ispe mein bas pehle wale part ki SC optimize kar raha

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SPACE-OPTIMIZED MEDIAN OF TWO SORTED ARRAYS):
   - Problem:
     Do sorted arrays `a` aur `b` ka combined median nikalna hai bina kisi 
     extra array ya vector ko memory me store kiye (O(1) Auxiliary Space).

   - Why Store The Whole Merged Array When We Only Need 2 Elements?
     Pichle solution me humne ek pura `vector<int> ans` banaya tha (size N1 + N2).
     Lekin dhyan se socho:
     Hume pure combined array se koi lena-dena nahi hai! Hume sirf aur sirf:
     - Index `(n / 2) - 1` wala element chahiye (`ind1el`)
     - Index `n / 2` wala element chahiye (`ind2el`)
     Agar total elements `n` hain:
     - `n` Even hai -> Median = (ind1el + ind2el) / 2.0
     - `n` Odd hai  -> Median = ind2el

   - Virtual Merging Technique (Counter Simulation):
     Hum Merge Sort ke two-pointer simulation ko run karte hain, lekin elements ko 
     vector me push karne ke bajaye ek imaginary pointer / counter `cnt` chalate hain:
     - `cnt = 0` pehla sabse chhota element represent karega.
     - `cnt = 1` doosra sabse chhota, aur aage aise hi.
     - Jaise hi `cnt == index_1`, jo bhi current chhota element hai use variable `ind1el` me store kar lo.
     - Jaise hi `cnt == index_2`, jo bhi current chhota element hai use variable `ind2el` me store kar lo.
     - Aur jaise hi `cnt > index_2`, hume aage ke elements dekhne ki zaroorat hi nahi hai! 
       Kyunki humara required median information already capture ho chuka hai (Early Break).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int n = n1 + n2; int index_2 = n / 2, index_1 = index_2 - 1;`:
     Combined sorted array ke dono target middle indices pehle hi calculate kar liye.
   - `int cnt = 0, ind1el = -1, ind2el = -1;`:
     `cnt`: Current virtual index track karta hai.
     `ind1el`, `ind2el`: Middle elements ko capture karne ke scalar registers.
   - `while(i < n1 && j < n2)`:
     Dono arrays ke elements compare karke simulated sorted order me traverse karte hain.
   - `if (cnt == index_1) ... if (cnt == index_2) ...`:
     Agar current virtual index target median index se match kare, toh value capture karo.
   - `cnt++; i++;` (ya `cnt++; j++;`):
     Virtual array ka agla index aur respective array ka pointer advance kiya.
   - `if (cnt > index_2) break;`:
     EARLY EXIT: Jaise hi dono middle elements mil gaye, bina bacha hua array traverse kiye loop tod diya.
   - Remaining `while(i < n1)` aur `while(j < n2)`:
     Agar ek array jaldi exhaust ho gaya tha aur target index tak nahi pahuche the, 
     toh bache hue array se values fill hoti hain.
     *(Optimization Note: In remaining loops me condition `while(i < n1 && cnt <= index_2)` 
     lagane se unwanted trailing traversal completely eliminate ho jata hai).*
   - `if (n % 2 == 0) return (ind1el + ind2el) / 2.0; else return ind2el;`:
     Even ke liye dono ka average, Odd ke liye middle element direct return.

======================================================================
3. DETAILED DRY RUN:

   Input:
   a = [2, 3, 4, 6]          (n1 = 4)
   b = [3, 4, 7, 9, 22, 23]  (n2 = 6)
   n = 4 + 6 = 10 (EVEN)
   index_2 = 10 / 2 = 5
   index_1 = 5 - 1 = 4
   Initial: i = 0, j = 0, cnt = 0, ind1el = -1, ind2el = -1

   -------------------------------------------------------------------
   Step 1:
     a[0]=2 < b[0]=3 -> Pick a[0] (2)
     cnt = 0 (neither index_1 nor index_2)
     cnt becomes 1, i becomes 1

   Step 2:
     a[1]=3 not < b[0]=3 -> Else branch: Pick b[0] (3)
     cnt = 1
     cnt becomes 2, j becomes 1

   Step 3:
     a[1]=3 < b[1]=4 -> Pick a[1] (3)
     cnt = 2
     cnt becomes 3, i becomes 2

   Step 4:
     a[2]=4 not < b[1]=4 -> Else branch: Pick b[1] (4)
     cnt = 3
     cnt becomes 4, j becomes 2

   Step 5:
     a[2]=4 < b[2]=7 -> Pick a[2] (4)
     cnt == index_1 (4 == 4) -> MATCH!
     ind1el = a[2] = 4
     cnt becomes 5, i becomes 3

   Step 6:
     a[3]=6 < b[2]=7 -> Pick a[3] (6)
     cnt == index_2 (5 == 5) -> MATCH!
     ind2el = a[3] = 6
     cnt becomes 6, i becomes 4
     Check: (cnt > index_2) => (6 > 5) -> TRUE! BREAK TRIGGERED!

   --- Loop Break ---
   i = 4, j = 2, cnt = 6.
   Bache hue while loops `while(i < n1)` aur `while(j < n2)` execute nahi honge ya 
   agar check add kar diya toh turant skip ho jayenge.

   Values Captured:
     ind1el = 4
     ind2el = 6

   Final Calculation:
     n % 2 == 0 (10 % 2 == 0) -> TRUE
     return (ind1el + ind2el) / 2.0 = (4 + 6) / 2.0 = 10 / 2.0 = 5.0
     Output: "The median value is 5"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * O((N1 + N2) / 2) -> Kyunki hum `cnt > index_2` par break kar dete hain, 
       hum maximum total elements ka sirf aadha hissa (half) hi traverse karte hain.
     * Big-O notation me constant factor ignore hota hai: O(N1 + N2).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Pure algorithm me koi array, vector ya heap 
       allocate nahi kiya gaya. Sirf 7 scalar integer variables (`n1`, `n2`, `i`, `j`, 
       `cnt`, `ind1el`, `ind2el`) use hue hain.
======================================================================
*/

// Optimal from 1st one 
double med(vector <int>& a,vector <int> &b){
    int n1=a.size(),n2=b.size();
    int i=0,j=0;
    int n=n1+n2;
    int index_2=n/2,index_1=index_2-1;
    int cnt=0;
    int ind1el=-1,ind2el=-1;
    while(i<n1 && j<n2){
        if(a[i]<b[j]){
            if(cnt==index_1){
                ind1el=a[i];
            }
            if(cnt==index_2){
                ind2el=a[i];
            }
            cnt++;
            i++;
        }
        else{
            if(cnt==index_1){
                ind1el=b[j];
            }
            if(cnt==index_2){
                ind2el=b[j];
            }
            cnt++;
            j++;
        }

        // 1. Early Exit: Agar dono target elements capture ho chuke hain
        if(cnt > index_2) break;
    }

    // Phase 2: Agar array 'a' me bache elements se median poora hona ho
    while(i<n1){     // upar ke 1 chk ke badle   while(i < n1 && cnt <= index_2)   and niche wala   bhi chalega
        if(cnt==index_1){
            ind1el=a[i];
        }
        if(cnt==index_2){
            ind2el=a[i];
        }
        cnt++;
        i++;
    }

    // Phase 3: Agar array 'b' me bache elements se median poora hona ho
    while(j<n2){     // upar ke 1 chk ke badle   while(j < n2 && cnt <= index_2)   and upar wala   bhi chalega
        if(cnt==index_1){
            ind1el=b[j];
        }
        if(cnt==index_2){
            ind2el=b[j];
        }
        cnt++;
        j++;
    }

    // Phase 4: Final calculation
    if(n%2==0){
        return (ind1el+ind2el)/2.0;
    }
    else{
        return ind2el;
    }
}

int main(){
    vector <int> arr_1={2,3,4,6};
    vector <int> arr_2={3,4,7,9,22,23};

    double m=med(arr_1,arr_2);
    cout<<"The median value is "<<m;
    return 0;
}