#include <bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (AGGRESSIVE COWS - BRUTE FORCE):
   - Problem:
     Hume `nums` array me stalls ke coordinates diye hain aur `total_cows` (k)
     cows di gayi hain. Hume cows ko stalls me aise baithana hai taaki kisi bhi
     do cows ke beech ka distance jitna ho sake BADA ho.
     Objective: "Maximize the Minimum Distance Between Any Two Cows".

   - Real-Life Analogy:
     Cows aggressive hain, agar do cows paas baithi toh aapas me ladengi.
     Isliye hum unhe jitna door-door ho sake utna door rakhna chahte hain.
     Hum ek testing distance `d` decide karte hain:
     "Kya hum saari cows ko aise place kar sakte hain ki har do cows ke beech 
     kam se kam `d` ka gap ho?"

   - Sorting Kyun Mandatory Hai?
     Real number line par agar positions sorted nahi hongi, toh hume pata hi 
     nahi chalega ki kaunsa stall kiske bagal me hai. Sort karne ke baad stalls 
     left-to-right line me aa jate hain, jisse greedy placement possible ho pati hai.

   - Greedy Placement Strategy (`canBePlaced`):
     - Pehli cow ko hamesha pehle sorted stall (`nums[0]`) par hi baithana sabse 
       optimal hota hai, taaki aage aane wali cows ke liye maximum jagah bache.
     - Agle stalls traverse karte jao: jaise hi koi aisa stall mile jiska gap 
       pichli cow se `>= distance` ho, turant wahan agli cow baitha do.
     - Agar saari cows baith gayi -> TRUE, warna FALSE.

   - Search Space Boundary Ka Exact Logic:
     - Minimum possible distance: `1` (Agar adjacent stalls 1 unit door ho).
     - Maximum possible distance: `nums.back() - nums.front()` 
       (Extreme left aur extreme right stalls ke beech ka total gap. 
       Isse bada distance mathematically exist hi nahi kar sakta).
     - Search range: `[1 ... max_possible_dist]`.

   - Brute Force Progression (Linear Check):
     - Jaise-jaise distance `d` BADHTA hai, cows ko place karna MUSHKIL hota jata hai.
     - Validity Pattern:
       Distance `d`:  1    2    3    4  |  5    6 ...
       Valid?       True True True True | False False
                                       ^
       Hume LAST TRUE (Maximum valid distance) nikalna hai.
     - Jaise hi distance `d` par placement fail (`false`) ho jaye, iska matlab theek 
       pichla distance `d - 1` hi humara maximum possible answer tha!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `canBePlaced(nums, distance, total_cows)` ---
   - `int cows_count = 1; int last_position = nums[0];`:
     Greedy start: Pehli cow ko pehle stall par baitha diya aur count 1 kar diya.
   - `if (nums[i] - last_position >= distance)`:
     Check kiya: Kya current stall aur pichli cow ke beech kam se kam `distance` ka gap hai?
     - `cows_count++;` -> Agli cow place kar di.
     - `last_position = nums[i];` -> Ab naye benchmark ke liye pichli cow ki position update kar di.
   - `if (cows_count >= total_cows) return true;`:
     Saari cows successfully place ho gayi, aage scan karne ki zaroorat nahi.
   - `return false;`:
     Array khatam ho gaya par saari cows place nahi ho payi.

   --- `min_distance_brute_force(nums, total_cows)` ---
   - `if (nums.size() < total_cows) return -1;`:
     Agar stalls hi cows se kam hain, toh ek stall par do cows nahi baith sakti -> Impossible.
   - `sort(nums.begin(), nums.end());`:
     Stalls ko number line par arrange kiya taaki adjacent distance measure ho sake.
   - `int max_possible_dist = nums.back() - nums.front();`:
     Absolute maximum possible gap nikala.
   - `for (int d = 1; d <= max_possible_dist; d++)`:
     Gap 1 se shuru karke linearly ek-ek gap bada karke dekha.
   - `if (canBePlaced(...)) continue; else return d - 1;`:
     Jab tak valid hai aage bado; jaise hi fail ho, pichla valid gap `d - 1` return kar do.
   - `return max_possible_dist;`:
     Agar maximum gap par bhi cows baith gayi (e.g., total_cows = 2), toh extreme ends ka gap answer hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [0, 3, 7, 4, 9, 10], total_cows = 4
   After sort: nums = [0, 3, 4, 7, 9, 10]
   n = 6 stalls
   max_possible_dist = 10 - 0 = 10

   -------------------------------------------------------------------
   --- Test d = 1 ---
   canBePlaced(nums, d = 1, cows = 4):
   - Cow 1 placed at nums[0] = 0
   - nums[1] = 3: (3 - 0 >= 1) -> Cow 2 placed at 3
   - nums[2] = 4: (4 - 3 >= 1) -> Cow 3 placed at 4
   - nums[3] = 7: (7 - 4 >= 1) -> Cow 4 placed at 7
   cows_count = 4 >= 4 -> TRUE.
   Action: continue (aur bada gap try karo).

   --- Test d = 2 ---
   canBePlaced(nums, d = 2, cows = 4):
   - Cow 1 at 0
   - nums[1] = 3: (3 - 0 >= 2) -> Cow 2 at 3
   - nums[2] = 4: (4 - 3 = 1 < 2) -> Skip stall 4
   - nums[3] = 7: (7 - 3 >= 2) -> Cow 3 at 7
   - nums[4] = 9: (9 - 7 >= 2) -> Cow 4 at 9
   cows_count = 4 >= 4 -> TRUE.
   Action: continue.

   --- Test d = 3 ---
   canBePlaced(nums, d = 3, cows = 4):
   - Cow 1 at 0
   - nums[1] = 3: (3 - 0 >= 3) -> Cow 2 at 3
   - nums[2] = 4: (4 - 3 = 1 < 3) -> Skip stall 4
   - nums[3] = 7: (7 - 3 >= 3) -> Cow 3 at 7
   - nums[4] = 9: (9 - 7 = 2 < 3) -> Skip stall 9
   - nums[5] = 10: (10 - 7 >= 3) -> Cow 4 at 10
   cows_count = 4 >= 4 -> TRUE.
   All 4 cows placed at positions: [0, 3, 7, 10] (all gaps >= 3).
   Action: continue.

   --- Test d = 4 ---
   canBePlaced(nums, d = 4, cows = 4):
   - Cow 1 at 0
   - nums[1] = 3: (3 - 0 < 4) -> Skip
   - nums[2] = 4: (4 - 0 >= 4) -> Cow 2 at 4
   - nums[3] = 7: (7 - 4 < 4) -> Skip
   - nums[4] = 9: (9 - 4 >= 4) -> Cow 3 at 9
   - nums[5] = 10: (10 - 9 < 4) -> Skip
   Array khatam ho gaya! Only 3 cows placed, but need 4.
   Result: FALSE!

   --- Result Trigger ---
   At d = 4, condition failed!
   Code executes: `return d - 1` => `return 4 - 1` = 3.
   Output: "The maximum value of minimum distance among cows is: 3"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Sorting: `sort()` array par chalta hai -> O(N * log N).
     * Linear Search Range: `max_possible_dist = (max_val - min_val)`.
     * Har distance `d` ke liye `canBePlaced()` pura array scan karta hai: O(N).
     * Total Time Complexity: O(N * log N) + O(N * (max_val - min_val)).
     * Agar stall coordinates 10^9 tak ho, toh (max_val - min_val) bohot bada hoga 
       aur yeh TLE de dega.
       (Is linear loop ko Binary Search on Answers se O(N * log(max_val - min_val)) 
       me convert karke optimize kiya jata hai).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf loop variables (`d`, `cows_count`, `last_position`, 
       `max_possible_dist`) use hue hain. 
       Sorting algorithms internal stack frame le sakte hain (O(log N) for `std::sort`), 
       par koi extra dynamic array allocate nahi hui.
