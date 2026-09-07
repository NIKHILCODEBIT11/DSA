/*
Suppose an array is given :- nums = [1,1,0,1,1,1,0,1,1]
And, i have to find MAXIMUM CONSECUTIVE ONES
There are 3 times "1" is consecutive with continous size of 2, 3, 2 respectively so i return MAXIMUM one i.e, 3
I will keep two variables counnt and maximum
ITERATING OVERTHE ARRAY :-
COUNT = 0 MAXIMUM = 0
S-1 :- 1 is encountered so COUNT = 1, MAXIMUM = 0, Since, COUNT > MAXIMUM ---> MAXIMUM = COUNT
S-2 :- 1 is encountered so COUNT = 2, MAXIMUM = 1, Since, COUNT > MAXIMUM ---> MAXIMUM = COUNT
S-3 :- 0 is encountered so COUNT = 0, MAXIMUM = 2, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
S-4 :- 1 is encountered so COUNT = 1, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
S-5 :- 1 is encountered so COUNT = 2, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
S-6 :- 1 is encountered so COUNT = 3, Since, COUNT > MAXIMUM ---> MAXIMUM = COUNT
S-7 :- 0 is encountered so COUNT = 0, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
S-8 :- 1 is encountered so COUNT = 1, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
S-9 :- 1 is encountered so COUNT = 2, Since, COUNT <= MAXIMUM ---> MAXIMUM = MAXIMUM ONLY
*/

#include<bits/stdc++.h>
using namespace std;

int maximum_consecutive_ones(vector <int> &nums){
    int n = nums.size();
    int count = 0, maximum = 0;

    // Iterating over the array :-
    for(int i = 0;i < n;i++){
        if(nums[i] == 1){
            count++;
            maximum = max(count, maximum);      // OPTIMAL WAY
        }
        else{
            count = 0;
        }
        // if(count > maximum){      // This part is also correct but taking 3ms to run as seen in leetcode, so instead use i directly select "max" out of count and maximum during array traversal only
        //     maximum = count;
        // }
    }
    return maximum;
}

int main(){
    vector <int> nums = {1,1,0,1,1,1,0,1,1};
    cout<<"The maximum consecutive ones are "<<maximum_consecutive_ones(nums);
    return 0;
}

// TC :- O(N) ----> As, the array nums of size "N" has been traversed only once
// SC :- O(1) ----> As, no extra space is used