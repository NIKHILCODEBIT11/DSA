#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (CAPACITY TO SHIP PACKAGES WITHIN D DAYS - BRUTE FORCE):
   - Problem:
     Ek conveyor belt par packages line me rakhe hain (weights = `wts`).
     Hume ek ship ki aisi MINIMUM weight capacity nikalni hai taaki saare packages 
     `threshold_days` ke andar ya barabar din me ship ho sakein.
     Strict Rule: Packages ko order me hi load karna hai (contiguous sub-arrays). 
     Kisi package ko chhodkar aage nahi badh sakte.

   - Real-Life Logic (Truck / Ship Loading Analogy):
     Maan lo tum ek truck me samaan bhar rahe ho:
     - Jab tak truck me jagah hai (`load + wts[i] <= capacity`), samaan daalte jao.
     - Jaise hi agla package daalne se truck ki capacity overload hoti hai (`load + wts[i] > capacity`), 
       tum us truck ko rawana kar dete ho (Day 1 khatam, `days++`).
     - Agle din naya truck aayega (`days = 2`), aur jo package kal overflow kar raha tha 
       wo sabse pehle naye truck me load hoga (`load = wts[i]`).

   - Search Space Boundary Ka Exact Logic:
     1. Minimum Possible Capacity = `max_element(wts)`:
        Kyun? Agar array ka sabse bhaari package 10 kg ka hai, aur humari boat ki capacity 9 kg hai, 
        toh wo 10 kg ka package zindagi me kabhi ship nahi ho payega!
        Isliye ship ki capacity array ke sabse bade single package ke barabar ya usse badi honi hi chahiye.
     2. Maximum Possible Capacity = `sum(all weights)`:
        Agar hume saara samaan sirf 1 hi din me ship karna ho (`threshold_days = 1`), 
        toh ship ki capacity itni honi chahiye ki wo ek baar me saara wazan utha sake 
        (yaani total sum of elements). Isse badi capacity lene ka koi practical sense nahi banta.
     - Range: `[max_element(wts) ... accumulate(wts)]`.

   - Brute Force Progression:
     Hum capacity ko `max_element` se shuru karte hain aur 1-1 karke badhate hain:
     - Jaise jaise ship ki capacity badhegi, per day zyada load aayega, 
       matlab required days hamesha ghatenge ya barabar rahenge (Monotonic relationship).
     - Isliye jo PEHLI capacity condition `days <= threshold_days` satisfy karegi, 
       wahi humara exact MINIMUM capacity answer hogi!

   - Important C++ Catch:
     Function `final_capac` ke end me ek default `return -1;` likhna best practice hoti hai 
     taaki compiler ko non-void return warning na mile (bhale hi loop ke andar answer guaranteed ho).

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `days_required(wts, capacity)` ---
   - `int load = 0, days = 1;`:
     `days = 1` se start kiya kyunki pehla din shuru hote hi pehla batch load hona start ho jata hai.
     `load = 0` current din ka accumulated weight track karta hai.
   - `if (load + wts[i] > capacity)`:
     Overflow check! Agar current package add karne se ship ki limit toot rahi hai.
     - `days += 1;` -> Pichla din khatam, agla din shuru.
     - `load = wts[i];` -> Overload karne wala package naye din ka pehla load bana.
   - `else load += wts[i];`:
     Limit bachi hui hai, package ko bina din badle usi din ke load me add kar liya.
   - `return days;`:
     Total kitne din lage packages deliver karne me, wo count return kiya.

   --- `final_capac(wts, threshold_days)` ---
   - `int capacity = *max_element(...); capacity <= accumulate(...); capacity++`:
     Search space ke lower bound (max single item) se upper bound (total weight) tak 
     ek-ek capacity linearly test kar rahe hain.
   - `int days = days_required(wts, capacity);`:
     Current capacity par kitne din lag rahe hain wo calculate kiya.
   - `if (days <= threshold_days) return capacity;`:
     Kyunki hum lowest possible capacity se start karke badh rahe hain, 
     pehle match milte hi wahi humara minimum answer ban jata hai -> return immediately.

