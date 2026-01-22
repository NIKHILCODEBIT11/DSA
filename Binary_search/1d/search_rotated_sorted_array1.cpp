#include<bits/stdc++.h>
using namespace std;

int search_rotated(vector <int> &nums,int target){
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;

        if(nums[mid]==target){
            return mid;
        }
        // Left sorted :-
        if(nums[low]<nums[mid]){
            if(nums[low]<=target && nums[mid]>=target){
                high=mid-1;

            }
            else{
                low=mid+1;
            }
        }

        // Right sorted
        else{               //      same as         if(nums[high]>nums[mid])
            if(nums[mid]<=target && target<=nums[high]){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
    return -1;
}

int main(){
    vector <int> nums={6,7,2,3,4,5};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int res=search_rotated(nums,n);
    cout<<"The index of "<<n<<" in rotated array is "<<res;
    return 0;
}