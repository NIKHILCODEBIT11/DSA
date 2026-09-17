/*
In finding maximum subarray sum i am gona use -----> kadane's algorithm
subarray means CONTIGIOUS PART OF ARRAY , it can also be a single element

In bruteforce :-
set maximum as INT_MIN
suppose nums = [-2,-3,4,-1,-2,1,5,-3]
Here, i will traverse whole array :- i : 0 -> n
and j : i -> n
then i will find sum of each subarray from i -> j and will find 
maximum among sum and maximum
*/

#include<bits/stdc++.h>
using namespace std;

int maximum_subarray_sum(vector <int> &nums){
    int maximum = INT_MIN;
    int n = nums.size();
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            int sum = 0;
            // Finding sum from i -> j subarray
            for(int k = i;k < j;k++){
                sum += nums[k];
            }
            maximum = max(sum, maximum);
        }
    }
    return maximum;
}

int main(){
    vector <int> nums = {-2,-3,4,-1,-2,1,5,-3};
    cout<<"The maximum sum of subarray is "<<maximum_subarray_sum(nums);
    return 0;
}

/*
TC :- Nearly O(N**3) ----> As, three for loops are present one inside another
SC :- O(1) -----> As, no extra space is used
*/