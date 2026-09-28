#include<bits/stdc++.h>
using namespace std;

int times(vector <int>&nums){
    int low=0;
    int high=nums.size()-1;
    int mn=INT_MAX;
    int index=-1;

    while(low<=high){
        int mid=(low+high)/2;

        if(nums[low]==nums[mid] && nums[mid]==nums[high]){
            low++;
            high--;
            continue;       // Because on chaning low and high also mid changes.
        }

        // Left-rotated
        if(nums[low]<=nums[mid]){
            if(mn>nums[low]){
                mn=nums[low];
                index=low;
            }
            low=mid+1;
        }

        // Right-rotated
        if(nums[mid]<=nums[high]){
            if(mn>nums[mid]){
                mn=nums[mid];
                index=mid;
            }
            high=mid-1;
        }
    }
    return index;
}

int main(){
    vector <int> nums={6,7,7,7,7,2,2,2,3,3,4,5};
    int res=times(nums);
    cout<<"The number of times array is rotated is "<<res;
    return 0;
}