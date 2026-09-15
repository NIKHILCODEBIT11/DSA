/*
It is not so much better than better approach as it also take TC of O(N*logN) but the only thing that makes
it diff from better is that it uses 2 pointer approach rather than using map
For a given array nums = [2,6,5,8,11] and target = 14
sort array :- [2,5,6,8,11]
i will keep 2 pointers left at start and right at end
then i will check :- 
left{2} + right{11} = 13 < target so to reach target i have to increase left or right ---> move left towards end
left{6} + right{11} = 17 > target so to reach target i have to decrease left or right ---> move right towards start
left{6} + right{8} = 14 = target 
But here i cant return index as iafter sorting i have not stored index so this approach works well only for printing yes or no
for also returning index i will have to use other data structure which will again take extra space complexity and time complexity
*/

#include<bits/stdc++.h>
using namespace std;

string two_sum(vector <int> &nums, int target){
    int n = nums.size();
    int left = 0, right = n-1;
    sort(nums.begin(), nums.end());
    while(left < right){
        int sum = nums[left] + nums[right];
        if(sum == target){
            return "yes";
        }
        else if(sum < target){
            left++;
        }
        else{
            right--;
        }
    }
    return "No";
}

int main(){
    vector <int> nums = {2,6,5,8,11};
    int target = 14;
    string result = two_sum(nums, target);
    cout<<result;
    return 0;
}

/*
TC :- O(N) + O(N*logN) ----> O(N) for worst case traversal of left and right if no element addition matches sum and O(NlogN) for sorting
SC :- O(1) ---> As, i am using no exra space
*/