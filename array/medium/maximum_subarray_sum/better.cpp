/*
In finding maximum subarray sum i am gona use -----> kadane's algorithm
subarray means CONTIGIOUS PART OF ARRAY , it can also be a single element

In better :-
set maximum as INT_MIN
suppose nums = [-2,-3,4,-1,-2,1,5,-3]
Here, i will traverse whole array :- i : 0 -> n
and j : i -> n
then i will find sum of each subarray from i -> j and will find 
maximum among sum and maximum

The only diff between bruteforce and better is that i won't be using an extra for loop {iterator 'k'} for finding sum
*/

#include<bits/stdc++.h>
using namespace std;

int maximum_subarray_sum(vector <int> &nums){
    int maximum = INT_MIN;
    int n = nums.size();
    for(int i = 0;i < n;i++){
        int sum = 0;
        for(int j = i;j < n;j++){
            sum += nums[j];
            maximum = max(sum, maximum);
            /*
            This  maximum = max(sum, maximum)  is inside for loop because :-
            Suppose nums = [4, -10, -10];
            When i = 0 with maximum inside j:
            j = 0: sum = 4 ---> maximum = max(INT_MIN, 4) = 4
            j = 1: sum = 4 + (-10) = -6 ---> maximum = max(4, -6) = 4
            j = 2: sum = -6 + (-10) = -16 ---> maximum = max(4, -16) = 4
            Result: 4 (Correct: subarray [4]).

            When i = 0 with maximum outside j:
            The inner loop finishes summing the whole suffix: sum = -16.
            The only check performed is maximum = max(INT_MIN, -16) = -16.
            The intermediate peak of 4 at j = 0 is completely discarded.
            */
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
TC :- Nearly O(N**2) ----> As, now only two for loops are present one inside another
SC :- O(1) -----> As, no extra space is used
*/