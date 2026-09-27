// Yeh lowe bound and upper bound calculate nahi kar raha standar binary search kar raha "first" nikalne ke liye phir dusri baar binary search kar raha hai "last" nikalne ke liye aur usi ko return kar raha hai

#include<bits/stdc++.h>
using namespace std;

/*
The below function is indeed cirrect for finding first and last occurence but since i am performing binary search than   "SURELY"
it will take total "2*log(N)" each "log(N)"" for each binary search{first and last}, but by writin separate functions for finding
"first" and "last" occurences i can "MAY BE" sace "1*log(n)" time.
*/

/*
pair<int,int> search(vector <int>&nums,int target){
    int low=0;
    int high=nums.size()-1;
    int first=-1,last=-1;              //      int first,last=-1;     Writing like this is wrong         
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            high=mid-1;
            first=mid;
        }
        else{
            high=mid-1;
        }
    }

    low=0;
    high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            last=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return {first,last};
}
*/



/*

By using below separate functions   :-  See conclusion at function          pair <int,int> first_last(vector <int>&nums,int target)

*/
int first_(vector<int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int first=-1,last=-1;              //      int first,last=-1;     Writing like this is wrong         
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            high=mid-1;
            first=mid;
        }
        else{
            high=mid-1;
        }
    }
    return first;
}

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (CUSTOM BS & EARLY EXIT OPTIMIZATION):
   - Problem:
     Sorted array me target element ka first aur last occurrence index nikalna hai, 
     bina Lower/Upper bound ke formula (LB aur UB-1) par rely kiye. Seedhe core 
     binary search logic se directly first aur last index hit karna hai.

   - The "A-Ha!" Optimization (Early Exit):
     * Agar target array me maujood hi nahi hai, toh `first_(...)` binary search 
       chala kar seedha `-1` return kar dega.
     * Logic: "Jab kisi cheez ki pehli occurrence hi nahi hai, toh aakhri kahan se hogi?"
     * Fayda: `if (first == -1) return {-1, -1};` likhne se hum dusra binary search 
       (`last_(...)`) call hi nahi karte! 
       Target missing hone par humara time direct $2 \cdot \log_2 N$ se ghaskar 
       $1 \cdot \log_2 N$ reh jata hai. Interviewer ko yeh dikhata hai ki tum blind coding 
       nahi kar rahe, balki unnecessary computations ko actively prune kar rahe ho.

   - First Occurrence Logic:
     Jab `nums[mid] == target`:
     Element mil gaya, par kya yeh pehla hai? Nahi pata! Sorted array me duplicates 
     hamesha left side me bhi ho sakte hain. 
     Isliye `first = mid` memorize karo aur aur left side explore karo: `high = mid - 1`.

   - Last Occurrence Logic:
     Jab `nums[mid] == target`:
     Element mil gaya, par kya yeh aakhri hai? Duplicate right side bhi ho sakta hai. 
     Isliye `last = mid` memorize karo aur right side explore karo: `low = mid + 1`.

   - C++ Variable Syntax Alert:
     `int first, last = -1;` likhne par sirf `last` ko `-1` milta hai, 
     `first` UNINITIALIZED reh jata hai (garbage value). 
     Sahi tarika: `int first = -1, last = -1;`.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `first_()` Function ---
   - `if (nums[mid] == target)`:
     `first = mid;` -> Current match index save kiya.
     `high = mid - 1;` -> Search window left side shrink ki taaki pehla duplicate pakad sakein.
   - `else if (nums[mid] < target)` -> `low = mid + 1;` (Target right me hai).
   - `else` (`nums[mid] > target`)  -> `high = mid - 1;` (Target left me hai).

   --- `last_()` Function ---
   - `if (nums[mid] == target)`:
     `last = mid;` -> Current match index save kiya.
     `low = mid + 1;` -> Search window right side expand/shift ki taaki aakhri duplicate pakad sakein.
   - Rest binary search conditions remain standard.

   --- `first_last()` Wrapper Function ---
   - `int first = first_(nums, target);`:
     Pehle first occurrence nikalne ki koshish ki ($O(\log N)$).
   - `if (first == -1) return {-1, -1};`:
     EARLY EXIT GUARD! Target array me hai hi nahi, toh `last_()` par faltu $O(\log N)$ 
     waste kare bina turant exit maro.
   - `int last = last_(nums, target);`:
     Tabhi execute hoga agar target present hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual):

   Array:
   Indices:   0   1   2   3   4   5   6   7   8   9
   Elements: [2,  3,  4,  6,  6,  6,  6,  6, 17, 19]
   n = 10

   -------------------------------------------------------------------
   SCENARIO 1: Target Missing (target = 5) -> Early Exit Demonstration
   -------------------------------------------------------------------
   Step 1: Call `first_(nums, 5)`
           low = 0, high = 9
           mid = 4 -> nums[4] = 6 > 5 -> high = 3
           mid = 1 -> nums[1] = 3 < 5 -> low = 2
           mid = 2 -> nums[2] = 4 < 5 -> low = 3
           mid = 3 -> nums[3] = 6 > 5 -> high = 2
           low > high (3 > 2) -> Loop ends.
           Returns `first = -1`.

   Step 2: In `first_last()`:
           Check: `if (first == -1)` -> TRUE!
           Immediately returns `{-1, -1}`.
           => `last_()` function call hi nahi hua! Poora $1 \cdot \log_2 N$ bacha liya!

   -------------------------------------------------------------------
   SCENARIO 2: Target Present (target = 6)
   -------------------------------------------------------------------
   [Part A: Call first_(nums, 6)]
   low = 0, high = 9, first = -1
   - mid = 4: nums[4] = 6 == 6 -> first = 4, high = mid - 1 = 3
   - mid = 1: nums[1] = 3 < 6  -> low = mid + 1 = 2
   - mid = 2: nums[2] = 4 < 6  -> low = mid + 1 = 3
   - mid = 3: nums[3] = 6 == 6 -> first = 3, high = mid - 1 = 2
   low > high (3 > 2) -> terminates.
   Returns `first = 3`.

   [Part B: Guard check in first_last()]
   `first == -1` ? (3 == -1) -> FALSE. Aage badho!

   [Part C: Call last_(nums, 6)]
   low = 0, high = 9, last = -1
   - mid = 4: nums[4] = 6 == 6 -> last = 4, low = mid + 1 = 5
   - mid = 7: nums[7] = 6 == 6 -> last = 7, low = mid + 1 = 8
   - mid = 8: nums[8] = 17 > 6 -> high = mid - 1 = 7
   low > high (8 > 7) -> terminates.
   Returns `last = 7`.

   Final Combined Return: `{3, 7}`.

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Case 1: Target Present:
       `first_()` takes $O(\log_2 N)$ + `last_()` takes $O(\log_2 N)$ 
       = $2 \cdot \log_2 N \Rightarrow O(\log N)$.
     * Case 2: Target Absent (Best/Early-Pruned Worst):
       Only `first_()` executes = $1 \cdot \log_2 N \Rightarrow O(\log N)$.
       Constant factor cut by 50% for missing targets!
   
   - Space Complexity (SC):
     * O(1) Auxiliary Space -> Dono functions pure iterative hain, 
       sirf low, high, mid aur answer variables use ho rahe hain.
======================================================================
*/

int last_(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int last=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            last=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return last;
}



pair <int,int> first_last(vector <int>&nums,int target){
    int first=first_(nums,target);
    
/*
Here, i   "MAY"     save    "1*log(N)"      as if the target is missing then only in search of  "first"     i will know about it 
and hence, I can avoid the time of finding      "last"      as,if there is no first occurence then surely there won't be
the last occurence.

This simple logical thinking can make the interviewer impress.

*/

    if(first==-1){
        return {-1,-1};
    }
    int last=last_(nums,target);
    return {first,last};
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    cout<<"The first occurence of "<<n<<" is "<<res.first<<" and the last occurence is "<<res.second;
    return 0;
}