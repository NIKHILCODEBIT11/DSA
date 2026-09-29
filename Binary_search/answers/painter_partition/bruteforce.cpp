#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (PAINTER'S PARTITION / SPLIT ARRAY LARGEST SUM):
   - Problem:
     Hume `nums` array me boards/walls ki length di gayi hai aur `assigned_painters` (k)
     painters diye gaye hain.
     Rules:
     1. Har painter CONTIGUOUS (lagataar) boards hi paint karega.
     2. 1 unit board paint karne me 1 unit time lagta hai.
     3. Objective: Saara kaam khatam karne ka MINIMUM time nikalna hai.
        Kyunki saare painters ek saath (parallel) kaam karte hain, 
        isliye total time wahi hoga jo "US PAINTER ka time hoga jisne MAXIMUM boards paint kiye".
        Matlab: "Minimize the Maximum Work Assigned to Any Painter".

   - Book Allocation Se 100% Mirror Problem:
     - Books  ----->  Boards / Walls ki length (`nums`)
     - Pages  ----->  Painting units / time (`block`)
     - Students ---->  Painters (`assigned_painters`)
     Dono problems ka mathematical backbone EXACTLY SAME hai!

   - Search Space Boundary Ka Reasoning:
     1. Minimum Possible Limit (`low` = `max_element(nums)` = 49):
        Array ka sabse lamba board (49 units) kisi na kisi painter ko akele 
        paint karna hi padega. Agar ceiling limit 49 se kam rakhi, toh wo board 
        kabhi paint hi nahi ho payega!
     2. Maximum Possible Limit (`high` = `accumulate(nums)` = 172):
        Agar sirf 1 hi painter hota, toh saare boards usi ko paint karne padte 
        (total time = 172). Isse badi limit ka koi practical matlab nahi.
     - Search range: `[max_element ... sum_of_elements]` yaani `[49 ... 172]`.

   - Linear Search (Brute Force) Approach:
     Hum minimum barrier `low` = 49 se start karke ek-ek limit test karte hain.
     Pehli aisi limit jahan required painters `<= assigned_painters` ho jayein, 
     wahi humara answer hai, kyunki hum sabse chhota barrier dhoondh rahe hain.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `number_of_painters(nums, block)` ---
   - `int painter = 1, block_size = 0;`:
     Pehle painter se kaam shuru karwaya (`painter = 1`), aur uska current work load 0 rakha.
   - `if (block_size + nums[i] <= block) block_size += nums[i];`:
     Current board dene ke baad bhi limit cross nahi hui, usi painter ko agla board de diya.
   - `else { painter += 1; block_size = nums[i]; }`:
     Limit exceed ho gayi! Current painter ka kaam yahan khatam, naya painter bulaya 
     (`painter += 1`), aur yeh board naye painter ka pehla kaam bana.
   - `return painter;`:
     Is specific capacity/limit `block` par saare boards paint karne ke liye 
     total kitne painters lagenge.

   --- `walls(nums, assigned_painters)` ---
   - `if (nums.size() < assigned_painters) return -1;`:
     Corner condition: Agar boards hi painters se kam hon, toh allocation impossible hai.
   - `int low = *max_element(...); int high = accumulate(...);`:
     Minimum possible single workload se leke total workload tak search space banaya.
   - `for(int i = low; i <= high; i++)`:
     Ek-ek limit ko linearly check kiya (49, 50, 51...).
   - `if (count_student <= assigned_painters) return i;`:
     Jaise hi pehli limit mili jahan painters limit ke andar manage ho gaye, 
     turant wahi answer return kar diya (kyunki lower limits pehle check hui hain).

======================================================================
3. DETAILED DRY RUN:

   Input: nums = [25, 46, 28, 49, 24], assigned_painters = 4
   low = max(nums) = 49
   high = sum(nums) = 172

   -------------------------------------------------------------------
   --- Step 1: Check limit i = 49 ---
   Call number_of_painters(nums, block = 49):
     - Board 0 (25): P1 -> load = 25
     - Board 1 (46): 25 + 46 = 71 > 49 -> P2 -> load = 46
     - Board 2 (28): 46 + 28 = 74 > 49 -> P3 -> load = 28
     - Board 3 (49): 28 + 49 = 77 > 49 -> P4 -> load = 49
     - Board 4 (24): 49 + 24 = 73 > 49 -> P5 -> load = 24
     Total painters needed = 5.
   Check: 5 <= 4 -> FALSE (49 ki limit par 5 painters chahiye, allowed sirf 4 hain).

   --- Step 2: Check limits i = 50 to 70 ---
   In sabhi values par consecutive boards ka sum break hota rahega aur 
   har baar total painters > 4 hi rahenge -> Sabhi FALSE.

   --- Step 3: Check limit i = 71 ---
   Call number_of_painters(nums, block = 71):
     - Board 0 (25): P1 -> load = 25
     - Board 1 (46): 25 + 46 = 71 <= 71 -> P1 handles both! load = 71
     - Board 2 (28): 71 + 28 = 99 > 71  -> P2 -> load = 28
     - Board 3 (49): 28 + 49 = 77 > 71  -> P3 -> load = 49
     - Board 4 (24): 49 + 24 = 73 > 71  -> P4 -> load = 24
     Total painters needed = 4.
   Check: 4 <= 4 -> TRUE!

   Painter Work Distribution at limit 71:
     Painter 1: [25, 46] -> 71 units
     Painter 2: [28]     -> 28 units
     Painter 3: [49]     -> 49 units
     Painter 4: [24]     -> 24 units
     Max work done by any single painter = max(71, 28, 49, 24) = 71.

   Action:
     Pehla valid answer 71 mil gaya, loop breaks and returns 71.
     Output: "The maximum number of walls assigned to any painter is :- 71"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = nums.size(), Sum = sum of all elements, Max = max element in nums.
     * Range = (Sum - Max + 1).
     * Linear loop chalta hai: (Sum - Max + 1) times.
     * Har step par `number_of_painters()` array par iterate karta hai: O(N).
     * Total Time Complexity: O(N * (Sum - Max + 1)).
     * For large constraints, yeh TLE dega. Isko Binary Search se O(N * log(Sum - Max)) 
       me optimize kiya ja sakta hai.

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard primitive variables 
       (`painter`, `block_size`, `low`, `high`, `i`) use hue hain.
       Koi extra auxiliary data structure allocate nahi kiya gaya.
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

int walls(vector <int>&nums,int assigned_painters){
    if(nums.size() < assigned_painters){   // kyuki har student ko kam se kam ek book to milni hi chhiye par agar total 5 books hain lekin bacche 6 hain us case mein koi ek bacha to hoga jise koi book nahi milega us case mein ye return book allocation nahi kiya ja sakta
        return -1;
    }

    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    for(int i=low;i<=high;i++){
        int count_student=number_of_painters(nums,i);
        if(count_student<=assigned_painters){
            return i;
        }
    }
}

int main(){
    vector <int> nums={25,46,28,49,24};
    int assigned_painters=4;
    cout<<"The maximum number of walls assigned to any painter is :-"<<walls(nums,assigned_painters);
    return 0;
}