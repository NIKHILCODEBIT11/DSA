/*
Suppose given array is nums = [2,2,3,3,1,2,2]
Here, i am going to use hashing
where "key" will be the element from array nums and "value" will be number of occurences

I will traverse whole array and make hashmap and since, hashmap is draw in ascending order based 
on "key" so i will return the "key" from hashmap with highest "value"
*/

#include<bits/stdc++.h>
using namespace std;

int majority_element_1(vector <int> &nums){
    int n  = nums.size();
    map <int, int> mpp;
    for(int i = 0;i < n;i++){
        mpp[nums[i]]++;
    }
    for(auto it : mpp){
        if(it.second > n/2){
            return it.first;
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
TC :- O(N*logN) + O(N) ----> For ordered map
SC :- O(N) ----> As, if all elements are unique then hashmap will takh "N" space
*/