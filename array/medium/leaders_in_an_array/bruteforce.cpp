/*
Suppose nums = [10, 22, 12, 3, 0, 6]
ab mujhe aise ELEMENT khojne hain jinke right mein saare ke saare elements, ELEMENT se chote ho

ans = [22, 12, 6]
kyuki 6 last mein hai isliye wo hamesha hi ans mein hoga

DRY RUN :-

nums = [10, 22, 12, 3, 0, 6]

PASS 1 :-
i = 0 and lead = true
1. j = 1 ----> 10 < 22 ---> lead = false ---> break ---> ans.push_back(nums[i]);   NOT RUNS
ans = []

PASS 2 :-
i = 1 and lead = true
1. j = 2 ----> 22 > 12 ---> if BLOCK RUN NAHI HOGA 
2. j = 3 ----> 22 > 3
3. j = 4 ----> 22 > 0
4. j = 5 ----> 22 > 6

At end of this pass still lead = true so ans.push_back(nums[i])
ans = [22]

PASS 3 :-
i = 2 and lead = true
1. j = 3 ----> 12 > 3 
2. j = 4 ----> 12 > 0
3. j = 5 ----> 12 > 6

At end of this pass still lead = true so ans.push_back(nums[i])
ans = [22, 12]

PASS 4 :-
i = 3 and lead = true
1. j = 4 ----> 3 > 0
2. j = 5 ----> 3 < 6 ---> lead = false ---> break ---> ans.push_back(nums[i])   NOT RUNS

At end of this pass still lead = true so ans.push_back(nums[i])
ans = [22, 12]

PASS 5 :-
i = 4 and lead = true
1. j = 5 ----> 0 < 6 ---> lead = false ---> break ---> ans.push_back(nums[i])   NOT RUNS

At end of this pass still lead = true so ans.push_back(nums[i])
ans = [22, 12]

PASS 6 :-
i = 5 and lead = true
1. j = 6 ----> OUT OF INDEX -----> SO "if" BLOCK DOESN'T RUNS SO lead stays true

At end of this pass still lead = true so ans.push_back(nums[i])
ans = [22, 12, 6]

*/

#include<bits/stdc++.h>
using namespace std;

vector <int> leaders(vector <int> &nums){
    int n = nums.size();
    vector <int> ans;
    for(int i = 0;i < n;i++){
        bool lead = true;
        for(int j = i+1;j < n;j++){
            if(nums[i] < nums[j]){
                lead = false;
                break;
            }
        }
        if(lead){         // Directly runs only if lead is true
            ans.push_back(nums[i]);
        }
    }
    return ans;
}

int main(){
    vector <int> nums = {10, 22, 12, 3, 0, 6};
    cout<<"Leaders are :-"<<endl;
    vector <int> ans = leaders(nums);
    for(int x : ans){
        cout<<x<<" ";
    }
    return 0;
}

/*
TC :- approx O(N**2) ----> As, second for loop runs for less 
SC :- O(N)----> In worst case if all elements inside nums are leader like [5,6,7,8,9] so ans will be of same size as that of nums 
*/