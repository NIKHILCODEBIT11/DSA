/*
Suppose nums = {3,1,-2,-5,2,-4}
mujhe final array aise banana hai ki (pehla element {+}, dusra element {-}, teesra element {+}, chautha element {-}, panchva element {+}, sixth element {-})
Aur wo bhi SAME ORDER MEIN
EX :-
Before rearranging :-
nums = {3,1,-2,-5,2,-4}
After rearranging :-
nums = {3,-2,1,-5,2,-4}
EXPLAINATION :- 
positive ka order :- 3   1   2      INDEX :- {0,2,4} ----> All even {2*i}
negative ka order :- -2 -5  -4      INDEX :- {1,3,5} ----> All odd {2*i + 1}

isliye pehle ek array banaunga pos jisme saare positive elements honge SAME ORDER mein
uske baad ek array banaunga neg jisme saare negative  elements honge SAME ORDER mein

phir :-
un elements ko array mein dalunga, Jaha i i=will traverse from index 0 -> N/2
positive elements ko nums ke index {2*i} mein
negative elements ko nums ke index {2*i + 1} mein

*/

#include<bits/stdc++.h>
using namespace std;

void rearrange_elements_by_sign(vector <int> &nums){
    int n = nums.size();
    vector <int> pos(n/2);
    vector <int> neg(n/2);
    int count_pos = 0;
    int count_neg = 0;

    // Putting positive elements in pos and negative elmenets in neg
    for(int i = 0;i < n;i++){
        if(nums[i] > 0){
            // pos.insert(pos.begin()+count_pos, nums[i]);        NOT USED REASON BELOW :-
            // count_pos++;
            pos[count_pos++] = nums[i];
        }
        else{
            // neg.insert(neg.begin()+count_neg, nums[i]);        NOT USED REASON BELOW :-
            // count_neg++;
            neg[count_neg++] = nums[i];
        }
    }

    // Putting elements back to array nums in same order :-
    for(int i = 0;i < n/2;i++){
        nums[2*i] = pos[i];
        nums[2*i + 1] = neg[i];
    }
}

int main(){
    vector <int> nums = {3,1,-2,-5,2,-4};
    cout<<"Before rearranging :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
    rearrange_elements_by_sign(nums);
    cout<<"After rearranging :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}

// ❌ GALTI: vector<int> pos(n/2) pehle se hi {0, 0, 0} bana deta hai.
// Jab aap pos.insert() karte ho, ye overwrite nahi karta balki naye elements add karke
// size double kar deta hai aur har insertion pe shift hone ki wajah se O(N^2) time leta hai.
//
// EXAMPLE:
// Initial: pos = {0, 0, 0}
// After insert(3), insert(1), insert(2):
// pos ban jata hai = {3, 1, 2, 0, 0, 0} (size = 6, na ki 3!)

// ✅ FIX (Option 1): Pehle se size diya hai toh direct index se overwrite karo (O(1))
// pos[count_pos++] = nums[i];

// ✅ FIX (Option 2): Agar insert/push hi karna hai, toh empty vector banao
// vector<int> pos; // size 0
// pos.push_back(nums[i]);

/*
TC :- O(N) + O(N/2) ----> First O(N) for traversing whole array and putting elements in pos and neg and 2nd O(N/2) for traversing arrays pos and neg 
SC :- O(N) ----> As, both pos and neg are created each having size N/2 so toal size is N
*/