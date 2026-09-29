#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (MINIMUM DAYS TO MAKE M BOUQUETS - BINARY SEARCH):
   - Problem:
     Hume ek array `nums` (bloomDay) diya hai jahan `nums[i]` batata hai ki phool kis din khilega.
     Hume `m` bouquets banane hain, aur har bouquet me `k` ADJACENT (lagataar) bloomed phool chahiye.
     Hume wo MINIMUM din nikalna hai jab hum `m` bouquets successfully bana sakein.

   - Monotonic Property (Binary Search kyun lagega?):
     - Minimum din jahan se checking shuru ho sakti hai: min_element(nums).
     - Maximum din jahan tak sabhi phool khil chuke honge: max_element(nums).
     - Jaise jaise din aage badhenge (days increase honge), phool sirf khilenge, murjhayenge nahi!
       Matlab available khile hue phoolon ki sankhya badhegi ya barabar rahegi, kabhi kam nahi hogi.
     - Search Space Pattern across [min_element ... max_element]:
       Days:      min   ...     d-1      d       d+1   ...    max
       Valid?   [ False ...    False |  True    True   ...   True ]
     - Kyunki transition ek monotonic barrier follow karta hai (False to True), 
       hum Linear Search (O(Max - Min)) ki jagah Binary Search (O(log(Max - Min))) laga sakte hain!

   - ChatGPT Ke Code Par Tumhara Point: "It is completely useless" -> 100% SPOT ON!
     Tumhara intuition bilkul solid hai:
     Agar `nums.size() >= (long long)m * k` hai, toh `maxDay` tak array ke SAARE phool khil chuke honge.
     Jab saare n phool khil chuke hain, toh unme se continuous chunks me total kitne bouquets banenge?
     Array ke saare n phool continuously available hain, toh total banenge: n / k bouquets.
     Kyunki n >= m * k diya hua hai, toh: n / k >= (m * k) / k => n / k >= m.
     Matlab maxDay par m bouquets banna MATHEMATICALLY GUARANTEED hai!
     Isliye `if (!possible(nums, maxDay, m, k))` check karna 100% redundant aur bekaar tha.

   - Why Returning `low` Works (Polarity Switch):
     - `low` shuru hota hai NOT POSSIBLE zone me (False side).
     - `high` shuru hota hai POSSIBLE zone me (True side).
     - Whenever possible(mid) == true:
       Bouquets ban gaye, par hume MINIMUM day chahiye, toh left check karo: `high = mid - 1`.
     - Whenever possible(mid) == false:
       Phool kam khile hain, time badhana padega: `low = mid + 1`.
     - Jab loop terminate hota hai (`low > high`):
       `high` slip hokar last FALSE day par baith jata hai.
       `low` cross hokar theek first TRUE day (MINIMUM valid day) par rukta hai!
       Isliye seedhe `return low;` answer deta hai.

   - Overflow Guard (`m * 1ll * k * 1ll`):
     LeetCode par m aur k 10^6 tak hote hain, toh `m * k = 10^12` ho sakta hai jo 32-bit int 
     ko overflow kar deta hai. `1ll` se multiply karke `long long` me convert karna bilkul correct hai!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `possible(nums, days, m, k)` ---
   - `int no_of_bouquet = 0, counter = 0;`:
     `counter` continuous khile hue phool count karta hai; `no_of_bouquet` total bouquets store karta hai.
   - `if (nums[i] <= days) counter++;`:
     Phool khil chuka hai, lagataar khile phoolon ki chain 1 badhi.
   - `else { no_of_bouquet += counter / k; counter = 0; }`:
     Beech me phool nahi khila mila, chain toot gayi. Jitne bouquets bane unhe add kiya aur counter reset.
   - `no_of_bouquet += counter / k;`:
     Loop ke baad aakhri chain ke bouquets add kiye.
   - `return no_of_bouquet >= m;`:
     Target m bouquets ban paye ya nahi, uska boolean result diya.

   --- `final_days(nums, m, k)` ---
   - `long long val = m * 1ll * k * 1ll; if (nums.size() < val) return -1;`:
     Agar array ke total phool hi requirement se kam hain, toh answer namumkin hai -> return -1.
   - `int low = min_max.first, high = min_max.second;`:
     Binary search boundaries set ki.
   - `int mid = low + (high - low) / 2;`:
     Overflow-safe middle day calculate kiya.
   - `if (possible(nums, mid, m, k)) high = mid - 1;`:
     Bouquet ban rahe hain, par smaller day dhundhne left half compress kiya.
   - `else low = mid + 1;`:
     Bouquet nahi ban paye, din badhane ke liye right half shift kiya.
   - `return low;`:
     Loop terminate hone par `low` theek first possible day par khada rehta hai.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [7, 8, 9, 10, 12, 13], m = 2, k = 3
   nums.size() = 6
   Required flowers: m * k = 2 * 3 = 6
   nums.size() < 6 ? (6 < 6) -> False (Possible, proceed)
   min_element = 7, max_element = 13
   Initial: low = 7, high = 13

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 7, high = 13
   mid = 7 + (13 - 7) / 2 = 10

   Call possible(nums, days = 10, m = 2, k = 3):
     nums = [7, 8, 9, 10, 12, 13]
     - i=0: nums[0]=7 <= 10  -> counter = 1
     - i=1: nums[1]=8 <= 10  -> counter = 2
     - i=2: nums[2]=9 <= 10  -> counter = 3
     - i=3: nums[3]=10 <= 10 -> counter = 4
     - i=4: nums[4]=12 > 10  -> Break! 
            no_of_bouquet += 4 / 3 = 1 bouquet. counter = 0.
     - i=5: nums[5]=13 > 10  -> Break! counter = 0.
     After loop: no_of_bouquet += 0 / 3 = 1.
     Check: no_of_bouquet >= m (1 >= 2) -> FALSE (NOT POSSIBLE).

   Action:
     Din badhao -> low = mid + 1 = 10 + 1 = 11.
   State: low = 11, high = 13

   --- Iteration 2 ---
   low = 11, high = 13
   mid = 11 + (13 - 11) / 2 = 12

   Call possible(nums, days = 12, m = 2, k = 3):
     nums = [7, 8, 9, 10, 12, 13]
     - i=0: nums[0]=7 <= 12  -> counter = 1
     - i=1: nums[1]=8 <= 12  -> counter = 2
     - i=2: nums[2]=9 <= 12  -> counter = 3
     - i=3: nums[3]=10 <= 12 -> counter = 4
     - i=4: nums[4]=12 <= 12 -> counter = 5
     - i=5: nums[5]=13 > 12  -> Break!
            no_of_bouquet += 5 / 3 = 1 bouquet. counter = 0.
     After loop: no_of_bouquet += 0 / 3 = 1.
     Check: no_of_bouquet >= m (1 >= 2) -> FALSE (NOT POSSIBLE).

   Action:
     Din badhao -> low = mid + 1 = 12 + 1 = 13.
   State: low = 13, high = 13

   --- Iteration 3 ---
   low = 13, high = 13
   mid = 13 + (13 - 13) / 2 = 13

   Call possible(nums, days = 13, m = 2, k = 3):
     Saare 6 phool khil chuke hain (nums[i] <= 13 for all i).
     counter = 6 tak jayega.
     After loop: no_of_bouquet = 6 / 3 = 2 bouquets.
     Check: no_of_bouquet >= m (2 >= 2) -> TRUE (POSSIBLE).

   Action:
     Candidate mil gaya, left jao:
     high = mid - 1 = 13 - 1 = 12.
   State: low = 13, high = 12

   --- Loop Terminate ---
   Condition: low <= high (13 <= 12) -> FALSE! Loop ends.

   Polarity Switch Summary:
   Days:        7     8     9     10    11    12  |  13
   Status:     No    No    No     No    No    No  |  Yes
                                               ^      ^
                                              high   low

   high = 12 (Last False day)
   low  = 13 (First True day / MINIMUM valid days)

   Return low -> 13.
   Output: "The minimum no of days are 13"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Min = min_element(nums), Max = max_element(nums).
     * `min_and_max()` scan karta hai array: O(N).
     * Binary Search space range = (Max - Min). Iterations = O(log2(Max - Min)).
     * Har iteration me `possible()` function pure array par loop chalata hai: O(N).
     * Total Time Complexity: O(N) + O(N * log2(Max - Min)) = O(N * log2(Max - Min)).
     * Brute force O(N * (Max - Min)) ke muqable exponentially faster hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard primitive variables
       (`low`, `high`, `mid`, `counter`, `no_of_bouquet`, `val`) use hue hain.
       Memory completely constant hai.
