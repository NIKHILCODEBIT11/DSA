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

This time i am going to run a single for loop unlike in optimal_2a

EX - Suppose N = 5 and nums = [1,5,3,4] with 5 MISSING

This time instead of running separate for loops for firstly calculating XOR1 then XOR2 i am goinh to run a single for loop and will calculate both XOR1 and XOR2

My for loop will run from i = 0 to nums.size() ----> and using XOR2 = XOR2 ^ nums[i] ---> I WILL GET FINAL XOR2
and i will do XOR1 = XOR1 ^ (i+1) ----> 0^1^2^3^4 I will get till here and at last i will left with only XOR1 = XOR ^ 5 Which i will do outisde for loop
The "0" in XOR1 = XOR1 ^ (i+1) ----> 0^1^2^3^4 is the initialized value from start no effect
*/

#include<bits/stdc++.h>
using namespace std;

int find_missing_number(vector <int> &nums, int N){
    int n = nums.size();
    int XOR1 = 0,XOR2 = 0;

    for(int i = 0;i < nums.size();i++){
        XOR2 = XOR2 ^ nums[i];
        XOR1 = XOR1 ^ (i+1);
    }

    // For final end value in calculation of XOR1 :-
    XOR1 = XOR1 ^ N;

    return XOR1 ^ XOR2;
}

int main(){
    int n = 7;     // Value of n
    vector <int> nums = {1,2,3,5,6,7};      // Array of size n -1 
    cout<<"The missing number is "<<find_missing_number(nums, n);
    return 0;
}

// TC :- O(n) ----> As, only a single for loop runs
// SC :- O(1) ----> As, no extra space is being used

// Here in optimal_2b the TC is same to that of in optimal_1 and also SC is same but 
// optimal_2b is more optimal than optimal_1 because in optimal_1 i am using "sum", which has a range for int 
// But in case of optimal_2b i am using XOR which always stays within the bound of the int