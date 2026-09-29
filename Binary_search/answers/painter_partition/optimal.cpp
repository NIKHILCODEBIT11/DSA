#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (PAINTER'S PARTITION - OPTIMAL BINARY SEARCH):
   - Problem:
     Hume `nums` array me boards ki lengths di gayi hain aur `assigned_painters` (k)
     painters diye gaye hain. Har painter ko continuous segment paint karna hai.
     Hume aisi allocation karni hai jisse kisi bhi painter ko jo maximum workload mile,
     wo MINIMIZE ho sake ("Minimize the Maximum Workload").

   - Core Intuition (Binary Search on Answer Space):
     Pichle brute force code me hum limit `i = low` se `high` tak ek-ek karke linearly
     check kar rahe the. Lekin agar dhyan se dekhein:
     - Workload capacity (`mid`) badhane se required painters ki ginti hamesha GHATTI hai 
       ya barabar rehti hai (Monotonic function).
     - Iska matlab pure search space me ek clear cutoff boundary exist karti hai:
       Workload Limit :  49 ... 70  |  71 ... 172
       Painters Needed:  > 4 ... > 4| <= 4 ... <= 4
       Valid?           False..False| True ... True
                                       ^
                                 (Smallest True chahiye = 71)

   - Range Decision Logic:
     - `low = *max_element(nums)`: Sabse bada single board (49) kisi na kisi ko paint 
       karna hi padega. Isse chhota answer mathematically impossible hai.
     - `high = accumulate(nums)`: Agar 1 hi painter hota toh saara kaam (sum = 172) 
       usi ko karna padta. Isse badi limit lene ki zaroorat nahi.

   - Opposite Polarity & Return `low`:
     - Jab `number_of_painters(nums, mid) > assigned_painters`:
       Bohot zyada painters lag gaye, matlab capacity limit bohot tight/chhoti hai.
       Limit badhao -> `low = mid + 1`.
     - Jab `number_of_painters(nums, mid) <= assigned_painters`:
       Kaam diye gaye painters me ho gaya (Valid candidate). Lekin hume MINIMUM capacity 
       chahiye, isliye aur chhota answer explore karo -> `high = mid - 1`.
     - Loop terminate hone ke baad (`low > high`), `high` rukta hai last INVALID capacity par
       aur `low` cross karke first VALID (optimal minimum) answer par pahunch jata hai.
       Isliye seedhe `return low;` answer deta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `number_of_painters(nums, block)` ---
   - `int painter = 1, block_size = 0;`:
     Pehle painter se kaam shuru kiya, uska initial workload 0 set kiya.
   - `if (block_size + nums[i] <= block) block_size += nums[i];`:
     Current board add karne par bhi limit cross nahi hui, usi painter ke account me add kiya.
   - `else { painter += 1; block_size = nums[i]; }`:
     Limit cross ho gayi! Agle painter ko bulaya (`painter += 1`) aur nayi board uske zimme ki.
   - `return painter;`:
     Given capacity `block` ke saath pure boards paint karne me kitne painters lage.

   --- `pages(nums, assigned_painters)` ---
   - `if (nums.size() < assigned_painters) return -1;`:
     Edge condition: Agar boards hi painters se kam hain, toh har painter ko at least 1 board 
     nahi mil sakta (agar har painter ko kaam milna mandatory ho).
   - `int low = *max_element(...); int high = accumulate(...);`:
     Binary search ka lower aur upper bound define kiya.
   - `int mid = low + (high - low) / 2;`:
     Overflow-safe candidate maximum capacity nikali.
   - `if (number_of_painters(...) > assigned_painters) low = mid + 1;`:
     Capacity bohot kam hai, badhao (Right half jao).
   - `else high = mid - 1;`:
     Capacity valid hai, par aur chhota answer dhoondho (Left half jao).
   - `return low;`:
     Optimal minimum answer.

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [25, 46, 28, 49, 24], assigned_painters = 4
   low = max(nums) = 49
   high = sum(nums) = 172

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 49, high = 172
   mid = 49 + (172 - 49) / 2 = 110

   Call number_of_painters(nums, block = 110):
     - nums[0]=25: P1 -> load = 25
     - nums[1]=46: P1 -> 25 + 46 = 71 <= 110
     - nums[2]=28: P1 -> 71 + 28 = 99 <= 110
     - nums[3]=49: 99 + 49 = 148 > 110 -> P2 -> load = 49
     - nums[4]=24: P2 -> 49 + 24 = 73 <= 110
     Total painters needed = 2
   Check: 2 > 4 -> FALSE (Valid! 2 painters <= 4)
   Action: high = mid - 1 = 110 - 1 = 109
   State: low = 49, high = 109

   --- Iteration 2 ---
   low = 49, high = 109
   mid = 49 + (109 - 49) / 2 = 79

   Call number_of_painters(nums, block = 79):
     - P1 gets [25, 46] = 71
     - P2 gets [28, 49] = 77
     - P3 gets [24]     = 24
     Total painters needed = 3
   Check: 3 > 4 -> FALSE (Valid!)
   Action: high = mid - 1 = 79 - 1 = 78
   State: low = 49, high = 78

   --- Iteration 3 ---
   low = 49, high = 78
   mid = 49 + (78 - 49) / 2 = 63

   Call number_of_painters(nums, block = 63):
     - P1: [25] -> 25
     - P2: [46] -> 46
     - P3: [28] -> 28
     - P4: [49] -> 49
     - P5: [24] -> 24
     Total painters needed = 5
   Check: 5 > 4 -> TRUE (Painters limit cross ho gayi!)
   Action: low = mid + 1 = 63 + 1 = 64
   State: low = 64, high = 78

   --- Iteration 4 ---
   low = 64, high = 78
   mid = 64 + (78 - 64) / 2 = 71

   Call number_of_painters(nums, block = 71):
     - P1: [25, 46] = 71 <= 71
     - P2: [28]     = 28
     - P3: [49]     = 49
     - P4: [24]     = 24
     Total painters needed = 4
   Check: 4 > 4 -> FALSE (Valid!)
   Action: high = mid - 1 = 71 - 1 = 70
   State: low = 64, high = 70

   --- Iteration 5 ---
   low = 64, high = 70
   mid = 64 + (70 - 64) / 2 = 67
   Call number_of_painters(nums, block = 67):
     Total painters = 5 (> 4) -> TRUE
   Action: low = mid + 1 = 67 + 1 = 68
   State: low = 68, high = 70

   --- Iteration 6 ---
   low = 68, high = 70
   mid = 68 + (70 - 68) / 2 = 69
   Call number_of_painters(nums, block = 69):
     Total painters = 5 (> 4) -> TRUE
   Action: low = mid + 1 = 69 + 1 = 70
   State: low = 70, high = 70

   --- Iteration 7 ---
   low = 70, high = 70
   mid = 70
   Call number_of_painters(nums, block = 70):
     Total painters = 5 (> 4) -> TRUE
   Action: low = mid + 1 = 70 + 1 = 71
   State: low = 71, high = 70

   --- Loop Terminate ---
   Condition: low <= high (71 <= 70) -> FALSE! Loop ends.

   Final Boundaries:
   high = 70 (Last invalid capacity)
   low  = 71 (First valid optimal capacity)

   Returns low -> 71.
   Output: 71.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Sum = sum of all boards, Max = max element in nums.
     * Finding initial min/max: `*max_element` O(N), `accumulate` O(N).
     * Binary Search space = (Sum - Max + 1).
     * Binary search loop runs: O(log2(Sum - Max)) iterations.
     * Har iteration me `number_of_painters()` poora array scan karta hai: O(N).
     * Total Time Complexity: O(N * log2(Sum - Max)).
     * Brute force ke O(N * (Sum - Max)) ke muqable yeh massively fast hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard primitive variables (`low`, `high`, `mid`, 
       `painter`, `block_size`) use hue hain. Zero extra memory overhead.
======================================================================
*/

int number_of_painters(vector <int>&nums,int block){
    int painter=1, block_size=0;
    for(int i=0;i<nums.size();i++){
        if(block_size+nums[i]<=block){
            block_size+=nums[i];
        }
        else{
            painter+=1;
            block_size=nums[i];
        }
    }
    return painter;
}

int pages(vector<int>&nums,int assigned_painters){

    // added as per in explaination comment
    if(nums.size() < assigned_painters){   // kyuki har student ko kam se kam ek book to milni hi chhiye par agar total 5 books hain lekin bacche 6 hain us case mein koi ek bacha to hoga jise koi book nahi milega us case mein ye return book allocation nahi kiya ja sakta
        return -1;
    }

    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    while(low<=high){
        int mid=low+(high-low)/2;
        if(number_of_painters(nums,mid)>assigned_painters){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low;
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int assigned_painters=4;
    cout<<"The maximum number of pages assigned to any student is :-"<<pages(nums,assigned_painters);
    return 0;
}