#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS (SEARCH INSERT POSITION):
   - Problem: Ek sorted array me ek `target` element ko insert karna hai 
     aise ki insertion ke baad bhi array STRICTLY SORTED hi rahe.
   - Core Idea:
     Sahi insertion index aur kuch nahi, balki target ka LOWER BOUND hota hai!
     - Lower Bound ka matlab: Pehla aisa index jahan `nums[i] >= target`.
     - Kyun? 
       * Agar target already exist karta hai (jaise target = 4, aur array me 4 hai index 2 par),
         toh naya 4 index 2 par aa jayega aur purana 4 right me shift ho jayega -> Sorted order intact.
       * Agar target exist nahi karta (jaise target = 5, aur array me 4 ke baad 6 hai),
         toh pehla element jo 5 se bada hai wo 6 hai (index 3). 5 ko index 3 par insert kar denge
         aur 6 aur uske aage ke numbers right shift ho jayenge -> Sorted order intact.
       * Agar target array ke saare elements se bada hai (jaise target = 25),
         toh lower bound default index `n` (array ka last index + 1) banega -> Element end me lag jayega.
   - Insertion Logic:
     Index milne ke baad array ke rightmost end par ek dummy slot (`nums.push_back(0)`) banate hain 
     aur target ke aage ke saare elements ko 1 step right shift kar dete hain taaki index free ho jaye, 
     phir target wahan place ho jata hai.

   - COMPILER NOTE (C++ Bug in Code Order):
     C++ me `search()` function `insert()` ko call kar raha hai, lekin `insert()` function 
     `search()` ke NICHE define hai. Agar function prototype pehle declare na ho 
     toh compiler error dega: "'insert' was not declared in this scope". 
     Solution: `insert()` ko `search()` ke upar define karo ya upar `void insert(...);` declare karo.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   --- `search()` Function (Finding Lower Bound) ---
   - `int ans = nums.size();` :
     Default insertion point array ke end me set kiya (agar target sabse bada nikle).
   - `if (nums[mid] >= target)` :
     Target insert hone ke liye ye index candidate ho sakta hai. 
     `ans = mid;` save kiya aur `high = mid - 1;` karke left side me dekha ki 
     isse pehle bhi koi valid jagah hai kya.
   - `else if (nums[mid] < target)` :
     `mid` tak ke elements chhote hain, wahan insert nahi ho sakta -> `low = mid + 1;`.
   - `insert(nums, ans, target);` :
     Calculated index milte hi insertion trigger kar diya.

   --- `insert()` Function (Right Shifting & Placement) ---
   - `nums.push_back(0);` :
     Vector ki size 1 badhayi taaki ek naya element rakhne ki jagah ban sake.
   - `for(int i = nums.size() - 1; i > index; i--) nums[i] = nums[i - 1];` :
     Piche se shuru karke har element ko ek-ek step right push kiya jab tak `index` 
     par jagah khali na ho jaye (Data overwrite hone se bachane ke liye piche se shift karte hain).
   - `nums[index] = target;` :
     Khali hui jagah par target element place kar diya.

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual):

   Array:
   Indices:   0    1    2    3     4     5
   Elements: [2,   3,   4,   6,   17,   19]
   n = 6
   Target = 5

   -------------------------------------------------------------------
   PHASE 1: Binary Search for Insertion Index (Lower Bound)
   -------------------------------------------------------------------
   Initial: low = 0, high = 5, ans = 6

   [Step 1]
   low = 0, high = 5 -> mid = 2
   nums[2] = 4
   4 >= 5 ? FALSE -> low = mid + 1 = 3
   State: low = 3, high = 5, ans = 6

   [Step 2]
   low = 3, high = 5 -> mid = 4
   nums[4] = 17
   17 >= 5 ? TRUE -> Candidate mil gaya!
   Action: ans = 4, high = mid - 1 = 3
   State: low = 3, high = 3, ans = 4

   [Step 3]
   low = 3, high = 3 -> mid = 3
   nums[3] = 6
   6 >= 5 ? TRUE -> Aur chhota index mila!
   Action: ans = 3, high = mid - 1 = 2
   State: low = 3, high = 2, ans = 3

   Condition Check: low <= high (3 <= 2) -> FALSE.
   Search Ended. Insertion Index `ans = 3`.

   -------------------------------------------------------------------
   PHASE 2: Shifting & Insertion at Index 3
   -------------------------------------------------------------------
   Input to insert(): nums, index = 3, target = 5

   Step 2.1: nums.push_back(0);
   Indices:   0   1   2   3   4   5   6
   Array:   [ 2,  3,  4,  6, 17, 19,  0 ]

   Step 2.2: Loop i = 6 down to i > 3
   - i = 6: nums[6] = nums[5] -> [ 2, 3, 4, 6, 17, 19, 19 ]
   - i = 5: nums[5] = nums[4] -> [ 2, 3, 4, 6, 17, 17, 19 ]
   - i = 4: nums[4] = nums[3] -> [ 2, 3, 4, 6,  6, 17, 19 ]
   Loop stops at i = 3!

   Step 2.3: nums[3] = target (5)
   Array:   [ 2,  3,  4,  5,  6, 17, 19 ]  <-- Array is still sorted!

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Binary Search step: O(log N) -> Target ki insertion position dhundhne me.
     * Insertion & Shifting step: O(N) -> Worst case me target sabse aage (index 0) 
       insert karna padega, toh N elements ko 1 step right shift karna padega.
     * Total Time Complexity: O(log N) + O(N) = O(N) overall.
   - Space Complexity (SC):
     * Auxiliary Space: O(1) -> Sirf pointer variables use hue hain.
     * Total Space: O(1) extra space beyond the newly inserted single element.
======================================================================
*/

void insert(vector <int> &nums,int index,int target){
    nums.push_back(0);
    for(int i=nums.size()-1;i>index;i--){
        nums[i]=nums[i-1];
    }
    nums[index]=target;
}

void search(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ans=mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
    }
    insert(nums,ans,target);
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    cout<<"Before insertion :-"<<endl;
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<"\t";
    }
    cout<<endl;
    search(nums,n);
    cout<<"After inserting :-"<<endl;
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<"\t";
    }
    return 0;
}