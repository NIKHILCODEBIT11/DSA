/*
Here, in a given array [1,2,1,3,2,4,4]
i will run 2 for loops where 11st for loop will move from 0 to n
and inside the first for loop i will write another for loop which will run from 0 to n and will keep a track of count
and if at end of 2nd for loop traversaal count is still 1 in that case i will return that num
*/

#include<bits/stdc++.h>
using namespace std;

int appear_once_not_twice(vector <int> &nums){
    int n = nums.size();
    for(int i = 0;i < n;i++){
        int count = 1;
        for(int j = 0;j < n;j++){
            if( i != j && nums[j] == nums[i]){     // As, in this case it will skip the part where j will reach to the number i to avoid false count of already selected i number
                count++;
            }
        }
        if(count == 1){
            return nums[i];
        }
    }
    return -1;    // If all numbers appear exactly twice
}

int main(){
    vector <int> nums = {1,2,1,3,2,4,4};
    cout<<"The number appearing only once is "<<appear_once_not_twice(nums);
    return 0;
}

// TC :- O(n**2)
// SC :- O(1)