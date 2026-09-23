#include<bits/stdc++.h>
using namespace std;

/*
================================================================================
            IS CODE MEIN `long long` KYU USE KIYA?
================================================================================

1. INT KI LIMIT (RANGE ISSUE):
--------------------------------------------------------------------------------
- C++ mein normal `int` sirf lagbhag 2 * 10^9 tak ki value sambhal sakta hai.
- Questions mein array ke elements bade ho sakte hain, jaise 10^9 ya usse zyada.


2. OVERFLOW KA KHATRA:
--------------------------------------------------------------------------------
- Jab hum 3 numbers ko add karte hain:
      sum = nums[i] + nums[j] + nums[k]
- Agar teen numbers 10^9 hue, toh unka sum 3 * 10^9 ho jayega.
- Yeh value `int` ki aukaat (2 * 10^9) se bahar nikal jaati hai (Integer Overflow).
- Overflow hote hi number wrap-around hoke galat (negative/garbage) ban jata hai.


3. `fourth = 0 - sum` MEIN GADBAD:
--------------------------------------------------------------------------------
- Agar `sum` hi overflow ho gaya, toh `fourth` ki value bhi poori galat niklegi.
- Phir hashset mein sahi number match hi nahi hoga aur quadruplet miss ho jayega.


4. `long long` KYA KARTA HAI?
--------------------------------------------------------------------------------
- `long long` 64-bit ka hota hai aur 9 * 10^18 tak ka bada number safely rakh sakta hai.
- Isliye:
    1. `sum` ko `long long` banaya taaki teen numbers ka addition overflow na kare.
    2. `(long long)nums[i] + nums[j]` likha taaki addition shuru se hi 64-bit mein ho.
    3. `fourth` ko `long long` banaya taaki `0 - sum` bilkul accurate rahe.
    4. `set<long long> hashset` banaya taaki find() karte waqt type match ho
       aur comparison bilkul accurate ho.
================================================================================
*/

