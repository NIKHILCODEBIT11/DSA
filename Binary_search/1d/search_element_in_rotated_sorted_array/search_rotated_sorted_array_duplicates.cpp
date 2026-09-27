#include<bits/stdc++.h>
using namespace std;

// Is wale question mein mujhe index return nahi karna bas yes/no return karna hai kyuki index return karne ke liye linear search use karna padega wo binary search se nahi ho sakta

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SEARCH IN ROTATED ARRAY WITH DUPLICATES):
   - Problem:
     Array rotated sorted hai, par pichle problem ke muqable isme ek twist hai:
     "Array me DUPLICATE elements maujood ho sakte hain!"
     Hume batana hai ki target exist karta hai ya nahi (return true/false).

   - Duplicates aane se pichla code kyun FAIL ho jata hai? (The Edge Case):
     Maan lo array hai: [3, 1, 2, 3, 3, 3, 3]
     low = 0, high = 6 -> mid = 3
     nums[low]  = nums[0] = 3
     nums[mid]  = nums[3] = 3
     nums[high] = nums[6] = 3
     
     Notice karo:
     `nums[low] == nums[mid] == nums[high] == 3`!
     Ab binary search confuse ho jata hai:
     - Kya Left Half sorted hai? (3 se 3 ke beech me 1 bhi hai -> unsorted!)
     - Kya Right Half sorted hai? (3 se 3 ke beech sab 3 hain -> sorted!)
     Computer ko pata hi nahi chalta ki sorted part kis taraf hai aur pivot kahan phasa hai.
     Toh hum bina dekhe kisi bhi half ko discard nahi kar sakte!

   - The Solution (Shrinking the Search Space):
     Agar `nums[low] == nums[mid] && nums[mid] == nums[high]`:
     Hum already check kar chuke hain ki `nums[mid] == target` nahi hai.
     Iska matlab `nums[low]` aur `nums[high]` bhi target ke barabar nahi ho sakte 
     (kyunki wo dono mid ke barabar hain).
     Toh dono boundaries ko 1-1 step aage/piche khiska do:
     `low++` aur `high--`.
     Isse search boundary shrink ho jayegi aur ambiguity khatam ho jayegi.
     Uske baad seedhe `continue` karke agla iteration check karo.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (nums[mid] == target) return true;`:
     Direct Hit! Target mil gaya, true return karke loop se bahar.
   - `if (nums[low] == nums[mid] && nums[mid] == nums[high])`:
     AMBIGUITY CHECK! Teeno pointers ek hi value point kar rahe hain.
     - `low++; high--; continue;` -> Dono corners useless the, boundary shrink ki 
       aur loop ko restart kiya taaki binary search sahi sorted half pehchan sake.
   - `if (nums[low] <= nums[mid])`:
     Standard Rotated Binary Search logic: Left half sorted hai.
     - Agar target `[nums[low], nums[mid]]` ke andar hai -> `high = mid - 1`.
     - Warna -> `low = mid + 1`.
   - `else`:
     Pakka Right half sorted hai.
     - Agar target `[nums[mid], nums[high]]` ke andar hai -> `low = mid + 1`.
     - Warna -> `high = mid - 1`.
   - `return false;`:
     Loop khatam hone tak nahi mila -> element array me nahi hai.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0   1   2   3   4   5   6
   Elements: [3,  1,  2,  3,  3,  3,  3]
   Target = 2
   n = 7

   -------------------------------------------------------------------
   --- Iteration 1 ---
   low = 0, high = 6
   mid = (0 + 6) / 2 = 3
   nums[low] = nums[0] = 3
   nums[mid] = nums[3] = 3
   nums[high] = nums[6] = 3

   1. Check Match: nums[mid] == target (3 == 2) -> False.
   2. Ambiguity Check:
      nums[low] == nums[mid] && nums[mid] == nums[high] (3 == 3 && 3 == 3) -> TRUE!
   3. Action:
      Ambiguity resolve karne ke liye boundary shrink karo:
      low = low + 1 = 1
      high = high - 1 = 5
      continue; (Next loop par jao)
   State: low = 1, high = 5

   --- Iteration 2 ---
   low = 1, high = 5
   mid = (1 + 5) / 2 = 3
   nums[low] = nums[1] = 1
   nums[mid] = nums[3] = 3
   nums[high] = nums[5] = 3

   1. Check Match: nums[3] == target (3 == 2) -> False.
   2. Ambiguity Check:
      (1 == 3 && 3 == 3) -> FALSE (Ab values alag hain, normal BS chalega).
   3. Identify Sorted Half:
      nums[low] <= nums[mid] => (1 <= 3) -> TRUE! (Left Half [1..3] sorted hai).
   4. Check Target in Left Range:
      nums[low] <= target && target <= nums[mid]
      => 1 <= 2 && 2 <= 3 -> TRUE! (Target left half me hi hai).
   5. Action:
      Right discard karo -> high = mid - 1 = 3 - 1 = 2
   State: low = 1, high = 2

   --- Iteration 3 ---
   low = 1, high = 2
   mid = (1 + 2) / 2 = 1
   nums[mid] = nums[1] = 1

   1. Check Match: nums[1] == target (1 == 2) -> False.
   2. Identify Sorted Half:
      nums[low] <= nums[mid] => (1 <= 1) -> TRUE! (Left sorted).
   3. Check Target in Range:
      1 <= 2 && 2 <= 1 -> FALSE.
   4. Action:
      Left discard karo -> low = mid + 1 = 2
   State: low = 2, high = 2

   --- Iteration 4 ---
   low = 2, high = 2
   mid = 2
   nums[mid] = nums[2] = 2

   1. Check Match: nums[2] == target (2 == 2) -> TRUE!
   2. Action:
      return true;

   Final Output: 1 (True).

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Average / Best Case: O(log2 N) -> Jab duplicates ambiguity create nahi karte, 
       array har step me aadhi hoti rehti hai.
     * Worst Case: O(N / 2) ≈ O(N) -> Jab array ke lagbhag saare elements duplicate hon 
       (jaise [3, 3, 3, 3, 3, 3, 3] aur target = 2). 
       Us case me har baar `low++` aur `high--` hoga aur binary search linear scan ban jayega.
   
   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf standard variable pointers (`low`, `high`, `mid`) 
       use hue hain, koi recursive call stack ya extra space nahi.
======================================================================
*/

bool search_rotated(vector <int>&nums,int target){
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;

        if(nums[mid]==target){
            return true;
        }

        if(nums[low]==nums[mid] && nums[mid]==nums[high]){
            low++;
            high--;
            continue;
        }

        // left sorted
        if(nums[low]<=nums[mid]){
            if(nums[low]<=target && target<=nums[mid]){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }

        // Right sorted
        else{           //   can also be written as         else if(nums[mid]>=target && target<=nums[high])
            if(nums[mid]<=target && target<=nums[high]){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
    return false;
}


int main(){
    vector <int> nums={6,7,2,3,3,3,3,4,4,4,4,5,6};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    bool res=search_rotated(nums,n);
    cout<<"The target value of "<<n<<" in rotated array is "<<res;
    return 0;
}