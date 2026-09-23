#include<bits/stdc++.h>
using namespace std;

vector <vector<int>> four_sum(vector <int> &nums, int target){
    int n = nums.size();
    vector <vector<int>> ans;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        if(i > 0 && nums[i] == nums[i-1]){
            continue;
        }
        for(int j = i+1; j < n; j++){
            if(j > i+1 && nums[j] == nums[j-1]){
                continue;
            }
            int k = j + 1;
            int l = n - 1;
            while(k < l){
                long long sum = nums[i] + nums[j];
                sum += nums[k];
                sum += nums[l];
                if(sum == target){
                    vector <int> temp = {nums[i], nums[j], nums[k], nums[l]};
                    ans.push_back(temp);
                    k++;
                    l--;
                    while(k < l && nums[k] == nums[k-1]){
                        k++;
                    }
                    while(k < l && nums[l] == nums[l+1]){
                        l--;
                    }
                }
                else if(sum < target){
                    k++;
                }
                else{
                    l--;
                }
            }
        }
    }
    return ans;
}

int main(){
    vector <int> nums = {1,2,3,1,2,3,1,2,3,4,4,5,4,5,5};
    cout<<"The numbers adding up to give sum as 8 are :-"<<endl;
    vector <vector<int>> ans = four_sum(nums, 8);
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
                    4-SUM: OPTIMAL TWO-POINTER APPROACH
================================================================================

1. INTUITION (SOCH KYA HAI?)
--------------------------------------------------------------------------------
- Pichle tareeqon mein hum duplicate hatane ke liye `std::set` use kar rahe the,
  jiski wajah se extra space lagti thi aur logarithmic time multiply hota tha.
- Is approach ka main goal:
    1. Time Complexity ko strictly O(N^3) lana (bina kisi log factor ke).
    2. Space Complexity ko O(1) lana (extra space zero, sirf ans vector return hoga).

Kaise karte hain?
1. ARRAY KO SORT KARO:
   - Sorting se saare identical elements paas-paas aa jaate hain.
   - Array monotonic ho jata hai, jisse hum two-pointer technique chala sakein.

2. DO POINTERS FIX KARO (i aur j):
   - Outer loop `i` pehla element chunega.
   - Inner loop `j` doosra element chunega.

3. TWO-POINTER TECHNIQUE (k aur l):
   - `k = j + 1` (left se aage badhega).
   - `l = n - 1` (right se peeche aayega).
   - Sum calculate karo: sum = nums[i] + nums[j] + nums[k] + nums[l]
     * Agar sum == target: Answer mil gaya! Result mein push karo, aur k++, l-- karo.
     * Agar sum < target: Sum badhane ke liye left pointer badhao (`k++`).
     * Agar sum > target: Sum ghatane ke liye right pointer ghatao (`l--`).

4. DUPLICATES KO MANUALLY SKIP KARNA (NO SET NEEDED):
   - `i` ke liye: Agar nums[i] == nums[i-1] ho, toh `continue` karo.
   - `j` ke liye: Agar nums[j] == nums[j-1] ho (jab j > i+1), toh `continue` karo.
   - `k` aur `l` ke liye: Answer milne ke baad jab tak same element repeat ho raha hai,
     tab tak k ko aage aur l ko peeche move karte raho.
   Is trick se bina kisi `set` ke hume 100% UNIQUE quadruplets milte hain.


================================================================================
2. STEP-BY-STEP DRY RUN
================================================================================
Input: nums = [1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 4, 5, 4, 5, 5], Target = 8

Step 1: Sort the array
nums (sorted) = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5]
Size n = 15

Chalo dekhte hain valid matches kaise bante hain:

--- Case A: i = 0 (val = 1), j = 1 (val = 1) ---
Remaining required sum = 8 - (1 + 1) = 6
Search range: k = 2 se l = 14 tak.

