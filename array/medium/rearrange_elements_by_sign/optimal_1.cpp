/*
suppose nums = 3,1,-2,-5,2,-4
maine ek aur vector define kiya named "ans" jiska size bhi N hoga aur mein return mein vector "ans" return karunga
ab yaha pe mein directly array traverse karte waaqt hi elements ko vector "ans" mein dalunga :-
pos = 0 :- kyuki vector "ans" ka start POSITIVE ELEMENT se hi hoga
neg = 1 :- kyuki vector "ans" ka start NEGATIVE ELEMENT se hi hoga

array nums traverse karunga :-
1. positive elment milte hi use "ans" ke pos index mein dalunga aur saath hi pos = pos+2 bhi karunga kyuki positive elements index {0, 2, 4,....} ---> EVEN INDEXES mein hi rahenge
2. Negetive elment milte hi use "ans" ke neg index mein dalunga aur saath hi neg = neg+2 bhi karunga kyuki positive elements index {1, 3, 5,....} ---> ODD INDEXES mein hi rahenge

*/

#include<bits/stdc++.h>
using namespace std;

vector <int> rearrange_elements_by_sign(vector <int> &nums){
    int n = nums.size();
    vector <int> ans(n);
    int pos = 0;
    int neg = 1;
    for(int i = 0;i < n;i++){
        if(nums[i] > 0){
            ans[pos] = nums[i];
            pos = pos + 2;
        }
        else{
            ans[neg] = nums[i];
            neg = neg + 2;
        }
    }
    return ans;
}

int main(){
    vector <int> nums = {3,1,-2,-5,2,-4};
    cout<<"Before rearranging :-"<<endl;
    for(int x : nums){
        cout<<x<<" ";
    }
    cout<<endl;
    vector <int> ans = rearrange_elements_by_sign(nums);
    cout<<"After rearranging :-"<<endl;
    for(int x : ans){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}

/*
TC :- O(N) ----> kyuki ek single for loop hi hai
SC :- O(N) ----> kyuki ek extra vector of size N use kiya ha "ans"
*/