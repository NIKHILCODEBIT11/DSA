#include<bits/stdc++.h>
using namespace std;

/*
======================================================================
1. INTUITION & THOUGHT PROCESS:
   - Problem: Ek sorted array me recursion ke through binary search execute karna.
   - Core Idea (Divide & Conquer):
     Har recursive call me problem ka size aada (half) hota hai:
     * Check karo middle element: `mid = (low + high) / 2`.
     * Agar target mil gaya (`nums[mid] == target`), to seedha index return.
     * Agar `nums[mid] < target`, to target right half me hai -> Call `search(..., mid + 1, high, ...)`.
     * Agar `nums[mid] > target`, to target left half me hai  -> Call `search(..., low, mid - 1, ...)`.
   - Base Case:
     Jab `low > high` ho jata hai, matlab search space collapse ho gaya aur element pure array me nahi hai -> Return -1.

======================================================================
2. CODE-TO-EXPLANATION ALIGNMENT:
   - `if (low > high) return -1;` :
     Base Condition. Jab boundaries overlap/cross kar jayein, recursion ruk jata hai.
   - `int mid = (low + high) / 2;` :
     Active search range ka middle pointer calculate hota hai.
   - `if (nums[mid] == target) return mid;` :
     Target matched! Return current index.
   - `return search(nums, mid + 1, high, target);` :
     Right subtree call (Target bada hai -> low right me shift).
   - `return search(nums, low, mid - 1, target);` :
     Left subtree call (Target chhota hai -> high left me shift).

======================================================================
3. DETAILED DRY RUN (Striver Blackboard-Style Visual Tree):

   Array:
   Indices:   0    1    2    3    4     5
   Elements: [2,   3,   5,   6,  17,   19]
   n = 6

   -------------------------------------------------------------------
   CASE A: Element Present (target = 17)
   -------------------------------------------------------------------

   f(nums, low=0, high=5, target=17)
   │
   ├── low > high? (0 > 5) -> False
   ├── mid = (0 + 5) / 2 = 2  ==> nums[2] = 5
   ├── nums[2] == 17? False
   ├── nums[2] < 17? (5 < 17) -> True (Right Half jao)
   │
   └── calls ──► f(nums, low=3, high=5, target=17)
                 │
                 ├── low > high? (3 > 5) -> False
                 ├── mid = (3 + 5) / 2 = 4  ==> nums[4] = 17
                 ├── nums[4] == 17? (17 == 17) -> True! (Target Mil Gaya)
                 └── returns 4 ──────────────────────┐
                                                     │
   f(nums, 0, 5, 17)  ◄── receives 4 ────────────────┘
   └── returns 4 (Final Answer to main())


   -------------------------------------------------------------------
   CASE B: Element NOT Present (target = 13) [Exact Striver Video Flow]
   -------------------------------------------------------------------

   Array:
   Indices:   0    1    2    3    4     5
   Elements: [2,   3,   5,   6,  17,   19]

   [Call 1: (low=0, high=5)]
   │  mid = (0+5)/2 = 2 -> nums[2] = 5
   │  5 < 13 -> Call right: f(mid+1, high) => f(3, 5)
   │
   └──► [Call 2: (low=3, high=5)]
        │  mid = (3+5)/2 = 4 -> nums[4] = 17
        │  17 > 13 -> Call left: f(low, mid-1) => f(3, 3)
        │
        └──► [Call 3: (low=3, high=3)]
             │  mid = (3+3)/2 = 3 -> nums[3] = 6
             │  6 < 13 -> Call right: f(mid+1, high) => f(4, 3)
             │
             └──► [Call 4: (low=4, high=3)]
                  │  low > high (4 > 3) ==> BASE CASE HIT!
                  └── returns -1
                         │
        [Call 3] ◄───────┘ receives -1, returns -1
           │
        [Call 2] ◄───────┘ receives -1, returns -1
           │
        [Call 1] ◄───────┘ receives -1, returns -1
           │
           └──► Final Output: -1 ("No occurence")

======================================================================
4. COMPLEXITY ANALYSIS:
   - Time Complexity (TC):
     * Best Case: O(1) -> Target pehle hi mid element par mil jaye.
     * Worst Case: O(log N) -> Target extreme end par ho ya exist na kare.
     * Average Case: O(log N).
   - Space Complexity (SC):
     * Auxiliary Space: O(log N) -> Har step pe stack frame banta hai (Call Stack).
     * Total Space: O(1) extra space beyond stack frames (vector passed by reference `&`).
======================================================================
*/

int search(vector <int>&nums,int low,int high,int target){
    if(low>high){   // Ye hai base case or TERMINATION STEP jo ki recursive function mein sabse pehle likha jata hai
        return -1;
    }
    int mid=(low+high)/2;
    if(nums[mid]==target){
        return mid;
    }
    else if(nums[mid]<target){
        return search(nums,mid+1,high,target);      // In recurssion i will always have to return something. 
    }
    else{
        return search(nums,low,mid-1,target);       
    }
}

