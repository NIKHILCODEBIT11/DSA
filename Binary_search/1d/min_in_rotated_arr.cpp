#include<bits/stdc++.h>
using namespace std;

int rotated_min(vector <int>&nums){
    int low=0,high=nums.size()-1,mn=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        
        // Left-sorted
        if(nums[low]<=nums[mid]){
            if(mn>nums[low]){
                mn=nums[low];
            }
            low=mid+1;
        }

        // Right-sorted
        else{
            if(nums[low]<mn){
                mn=min(mn,nums[mid]);           // min() is a function
            }
            high=mid-1;
        }
    }
    return mn;
}

int main(){
    vector <int> nums={6,7,2,3,4,5};
    int res=rotated_min(nums);
    cout<<"The minimum in rotated array is "<<res;
    return 0;
}