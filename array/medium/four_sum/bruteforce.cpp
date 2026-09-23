#include<bits/stdc++.h>
using namespace std;

vector <vector<int>> four_sum(vector<int> &nums){
    int n = nums.size();
    set <vector<int>> st;
    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            for(int k = j+1;k < n;k++){
                for(int l = k+1;l < n;l++){
                    long long sum = nums[i] + nums[j];
                    sum += nums[k];
                    sum += nums[l];
                    if(sum == 0){
                        vector <int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
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
                        4-SUM: BRUTE FORCE APPROACH
================================================================================

1. INTUITION (SOCH KYA HAI?)
--------------------------------------------------------------------------------
- Array mein se aise 4 elements (quadruplets) dhoondhne hain jinka sum 0 ho.
- Har element ka index alag hona chahiye: i != j != k != l.
- Duplicate quadruplets answer mein nahi aane chahiye (jaise [-1, 0, 0, 1] 
  aur [0, -1, 1, 0] same maane jaayenge).

Brute Force Logic:
1. Saare possible 4 elements ke groups check karne ke liye 4 nested loops lagao:
   - Loop 1 (i): Pehla element chunega.
   - Loop 2 (j = i + 1): Doosra element chunega.
   - Loop 3 (k = j + 1): Teesra element chunega.
   - Loop 4 (l = k + 1): Chautha element chunega.
2. Chaaro ka sum nikalo. Agar sum == 0 milta hai:
   - In 4 elements ko ek temporary vector mein daalo.
   - Uss vector ko SORT kar do taaki same elements ka order hamesha identical rahe.
   - Vector ko `std::set` mein daal do. Set duplicate quadruplets ko automatically
     reject kar dega aur sirf unique results rakhega.
3. Last mein set ke unique elements ko vector mein daal kar return kar do.


================================================================================
2. STEP-BY-STEP DRY RUN
================================================================================
Input: nums = [1, 0, -1, 0, -2, 2]
Size (n) = 6, Target = 0

Indices:
Index:   0   1   2   3   4   5
Value:   1   0  -1   0  -2   2

Total combinations: 6C4 = 15

Valid matches jo set mein store honge:

1. Match 1:
   - i = 0 (1), j = 1 (0), k = 2 (-1), l = 3 (0)
   - Sum = 1 + 0 + (-1) + 0 = 0 (Valid)
   - Temp vector: {1, 0, -1, 0}
   - Sort karne ke baad: {-1, 0, 0, 1}
   - Set mein insert: { {-1, 0, 0, 1} }

2. Match 2:
   - i = 0 (1), j = 2 (-1), k = 4 (-2), l = 5 (2)
   - Sum = 1 + (-1) + (-2) + 2 = 0 (Valid)
   - Temp vector: {1, -1, -2, 2}
   - Sort karne ke baad: {-2, -1, 1, 2}
   - Set mein insert: { {-2, -1, 1, 2}, {-1, 0, 0, 1} }

3. Match 3:
   - i = 1 (0), j = 3 (0), k = 4 (-2), l = 5 (2)
   - Sum = 0 + 0 + (-2) + 2 = 0 (Valid)
   - Temp vector: {0, 0, -2, 2}
   - Sort karne ke baad: {-2, 0, 0, 2}
   - Set mein insert: { {-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1} }

Duplicate handling:
- Agar aage jaake kisi aur index combination se dobara {0, -1, 1, 0} banta,
  to sort hoke wo wapas {-1, 0, 0, 1} banta. Set use dubara add nahi karta.

Final Output:
[-2, -1, 1, 2]
[-2,  0, 0, 2]
[-1,  0, 0, 1]


================================================================================
3. TIME COMPLEXITY (TC)
================================================================================
Total TC: O(N^4 * log(K))
(Jahan N = array size, K = set ke andar unique quadruplets ki count)

Breakdown:
1. 4 Nested Loops:
   - Iterations roughly N * (N-1) * (N-2) * (N-3) / 24 hoti hain.
   - Yeh banata hai O(N^4).

2. Operations inside the innermost loop:
   - Size-4 vector ko sort karna: 4 * log(4) = O(1) constant time.
   - Set mein insert karna: Set mein 4 elements ka vector compare hoke insert
     hone mein O(4 * log(K)) = O(log(K)) time lagta hai.

Isliye total Time Complexity = O(N^4 * log(K)).


================================================================================
4. SPACE COMPLEXITY (SC)
================================================================================
Total Auxiliary Space: O(K)
(Jahan K = unique quadruplets ka count)

Breakdown:
1. std::set<vector<int>> st:
   - K quadruplets store karne ke liye space = O(4 * K) = O(K).

2. Final ans vector:
   - Result return karne ke liye use hota hai = O(K).

3. Temp vector inside loop:
   - Har baar sirf 4 integers store karta hai = O(1).

Isliye extra space sirf unique answers ko store karne ke liye O(K) lagta hai.
*/