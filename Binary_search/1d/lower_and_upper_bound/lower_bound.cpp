#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (LOWER BOUND KA KHEL):
   - Definition of Lower Bound:
     Sorted array me pehla aisa index `i` dhundhna jahan `nums[i] >= target` ho.
     Matlab: Ya toh target ke barabar element mil jaye, ya target se theek 
     bada (smallest element greater than or equal to target) mil jaye.

   - KYUN BANAYA `ans = nums.size()` START MEIN? (Hypothetical Index Logic):
     1. Maan lo array hai: [2, 3, 5] (size = 3, indices 0, 1, 2)
     2. Agar target = 10 hai, toh array me koi bhi element >= 10 nahi hai.
     3. Aise case me standard lower bound definition (jaise C++ STL ka `std::lower_bound`) 
        end-iterator yaani `nums.size()` return karta hai.
     4. Iska practical matlab: "Agar target ko is sorted order ko todhe bina 
        array me insert karna ho, toh use index `n` (array ke aakhir) par insert karna padega."
     5. Isliye `ans` ko initially `nums.size()` (n) set karte hain as a DEFAULT answer. 
        Agar pure array me koi element >= target nahi mila, toh `ans` bina update hue 
        safely `n` hi return hoga, jisse caller ko pata chal jata hai ki aisa koi element array me nahi tha!

   - Binary Search Logic (Elimination Technique):
     - Agar `nums[mid] >= target`:
       Hume ek possible answer mil gaya (`ans = mid`). Lekin hume "PEHLA" (smallest index) 
       chahiye. Ho sakta hai isse pehle (left side me) bhi koi valid number baitha ho. 
       Isliye hum right side discard kar dete hain aur left me aur behtar answer dhundhte hain: `high = mid - 1`.
     - Agar `nums[mid] < target`:
       Yeh number target se chhota hai, toh yeh answer kabhi nahi ho sakta. 
       Aur kyunki array sorted hai, iske piche ke saare numbers bhi chhote hi honge. 
       Isliye pure left half ko eliminate karke right side move karte hain: `low = mid + 1`.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int ans = nums.size();` :
     Default answer initialize kiya. Agar koi element condition satisfy nahi karega, 
     toh answer automatically `n` rahega.
   - `int mid = (low + high) / 2;` :
     Middle index find kiya (Production/LeetCode me `low + (high - low) / 2` use karna overflow se bachne ke liye).
   - `if (nums[mid] >= target)` :
     Condition check: Kya current element target ke barabar ya usse bada hai?
     - `ans = mid;` -> Possible answer store kiya (Save the best candidate so far).
     - `high = mid - 1;` -> Left half me search space compress kiya (Try to find a smaller valid index).
   - `else if (nums[mid] < target)` (ya simply `else`) :
     Current element chhota hai, toh valid candidate nahi hai. 
     Left half eliminate karke right half me check karo: `low = mid + 1`.
   - `return ans;` :
     Loop terminate hone ke baad jo smallest valid index store hua tha, wo return ho jayega.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual):

   Array:
   Indices:   0    1    2    3     4     5
   Elements: [2,   3,   4,   6,   17,   19]
   n = 6

   -------------------------------------------------------------------
   TEST CASE 1: target = 5 (Element not directly present, finds ceil)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ans = 6

   --- Iteration 1 ---
   low = 0, high = 5  (low <= high -> True)
   mid = (0 + 5) / 2 = 2
   nums[mid] = nums[2] = 4
   Check: nums[mid] >= target => 4 >= 5? -> False
   Action: Right jao -> low = mid + 1 = 3
   State: low = 3, high = 5, ans = 6

   --- Iteration 2 ---
   low = 3, high = 5  (low <= high -> True)
   mid = (3 + 5) / 2 = 4
   nums[mid] = nums[4] = 17
   Check: nums[mid] >= target => 17 >= 5? -> True! (Candidate Mil Gaya)
   Action:
     - ans update karo: ans = mid = 4
     - Left jao (chhota index check karne): high = mid - 1 = 3
   State: low = 3, high = 3, ans = 4

   --- Iteration 3 ---
   low = 3, high = 3  (low <= high -> True)
   mid = (3 + 3) / 2 = 3
   nums[mid] = nums[3] = 6
   Check: nums[mid] >= target => 6 >= 5? -> True! (Aur chhota index mil gaya)
   Action:
     - ans update karo: ans = mid = 3
     - Left jao: high = mid - 1 = 2
   State: low = 3, high = 2, ans = 3

   --- Loop Terminate ---
   low = 3, high = 2 -> (low <= high: 3 <= 2) -> FALSE.
   Loop End!
   Return ans = 3 (nums[3] = 6, jo ki 5 se theek bada pehla number hai).

   -------------------------------------------------------------------
   TEST CASE 2: target = 25 (Saare elements target se chhote hain)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ans = 6

   Iter 1: low=0, high=5 -> mid=2 (nums[2]=4 < 25)  -> low = 3
   Iter 2: low=3, high=5 -> mid=4 (nums[4]=17 < 25) -> low = 5
   Iter 3: low=5, high=5 -> mid=5 (nums[5]=19 < 25) -> low = 6
   Loop ends (low = 6, high = 5 -> condition false).
   ans kabhi update hi nahi hua!
   Return ans = 6 (nums.size())
   Main check: `if(res == nums.size())` -> Output: "Target value not present".

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) [Agar array size 1 ho ya pehla mid hi boundaries shrink karke ruk jaye]
     * Worst Case: O(log2 N) -> Har iteration me search boundary aadhi (half) ho rahi hai.
     * Average Case: O(log2 N).
   - Space Complexity (SC):
     * O(1) Auxiliary Space -> Sirf pointers (`low`, `high`, `mid`, `ans`) use hue hain, koi extra memory ya stack frame nahi laga.
======================================================================
*/

int search(vector <int>& nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();

    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){    
            ans=mid;
            high= mid - 1;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }

        /*
        
        I can also write this only

        else{               
            low=mid+1;
        }

        */
    }
    return ans;
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int res=search(nums,n);
    if(res==nums.size()){
        cout<<"Target value not present";
    }
    else{
        cout<<"The lower bound is "<<res;
    }
    return 0;
}