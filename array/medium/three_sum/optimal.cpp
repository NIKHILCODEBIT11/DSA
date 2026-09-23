#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
  3-SUM : OPTIMAL APPROACH (SORTING + TWO POINTERS)
================================================================================

  INTUITION (Dimaag me approach kaise aayi?):
  -------------------------------------------
  1. Hashing wali approach me hum O(N^2) time to le aaye the, lekin extra space
     lag raha tha (hashset aur set<vector<int>> st) aur log factor bhi tha.
  
  2. Agar array ko pehle hi SORT kar diya jaye, to do bohot bade fayde milte hain:
     - Fayda 1: Saare duplicate numbers ek saath aa jate hain, jisse unhe bina
       kisi 'set' container ke sirf simple pointer skips se discard kiya ja sakta hai.
     - Fayda 2: Sorted order ka use karke hum standard TWO-POINTER technique
       laga sakte hain (jaha sum chhota ho to left badhao, bada ho to right ghatao).

  THOUGHT PROCESS (Step-by-step logic):
  ------------------------------------
  Step 1: Array ko sort karo.
          Ab hum array ke pehle element (i) ko ek-ek karke fix karenge.
  
  Step 2: 'i' ke duplicates skip karo.
          Agar nums[i] == nums[i-1] hai, to wahi same calculation dobara hogi.
          Isliye seedhe 'continue;' karke agle unique number par jao.
  
  Step 3: Baki bache hue array me Two Pointers lagao:
          - j = i + 1 (Left pointer)
          - k = n - 1 (Right pointer)
          
          Jab tak j < k hai:
          - sum = nums[i] + nums[j] + nums[k]
          - Agar sum < 0: Hume bada sum chahiye, aur array sorted hai,
                          isliye left pointer aage badhao (j++).
          - Agar sum > 0: Hume chhota sum chahiye, isliye right pointer
                          peeche lao (k--).
          - Agar sum == 0: Ek valid triplet mil gaya!
            * Use ans me push_back karo.
            * j ko ek aage badhao (j++), k ko ek peeche lao (k--).
            * Ab 'j' aur 'k' par aane wale saare duplicate values ko skip
              kar do taaki same triplet dobara ans me na jud jaye.

*/

