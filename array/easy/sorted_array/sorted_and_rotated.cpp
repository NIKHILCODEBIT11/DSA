/*
The Question LeetCode is asking you:
"If I give you a random list of numbers, could it have been created by taking a sorted staircase and rotating it?"

Example 1: [3, 4, 5, 1, 2]
3 to 4: Going UP
4 to 5: Going UP
5 to 1: DROP DOWN #1
1 to 2: Going UP
(Check last to first) 2 to 3: Going UP

If it drops 0 times ----> It's already sorted (e.g., [1, 2, 3]). VALID!
If it drops 1 time ----> It was sorted, then rotated (e.g., [3, 4, 5, 1, 2]). VALID!
If it drops 2 or more times ----> It's completely scrambled (e.g., [2, 1, 4, 3]). INVALID!
*/

#include<bits/stdc++.h>
using namespace std;

bool check(vector<int>& nums) {
    int count = 0;
    for(int i = 1; i < nums.size(); i++){
        if(nums[i] < nums[i-1]){
                count++;
        }
    }

    // This is for last element to first element BOUNDARY CHECK
    if(nums[nums.size()-1] > nums[0]){
        count++;
    }
    return count <= 1;
}

int main(){
    vector <int> arr={1,2,3,41,4,55,65,66};
    cout<<"The array is sorted and rotated : "<<std::boolalpha<<check(arr);
    return 0;
}

// Time complexity :- O(N)