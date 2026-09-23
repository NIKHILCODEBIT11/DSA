#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> three_sum(vector<int> &nums){   // kyuki mujhe waisa vector return karna hai jiske andar bhi vectors ho
    int n = nums.size();
    set<vector<int>> st;    // kyuki mujhe aisa set banana hai jiske andar ke elements vector ho
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            for(int k = j+1; k < n; k++){
                if(nums[i] + nums[j] + nums[k] == 0){
                    vector <int> temp = {nums[i], nums[j], nums[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
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
  PROBLEM SUMMARY:
  Array me se aise 3 distinct index wale elements (i, j, k) nikalne hain jinka
  sum 0 ho: nums[i] + nums[j] + nums[k] == 0.
  Shart ye hai ki answer me duplicate triplets nahi aane chahiye.

================================================================================
  THOUGHT PROCESS (Kyun aur kaise socha?):
================================================================================

  1. Brute Force (Har ek triplet ko check karo):
     - Teen nested loops lagaye:
       * i chalega 0 se n-1
       * j chalega i+1 se n-1
       * k chalega j+1 se n-1
     - Aise chalane se automatically teeno indices alag rahenge (i != j != k)
       aur koi bhi index combination repeat nahi hoga.

  2. Duplicates ka issue kaise solve kiya?
     - Problem: Array me agar multiple same numbers hain (jaise kai saare -2, 0, 2),
       to sum 0 baar-baar banega aur same triplet multiple times capture hoga.
       Dusri dikkat: Order ka farak. {2, -2, 0} aur {-2, 0, 2} mathematically
       same triplet hain, lekin list comparison me alag dikh sakte hain.
     - Solution Step 1: Jaise hi sum == 0 mila, teeno elements ko temp vector me
       daal kar SORT kar diya. Isse {2, 0, -2} ho ya {0, -2, 2}, hamesha
       {-2, 0, 2} hi banega.
     - Solution Step 2: Inhe `set<vector<int>>` me store kiya. C++ ka 'set'
       sirf UNIQUE elements rakhta hai. Agar {-2, 0, 2} pehle se set me hai,
       to agli baar wo use ignore kar dega.

  3. Final Output:
     - 'set' ke paas saare unique sorted triplets aa gaye.
     - Unhe normal `vector<vector<int>>` me copy karke return kar diya.

================================================================================
  DRY RUN STEP-BY-STEP:
  Input Array: nums = [-2, -2, -2, 0, 0, 0, 2, 2, -1, -1, -1, 2, 2]
  Total elements (n) = 13
================================================================================

  Initial State:
  - set<vector<int>> st = {} (Khaali hai)

  Loop Execution Trace (Key Iterations):

  Case A: Jab pehla sum == 0 milta hai
  - i = 0 (nums[0] = -2)
  - j = 3 (nums[3] = 0)
  - k = 6 (nums[6] = 2)
  - Check: (-2) + 0 + 2 == 0 -> TRUE.
  - temp = {-2, 0, 2} -> Sort hone ke baad bhi {-2, 0, 2}.
  - st.insert(temp) -> Triplet set me add ho gaya.
  - st abhi: { {-2, 0, 2} }

  Case B: Duplicate triplets ka handle hona
  - i = 1 (nums[1] = -2)
  - j = 4 (nums[4] = 0)
  - k = 7 (nums[7] = 2)
  - Check: (-2) + 0 + 2 == 0 -> TRUE.
  - temp = {-2, 0, 2} -> Sort hone ke baad {-2, 0, 2}.
  - st.insert(temp) -> Set ne dekha {-2, 0, 2} pehle se maujood hai,
    isliye duplicate ko REJECT kar diya.
  - st abhi bhi: { {-2, 0, 2} }

  Case C: Dusra unique triplet (-1 wale elements se)
  - i = 8  (nums[8] = -1)
  - j = 9  (nums[9] = -1)
  - k = 11 (nums[11] = 2)
  - Check: (-1) + (-1) + 2 == 0 -> TRUE.
  - temp = {-1, -1, 2} -> Sort hone ke baad {-1, -1, 2}.
  - st.insert(temp) -> Ye naya triplet hai, set me add ho gaya.
  - st ab: { {-2, 0, 2}, {-1, -1, 2} }

  Case D: Teeno zeros ka milna
  - i = 3 (nums[3] = 0)
  - j = 4 (nums[4] = 0)
  - k = 5 (nums[5] = 0)
  - Check: 0 + 0 + 0 == 0 -> TRUE.
  - temp = {0, 0, 0} -> Sort hone ke baad {0, 0, 0}.
  - st.insert(temp) -> Ye bhi naya triplet hai, set me add hua.
  - st ab: { {-2, 0, 2}, {-1, -1, 2}, {0, 0, 0} }

  Case E: Baki ke sare combinations
  - Baki bache hue combinations ya to sum 0 nahi banayenge,
    ya fir upar wale 3 triplets me se hi duplicate generate karenge
    jise set drop karta rahega.

  End Result:
  - Set me total 3 unique triplets bache:
    1. {-2, 0, 2}
    2. {-1, -1, 2}
    3. {0, 0, 0}
  - Inhe 2D vector 'ans' me convert karke return kiya jata hai.

================================================================================
  COMPLEXITY REASONING:
  - Time Complexity: O(n^3 * log(number_of_unique_triplets))
    * Teen nested loops = O(n^3)
    * Set me vector insert karna = O(3 * log(size_of_set))
  - Space Complexity: O(2 * number_of_unique_triplets)
    * Ek set me store karne ke liye aur ek final answer vector ke liye.
================================================================================
*/