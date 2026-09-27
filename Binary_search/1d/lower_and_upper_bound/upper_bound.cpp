#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (UPPER BOUND KA LOGIC):
   - Definition of Upper Bound:
     Sorted array me pehla aisa index `i` dhundhna jahan `nums[i] > target` ho 
     (Strictly greater than target, barabar nahi chalega).
   
   - Lower Bound vs Upper Bound (Single Difference):
     * Lower Bound : Pehla index jahan `nums[i] >= target` (Target ya usse bada).
     * Upper Bound : Pehla index jahan `nums[i] > target`  (Sirf target se bada).

   - NOTE ON CODE LOGIC:
     Function ke andar logic bilkul correct Upper Bound ka hai (`nums[mid] > target`), 
     lekin `main()` me print statement "The lower bound is" likha hua hai. 
     Technically yeh code UPPER BOUND calculate kar raha hai.

   - Elimination Strategy:
     - Agar `nums[mid] > target`:
       Hume ek strictly greater element mil gaya (`ans = mid`). Lekin hume "PEHLA" 
       (smallest index) strictly greater element chahiye. Ho sakta hai iske left side 
       me bhi koi number ho jo target se strictly bada ho. Isliye right side eliminate 
       karke left me move karte hain: `high = mid - 1`.
     - Agar `nums[mid] <= target`:
       Yeh element ya toh target se chhota hai ya barabar hai. Dono hi cases me yeh 
       upper bound nahi ban sakta (kyunki hume STRICTLY greater chahiye). Isliye mid aur 
       uske left side ke saare chhote elements ko eliminate karke right move karo: `low = mid + 1`.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `int ans = nums.size();` :
     Default answer initialize kiya index `n`. Agar array ka sabse aakhri element bhi 
     target se bada na ho, toh koi upper bound exist nahi karega aur answer `n` hi rahega.
   - `int mid = (low + high) / 2;` :
     Middle index find kiya (Standard binary search step).
   - `if (nums[mid] > target)` :
     Condition check: Kya element strictly target se bada hai?
     - `ans = mid;` -> Possible valid candidate mil gaya, index save kiya.
     - `high = mid - 1;` -> Isse bhi chhota index dhundhne ke liye search range left half me shift ki.
   - `else if (nums[mid] <= target)` :
     Target ke barabar ya chhota hone par upper bound nahi mil sakta. 
     Left half eliminate karke right half explore karo: `low = mid + 1`.
   - `return ans;` :
     Loop terminate hone par jo smallest index target se strictly bada mila, wo return ho jayega.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual):

   Array:
   Indices:   0    1    2    3     4     5
   Elements: [2,   3,   4,   6,   17,   19]
   n = 6

   -------------------------------------------------------------------
   TEST CASE 1: target = 4 (Element array me present hai)
   Note: Lower bound index 2 (element 4) deta, par Upper bound strictly 
         bada element (6 at index 3) dega.
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ans = 6

   --- Iteration 1 ---
   low = 0, high = 5  (low <= high -> True)
   mid = (0 + 5) / 2 = 2
   nums[mid] = nums[2] = 4
   Check: nums[mid] > target => 4 > 4? -> FALSE (Barabar hai, bada nahi)
   Action: Right jao -> low = mid + 1 = 3
   State: low = 3, high = 5, ans = 6

   --- Iteration 2 ---
   low = 3, high = 5  (low <= high -> True)
   mid = (3 + 5) / 2 = 4
   nums[mid] = nums[4] = 17
   Check: nums[mid] > target => 17 > 4? -> TRUE! (Candidate Mil Gaya)
   Action:
     - ans update karo: ans = mid = 4
     - Left jao (chhota index check karne): high = mid - 1 = 3
   State: low = 3, high = 3, ans = 4

   --- Iteration 3 ---
   low = 3, high = 3  (low <= high -> True)
   mid = (3 + 3) / 2 = 3
   nums[mid] = nums[3] = 6
   Check: nums[mid] > target => 6 > 4? -> TRUE! (Aur chhota valid index mil gaya)
   Action:
     - ans update karo: ans = mid = 3
     - Left jao: high = mid - 1 = 2
   State: low = 3, high = 2, ans = 3

   --- Loop Terminate ---
   low = 3, high = 2 -> (low <= high: 3 <= 2) -> FALSE.
   Loop End!
   Return ans = 3 (nums[3] = 6, jo 4 se strictly bada pehla element hai).

   -------------------------------------------------------------------
   TEST CASE 2: target = 19 (Array ka largest element target hai)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ans = 6

   Iter 1: low=0, high=5 -> mid=2 (nums[2]=4 <= 19)  -> low = 3
   Iter 2: low=3, high=5 -> mid=4 (nums[4]=17 <= 19) -> low = 5
   Iter 3: low=5, high=5 -> mid=5 (nums[5]=19 <= 19) -> low = 6
   Loop ends (low = 6, high = 5 -> condition false).
   ans update nahi hua -> return ans = 6.
   Main output: "Target value not present" (Kyuki 19 se strictly bada koi nahi hai).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1)
     * Worst Case: O(log2 N) -> Har iteration me search window aadhi (N/2) hoti hai.
     * Average Case: O(log2 N).
   - Space Complexity (SC):
     * O(1) Auxiliary Space -> Sirf simple pointer variables (`low`, `high`, `mid`, `ans`) 
       use hue hain, koi recursive call stack ya extra space nahi hai.
======================================================================
*/

int search(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>target){
            ans=mid;
            high=mid-1;
        }
        else if(nums[mid]<=target){
            low=mid+1;
        }
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