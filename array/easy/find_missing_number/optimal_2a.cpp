/*
This problem has 2 OPTIMAL SOLUTIONS :-
2. This one focusses on optimization using XOR :-
I will be learning XOR in detail in BITWISE operatores but for now :-

A. XOR of ANY 2 SAME numbers is 0 :-
EX - 3^3 = 0 , 2^2^4^4 = (2^2)^(4^4) = 0^0 = 0 , 2^3^4^3^2^4 = (2^2)^(3^3)^(4^4) = (0^0)^0 = 0^0 = 0

B. XOR of ANY NUMBER WITH 0 is the NUMBER itself :-
EX - 3^0 = 3 , 2^2^4^4^5 = (2^2)^(4^4)^5 = 0^0^5 = 0^5 = 5

Considering the problem :- 
suppose i have been given N = 5 that means i have to store numbers from 1 to 5 inside an array nums of size N-1 , nums = [3,4,5,2]
XOR1 = XOR of all first N natural numbers
XOR2 = XOR of all N-1 numbers present in array

XOR1 = 1^2^3^4^5
XOR2 = 3^4^5^2

When i do XOR1^XOR2 = (1^2^3^4^5)^(3^4^5^2) = 1^(2^2)^(3^3)^(4^4)^(5^5) = 1^(0)^(0)^(0)^(0) = 1^0^0 = 1^0 = 1
And 1 is missing

*/

#include<bits/stdc++.h>
using namespace std;

int find_missing_number(vector <int> &nums, int N){
    int n = nums.size();
    int XOR1 = 0, XOR2 = 0;

    // Finding XOR1 i.e, XOR of all N natural numbers :-
    for(int i = 1;i < N+1; i++){
        XOR1 = XOR1 ^ i;
    }

    // Finding XOR2 i.e, XOR of all elements present in array
    for(int i = 0;i < n;i++){
        XOR2 = XOR2 ^ nums[i];
    }

    return XOR1 ^ XOR2;
}

int main(){
    int n = 7;     // Value of n
    vector <int> nums = {1,2,3,5,6,7};      // Array of size n -1 
    cout<<"The missing number is "<<find_missing_number(nums, n);
    return 0;
}

// TC :- O(n) + O(n) = O(2*n) ---> for 2 for loops
// SC :- O(1) ----> As, no extra space is being used

// Here in optimal_2a the TC is increased but SC is same so in optimal_2b i am gonna optimize TC