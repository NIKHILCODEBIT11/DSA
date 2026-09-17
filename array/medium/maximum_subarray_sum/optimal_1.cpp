/*
Kadane's Algorithm ka seedha sa ek golden rule hai:
"Agar pichla sum negative ban gaya hai, toh us bojh ko aage mat dho-o. Use yahin chhod do aur 
nayi shuruat karo."

Negative sum aane wale numbers ki value ko hamesha kam hi karega, kabhi badhayega nahi. Isi simple 
thought par pura Kadane's algorithm chalta hai.

Kadane's Algorithm Step-by-Step
Array: [-2, -3, 4, -1, -2, 1, 5, -3]
Hum bas do variables maintain karte hain:
sum: Current subarray ka running total.
max_so_far: Ab tak ka sabse bada sum jo humne dekha (initialise with INT_MIN).

Index       Element     sum += x        max_so_far = max(max_so_far, sum)       if (sum < 0) sum = 0;       Kyun hua?
0             -2           -2               max(-inf, -2) = -2                      sum = 0         Negative ho gaya, drop kar do
1             -3           -3               max(-2, -3) = -2                        sum = 0         Phir negative, drop kar do
2              4            4               max(-2, 4) = 4                          sum = 4         Positive hai, aage le jao
3             -1            3               max(4, 3) = 4                           sum = 3         Abhi bhi positive bacha hai (3), sath rakho
4             -2            1               max(4, 1) = 4                           sum = 1         Abhi bhi positive bacha hai (1)
5              1            2               max(4, 2) = 4                           sum = 2         Chalo aage
6              5            7               max(4, 7) = 7                           sum = 7         Peak mil gaya!
7             -3            4               max(7, 4) = 7                           sum = 4         Array khatam

*/

#include<bits/stdc++.h>
using namespace std;

int maximum_subarray_sum(vector <int> &nums){
    int n = nums.size();
    int maximum = INT_MIN;
    int sum = 0;

    for(int x : nums){
        sum += x;

        // 1. Check karo kya ab tak ka sabse bada sum mila
        maximum = max(sum, maximum);

        // 2. Agar current_sum negative ho gaya, to naye sire se shuru karo
        if(sum < 0){
            sum = 0;
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
TC :- O(N) ----> As. traversal of array is done only once
SC :- O(1) ----> As, no extra space is used
*/