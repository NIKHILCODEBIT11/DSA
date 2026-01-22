#include<bits/stdc++.h>
#include<vector>

using namespace std;

int search(vector <int>& nums,int target){
    int n=nums.size();
    int low=0;
    int high=n-1;

    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={2,3,5,6,17,19};
    int n;
    cout<<"Enter target : ";
    cin>>n;
    int res=search(nums,n);
    if(res!=-1){
        cout<<"The target is at index "<<res;
    }
    else{
        cout<<"No occurence";
    }
    return 0;
}