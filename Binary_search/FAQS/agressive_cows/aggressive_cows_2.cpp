#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (AGGRESSIVE COWS - OPTIMAL BINARY SEARCH ON ANSWERS):
   - Problem:
     Hume `nums` array me stalls ke coordinates diye hain aur `total_cows` (k)
     cows di gayi hain. Hume cows ko stalls me aise baithana hai taaki kisi bhi
     do cows ke beech ka gap kam se kam 'distance' ho, aur us minimum distance ko
     jitna ho sake MAXIMIZE karna hai ("Maximize the Minimum Distance").

   - Monotonic Search Space (Decision Boundary):
     Pichle brute force code me hum distance `d = 1, 2, 3...` linearly test kar rahe the.
     Lekin notice karo ki ek clear monotonic transition exist karta hai:
       Distance:  1      2      3   |   4      5      6 ...
       Valid?    True   True   True | False  False  False
                                  ^
                            (Last True = Maximum Valid Distance = 3)
     - Agar distance chhota hai, cows aasaani se fit ho jati hain (True).
     - Jaise-jaise distance badhta hai, ek point ke baad cows place hona band ho jati hain (False).
     - Jab bhi search space me `[True, True, ..., True, False, False, ...]` ka pattern ho,
       hum wahan Binary Search laga sakte hain!

   - Search Space Boundary Ka Logic:
     - `low = 1`: Do cows ke beech minimum possible gap 1 unit ho sakta hai.
     - `high = nums[nums.size() - 1] - nums[0]`: 
       Extreme ends ke beech ka total gap maximum possible distance hai.
       (Note: Code me `high = nums[nums.size()-1]` likha hai, jo safe upper bound hai 
       kyunki max_element hamesha `(max_element - min_element)` se bada ya barabar hi hoga).

   - Polarity Shift & Return `high` (Sabse Important Trick):
     - Jab `canbeplaced(..., mid, ...) == true`:
       Distance valid hai! Cows aasaani se baith gayi. Lekin hume MAXIMUM possible 
       distance chahiye, toh hum aur bada gap try karne right half jayenge: `low = mid + 1`.
     - Jab `canbeplaced(...) == false`:
       Distance bohot bada ho gaya, cows place nahi ho payi. Gap chhota karne 
       left half aayenge: `high = mid - 1`.
     - Loop termination (`low > high`):
       `low` aage nikal kar pehle INVALID (False) distance par pahunch jata hai.
       `high` piche khisak kar theek aakhri VALID (True) distance par rukta hai.
       Isliye hum seedhe `return high;` karte hain!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `canbeplaced(nums, distance, total_cows)` ---
   - `int cow = 1, last = nums[0];`:
     Greedy approach: Pehli cow ko pehle stall par fix kar diya taaki aage wali cows 
     ke liye maximum space bache.
   - `if (nums[i] - last >= distance)`:
     Current stall aur last placed cow ke beech ka gap test kiya.
     - `cow += 1;` -> Agli cow successfully place ho gayi.
     - `last = nums[i];` -> Nayi cow ki position ko benchmark banaya.
   - `if (cow == total_cows) return true;`:
     Saari cows fit ho gayi, aage array check karne ki zaroorat nahi (Early exit).
   - `return false;`:
     Array khatam ho gaya par saari cows place nahi ho payi.

   --- `distance(nums, total_cows)` ---
   - `sort(nums.begin(), nums.end());`:
     Stalls ko number line par arrange kiya taaki adjacent distance measure karna possible ho.
   - `int low = 1, high = nums[nums.size() - 1];`:
     Possible distance answers ki range set ki.
   - `int mid = low + (high - low) / 2;`:
     Testing distance candidate calculate kiya.
   - `if (canbeplaced(...) == true) low = mid + 1;`:
     Gap valid hai, bada gap dhoondhne right half jao.
   - `else high = mid - 1;`:
     Gap invalid hai, chhota gap dhoondhne left half aao.
   - `return high;`:
     Polarity swap ke baad `high` largest valid answer par rukta hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [0, 3, 7, 4, 9, 10], total_cows = 4
   After sort: nums = [0, 3, 4, 7, 9, 10]
   low = 1, high = 10

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 1, high = 10
   mid = 1 + (10 - 1) / 2 = 5

   Call canbeplaced(nums, distance = 5, total_cows = 4):
     - Cow 1 placed at nums[0] = 0, last = 0
     - nums[1] = 3: (3 - 0 = 3 < 5)  -> Skip
     - nums[2] = 4: (4 - 0 = 4 < 5)  -> Skip
     - nums[3] = 7: (7 - 0 = 7 >= 5) -> Cow 2 placed at 7, last = 7
     - nums[4] = 9: (9 - 7 = 2 < 5)  -> Skip
     - nums[5] = 10: (10 - 7 = 3 < 5)-> Skip
     Array ends. Total cows placed = 2 (< 4).
     Returns FALSE.
   Action: high = mid - 1 = 5 - 1 = 4
   State: low = 1, high = 4

   --- Iteration 2 ---
   low = 1, high = 4
   mid = 1 + (4 - 1) / 2 = 2

   Call canbeplaced(nums, distance = 2, total_cows = 4):
     - Cow 1 placed at 0, last = 0
     - nums[1] = 3: (3 - 0 >= 2) -> Cow 2 placed at 3, last = 3
     - nums[2] = 4: (4 - 3 = 1 < 2) -> Skip
     - nums[3] = 7: (7 - 3 >= 2) -> Cow 3 placed at 7, last = 7
     - nums[4] = 9: (9 - 7 >= 2) -> Cow 4 placed at 9, last = 9
     cows placed == 4 -> TRUE!
   Action: low = mid + 1 = 2 + 1 = 3
   State: low = 3, high = 4

   --- Iteration 3 ---
   low = 3, high = 4
   mid = 3 + (4 - 3) / 2 = 3

   Call canbeplaced(nums, distance = 3, total_cows = 4):
     - Cow 1 placed at 0, last = 0
     - nums[1] = 3: (3 - 0 >= 3) -> Cow 2 placed at 3, last = 3
     - nums[2] = 4: (4 - 3 = 1 < 3) -> Skip
     - nums[3] = 7: (7 - 3 >= 3) -> Cow 3 placed at 7, last = 7
     - nums[4] = 9: (9 - 7 = 2 < 3) -> Skip
     - nums[5] = 10: (10 - 7 >= 3) -> Cow 4 placed at 10, last = 10
     cows placed == 4 -> TRUE!
   Action: low = mid + 1 = 3 + 1 = 4
   State: low = 4, high = 4

   --- Iteration 4 ---
   low = 4, high = 4
   mid = 4 + (4 - 4) / 2 = 4

   Call canbeplaced(nums, distance = 4, total_cows = 4):
     - Cow 1 placed at 0, last = 0
     - nums[1] = 3: (3 - 0 < 4)  -> Skip
     - nums[2] = 4: (4 - 0 >= 4) -> Cow 2 placed at 4, last = 4
     - nums[3] = 7: (7 - 4 < 4)  -> Skip
     - nums[4] = 9: (9 - 4 >= 4) -> Cow 3 placed at 9, last = 9
     - nums[5] = 10: (10 - 9 < 4)-> Skip
     Array ends. Total cows placed = 3 (< 4).
     Returns FALSE.
   Action: high = mid - 1 = 4 - 1 = 3
   State: low = 4, high = 3

   --- Loop Terminate ---
   Condition: low <= high (4 <= 3) -> FALSE! Loop ends.

   Final Boundaries:
   high = 3 (Aakhri valid distance jahan 4 cows place ho payi thi -> TRUE)
   low  = 4 (Pehla invalid distance jahan cows fit nahi hui -> FALSE)

   Returns high -> 3.
   Output: "The maximum value of minimum distance among cows is 3"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Sorting: `sort()` takes O(N * log N), jahan N stalls ka count hai.
     * Binary Search Range: Let Range = (max_element - min_element).
     * Binary search loop runs: O(log2(Range)) iterations.
     * Har iteration me `canbeplaced()` linearly array traverse karta hai: O(N).
     * Total Time Complexity: O(N * log N) + O(N * log2(Range)).
     * Brute force ke O(N * Range) ke muqable yeh massively fast hai 
       (e.g., coordinates 10^9 hone par bhi log2(10^9) sirf ~30 iterations lega).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard integer variables (`cow`, `last`, 
       `low`, `high`, `mid`) use hue hain. 
       Koi extra auxiliary array ya hashmap nahi banaya gaya.
======================================================================
*/

bool canbeplaced(vector <int> &nums,int distance,int total_cows){
    int cow=1,last=nums[0];
    for(int i=1;i<nums.size();i++){
        if(nums[i]-last>=distance){
            cow+=1;
            last=nums[i];
        }
        if(cow==total_cows){
            return true;
        }
    }
    return false;
}

int distance(vector <int>&nums,int total_cows){
    sort(nums.begin(),nums.end());
    int low=1,high=nums[nums.size()-1];
    while(low<=high){
        int mid=low+(high-low)/2;
        if(canbeplaced(nums,mid,total_cows)==true){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return high;
}

int main(){
    vector <int> nums={0,3,7,4,9,10};
    int total_cows=4;
    int min_dist=distance(nums,total_cows);
    cout<<"The maximum value of minimum distance among cows is "<<min_dist;
    return 0;
}