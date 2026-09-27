#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (FLOOR AND CEIL):
   - Definitions:
     * Floor: Sorted array me se target se chhota ya barabar sabse BADA number 
       (Largest element in array <= target).
     * Ceil : Sorted array me se target se bada ya barabar sabse CHHOTA number 
       (Smallest element in array >= target). Note: Ceil aur kuch nahi balki Lower Bound ki VALUE hai!

   - Floor Logic (Largest element <= target):
     Agar `nums[mid] <= target`:
     Yeh number valid candidate hai, isliye isko store kar lo (`floor = nums[mid]`).
     Lekin hume "LARGEST" number chahiye <= target. Array sorted hai, toh isse bada 
     valid number hume right side hi mil sakta hai. Isliye right me move karo: `low = mid + 1`.
     Agar `nums[mid] > target`:
     Yeh number target se bada ho gaya, toh yeh floor nahi ban sakta. Left jao: `high = mid - 1`.

   - Ceil Logic (Smallest element >= target):
     Agar `nums[mid] >= target`:
     Yeh number valid candidate hai (`ceil = nums[mid]`).
     Lekin hume "SMALLEST" number chahiye >= target. Isse chhota valid number hume 
     left side hi mil sakta hai. Isliye left me move karo: `high = mid - 1`.
     Agar `nums[mid] < target`:
     Yeh number chhota hai, ceil nahi ban sakta. Right jao: `low = mid + 1`.

   - Default Value (-1):
     Agar array me aisa koi element exist hi nahi karta (jaise target pure array ke 
     sabse chhote element se bhi chhota ho toh floor nahi milega, ya sabse bade element 
     se bada ho toh ceil nahi milega), toh variable bina update hue safely `-1` return karega.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `floor_()` Function ---
   - `int floor = -1;` :
     Default initialization. Agar koi element <= target na ho, toh -1 return hoga.
   - `if (nums[mid] <= target)` :
     Condition true hui toh `floor = nums[mid]` save kiya aur `low = mid + 1` karke 
     right half me dekha ki kya target ke aur kareeb (usse bada lekin <= target) number mil sakta hai.
   - `else` :
     Number target se bada hai, floor banne ke kabil nahi -> `high = mid - 1`.

   --- `ceil_()` Function ---
   - `int ceil = -1;` :
     Default initialization. Agar koi element >= target na ho, toh -1 return hoga.
   - `if (nums[mid] >= target)` :
     Condition true hui toh `ceil = nums[mid]` save kiya aur `high = mid - 1` karke 
     left half me search kiya taaki koi aur chhota valid number mil sake.
   - `else` :
     Number target se chhota hai, ceil nahi ban sakta -> `low = mid + 1`.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0    1    2    3     4     5
   Elements: [2,   3,   4,   6,   17,   19]
   Target = 5

   -------------------------------------------------------------------
   DRY RUN 1: Floor of 5 (Target se chhota ya barabar sabse bada number)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, floor = -1

   [Call 1: low = 0, high = 5]
   │  mid = (0 + 5) / 2 = 2 -> nums[2] = 4
   │  nums[2] <= 5 ? (4 <= 5) -> TRUE!
   │  Action: floor = 4 (Candidate saved)
   │          Aur bada number dhundho -> low = mid + 1 = 3
   │
   └──► [Call 2: low = 3, high = 5]
        │  mid = (3 + 5) / 2 = 4 -> nums[4] = 17
        │  nums[4] <= 5 ? (17 <= 5) -> FALSE (Bada hai)
        │  Action: Left aao -> high = mid - 1 = 3
        │
        └──► [Call 3: low = 3, high = 3]
             │  mid = (3 + 3) / 2 = 3 -> nums[3] = 6
             │  nums[3] <= 5 ? (6 <= 5) -> FALSE (Bada hai)
             │  Action: Left aao -> high = mid - 1 = 2
             │
             └──► [Terminates: low = 3, high = 2 (low > high)]
                  Returns floor = 4 (Correct, 4 is largest element <= 5)

   -------------------------------------------------------------------
   DRY RUN 2: Ceil of 5 (Target se bada ya barabar sabse chhota number)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ceil = -1

   [Call 1: low = 0, high = 5]
   │  mid = (0 + 5) / 2 = 2 -> nums[2] = 4
   │  nums[2] >= 5 ? (4 >= 5) -> FALSE (Chhota hai)
   │  Action: Right jao -> low = mid + 1 = 3
   │
   └──► [Call 2: low = 3, high = 5]
        │  mid = (3 + 5) / 2 = 4 -> nums[4] = 17
        │  nums[4] >= 5 ? (17 >= 5) -> TRUE!
        │  Action: ceil = 17 (Candidate saved)
        │          Aur chhota number dhundho -> high = mid - 1 = 3
        │
        └──► [Call 3: low = 3, high = 3]
             │  mid = (3 + 3) / 2 = 3 -> nums[3] = 6
             │  nums[3] >= 5 ? (6 >= 5) -> TRUE!
             │  Action: ceil = 6 (Better candidate saved)
             │          Aur chhota number dhundho -> high = mid - 1 = 2
             │
             └──► [Terminates: low = 3, high = 2 (low > high)]
                  Returns ceil = 6 (Correct, 6 is smallest element >= 5)

   -------------------------------------------------------------------
   EDGE CASES:
   - Target = 1 (Target sabse chhota hai):
     * floor = -1 (Array me koi element <= 1 nahi hai)
     * ceil  = 2  (Array ka pehla element)
   - Target = 20 (Target sabse bada hai):
     * floor = 19 (Array ka aakhri element)
     * ceil  = -1 (Array me koi element >= 20 nahi hai)

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * `floor_()`: O(log2 N)
     * `ceil_()` : O(log2 N)
     * Total Time: O(log2 N) + O(log2 N) = O(log2 N).
   - Space Complexity (SC):
     * O(1) Auxiliary Space -> Sirf pointers aur result variables (`low`, `high`, `mid`, `floor`, `ceil`) 
       use kiye gaye hain, koi recursion call stack ya extra array nahi.
======================================================================
*/

int floor_(vector <int> &nums,int target){          // Largest number is array <= target
    int low=0;
    int high=nums.size()-1;
    int floor=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<=target){
            low=mid+1;
            floor=nums[mid];
        }
        else{
            high=mid-1;
        }
    }
    return floor;
}

int ceil_(vector <int> &nums,int target){           // Smallest number in array >= target
    int low=0;
    int high=nums.size()-1;
    int ceil=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ceil=nums[mid];
        }
        else{
            low=mid+1;
        }
    }
    return ceil;
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int floor=floor_(nums,n);
    int ceil=ceil_(nums,n);
    cout<<"The floor value is "<<floor<<" and ceil value is "<<ceil;
    return 0;
}