======================================================================
*/



// BINARY SEARCH :-
/*

Why i followed binary search :-

Surely the possibility of "number of final days" is in different continous parts of "nums" 

                    7       8       9       10        12       13
                   not     not     not     not        yes      yes

Since, i know answer lying in right side is possible and on left side is not possible so i can use binary search

*/


bool possible(vector <int> &nums,int days,int m,int k){
    int no_of_bouquet=0,counter=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<=days){
            counter++;
        }else{
            no_of_bouquet+=counter/k;
            counter=0;
        }
    }
    no_of_bouquet+=counter/k;
    if(no_of_bouquet>=m){
        return true;
    }
    else{
        return false;
    }
}

pair <int,int> min_and_max(vector <int> &nums){
    int min=INT_MAX,max=INT_MIN;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<min){
            min=nums[i];
        }
        if(nums[i]>max){
            max=nums[i];
        }
    }
    return {min,max};
}

int final_days(vector <int> &nums,int m,int k){
    long long val=m*1ll*k*1ll;
    if(nums.size()<val){
        return -1;
    }
    auto min_max=min_and_max(nums);
    int low=min_max.first,high=min_max.second;
    /*
    int maxDay = *max_element(nums.begin(), nums.end());
    if (!possible(nums, maxDay, m, k))
        return -1;

    It is completely useless given by chatgpt

    */

    // The reason of not returning -1 at end of final_days is that as i know, SURELY that answer exists so there is NO CHANCE OF GETTING NO ANSWER, and the only problematic scenariois checked for days<m*k
    while(low<=high){
        int mid=low+(high-low)/2;
        if(possible(nums,mid,m,k)){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;
}

int main(){
    vector <int> nums={7,8,9,10,12,13};
    int m=2,k=3;
    cout<<"The minimum no of days are "<<final_days(nums,m,k);
    return 0;
}