#include<bits/stdc++.h>
using namespace std;

//      Similar concept like of finding "MINIMUM" and simply returning the index of that "MINIMUM"

int times(vector <int> &nums){
    int low=0,high=nums.size()-1,mn=INT_MAX;
    int index=-1;

    while(low<=high){
        int mid=(low+high)/2;

        // One condition :-     If array is already sorted writing below line because then this code can be used even though rotation is done or not.
        if(nums[low]<=nums[high]){
            if(mn>nums[low]){
                mn=nums[low];
                index=low;
            }
            break;
        }
        
        // left-rotated
        if(nums[low]<=nums[mid]){
            if(mn>nums[low]){
                mn=nums[low];
                index=low;
            }
            low=mid+1;
        }

        // Right-sorted
        else{
            if(nums[mid]<=nums[high]){
                mn=min(mn,nums[mid]);
                index=mid;
            }
            high=mid-1;
        }
    }
    return index;
}


int main(){
    vector <int> nums={6,7,2,3,4,5};
    int res=times(nums);
    cout<<"The number of times array is rotated is "<<res;
    return 0;
}