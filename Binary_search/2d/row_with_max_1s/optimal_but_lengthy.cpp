#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (BINARY SEARCH OPTIMIZATION - LOWER BOUND OF 1):
   - Problem:
     Hume ek 2D matrix di hai jisme har row individually SORTED hai (pehle 0s aate hain, fir 1s).
     Hume aisi row ka index return karna hai jisme sabse zyada 1s hon.
     Agar tie ho (multiple rows me barabar max 1s hon), toh sabse chhota index return karna hai.
     Agar matrix me ek bhi 1 na ho, toh -1 return karna hai.

   - Kyun Linear Sum/Count Faltu Tha Aur Binary Search Kyun Lagaya?
     Linear search me hum har element ko ek-ek karke add karte hain (O(N * M)).
     Lekin row SORTED hai!
     Sorted binary row ka structure hamesha aisa hota hai:
       [0,  0,  0,  1,  1,  1,  1]
                    ^
             first occurrence of 1
     Agar hum sirf yeh pata laga lein ki pehla '1' kis index par aaya hai (Lower Bound of 1),
     toh uske aage ke saare elements 1 hi honge.
     Toh 1-by-1 traverse karne ki zaroorat nahi hai:
       Total 1s in this row = columns - first_occurrence_index!
     Pehla 1 dhundhne me Linear Search O(M) leta hai, jabki Binary Search sirf O(log M) leta hai.

   - O(1) Pruning Optimization (nums[i][high] == 0):
     Kyunki row sorted hai, agar row ka aakhri element (nums[i][high]) hi 0 hai,
     toh us row me aage ya piche koi 1 ho hi nahi sakta (saare elements 0 hain).
     Aisi row par Binary Search chalana time waste hai, isliye seedhe continue karke skip kar diya.

   - Return / Polarity Trick:
     Jab Binary Search loop while(low <= high) terminate hota hai:
     - high aakhri 0 par rukta hai.
     - low hamesha PEHLE 1 ke index par aakar rukta hai.
     Isliye columns - low directly current row ke total 1s ka count de deta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - int max_1s = 0; int index = -1; :
     Agar matrix me pure 0s honge, toh columns - low > max_1s kabhi true nahi hoga
     aur index = -1 safely return hoga (Default guard).
   - if (nums[i][high] == 0) continue; :
     Instant Check O(1): Agar aakhri element hi 0 hai, toh row me koi 1 nahi ho sakta.
     Faltu binary search skip karo.
   - while(low <= high) :
     Current row me pehle 1 ka index dhundhne ke liye Binary Search.
     - if (nums[i][mid] == 0) low = mid + 1; :
       Mid par 0 hai, matlab pehla 1 right side hi aayega.
     - else high = mid - 1; :
       Mid par 1 hai, par yeh pehla 1 hai ya nahi? Left side check karne ke liye high = mid - 1.
   - if (columns - low > max_1s) :
     Loop terminate hone par low exact pehle 1 ke index par khada hota hai.
     columns - low ne direct total 1s calculate kiya.
     Strict > ensure karta hai ki tie hone par pehla (smaller index) retain rahe.
   - return index; :
     Maximum 1s wali row ka index return karta hai.

======================================================================
3. DETAILED DRY RUN:

   Input Matrix (5 rows, 5 columns -> columns = 5):
   Row 0: [0, 0, 1, 1, 1]
   Row 1: [0, 0, 0, 0, 0]
   Row 2: [0, 1, 1, 1, 1]
   Row 3: [0, 0, 0, 0, 0]
   Row 4: [0, 1, 1, 1, 1]

   Initial: max_1s = 0, index = -1

   -------------------------------------------------------------------
   --- Row 0: [0, 0, 1, 1, 1] ---
   nums[0][4] = 1 != 0 -> No skip.
   low = 0, high = 4
   - mid = 2: nums[0][2] = 1 -> high = mid - 1 = 1
   - mid = 0: nums[0][0] = 0 -> low = mid + 1 = 1
   - mid = 1: nums[0][1] = 0 -> low = mid + 1 = 2
   low > high (2 > 1) -> Loop ends. First 1 is at index low = 2.
   Total 1s = columns - low = 5 - 2 = 3.
   Compare: 3 > max_1s (3 > 0) -> TRUE!
   State: max_1s = 3, index = 0.

   --- Row 1: [0, 0, 0, 0, 0] ---
   nums[1][4] = 0 == 0 -> SKIP TRIGGERED (continue)!
   (Zero binary search operations, instant skip).

   --- Row 2: [0, 1, 1, 1, 1] ---
   nums[2][4] = 1 != 0 -> No skip.
   low = 0, high = 4
   - mid = 2: nums[2][2] = 1 -> high = 1
   - mid = 0: nums[2][0] = 0 -> low = 1
   - mid = 1: nums[2][1] = 1 -> high = 0
   low > high (1 > 0) -> Loop ends. First 1 is at low = 1.
   Total 1s = columns - low = 5 - 1 = 4.
   Compare: 4 > max_1s (4 > 3) -> TRUE!
   State: max_1s = 4, index = 2.

   --- Row 3: [0, 0, 0, 0, 0] ---
   nums[3][4] = 0 == 0 -> SKIP TRIGGERED (continue)!

   --- Row 4: [0, 1, 1, 1, 1] ---
   nums[4][4] = 1 != 0 -> No skip.
   Binary search finds first 1 at low = 1.
   Total 1s = 5 - 1 = 4.
   Compare: 4 > max_1s (4 > 4) -> FALSE (Strict inequality prevents overwrite).
   State: max_1s = 4, index = 2 (Index 2 retained).

   Loop Ends.
   Function returns index = 2.
   Output: "The maximum 1s are at 2"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Total rows = N, Total columns = M.
     * Har row ke liye Binary Search run hota hai jisme log2(M) steps lagte hain.
     * All-zero rows par instant O(1) pruning hoti hai.
     * Worst Case: O(N * log M) (jab saari rows me 1s maujood hon).
     * Brute Force O(N * M) ke comparison me bohot fast hai.
       Jaise M = 100000 par 100000 operations ke badle sirf lagbhag 17 operations lagenge.

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Koi extra memory, vector ya array allocate nahi hua.
     * Sirf standard integer pointers (rows, columns, max_1s, index, low, high, mid) use hue hain.
======================================================================
*/


int row_with_max_1s(vector <vector<int>> &nums){
    int rows = nums.size();
    int columns = nums[0].size();
    int max_1s = 0;
    int index = -1;
    for(int i = 0; i < rows; i++){
        int low = 0;
        int high = columns - 1;
        
        if(nums[i][high] == 0){
            continue;
        }

        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[i][mid] == 0){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }

        if(columns - low > max_1s){
            max_1s = columns - low;
            index = i;
        }
    }
    return index;
}

int main(){
    vector<vector<int>> mat = {
    {0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1}
};

    cout<<"The maximum 1s are at "<<row_with_max_1s(mat);
}