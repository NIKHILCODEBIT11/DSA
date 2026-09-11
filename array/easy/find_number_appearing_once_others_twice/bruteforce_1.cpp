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
        // int count = 1;          If i write this then everytime atleast once nums[i] matches to nums[j] as i am traversing from start to end even in j, so count = 1 will be true for evey case 
        int count = 0;
        for(int j = 0;j < n;j++){
            if(nums[j] == nums[i]){
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