int main(){
    vector <int> nums={2,3,5,6,17,19};
    int n;
    cout<<"Enter target : ";
    cin>>n;
    int res=search(nums,0,nums.size()-1,n);
    if(res!=-1){
        cout<<"The target is at index "<<res;
    }
    else{
        cout<<"No occurence";
    }
    return 0;
}

/*

CASE OF OVERFLOW :-

======================================================================
1. INTUITION & THOUGHT PROCESS (INTEGER OVERFLOW KYA HAI AUR KYUN HOTA HAI?):
   - C++ me standard signed 32-bit `int` ki ek aukat (limit) hoti hai:
       Minimum: -2^31 = -2,147,483,648
       Maximum:  2^31 - 1 =  2,147,483,647 (jise hum INT_MAX bolte hain)
   
   - PROBLEM KA BIRTH:
     Jab hum likhte hain:
         int mid = (low + high) / 2;
     
     Computer pehle right-hand side evaluate karta hai:
     Step 1: (low + high) calculate karta hai.
     Step 2: Jo answer aata hai use 2 se divide karta hai.

     Socho agar array ka size bohot bada ho, aur binary search karte karte 
     `low` aur `high` dono array ke aakhri part me aa jayein, 
     jaise dono ki value INT_MAX ke kareeb ho:
         low  = INT_MAX - 1
         high = INT_MAX

     Toh Step 1 me kya hoga?
         low + high = (INT_MAX - 1) + INT_MAX ≈ 2 * INT_MAX

     Yeh value 2,147,483,647 se badi ho gayi! 
     Isse kehte hain **Integer Overflow**. 
     Computer isse hold nahi kar pata aur value cycle hokar NEGATIVE me wrap 
     ho jati hai (Garbage negative value ban jati hai).
     Phir negative number / 2 = NEGATIVE INDEX!
     Aur jaise hi tum `nums[negative_mid]` karoge -> **Segmentation Fault / Runtime Error (SIGSEGV)**!

======================================================================
2. SOLUTIONS & CODE-TO-EXPLANATION ALIGNMENT:

   --- SOLUTION 1: `long long` use kar lo ---
   Formula:
       int mid = ((long long)low + high) / 2;
   - Intuition: `long long` 64-bit hota hai (limit ≈ 9 * 10^18), toh `low + high` 
     usme bina overflow hue aaram se fit ho jata hai.
   - Downside: Extra casting karni padti hai aur type conversion ka dhyan rakhna padta hai.

   --- SOLUTION 2 (BEST PRACTICE / INDUSTRY STANDARD): Mathematical Rearrangement ---
   Formula:
       int mid = low + (high - low) / 2;

   - Math Proof (Yeh formula same kaise hai?):
       mid = low + (high - low) / 2
           = (2 * low + high - low) / 2      [Take LCM as 2]
           = (low + high) / 2

       Mathematically dono formula 100% IDENTICAL hain!

   - Phir isme overflow kyun nahi hota?
     Look at the operations:
     1. `(high - low)`:
        Kyunki `high >= low`, `(high - low)` hamesha positive hoga aur 
        kisi bhi case me array ki current range se bada nahi ho sakta.
        Dono INT_MAX bhi hue to `INT_MAX - INT_MAX = 0`. No overflow!
     2. `(high - low) / 2`:
        Diff ka aadha kiya (yeh aur bhi chhota ho gaya).
     3. `low + (high - low) / 2`:
        Kyunki `mid` hamesha `low` aur `high` ke beech me lie karega, 
        aur `high <= INT_MAX`, isliye final sum kabhi bhi INT_MAX cross kar hi nahi sakta!

======================================================================
3. DETAILED DRY RUN (STRIEVER BLACKBOARD VISUAL):

   Maan lo ek hypothetically small integer data type hai jo sirf 100 tak store kar sakta hai:
   MAX_LIMIT = 100
   Search range aage badhte badhte yahan pahunchi:
   low  = 70
   high = 90

   -------------------------------------------------------------------
   CASE 1: Purana Tarika -> mid = (low + high) / 2
   -------------------------------------------------------------------
   Step 1: low + high = 70 + 90 = 160
   Step 2: 160 > 100 (LIMIT EXCEEDED!) 
           => 💥 OVERFLOW! 
           => Value wrap hokar negative garbage ban gayi (e.g., -40)
   Step 3: mid = -40 / 2 = -20
   Step 4: nums[-20] ==> CRASH! (Negative Index Error)

   -------------------------------------------------------------------
   CASE 2: Naya Tarika -> mid = low + (high - low) / 2
   -------------------------------------------------------------------
   Step 1: (high - low) = 90 - 70 = 20        (Safe! 20 <= 100)
   Step 2: 20 / 2 = 10                        (Safe!)
   Step 3: low + 10 = 70 + 10 = 80            (Safe! 80 <= 100)
   Result: mid = 80
   Check: 70 aur 90 ka exact center 80 hi hota hai. No Overflow! Safe Execution!

======================================================================
4. COMPLEXITY IMPACT:
   - Time Complexity: O(1) [Kyunki operations wahi simple addition, subtraction, division hain].
   - Space Complexity: O(1) [Koi extra memory use nahi hoti].
======================================================================
*/