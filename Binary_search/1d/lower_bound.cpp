#include<bits/stdc++.h>
using namespace std;

int search(vector <int>& nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();

    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ans=mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }

        /*
        
        I can also write this only

        else{               
            low=mid+1;
        }

        */
    }
    return ans;
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    int res=search(nums,n);
    if(res==nums.size()){
        cout<<"Target value not present";
    }
    else{
        cout<<"The lower bound is "<<res;
    }
    return 0;
}