======================================================================
*/


// Helper: Check karta hai kya 'distance' gap par saari cows place ho sakti hain
bool canBePlaced(const vector<int>& nums, int distance, int total_cows) {
    int cows_count = 1;
    int last_position = nums[0]; // Pehli cow hamesha pehle sorted stall par baithegi

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] - last_position >= distance) {
            cows_count++;
            last_position = nums[i]; // Agli cow place kardi, last position update
        }
        if (cows_count >= total_cows) {
            return true; // Saari cows place ho gayi
        }
    }
    return false;
}

int min_distance_brute_force(vector<int>& nums, int total_cows) {
    // Edge case: Agar stalls cows se kam hain
    if (nums.size() < total_cows) return -1;

    // Step 1: Stalls ko sort karna mandatory hai
    sort(nums.begin(), nums.end());

    int max_possible_dist = nums.back() - nums.front();

    // Step 2: Distance 1 se lekar maximum possible distance tak linearly test karo
    for (int d = 1; d <= max_possible_dist; d++) {
        if (canBePlaced(nums, d, total_cows)) {
            continue; // Agar 'd' par place ho rahi hain, toh aage badh kar aur bada gap check karo
        } else {
            // Jaise hi 'd' par fail ho, iska matlab isse theek pehle wala gap (d - 1) hamara maximum valid answer tha
            return d - 1;
        }
    }

    // Agar pure range (d = max_possible_dist) tak true raha (jaise cows = 2 ho)
    return max_possible_dist;
}

int main() {
    vector<int> nums = {0, 3, 7, 4, 9, 10};
    int total_cows = 4;
    int ans = min_distance_brute_force(nums, total_cows);
    cout << "The maximum value of minimum distance among cows is: " << ans << "\n";
    return 0;
}