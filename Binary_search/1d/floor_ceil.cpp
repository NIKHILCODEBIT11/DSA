#include<bits/stdc++.h>
using namespace std;

int floor_(vector <int> &nums,int target){          // Largest number is array <= target
    int low=0;
    int high=nums.size()-1;
    int floor=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<=target){
            low=mid+1;
            floor=nums[mid];
        }
        else{
            high=mid-1;
        }
    }
    return floor;
}

int ceil_(vector <int> &nums,int target){           // Smallest number in array >= target
    int low=0;
    int high=nums.size()-1;
    int ceil=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ceil=nums[mid];
        }
        else{
            low=mid+1;
        }
    }
    return ceil;
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int floor=floor_(nums,n);
    int ceil=ceil_(nums,n);
    cout<<"The floor value is "<<floor<<" and ceil value is "<<ceil;
    return 0;
}