/*
================================================================================
  3-SUM : VISUAL DRY RUN (POINTER POSITIONS AT EVERY STEP)
================================================================================

  Sorted Array Reference:
  Index:   0    1    2    3    4    5    6    7    8    9   10   11   12
  Value: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]

  Initial: ans = []

================================================================================
  ROUND 1: i = 0 (nums[i] = -2)
================================================================================

  Step 1.1:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i    j                                                      k
  Indices: 0    1                                                     12
  Values:  nums[i]=-2, nums[j]=-2, nums[k]=2
  Sum = (-2) + (-2) + 2 = -2 (< 0) -> Sum chhota hai, j++ karo.
  ------------------------------------------------------------------------------

  Step 1.2:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i         j                                                 k
  Indices: 0         2                                                12
  Values:  nums[i]=-2, nums[j]=-2, nums[k]=2
  Sum = (-2) + (-2) + 2 = -2 (< 0) -> Sum chhota hai, j++ karo.
  ------------------------------------------------------------------------------

  Step 1.3:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i              j                                            k
  Indices: 0              3                                           12
  Values:  nums[i]=-2, nums[j]=-1, nums[k]=2
  Sum = (-2) + (-1) + 2 = -1 (< 0) -> Sum chhota hai, j++ karo.
  ------------------------------------------------------------------------------

  Step 1.4:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i                   j                                       k
  Indices: 0                   4                                      12
  Values:  nums[i]=-2, nums[j]=-1, nums[k]=2
  Sum = (-2) + (-1) + 2 = -1 (< 0) -> Sum chhota hai, j++ karo.
  ------------------------------------------------------------------------------

  Step 1.5:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i                        j                                  k
  Indices: 0                        5                                 12
  Values:  nums[i]=-2, nums[j]=-1, nums[k]=2
  Sum = (-2) + (-1) + 2 = -1 (< 0) -> Sum chhota hai, j++ karo.
  ------------------------------------------------------------------------------

  Step 1.6:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:i                             j                             k
  Indices: 0                             6                            12
  Values:  nums[i]=-2, nums[j]=0, nums[k]=2
  Sum = (-2) + 0 + 2 = 0  --> MATCH MIL GAYA!
  ans.push_back({-2, 0, 2})
  ans = [ [-2, 0, 2] ]

  Action:
  1. j++ (j=7) aur k-- (k=11)
  2. Duplicates skip:
     - j ko tab tak badhao jab tak nums[j] == nums[j-1]:
       j=7 (0 == 0) -> j=8
       j=8 (0 == 0) -> j=9
     - k ko tab tak ghatao jab tak nums[k] == nums[k+1]:
       k=11 (2 == 2) -> k=10
       k=10 (2 == 2) -> k=9
  Ab j=9, k=9. Condition (j < k) fail -> Round 1 complete!

================================================================================
  ROUNDS 2 & 3: i = 1 aur i = 2 (nums[1]=-2, nums[2]=-2)
================================================================================
  nums[i] == nums[i-1] (-2 == -2) -> Duplicates skipped by 'continue;'.

================================================================================
  ROUND 4: i = 3 (nums[i] = -1)
================================================================================

  Step 4.1:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:               i    j                                       k
  Indices:                3    4                                      12
  Values:  nums[i]=-1, nums[j]=-1, nums[k]=2
  Sum = (-1) + (-1) + 2 = 0  --> MATCH MIL GAYA!
  ans.push_back({-1, -1, 2})
  ans = [ [-2, 0, 2], [-1, -1, 2] ]

  Action:
  1. j++ (j=5) aur k-- (k=11)
  2. Duplicates skip:
     - j=5 (nums[5]==nums[4] -> -1==-1) -> j=6 (nums[6]=0)
     - k=11 (nums[11]==nums[12] -> 2==2) -> k=10
     - k=10 (nums[10]==nums[11] -> 2==2) -> k=9 (nums[9]=2)
  Nayi positions: j = 6, k = 9
  ------------------------------------------------------------------------------

  Step 4.2:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:               i              j              k
  Indices:                3              6              9
  Values:  nums[i]=-1, nums[j]=0, nums[k]=2
  Sum = (-1) + 0 + 2 = 1 (> 0) -> Sum bada hai, k-- karo -> k = 8.
  ------------------------------------------------------------------------------

  Step 4.3:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:               i              j         k
  Indices:                3              6         8
  Values:  nums[i]=-1, nums[j]=0, nums[k]=0
  Sum = (-1) + 0 + 0 = -1 (< 0) -> Sum chhota hai, j++ karo -> j = 7.
  ------------------------------------------------------------------------------

  Step 4.4:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:               i                   j    k
  Indices:                3                   7    8
  Values:  nums[i]=-1, nums[j]=0, nums[k]=0
  Sum = (-1) + 0 + 0 = -1 (< 0) -> Sum chhota hai, j++ karo -> j = 8.

  Ab j=8, k=8. Condition (j < k) fail -> Round 4 complete!

================================================================================
  ROUNDS 5 & 6: i = 4 aur i = 5 (nums[4]=-1, nums[5]=-1)
================================================================================
  nums[i] == nums[i-1] (-1 == -1) -> Duplicates skipped by 'continue;'.

================================================================================
  ROUND 7: i = 6 (nums[i] = 0)
================================================================================

  Step 7.1:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:                             i    j                         k
  Indices:                              6    7                        12
  Values:  nums[i]=0, nums[j]=0, nums[k]=2
  Sum = 0 + 0 + 2 = 2 (> 0) -> Sum bada hai, k-- karo -> k = 11.
  ------------------------------------------------------------------------------

  Step 7.2 to 7.4 (k peeche aayega jab tak 2 khatam na ho):
  k=11, 10, 9 par value 2 hi rahegi, sum > 0 rahega, k-- hota rahega.
  Aakhir me k = 8 par rukega (nums[8] = 0).
  ------------------------------------------------------------------------------

  Step 7.5:
  Array: [-2,  -2,  -2,  -1,  -1,  -1,   0,   0,   0,   2,   2,   2,   2]
  Pointers:                             i    j    k
  Indices:                              6    7    8
  Values:  nums[i]=0, nums[j]=0, nums[k]=0
  Sum = 0 + 0 + 0 = 0  --> MATCH MIL GAYA!
  ans.push_back({0, 0, 0})
  ans = [ [-2, 0, 2], [-1, -1, 2], [0, 0, 0] ]

  Action:
  j++ (j=8), k-- (k=7) -> Pointers cross ho gaye (j > k). Round 7 complete!

================================================================================
  ROUND 8 ONWARDS:
================================================================================
  - i = 7, 8 (value: 0) -> nums[i] == nums[i-1] se continue ho jayenge.
  - i = 9, 10, 11, 12 (value: 2) -> nums[i] > 0 hai, positive numbers ka sum
    kabhi 0 nahi ho sakta.

================================================================================
  FINAL OUTPUT RETURNED:
  [
    [-2, 0, 2],
    [-1, -1, 2],
    [0, 0, 0]
  ]
================================================================================
*/

