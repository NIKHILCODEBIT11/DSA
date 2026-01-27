#include<bits/stdc++.h>
using namespace std;

bool canbeplaced(vector <int> &nums,int distance,int total_cows){
    int cow=1,last=nums[0];
    for(int i=1;i<nums.size();i++){
        if(nums[i]-last>=distance){
            cow+=1;
            last=nums[i];
        }
        if(cow==total_cows){
            return true;
        }
    }
    return false;
}

int distance(vector <int>&nums,int total_cows){
    sort(nums.begin(),nums.end());
    int low=1,high=nums[nums.size()-1];
    while(low<=high){
        int mid=low+(high-low)/2;
        if(canbeplaced(nums,mid,total_cows)==true){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return high;
}

int main(){
    vector <int> nums={0,3,7,4,9,10};
    int total_cows=4;
    int min_dist=distance(nums,total_cows);
    cout<<"The maximum value of minimum distance among cows is "<<min_dist;
    return 0;
}