/*

here, i am given an array nums = [2,6,5,8,11] and also a target = 14
i have to find any 2 indexes whose value add up to give target
in simplest approach :-
Take variable i iterating from 0->n and also take a variable j iterating from i->n
then check if adding nums[i]+nums[j] gives sum if yes return indexes or else retirn -1
*/

#include<bits/stdc++.h>
using namespace std;

vector <int> two_sum(vector <int> &nums, int target){
    int n = nums.size();
    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            if(nums[i] + nums[j] == target){
                cout<<"Yes target sum exists"<<endl;
                return {i, j};
            }
        }
    }
    cout<<"No";
    return {-1, -1};
}

int main(){
    vector <int> nums = {2,6,5,8,11};
    int target = 14;
    vector<int> result = two_sum(nums, target);
    cout<<"Indices : ["<<result[0]<<", "<<result[1]<<"]";
    return 0;
}

/*
TC :- O(n**2) ----> as, two for loops are present and that one is inside another
SC :- O(1) -----> As, no extra space is required
*/