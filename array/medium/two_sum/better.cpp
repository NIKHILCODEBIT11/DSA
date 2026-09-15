/*
Here, i am going to use hashing :-
For a given array nums = [2,6,5,8,11] and target = 14
i will create an empty hashmap whose size i will increase dynamically
I WILL TRAVERSE FROM ARRAY ONLY ONCE
suppose at index  0 :- nums[0] = 2 so to reach target 14 i need 12 i will look for 12 in hashmap and since, it is empty i wont get 12 and will just put (2, 0) inside hashmap where 2 is value and 0 is index
now i am in index 1 :- nums[1] = 6 so to reach target 14 i need 8 i will look for 8 in hashmap and since, it contains only {(2,0)} i wont get 8 and will just put (6, 1) inside hashmap where 6 is value and 1 is index
now i am in index 2 :- nums[2] = 5 so to reach target 14 i need 9 i will look for 9 in hashmap and since, it contains only {(2,0), (6,1)} i wont get 9 and will just put (5, 2) inside hashmap where 5 is value and 2 is index
now i am in index 3 :- nums[3] = 8 so to reach target 14 i need 6 i will look for 6 in hashmap and since, 6 is present in hashmap so it will just return index of both 6 an 8
*/

#include<bits/stdc++.h>
using namespace std;

pair <int, int> two_sum(vector <int> &nums, int target){
    int n = nums.size();
    map <int, int> mpp;      // un-ordered map
    for(int i = 0;i < n;i++){
        if(mpp.find(target - nums[i]) != mpp.end()){
            cout<<"yes\n";
            return {mpp[target - nums[i]], i};
        }
        else{
            mpp[nums[i]] = i;
        }
    }
    cout<<"No\n";
    return {-1, -1};
}

int main(){
    vector <int> nums = {2,6,5,8,11};
    int target = 140;
    pair<int, int> result = two_sum(nums, target);
    if(result.first == -1){
        cout<<"No pair found";
    }
    else{
        cout<<"Indices : ["<<result.first<<", "<<result.second<<"]";
    }
    return 0;
}

/*
for unorder map :-
TC :- O(N) ----> As, a single traversal is done, for worst case O(n**2), as for worst case find() can take upto O(n)
SC :- O(N) ----> As, hasmap is used

for ordered map :-
TC :- O(N*logN) 
*/