vector <vector<int>> four_sum(vector <int> &nums){
    int n = nums.size();
    set <vector<int>> st;
    for(int i = 0; i < n;i++){
        for(int j = i+1; j < n;j++){
            set <long long> hashset;
            for(int k = j+1;k < n;k++){
                long long sum = (long long)nums[i] + nums[j];
                sum+= nums[k];
                long long fourth = 0 - sum;
                if(hashset.find(fourth) != hashset.end()){;
                    vector <int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hashset.insert(nums[k]);
            }
        }
    }
    vector <vector<int>> ans(st.begin(), st.end());
    return ans;
}

int main(){
    vector <int> nums = {1, 0, -1, 0, -2, 2};
    cout<<"The numbers adding up to give sum as 0 are :-"<<endl;
    vector <vector<int>> ans = four_sum(nums);
    for(auto row : ans){
        //cout<<x<<endl;    // std::cout << x does not work because x is a vector<int>, and std::ostream doesn't define an << operator for vectors. You must iterate through the elements
        for(int x : row){
            cout<<x<<" ";
        }
        cout<<endl;
    }
    return 0;
}

/*
================================================================================
                    4-SUM: BETTER APPROACH (HASHING)
================================================================================

1. INTUITION (SOCH KYA HAI?)
--------------------------------------------------------------------------------
- Brute Force mein 4 loops the -> O(N^4).
- Fourth loop ka kaam sirf itna tha ki wo aisa element dhoondhe jisse sum 0 ban jaye.
- Equation:
      nums[i] + nums[j] + nums[k] + nums[l] = 0
  Iska matlab:
      nums[l] = -(nums[i] + nums[j] + nums[k])

- Fourth loop lagane ke bajaye hum ek `hashset` maintain karte hain.
- Jab hum 3rd pointer `k` ko aage badha rahe hote hain:
  1. Pehle calculate karo: fourth = -(nums[i] + nums[j] + nums[k])
  2. Dekho kya `fourth` pehle se hamare `hashset` mein maujood hai?
     - Agar HAA: matlab index j aur k ke beech mein koi aisa number tha jo
       fourth element ban kar sum 0 kar sakta hai. Quadruplet mil gaya!
  3. Current element `nums[k]` ko hashset mein insert kar do taaki aage aane
     wale k ke liye ye choice ban sake.
- Unique quadruplets ensure karne ke liye sorted `temp` vector ko `st` (set of vectors)
  mein insert karte hain.


================================================================================
2. STEP-BY-STEP DRY RUN
================================================================================
Input: nums = [1, 0, -1, 0, -2, 2]
Size (n) = 6

Indices:
Index:   0   1   2   3   4   5
Value:   1   0  -1   0  -2   2

Chalo trace karte hain execution:

Case 1: i = 0 (val = 1), j = 1 (val = 0)
-----------------------------------------
hashset empty hai: {}

- k = 2 (val = -1):
  fourth = -(1 + 0 + (-1)) = 0
  Kya 0 hashset mein hai? Nahi (hashset is empty).
  hashset mein nums[2] daalo -> hashset: {-1}

- k = 3 (val = 0):
  fourth = -(1 + 0 + 0) = -1
  Kya -1 hashset mein hai? HAA! (nums[2] tha).
  -> Quadruplet mila: {nums[i], nums[j], nums[k], fourth} = {1, 0, 0, -1}
  Sort temp: {-1, 0, 0, 1}
  st.insert({-1, 0, 0, 1})
  hashset mein nums[3] daalo -> hashset: {-1, 0}

- k = 4 (val = -2):
  fourth = -(1 + 0 + (-2)) = 1
  Kya 1 hashset mein hai? Nahi.
  hashset mein nums[4] daalo -> hashset: {-2, -1, 0}

- k = 5 (val = 2):
  fourth = -(1 + 0 + 2) = -3
  Kya -3 hashset mein hai? Nahi.
  hashset: {-2, -1, 0, 2}

-----------------------------------------
Case 2: i = 0 (val = 1), j = 2 (val = -1)
-----------------------------------------
hashset empty: {}

- k = 3 (val = 0):
  fourth = -(1 + (-1) + 0) = 0 -> Not in hashset.
  hashset: {0}

- k = 4 (val = -2):
  fourth = -(1 + (-1) + (-2)) = 2 -> Not in hashset.
  hashset: {-2, 0}

- k = 5 (val = 2):
  fourth = -(1 + (-1) + 2) = -2 -> FOUND in hashset!
  -> Quadruplet mila: {1, -1, 2, -2}
  Sort temp: {-2, -1, 1, 2}
  st.insert({-2, -1, 1, 2})

-----------------------------------------
Case 3: i = 1 (val = 0), j = 3 (val = 0)
-----------------------------------------
hashset empty: {}

- k = 4 (val = -2):
  fourth = -(0 + 0 + (-2)) = 2 -> Not in hashset.
  hashset: {-2}

- k = 5 (val = 2):
  fourth = -(0 + 0 + 2) = -2 -> FOUND in hashset!
  -> Quadruplet mila: {0, 0, 2, -2}
  Sort temp: {-2, 0, 0, 2}
  st.insert({-2, 0, 0, 2})

Final Unique Quadruplets in `st`:
1. [-2, -1, 1, 2]
2. [-2,  0, 0, 2]
3. [-1,  0, 0, 1]


================================================================================
3. TIME COMPLEXITY (TC)
================================================================================
Total TC: O(N^3 * log(N))  [agar `set<int>` use ho raha hai]
          O(N^3)          [agar `unordered_set<int>` use karein]

Breakdown:
1. Loops:
   - 3 nested loops: i (0 to n), j (i+1 to n), k (j+1 to n).
   - Iterations roughly: N * (N-1) * (N-2) / 6 = O(N^3).

2. Inside innermost loop:
   - `hashset.find(fourth)`:
     `std::set` (Red-Black tree) use ho raha hai, toh search time = O(log(size)).
     Hashset ka size max N ho sakta hai -> O(log N).
   - `hashset.insert(nums[k])`: O(log N).
   - `st.insert(temp)`: Unique quadruplets insert karne ka time O(log K).

Isliye current code ki TC = O(N^3 * log(N) + N^3 * log(K)).
(Note: Agar `set<int> hashset` ki jagah `unordered_set<int>` use karein toh average TC O(N^3) ho jaati hai).


================================================================================
4. SPACE COMPLEXITY (SC)
================================================================================
Total Auxiliary Space: O(N) + O(2 * K) -> O(N + K)
(Jahan N = array size, K = unique quadruplets ki count)

Breakdown:
1. `set<int> hashset`:
   - Inner loop mein har baar max (N) elements store karta hai -> O(N).
2. `set<vector<int>> st`:
   - K quadruplets store karta hai -> O(4 * K) = O(K).
3. `vector<vector<int>> ans`:
   - Output return karne ke liye K quadruplets -> O(K).

Total Space: O(N) auxiliary space + O(K) space for returning the result.
*/