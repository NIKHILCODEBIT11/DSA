#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (K-TH MISSING POSITIVE NUMBER - BINARY SEARCH):
   - Problem:
     Sorted array `nums` me k-th missing positive number nikalna hai in O(log N) time.
     
   - Missing Numbers Formula at Any Index:
     Agar array me koi number missing NAHI hota, toh index `i` par ideally value 
     kya honi chahiye thi?
     Index:    0   1   2   3   4 ...
     Ideal:    1   2   3   4   5 ... (Formula: index + 1)
     
     Lekin actual array me value hai `nums[i]`.
     Toh index `i` tak kitne numbers gayab (missing) ho chuke hain?
     `missing_count = nums[i] - (i + 1)`.
     
     Example: nums = [2, 3, 6, 7, 9]
     - at index 2: nums[2] = 6.
     - ideal value = 2 + 1 = 3.
     - missing before index 2 = 6 - 3 = 3 numbers (wo numbers hain 1, 4, 5).
     
   - Monotonic Search Space:
     Kyunki array strictly increasing sorted hai, missing count bhi index ke saath 
     hamesha monotonically increase ya constant rahega (kabhi ghat nahi sakta).
     Isliye hum `missing < k` condition par binary search laga sakte hain!

   - Golden Derivation (Kyun `low + k` hi answer banta hai?):
     1. Binary Search hume wo do adjacent indices nikal kar deta hai jinke beech 
        humara target missing number gira hai:
        `high` rukta hai last index par jahan `missing < k` tha.
        `low` rukta hai first index par jahan `missing >= k` tha (`low = high + 1`).
     2. Index `high` tak already kitne numbers missing the?
        `missing_at_high = nums[high] - (high + 1)`
     3. Hume total `k` missing numbers chahiye the.
        Toh `nums[high]` ke baad hume kitne aur ("more") missing numbers jump karna hai?
        `more = k - missing_at_high`
     4. Final Answer `nums[high]` se `more` kadam aage hoga:
        `ans = nums[high] + more`
        `ans = nums[high] + (k - missing_at_high)`
        `ans = nums[high] + k - (nums[high] - (high + 1))`
        `ans = nums[high] + k - nums[high] + high + 1`
        `ans = high + 1 + k`
     5. Jab binary search terminate hota hai (`low > high`), toh strictly `low = high + 1` hota hai.
        Isliye `high + 1` ko `low` se replace kar sakte hain:
        `ans = low + k`!

   - Edge Case Beauty (Why `low + k` handles out-of-bounds):
     Agar `k` bohot chhota ho aur pehle element se pehle hi answer lie kare 
     (jaise nums = [4, 7, 8], k = 3):
     Binary search me `high` ghus kar `-1` ban jayega (out of bounds).
     Agar hum formula `nums[high] + more` use karte toh `nums[-1]` runtime error deta!
     Lekin algebraic derivation se `nums[high]` cancel out ho chuka hai!
     Formula ban gaya `high + 1 + k` = `-1 + 1 + 3` = `3`.
     Ya simply `low + k` = `0 + 3` = `3`. 
     Bina kisi special `if-else` ke out-of-bounds automatically handle ho gaya!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int low = 0, high = nums.size() - 1;`:
     Pure array ke indices par binary search boundary set ki.
   - `int mid = low + (high - low) / 2;`:
     Overflow-safe middle index calculate kiya.
   - `int missing = nums[mid] - (mid + 1);`:
     Core logic: mid index tak total kitne positive integers gayab ho chuke hain.
   - `if (missing < k)` -> `low = mid + 1;`:
     Abhi tak k se kam numbers missing hue hain, iska matlab k-th missing number 
     right half me aage lie karega. Right shift karo.
   - `else` -> `high = mid - 1;`:
     Mid tak already k ya usse zyada numbers missing ho chuke hain, iska matlab 
     k-th missing number left half me piche nikal chuka hai. Left shift karo.
   - `return low + k;`:
     Derivation `high + 1 + k` ke mathematical equivalence ki wajah se direct answer.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [2, 3, 6, 7, 9, 12, 14], k = 5
   Indices:   0   1   2   3   4    5    6
   Values:    2   3   6   7   9   12   14
   Ideal:     1   2   3   4   5    6    7  (mid + 1)
   Missing:   1   1   3   3   4    6    7  (nums[mid] - (mid + 1))

   Target: k = 5

   --- Iteration 1 ---
   low = 0, high = 6
   mid = 0 + (6 - 0) / 2 = 3
   nums[3] = 7
   missing = nums[3] - (3 + 1) = 7 - 4 = 3
   Check: missing < k => 3 < 5 -> TRUE (Missing count kam hai, right jao)
   Action: low = mid + 1 = 3 + 1 = 4
   State: low = 4, high = 6

   --- Iteration 2 ---
   low = 4, high = 6
   mid = 4 + (6 - 4) / 2 = 5
   nums[5] = 12
   missing = nums[5] - (5 + 1) = 12 - 6 = 6
   Check: missing < k => 6 < 5 -> FALSE (Zyada missing ho gaye, left jao)
   Action: high = mid - 1 = 5 - 1 = 4
   State: low = 4, high = 4

   --- Iteration 3 ---
   low = 4, high = 4
   mid = 4 + (4 - 4) / 2 = 4
   nums[4] = 9
   missing = nums[4] - (4 + 1) = 9 - 5 = 4
   Check: missing < k => 4 < 5 -> TRUE (Missing count abhi bhi < 5 hai, right jao)
   Action: low = mid + 1 = 4 + 1 = 5
   State: low = 5, high = 4

   --- Loop Terminate ---
   Condition: low <= high => 5 <= 4 -> FALSE! Loop ends.

   Final Pointer State:
   high = 4 (nums[4] = 9, missing = 4)
   low  = 5 (nums[5] = 12, missing = 6)

   Result Calculation:
   Using formula: low + k = 5 + 5 = 10.
   (Ya alternative formula: high + 1 + k = 4 + 1 + 5 = 10).
   Output: "The 5th missing number is 10" (Correct!).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Middle element par hi exact range squeeze ho jaye.
     * Worst Case: O(log2 N) -> Binary search array ke size ko har step par aada karta hai.
     * Average Case: O(log2 N).
     * Linear solution ke O(N) ke muqable yeh massively fast hai (e.g., N = 10^5 ke liye sirf ~17 steps).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer pointers (`low`, `high`, `mid`, `missing`) 
       use hue hain, koi extra array ya recursive memory nahi lagti.
======================================================================
*/

int missing(vector <int>&nums,int k){           //  {2  3     7   12}         k=5
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        int missing=nums[mid]-(mid+1);
        if(missing<k){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low+k;           //      low + k = high + 1 + k
}

int main(){
    vector <int> nums={2,3,6,7,9,12,14};
    int n;
    cout<<"Enter missing value to be found :- ";
    cin>>n;
    cout<<"The "<<n<<"th missing number is "<<missing(nums,n);
    return 0;
}


/*

Derivation for returning            low + k

index :-        0       1       2       3       4
nums :-         2       3       4       7       12
missing :-      1       1       1       3       7

1st            low              mid            high
2nd                                    low     high
                                       mid
3rd                                            high
                                               low
                                               mid
4th                                    high    low                          here    high = low - 1
                                               mid


For finding the answer i firstly will need range of indexes where the required missing value is present
---------->   "low" started from lowest missing value and reached to that index range which has max missing value
---------->   "High" started from highest missing value and reached to that index range which has minimum missing value

consider arr[high]=7 with 3 missing values, 
so i can say            answer = arr[high] + more
as, i know answer is 9 so theoretically more should be 2

calculation of more :-

arr[high] = 7           missing = 3         more=2

as,         missing = arr[high] - (high + 1)

surely,         more = k - missing
------>   answer = arr[high] + k - (arr[high] - (high + 1))
------->      answer = high + 1 + k
------->      answer = low + k


########## Reason of derivation instead of directly returning "high" :-

consider  array         arr = [4 , 7 , 8]       and    k = 3
by looking i can confirm     ans = 3

and by calculating by binary search i would need range of indexes :-    low = index 0 (value = 4) but high is out of index as at left of 4 array ends
that's why new formula required.
*/



/*
======================================================================
1. INTUITION & THOUGHT PROCESS (KYUN `missing < k` AUR `missing <= k` NAHI?):

   - Core Goal:
     Hume `high` aur `low` ko aisi specific jagah par rokna hai jahan:
       `high` -> Theek US element par ruke jahan tak missing numbers `< k` the (Last Index where missing < k).
       `low`  -> Theek US element par ruke jahan missing numbers `>= k` ho gaye (First Index where missing >= k).
     
   - Formula Kis Par Tika Hai?
     Humara final formula tha:
         ans = nums[high] + more
         jahan `more = k - missing_at_high`
     
     Dhyan se dekho: `more` hamesha POSITIVE (> 0) hona chahiye!
     Matlab hume `nums[high]` se aage badhkar missing numbers count karne hain.
     Agar `missing_at_high < k` hoga, tabhi toh `k - missing_at_high > 0` aayega!

======================================================================
2. KYA HOGA AGAR HUM `missing <= k` LIKH DEIN? (CRASH & BUG ANALYSIS):

   Maan lo hum likhte hain:
       if (missing <= k) {
           low = mid + 1;
       } else {
           high = mid - 1;
       }

   Iska matlab jab `missing == k` hoga, tab bhi hum `low = mid + 1` kar denge!
   Isse do badi galtiyan hongi:

   1. Polarity aur Derivation toot jayegi:
      - `high` us index par ruk jayega jahan `missing == k` tha.
      - Ab agar tum formula lagaoge:
            more = k - missing_at_high
                 = k - k = 0
            ans = nums[high] + 0 = nums[high]
      - Lekin `nums[high]` toh array me PRESENT number hai! Wo MISSING kaise ho sakta hai?
        Missing number kabhi bhi array ka present element nahi ho sakta!

   2. Duplicate missing counts ka problem:
      Agar multiple indices par missing count same (barabar) ho, toh `missing <= k` 
      `high` ko k-th missing number se bohot aage phek dega.

======================================================================
3. DETAILED DRY RUN (CONCRETE COUNTER-EXAMPLE):

   Array:
   Indices:   0    1    2     3
   nums:     [2,   3,   4,    7]
   Ideal:     1    2    3     4  (mid + 1)
   Missing:   1    1    1     3  (nums[mid] - (mid + 1))

   Hume chahiye: k = 2 (2nd missing number)
   Reality check:
     Stream: 1, [2], [3], [4], 5, 6, [7]...
     Missing numbers list: 1, 5, 6, 8...
     1st missing = 1
     2nd missing = 5  ===> CORRECT ANSWER = 5.

   -------------------------------------------------------------------
   CASE A: Sahi Logic -> `if (missing < k)` [k = 2]
   -------------------------------------------------------------------
   Iter 1: low=0, high=3 -> mid=1
           nums[1] = 3, missing = 3 - 2 = 1.
           missing < k (1 < 2) -> TRUE -> low = mid + 1 = 2.

   Iter 2: low=2, high=3 -> mid=2
           nums[2] = 4, missing = 4 - 3 = 1.
           missing < k (1 < 2) -> TRUE -> low = mid + 1 = 3.

   Iter 3: low=3, high=3 -> mid=3
           nums[3] = 7, missing = 7 - 4 = 3.
           missing < k (3 < 2) -> FALSE -> high = mid - 1 = 2.

   Loop Ends: low = 3, high = 2.
   Formula calculation:
     ans = low + k = 3 + 2 = 5!  (100% CORRECT)
     (Ya nums[high] + (k - missing) = nums[2] + (2 - 1) = 4 + 1 = 5).

   -------------------------------------------------------------------
   CASE B: Galat Logic -> `if (missing <= k)`
   Consider array: nums = [1, 3], k = 1
   Indices:  0    1
   nums:    [1,   3]
   Missing:  0    1
   Expected 1st missing number = 2.

   Trace with `missing <= k`:
   Iter 1: low=0, high=1 -> mid=1
           nums[1] = 3, missing = 3 - (1 + 1) = 1.
           Condition: missing <= k => (1 <= 1) -> TRUE!
           Action: low = mid + 1 = 2.

   Loop Ends (low=2, high=1):
   Formula: low + k = 2 + 1 = 3!
   💥 WRONG ANSWER: 3 array me already present hai, jabki answer 2 hona chahiye tha!

======================================================================
4. ONE-LINE TAKEAWAY:
   - `missing < k` ensure karta hai ki `high` hamesha target missing number ke 
     THEEK PEHLE (strictly before) ruke.
   - Taaki hum safe reh kar uske piche bache hue missing steps (`more = k - missing`) 
     aage jump kar sakein.
   - Agar `<=` laga diya, toh pointer us number ko bhi cross kar jayega jahan 
     already `k` numbers missing ho chuke the, aur answer galat aage shift ho jayega.
======================================================================
*/