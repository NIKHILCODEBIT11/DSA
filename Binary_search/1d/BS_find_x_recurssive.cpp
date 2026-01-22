#include<bits/stdc++.h>
using namespace std;

int search(vector <int>&nums,int low,int high,int target){
    if(low>high){
        return -1;
    }
    int mid=(low+high)/2;
    if(nums[mid]==target){
        return mid;
    }
    else if(nums[mid]<target){
        return search(nums,mid+1,high,target);      // In recurssion i will always have to return something. 
    }
    else{
        return search(nums,low,mid-1,target);       
    }
}

int main(){
    vector <int> nums={2,3,5,6,17,19};
    int n;
    cout<<"Enter target : ";
    cin>>n;
    int res=search(nums,0,nums.size(),n);
    if(res!=-1){
        cout<<"The target is at index "<<res;
    }
    else{
        cout<<"No occurence";
    }
    return 0;
}