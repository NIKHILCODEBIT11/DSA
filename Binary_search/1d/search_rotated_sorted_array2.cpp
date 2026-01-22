#include<bits/stdc++.h>
using namespace std;

bool search_rotated(vector <int>&nums,int target){
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;

        if(nums[mid]==target){
            return true;
        }

        else if(nums[low]==nums[mid] && nums[mid]==nums[high]){
            low++;
            high--;
        }

        else if(nums[low]<=nums[mid]){
            if(nums[low]<=target && target<=nums[mid]){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }

        // Right sorted
        else{           //   can also be written as         else if(nums[mid]>=target && target<=nums[high])
            if(nums[mid]<=target && target<=nums[high]){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
    return false;
}


int main(){
    vector <int> nums={6,7,2,3,3,3,3,4,4,4,4,5,6};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    bool res=search_rotated(nums,n);
    cout<<"The target value of "<<n<<" in rotated array is "<<res;
    return 0;
}