vector<vector<int>> three_sum(vector <int> &nums){
    int n = nums.size();
    vector <vector<int>> ans;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        if(i > 0 && nums[i] == nums[i-1]){
            continue;
        }
        int j = i + 1;
        int k = n - 1;
        while(j < k){
            int sum = nums[i] + nums[j] + nums[k];
            if(sum < 0){
                j++;
            }
            else if(sum > 0){
                k--;
            }
            else{
                ans.push_back({nums[i], nums[j], nums[k]});
                j++;
                k--;
                while(j < k && nums[j] == nums[j-1]){
                    j++;
                }
                while(j < k && nums[k] == nums[k+1]){
                    k--;
                }
            }
        }
    }
    return ans;
}

int main(){
    vector <int> nums = {-2, -2, -2, 0, 0, 0, 2, 2, -1, -1, -1, 2, 2};
    cout<<"The three numbers giving sum as 0 are :-"<<endl;
    vector<vector<int>> ans = three_sum(nums);
    for(auto row : ans){
        for(int x : row){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return 0;
}

/*
================================================================================
  COMPLEXITY ANALYSIS (3-SUM : OPTIMAL TWO-POINTER APPROACH)
================================================================================

  1. TIME COMPLEXITY (TC):
  ------------------------
  Total Time = O(N log N) + O(N^2) ≈ O(N^2)

  Breakdown:
  - Step 1 (Sorting):
    `sort(nums.begin(), nums.end())` array ko sort karne me O(N log N) leta hai.

  - Step 2 (Nested Loops):
    * Outer loop 'i' chalta hai N baar -> O(N).
    * Inner loop me two pointers 'j' aur 'k' milkar bache hue array ko
      ek hi pass me cover karte hain (j++ aage badhta hai, k-- peeche aata hai).
      Dono pointers total milkar maximum N steps chalte hain -> O(N).
    * Isliye inner work har 'i' ke liye O(N) hai.

  - Overall Time:
    O(N log N) + O(N * N) = O(N^2).

--------------------------------------------------------------------------------

  2. SPACE COMPLEXITY (SC):
  -------------------------
  Auxiliary Space (Algorithm ka extra space) = O(1)
  Total Space (Answer store karne ke sath)   = O(no. of unique triplets)

  Breakdown:
  - Humne duplicates handle karne ke liye koi bhi extra Hashset ya 
    `set<vector<int>>` use nahi kiya hai.
  - Sirf 3 pointer variables (i, j, k) aur ek 'sum' variable use ho rahe hain,
    jo constant memory lete hain -> O(1).
  - 'ans' vector ka space algorithm ki logic ka hissa nahi balki required
    output return karne ke liye hai.

================================================================================
  ALL 3 APPROACHES COMPARISON (FOR INTERVIEWS / REVISION)
================================================================================
  
  Approach 1: Brute Force (3 Loops + Set)
  - TC: O(N^3 * log(M))   [3 nested loops + set insertion]
  - SC: O(2 * M)          [set container + ans vector]

  Approach 2: Better (2 Loops + Hashset + Set)
  - TC: O(N^2 * log(M))   [2 loops + set insertion]
  - SC: O(N) + O(2 * M)   [hashset + set container + ans vector]

  Approach 3: Optimal (Sorting + Two Pointers)
  - TC: O(N^2)            [O(N log N) sorting + O(N^2) two pointers]
  - SC: O(1)              [zero extra data structures used]

  *(Yaha N = array size, M = unique triplets count)*
================================================================================
*/