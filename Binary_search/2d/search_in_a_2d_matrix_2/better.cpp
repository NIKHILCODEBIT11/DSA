#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (ROW-BY-ROW BINARY SEARCH):
   - Problem:
     Hume ek 2D matrix di gayi hai jisme har row individually sorted hai.
     Matrix me `target` element search karna hai aur uska exact cell coordinate 
     `{row_index, col_index}` return karna hai. Agar target na mile toh `{-1, -1}` return karna hai.

   - Code Evolution & Intuition:
     - Brute Force approach me hum pure matrix ke har cell ko check karte hain (Time: O(N * M)).
     - Kyunki har row INDIVIDUALLY SORTED hai, hume row ke andar linear search karne 
       ki bilkul zaroorat nahi hai!
     - Hum matrix ki har row par ek independent 1D Binary Search chala sakte hain:
       * Row 0 par Binary Search lagao (O(log M)). Agar target mil gaya, wahi coordinate return karo.
       * Agar nahi mila, toh agli row (Row 1) par Binary Search lagao.
       * Yeh process tab tak repeat karo jab tak target na mil jaye ya saari rows khatam na ho jayein.
     - Isse time complexity seedhe O(N * M) se ghatkar O(N * log M) ho jati hai.

   - Fixes Verified in this Version:
     1. `int high = nums.size() - 1;` -> Bounds bilkul correct hain, koi out-of-bounds risk nahi.
     2. `int ind = -1;` declare karke loop me `ind = binary(...)` use kiya gaya hai -> Variable shadowing resolved!

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `binary(vector<int> &nums, int target)` ---
   - `int low = 0; int high = nums.size() - 1;`:
     1D binary search ke valid boundaries set kiye (0-indexed array ka pehla aur aakhri element).
   - `while(low <= high)`:
     Search space jab tak valid hai tab tak chalega.
   - `int mid = (low + high) / 2;`:
     Midpoint element calculate kiya.
   - `if (nums[mid] == target) return mid;`:
     Target exact match ho gaya, column index `mid` return karke function exit.
   - `else if (nums[mid] <= target) low = mid + 1;`:
     Target bada hai, search space right half me narrow kiya.
     *(Clean code note: Kyunki upar == target handle ho chuka hai, yahan `<` bhi likh sakte hain).*
   - `else high = mid - 1;`:
     Target chhota hai, search space left half me narrow kiya.
   - `return -1;`:
     Pura search space exhaust ho gaya par element nahi mila.

   --- `search_2d(vector<vector<int>> &nums, int target)` ---
   - `int row = nums.size(); int column = nums[0].size();`:
     Matrix ke grid dimensions measure kiye.
   - `int ind = -1;`:
     Column index store karne ke liye variable initialize kiya.
   - `for(int i = 0; i < row; i++)`:
     Ek-ek karke har row ko visit karne ke liye loop.
   - `ind = binary(nums[i], target);`:
     Current row `nums[i]` par 1D Binary Search call kiya.
   - `if (ind != -1) return {i, ind};`:
     Early Exit! Jaise hi kisi row me element mila (`ind != -1`), turant `{row, column}` 
     pair return karke function terminate kar diya.
   - `return {-1, -1};`:
     Saari rows check ho gayi aur target kisi bhi row me nahi mila.

======================================================================
3. DETAILED DRY RUN:

   Matrix (row = 4, column = 5):
   Row 0: [ 2,  4,  6,  7,  9]
   Row 1: [21, 23, 25, 26, 27]
   Row 2: [29, 32, 33, 34, 36]
   Row 3: [37, 39, 40, 42, 26]

   Target = 34

   -------------------------------------------------------------------
   --- Step 1: i = 0 (Row 0) ---
   Call binary(nums[0], 34):
     nums[0] = [2, 4, 6, 7, 9]
     low = 0, high = 4
     mid = 2 -> nums[0][2] = 6 < 34 -> low = 3
     mid = 3 -> nums[0][3] = 7 < 34 -> low = 4
     mid = 4 -> nums[0][4] = 9 < 34 -> low = 5
     low > high (5 > 4) -> Loop ends, returns -1.
   ind = -1. Condition `ind != -1` is FALSE. Loop continues.

   --- Step 2: i = 1 (Row 1) ---
   Call binary(nums[1], 34):
     nums[1] = [21, 23, 25, 26, 27]
     Saare elements 34 se chhote hain -> binary search exhaust hokar returns -1.
   ind = -1. Condition `ind != -1` is FALSE. Loop continues.

   --- Step 3: i = 2 (Row 2) ---
   Call binary(nums[2], 34):
     nums[2] = [29, 32, 33, 34, 36]
     low = 0, high = 4

     - Iteration 1:
       mid = (0 + 4) / 2 = 2
       nums[2][2] = 33
       33 == 34 ? False
       33 <= 34 ? True -> low = mid + 1 = 3
       State: low = 3, high = 4

     - Iteration 2:
       mid = (3 + 4) / 2 = 3
       nums[2][3] = 34
       34 == 34 ? TRUE! (Match found!)
       Action: return mid => returns 3.

   Back in search_2d():
     ind = 3
     Check: ind != -1 (3 != -1) -> TRUE!
     Action: return {i, ind} => return {2, 3}.
     Function terminates immediately!

   In main():
   Output: "The position of target is (2,3)"

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Let N = number of rows (`nums.size()`), M = number of columns (`nums[0].size()`).
     * Outer for-loop: Worst case me N rows iterate karega.
     * Inner Binary Search: Har row par `binary()` chalane me O(log2 M) time lagta hai.
     * Best Case: O(log M) -> Target pehli hi row (Row 0) me mil jaye.
     * Worst Case: O(N * log M) -> Target aakhri row me ho ya pure matrix me exist hi na kare.
     * Average Case: O(N * log M).

   - Space Complexity (SC):
     * Auxiliary Space: O(1).
     * Algorithm sirf standard scalar variables (`row`, `column`, `ind`, `i`, `low`, `high`, `mid`) 
       memory me banata hai.
     * Koi auxiliary vector ya recursive stack use nahi hua, memory bilkul constant hai.
======================================================================
*/

// BETTER SOLUTION
int binary(vector <int>&nums,int target){
    int low=0;
    int high=nums.size() -1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]<=target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}

pair <int,int> search_2d(vector <vector<int>> &nums,int target){
    int row=nums.size();
    int column=nums[0].size();
    int ind=-1;
    for(int i=0;i<row;i++){
        ind=binary(nums[i],target);
        if(ind!=-1){
            return {i,ind};
        }
    }
    return {-1,-1};
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=34;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    pair <int,int> ans = search_2d(nums,target);
    cout<<"The position of target is ("<<ans.first<<","<<ans.second<<")";
    return 0;
}