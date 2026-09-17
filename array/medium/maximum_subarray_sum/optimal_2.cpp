/*
Optimal_1.cpp mein wo subarray print nahi kar raha tha lekin yaha karna hai :-

Subarray print karne ke liye hume bas start aur end index track karne hote hain.
Logic (2 simple pointers ka game)

1. ans_start & ans_end: Best subarray ka final start aur end index.
2. start: Current chal rahe subarray ki shuruat.
        Jab bhi sum == 0 hota hai (yaani hum nayi shuruat kar rahe hain), temp_start = i set kar do.
        Jab bhi naya maximum milta hai (sum > max_so_far), tab final start = temp_start aur end = i fix kar do.

*/

#include<bits/stdc++.h>
using namespace std;

void maximum_subarray_sum(vector <int> &nums){
    int n = nums.size();
    int sum = 0;
    int maximum = INT_MIN;

    int start;
    int ans_start = -1;
    int ans_end = -1;

    for(int i = 0;i < n;i++){
        if(sum == 0){
            start = i;
        }
        sum += nums[i];

        if(sum > maximum){
            maximum = sum;
            ans_start = start;
            ans_end = i;
        }

        if(sum < 0){
            sum = 0;
        }
    }

    cout<<"The maximum sum of subarray is "<<maximum<<endl;
    cout << "Subarray indices: [" << ans_start << " to " << ans_end << "]\n";
    cout << "Actual Subarray: [ ";
    for (int i = start; i <= ans_end; i++) {
        cout << nums[i] << " ";
    }
    cout << "]\n";
}

int main(){
    vector <int> nums = {-2,-3,4,-1,-2,1,5,-3};
    maximum_subarray_sum(nums);
    return 0;
}

/*
TC :- O(N) ---> As, only a single traversal is done
SC :- O(1) ---> As, no exra space is used
*/