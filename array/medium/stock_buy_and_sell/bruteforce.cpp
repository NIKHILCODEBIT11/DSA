/*
suppose nums = [7,1,5,3,6,4]
It is based on simple rule :-

1. pehle stock KHARIDNA hai uske baad hi BECHNA hai
aur kyuki agar mein nums[0] yaani pehle hi din stock kharidu aur bechu to profit = 0 hogi isliye iteration nums[1] se start karta hu
aur har iteration mein "minimum" aur "profit" update karta rehta hu

DRY RUN :-
nums = [7,1,5,3,6,4]
pehle profit = 0 and minimum = nums[0] = 7

pass 1 :- i = 1
cost = nums[i] - minimum = 1 - 7 = -6
profit = max(profit, cost) = 0
minimum = min(minimum, nums[i]) = 1

pass 2 :- i = 2
cost = nums[i] - minimum = 5 - 1 = 4
profit = max(profit, cost) = 4
minimum = min(minimum, nums[i]) = 1

pass 3 :- i = 3
cost = nums[i] - minimum = 3 - 1 = 2
profit = max(profit, cost) = 4
minimum = min(minimum, nums[i]) = 1

pass 4 :- i = 4
cost = nums[i] - minimum = 6 - 1 = 5
profit = max(profit, cost) = 5
minimum = min(minimum, nums[i]) = 1

pass 5 :- i = 5
cost = nums[i] - minimum = 4 - 1 = 3
profit = max(profit, cost) = 5
minimum = min(minimum, nums[i]) = 1

return profit = 5

*/

#include<bits/stdc++.h>
using namespace std;

int stock_buy_and_sell(vector <int> &nums){
    int n = nums.size();
    int profit = 0;   // Initialize with 0 because i surely don't want negative profits
    int minimum = nums[0];   // This signifies the minimum value at which i will BUY stock

    for(int i = 1;i < n;i++){
        int cost = nums[i] - minimum;
        profit = max(profit, cost);
        minimum = min(minimum, nums[i]);
    }
    return profit;
}

int main(){
    vector <int> nums = {7,1,5,3,6,4};
    cout<<"The maximum profit is "<<stock_buy_and_sell(nums);
    return 0;
}

/*
TC :- O(N) ----> As, traversing whole array from index 1 to n-1
SC :- o(1) ----> As, no extra space is used
*/