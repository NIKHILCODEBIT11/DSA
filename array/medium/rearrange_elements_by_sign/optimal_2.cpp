/*

optimal_1 mein bas ek extra vector "ans" define kiya aur return kiya isliye SC o(1) HO GAYI
optimal_2 mein 
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
    nums = move(ans);
    return nums;      // deep copy ki jagah ownership transfer (move semantics) karta hai.

    /*
    Normally, jab aap nums = result; likhte hain, toh C++ result ke har ek element ko ek-ek karke copy karke nums mein daalta hai (\mathcal{O}(n) time).
    Jab aap std::move(result) use karte hain:
    1. Internal Pointer Swap: C++ naya data copy nahi karta. result ka heap memory pointer seedha nums ko de diya jaata hai.
    2. Instant (O(1) time): Chahe array mein 6 elements hon ya 10 lakh, yeh operation fractions of a nanosecond mein ho jaata hai.
    3. result khali ho jaata hai: Iske baad result vector ek valid lekin empty/unspecified state mein chala jaata hai, kyunki uska saara data nums ke paas chala gaya.

    nums = result;        -> 🐢 Copy har element ko: O(N) time
    nums = move(result);  -> ⚡ Sirf pointer swap:   O(1) time
    */
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
Time Complexity (TC): O(N)
    1. for loop 0 se n-1 tak chalta hai: O(N).
    2. nums = move(ans); ek constant time operation hai: O(1) (sirf internal memory pointers swap hote hain).
    3. Overall TC = O(N) + O(1) = O(N).
Space Complexity (SC): O(N)
    1. std::move() runtime par data copy hone se bachata hai, lekin extra space ki allocation ko nahi rokta.
    2. Function ke andar vector<int> ans(n); declare karke heap memory par N integers ki extra memory allocate ki gayi hai.
    3. Auxiliary Space tabhi O(1) maani jaati hai jab bina kisi naye dynamic container/vector ke array ko in-place modify kiya jaye (sirf aadh variables use karke). Kyunki N size ka buffer create hua hai, isliye Space Complexity O(N) hi rahegi.
*/