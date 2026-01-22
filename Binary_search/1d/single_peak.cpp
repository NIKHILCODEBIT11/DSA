#include<bits/stdc++.h>
using namespace std;

int single(vector <int>&nums){
    int low=1;
    int high=nums.size()-2;

    if(nums.size()==1){
        return nums[0];
    }
    // Checking for first and last index
    else if(nums[0]>nums[1]){
        return nums[0];
    }
    else if(nums[nums.size()-1]>nums[nums.size()-2]){
        return nums[nums.size()-1];
    }
    else{
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]>nums[mid-1] && nums[mid]>nums[mid+1]){
                return nums[mid];
            }
            else{
                if(nums[mid]<nums[mid+1]){
                    low=mid+1;
                }
                else{
                    high=mid-1;
                }
            }
        }
    }
    return -1;      // This line will never never be executed but just to respect return type of function it is written.
}

int main(){
    vector <int> nums={2,3,4,12,13,7,6,4,3};
    int res=single(nums);
    cout<<"The single peak element is "<<res;
    return 0;
}