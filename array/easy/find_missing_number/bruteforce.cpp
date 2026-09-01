// Here, i will be given a value 'n' and also 'n-1' numbers in an array and that array will be containing numbers from 1 to n-1 i have to find the number which is not present in array which will be EXACTLY A SINGLE NUMBER AS THERE IS NO REPEATITION
// Ex :- n = 7 and given array :- [1,2,3,4,5,6] -----> Here, 7 is missing

// I am going to keep a variable flag initialized to 0 for each i varying from 1 to n and if 
// that i is found in nums then it will be switched to 1 otherwise it will be 0 and at end of 
// 2nd for loop if there is still any flag with value 0 after the whole iteration of 2nd for loop 
// that means that i is missing

#include<bits/stdc++.h>
using namespace std;

int find_missing_number(vector <int> &nums, int n){
    int n1 = nums.size();

    for(int i = 1; i <= n; i++){
        int flag = 0;
        for(int j = 0; j < n1; j++){
            if(nums[j] == i){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            return i;
        }
    }
}

int main(){
    int n = 7;     // Value of n
    vector <int> nums = {1,2,3,5,6,7};      // Array of size n -1 
    cout<<"The missing number is "<<find_missing_number(nums, n);
    return 0;
}

/*
Explaination :-

Considering n = 7 and nums = [1,2,3,5,6,7]

Step - 1 :-
i = 1 and flag = 0
nums[0] = i so flag = 1 ----> BREAK

Step - 2 :-
i = 2 and flag = 0
nums[0] != i
nums[1] == i so flag = 1 ----> BREAK

Step - 3 :-
i = 3 and flag = 0
nums[0] != 3
nums[1] != 3
nums[2] == i so flag = 1 -----> BREAK

Step - 4 :-
i = 4 and flag = 0
nums[0] != i
nums[1] != i
nums[2] != i
nums[3] != i
nums[4] != i
nums[5] != i
so flag is still 0 even after completely iterating over nums with j
As, flag = 0 ----> return i i.e, return 4
*/

// TC :- O(N**2) ----> As, it contains 2 loops of each size N so in worst case it takes O(N**2)
// SC :- O(1) 