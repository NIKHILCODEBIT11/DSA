/*
Suppose given array is nums = [2,2,3,3,1,2,2]
Here, i have to find majority element i.e, element which occurs more than n/2 times
EX :-
For odd size array like 7 :- element should occur more than (7/2) = more than 3 times
For even size array like 8 :- element should occur more than (8/2) = more than 4 times

I will traverse whole array using i from 0 -> n
and also use j traversing from 0 -> n
and will update counter and if at end of traversal of j if cout > n/2 then return the number
*/
#include<bits/stdc++.h>
using namespace std;

int majority_element_1(vector <int> &nums){
    int n = nums.size();
    for(int i = 0;i < n;i++){
        int counter = 0;
        for(int j = 0;j < n;j++){
            if(nums[j] == nums[i]){
                counter++;
            }
        }
        if(counter > n/2){
            return nums[i];
        }
    }
    return -1;
}

int main(){
    vector <int> nums = {2,2,3,3,1,2,2};
    cout<<"The majority element is "<<majority_element_1(nums);
    return 0;
}

/*
TC :- O(n**2)
SC :- O(1)
*/