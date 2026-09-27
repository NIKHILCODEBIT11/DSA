#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SEARCH IN ROTATED SORTED ARRAY):
   - Problem:
     Ek sorted array ko kisi pivot point par rotate kiya gaya hai (e.g. [2,3,4,5,6,7] 
     rotate hokar ban gaya [6,7,2,3,4,5]). Saare elements UNIQUE hain. Hume isme 
     ek `target` ka index dhundhna hai in O(log N) time.

   - Core Golden Rule of Rotated Sorted Array:
     Agar tum array ko kisi bhi index `mid` par kaat-te ho, toh kam se kam 
     EK HALF (ya toh Left Half ya fir Right Half) HAMESHA 100% SORTED MILEGA!
     Dono halves kabhi ek saath un-sorted nahi ho sakte.

   - Strategy (Identify the Sorted Half first):
     1. Pehle dekho kaunsa half sorted hai:
        - Agar `nums[low] <= nums[mid]` hai, toh LEFT HALF sorted hai.
        - Warna RIGHT HALF sorted hai (`nums[mid] <= nums[high]`).
     2. Jo half sorted hai, uski boundaries defined hain!
        Isliye sorted half par check karna bohot aasan hai ki kya target 
        us range ke andar fall karta hai:
        - Agar Left Half sorted hai:
          Check karo: Kya target `[nums[low], nums[mid]]` ke beech lie karta hai?
          * Agar YES -> Target yahin maujood hai, right half ko discard kar do (`high = mid - 1`).
          * Agar NO  -> Target yahan ho hi nahi sakta, left half discard kar do (`low = mid + 1`).
        - Agar Right Half sorted hai:
          Check karo: Kya target `[nums[mid], nums[high]]` ke beech lie karta hai?
          * Agar YES -> Target yahin hai, left discard kar do (`low = mid + 1`).
          * Agar NO  -> Target right me nahi hai, right discard kar do (`high = mid - 1`).

   - CRITICAL EDGE CASE IN CODE:
     Code me `if (nums[low] < nums[mid])` likha hai. 
     Isko standard practice me `if (nums[low] <= nums[mid])` likhna chahiye.
     Kyun? Kyunki jab search space sirf 2 elements ka bachta hai (jaise low=0, high=1), 
     toh `mid = 0` ban jata hai, jisse `low == mid` ho jata hai. Strict `<` lagane 
     se code else block me gir jayega. Har case me accurate rehne ke liye `<=` lagana safe rehta hai.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (nums[mid] == target) return mid;`:
     Direct Hit! Target mil gaya, uska index return karke loop se bahar aa jao.
   - `if (nums[low] <= nums[mid])`:
     Step 1: Left half sorted hone ki tasdeeq (confirmation) ki.
     - `if (nums[low] <= target && target <= nums[mid])`:
       Step 2: Check kiya kya target is left sorted boundary ke andar baitha hai.
       - Agar haan, toh right side discard: `high = mid - 1;`
       - Agar nahi, toh left side discard: `low = mid + 1;`
   - `else`:
     Step 1: Left sorted nahi hai, iska matlab pakka RIGHT HALF SORTED hai.
     - `if (nums[mid] <= target && target <= nums[high])`:
       Step 2: Check kiya kya target is right sorted boundary ke andar baitha hai.
       - Agar haan, toh left side discard: `low = mid + 1;`
       - Agar nahi, toh right side discard: `high = mid - 1;`
   - `return -1;`:
     Search space khatam ho gaya par element nahi mila -> element array me nahi hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0    1    2    3    4    5
   Elements: [6,   7,   2,   3,   4,   5]
   Target = 4
   n = 6

   Initial State:
   low = 0, high = 5

   --- Iteration 1 ---
   low = 0, high = 5 (0 <= 5 -> True)
   mid = (0 + 5) / 2 = 2
   nums[mid] = nums[2] = 2

   1. Check Match: nums[2] == 4 ? (2 == 4) -> FALSE.
   2. Identify Sorted Half:
      Is nums[low] <= nums[mid]? (nums[0] <= nums[2] => 6 <= 2) -> FALSE!
      => Left half sorted NAHI hai!
      => Pakka RIGHT HALF [index 2 to 5: {2, 3, 4, 5}] SORTED HAI!
   3. Check Target in Right Sorted Range:
      Kya target range [nums[mid], nums[high]] me hai?
      => nums[2] <= 4 && 4 <= nums[5]
      => 2 <= 4 && 4 <= 5 -> TRUE! (Target right half me hi phasa hua hai)
   4. Action:
      Left half ko discard karo -> low = mid + 1 = 2 + 1 = 3
   Boundary updated: low = 3, high = 5

   --- Iteration 2 ---
   low = 3, high = 5 (3 <= 5 -> True)
   mid = (3 + 5) / 2 = 4
   nums[mid] = nums[4] = 4

   1. Check Match: nums[4] == 4 ? (4 == 4) -> TRUE!
   2. Action:
      Return mid => Return 4.

   Final Output: "The index of 4 in rotated array is 4"

   -------------------------------------------------------------------
   CASE B: Element NOT Present (target = 8)
   -------------------------------------------------------------------
   Iter 1: low=0, high=5, mid=2 (nums[2]=2).
           Right half [2..5] sorted hai: {2, 3, 4, 5}.
           Kya 8 lie karta hai [2..5] me? No (8 > 5).
           Toh right discard -> high = mid - 1 = 1.
   Iter 2: low=0, high=1, mid=0 (nums[0]=6).
           Left half [0..0] sorted hai (6 <= 6).
           Kya 8 lie karta hai [6..6] me? No.
           Toh left discard -> low = mid + 1 = 1.
   Iter 3: low=1, high=1, mid=1 (nums[1]=7).
           Match nahi hua (7 != 8).
           Kya 8 lie karta hai [7..7] me? No.
           high = mid - 1 = 0.
   Iter 4: low=1, high=0 -> low > high -> Loop ends -> returns -1.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Target array ke middle element par pehli hi baar me mil jaye.
     * Worst Case: O(log2 N) -> Har bar hum array ke aadhe hisse ko discard kar rahe 
       hain (chahe left sorted ho ya right sorted). Search boundary har step me N -> N/2 -> N/4... shrink hoti hai.
     * Average Case: O(log2 N).

   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Pure iterative binary search hai. Sirf 3 pointers 
       (`low`, `high`, `mid`) memory me ban rahe hain. Zero extra space.
======================================================================
*/

int search_rotated(vector <int> &nums,int target){
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;

        if(nums[mid]==target){
            return mid;
        }
        // checking for Left sorted :-
        if(nums[low]<=nums[mid]){
            if(nums[low]<=target && target<=nums[mid]){
                high=mid-1;

            }
            else{
                low=mid+1;
            }
        }

        // checking for Right sorted :-
        else{               //      same as         if(nums[high]>nums[mid])
            if(nums[mid]<=target && target<=nums[high]){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
    return -1;
}

int main(){
    vector <int> nums={6,7,2,3,4,5};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int res=search_rotated(nums,n);
    cout<<"The index of "<<n<<" in rotated array is "<<res;
    return 0;
}