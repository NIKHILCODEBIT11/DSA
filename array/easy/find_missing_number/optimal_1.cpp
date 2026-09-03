// This problem has 2 OPTIMAL SOLUTIONS :-
// 1. This one focusses on optimization using sum :-
// suppose i have been given N = 5 that means i have to store numbers from 1 to 5 inside an array nums of size N-1 , nums = [3,4,5,2]
// TRUE SUM = S1 = sum of all N numbers :- In this case :- 1+2+3+4+5 = 15
// ARRAY SUM = S2 = sum of all elements n array :- In this case :- 3+4+5+2 = 14
// To find the missing number :- Since, only 1 number is missing so difference between the sum {s1 - s2} will give that missing number
// For finding TRUE SUM :- First N numbers :- N(N+1)/2

#include<bits/stdc++.h>
using namespace std;

int find_missing_number(vector <int> &nums, int N){
    int n = nums.size();    // In this question it is same to    int n = N-1

    // Finding true sum i.e, S1 i,e. sum of N numbers :-
    int s1 = N*(N+1)/2;

    // Finding array sum i.e, S2 i.e, sum of n-1 numbers stored in array
    int s2 = 0;
    for(int i = 0;i < n; i++){
        s2+=nums[i];
    }

    return s1 - s2;   // Difference netween sums
}

int main(){
    int n = 7;     // Value of n
    vector <int> nums = {1,2,3,5,6,7};      // Array of size n -1 
    cout<<"The missing number is "<<find_missing_number(nums, n);
    return 0;
}

// TC :- O(n) ---> Iteration over array to find array sum
// SC :- O(1) ----> As, no extra space is being used