- k = 2 (val = 1), l = 14 (val = 5):
  sum = 1 + 1 + 1 + 5 = 8 == Target -> MATCH FOUND!
  Quadruplet: [1, 1, 1, 5]
  Duplicate skip:
  - k ko aage badhaya, l ko peeche kiya.
  - Ab k = 3 (val = 2), l = 13 (val = 5).

- k = 3 (val = 2), l = 13 (val = 5):
  sum = 1 + 1 + 2 + 5 = 9 > 8 -> Sum bada hai, so l--.
  l = 12 (val = 5) -> sum = 9 > 8 -> l--.
  l = 11 (val = 4):
  sum = 1 + 1 + 2 + 4 = 8 == Target -> MATCH FOUND!
  Quadruplet: [1, 1, 2, 4]
  Duplicate skip:
  - k skipped over remaining 2's -> k reaches index 6 (val = 3).
  - l skipped over remaining 4's -> l reaches index 8 (val = 3).

- k = 6 (val = 3), l = 8 (val = 3):
  sum = 1 + 1 + 3 + 3 = 8 == Target -> MATCH FOUND!
  Quadruplet: [1, 1, 3, 3]
  k++, l-- -> k cross kar gaya l ko (loop ends for this j).

--- Case B: i = 0 (val = 1), j duplicate check ---
- j = 2 (val = 1): nums[2] == nums[1] -> SKIP (continue).
- j = 3 (val = 2):
  Remaining required sum = 8 - (1 + 2) = 5
  k = 4 (val = 2), l = 14 (val = 5)
  - k = 4 (val = 2), l = 8 (val = 3):
    sum = 1 + 2 + 2 + 3 = 8 == Target -> MATCH FOUND!
    Quadruplet: [1, 2, 2, 3]

--- Case C: Other i and j combinations ---
- i = 1 (val = 1), i = 2 (val = 1) -> nums[i] == nums[i-1] hone ki wajah se SKIP.
- i = 3 (val = 2), j = 4 (val = 2):
  Remaining required sum = 8 - (2 + 2) = 4
  k = 5 (val = 2), l = 14 (val = 5)
  k = 5 (val = 2), l = 6 (val = 2):
  sum = 2 + 2 + 2 + 2 = 8 == Target -> MATCH FOUND!
  Quadruplet: [2, 2, 2, 2]

Final Unique Quadruplets Output:
[1, 1, 1, 5]
[1, 1, 2, 4]
[1, 1, 3, 3]
[1, 2, 2, 3]
[2, 2, 2, 2]


================================================================================
3. TIME COMPLEXITY (TC)
================================================================================
Total TC: O(N^3)

Breakdown:
1. Sorting:
   - `sort(nums.begin(), nums.end())` takes O(N * log(N)) time.

2. Nested Loops + Two-Pointer:
   - Outer loop `i` chalta hai O(N) baar.
   - Middle loop `j` chalta hai O(N) baar.
   - Inner while loop (`k` aur `l`):
     Donon pointers milkar array ke bache hue hisse ko sirf ek baar traverse karte hain.
     Har element max ek baar visit hota hai -> O(N).
   - Total loops execution = N * N * N = O(N^3).

3. Duplicate Skips:
   - Duplicate skip karte waqt `while` loops sirf pointers (`k++`, `l--`) ko aage
     badhate hain, yeh koi extra work nahi karte balki inner loop ko jaldi khatam karte hain.

Overall Time Complexity = O(N * log N) + O(N^3) = O(N^3).


================================================================================
4. SPACE COMPLEXITY (SC)
================================================================================
Total Auxiliary Space: O(1)

Breakdown:
1. Koi `std::set` ya `unordered_set` use nahi ho raha.
2. Extra variables (`i`, `j`, `k`, `l`, `sum`) sirf constant primitive space lete hain -> O(1).
3. `vector<vector<int>> ans`:
   - Yeh sirf required output return karne ke liye use hota hai (not auxiliary space).
4. Sorting space:
   - C++ standard `std::sort` internally introsort use karta hai, jo recursive call stack
     ke liye O(log N) space leta hai.

Auxiliary Space (excluding output): O(1).
*/