======================================================================
3. DETAILED DRY RUN:

   Input: wts = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], threshold_days = 5
   max_element = 10
   sum_of_all  = 55
   Search Range: capacity = 10 se 55 tak

   -------------------------------------------------------------------
   --- Test Capacity = 10 ---
   Day 1: 1+2+3+4 = 10 (Next is 5 -> 10+5=15 > 10, shift to Day 2)
   Day 2: 5 (Next is 6 -> 5+6=11 > 10, shift to Day 3)
   Day 3: 6 (Next is 7 -> 6+7=13 > 10, shift to Day 4)
   Day 4: 7 (Next is 8 -> shift to Day 5)
   Day 5: 8 (Next is 9 -> shift to Day 6)
   Day 6: 9 (Next is 10 -> shift to Day 7)
   Day 7: 10
   Total Days = 7
   Check: days <= threshold_days (7 <= 5) -> FALSE!

   --- Test Capacity = 11 to 14 ---
   Capacity badhane par bhi days 5 se zyada lag rahe hain (e.g., cap=11 takes 6 days, etc.) -> All FALSE.

   --- Test Capacity = 15 ---
   Call: days_required(wts, capacity = 15)
   Step-by-step trace:
   - i = 0: load = 1 (<= 15)
   - i = 1: load = 1 + 2 = 3 (<= 15)
   - i = 2: load = 3 + 3 = 6 (<= 15)
   - i = 3: load = 6 + 4 = 10 (<= 15)
   - i = 4: load = 10 + 5 = 15 (<= 15)
   - i = 5: wts[5] = 6. Check: 15 + 6 = 21 > 15 -> OVERFLOW!
            days = days + 1 = 2 (Day 2 start)
            load = wts[5] = 6
   - i = 6: load = 6 + 7 = 13 (<= 15)
   - i = 7: wts[7] = 8. Check: 13 + 8 = 21 > 15 -> OVERFLOW!
            days = days + 1 = 3 (Day 3 start)
            load = wts[7] = 8
   - i = 8: wts[8] = 9. Check: 8 + 9 = 17 > 15 -> OVERFLOW!
            days = days + 1 = 4 (Day 4 start)
            load = wts[8] = 9
   - i = 9: wts[9] = 10. Check: 9 + 10 = 19 > 15 -> OVERFLOW!
            days = days + 1 = 5 (Day 5 start)
            load = wts[9] = 10
   Loop ends.
   Total days required for capacity 15 = 5 days.

   Check: days <= threshold_days (5 <= 5) -> TRUE! (Condition Satisfied!)

   Action:
     Pehli valid capacity = 15 mil gayi!
     Return 15 immediately.
     Output: "The minimum capacity of ship is 15"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = wts.size(), Max = max_element(wts), Sum = sum of all wts.
     * Capacity range = (Sum - Max + 1).
     * Outer loop capacity = Max se Sum tak linearly chalta hai: O(Sum - Max + 1) steps.
     * Har iteration me `days_required()` pure array par loop lagata hai: O(N) operations.
     * Total Time Complexity: O(N * (Sum - Max + 1)).
     * Worst case limitation: Agar Sum bohot bada ho (e.g., 5 * 10^7) aur N = 5 * 10^4 ho, 
       toh yeh approach Time Limit Exceeded (TLE) de degi.
       (Isliye is linear search range ko Binary Search on Answers se O(N * log(Sum - Max)) me convert karte hain).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard loop variables (`load`, `days`, `capacity`, `i`) 
       use hue hain. Extra memory bilkul constant hai.
======================================================================
*/


// BRUTEFORCE :-
int days_required(vector <int> &wts,int capacity){      // 1    2   3   4   5   6   7   8   9   10      days=5
    int load=0,days=1;
    for(int i=0;i<wts.size();i++){
        if(load+wts[i]>capacity){   // agar current day ke load mein weight add karu aur agar wo cpacity se jyada ho raha hai to us case mein us weight ko agle din ke liye rakhna padega
            days+=1;        // isliye next day mein transmit kar gaya
            load=wts[i];    // aur kyuki next day se mujhe pichle din jo weight ki wajah se capacity se bahar jaa raha tha usko ship karna hai isliye load usi weight se start hoga
        }
        else{
            load+=wts[i];   // lekin agar if run nahi hua uska matlab hai ki capacity reach nahi hui isliye load mein aur weight daal raha hu
        }
    }
    return days;
}

int final_capac(vector <int> &wts,int threshold_days){
    // capacity jo hai wo "wts" ke maximum weight se leke ssum of all weights tak jayega
    // capacity = max(wts) -> sum(all weights in wts)
    // start max(wts se ho raha hai kuyki agar mein wts = [2,3,4,5,6] mein se capacity = 4 select karu to us case mein kabhi bhi weight 5 and 6 ship hi nahi ho payenge
    // end sum(all weights in wts) kar raha hu kyui 1 agar threshold day KAM SE KAM 1 bhi hua to us case mein 1 day mein hi saare weights ship ho jayenge

    for(int capacity=*max_element(wts.begin(),wts.end());capacity<=accumulate(wts.begin(),wts.end(),0);capacity++){
        int days=days_required(wts,capacity);
        if(days<=threshold_days){
            return capacity;
        }
    }
}

int main(){
    vector <int> wts={1,2,3,4,5,6,7,8,9,10};
    int threshold_days=5;
    int capacity=final_capac(wts,threshold_days);
    cout<<"The minimum capacity of ship is "<<capacity;
    return 0;
}