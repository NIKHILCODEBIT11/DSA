#include<bits/stdc++.h>
using namespace std;

// BETTER SOLUTION
int binary(vector <int>&nums,int target){
    int low=0;
    int high=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target){
            return mid;
        }
        else if(nums[mid]<=target){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}

pair <int,int> search_2d(vector <vector<int>> &nums,int target){
    int row=nums.size();
    int column=nums[0].size();
    int ind=-1;
    for(int i=0;i<row;i++){
        int ind=binary(nums[i],target);
        if(ind!=-1){
            return {i,ind};
        }
    }
    return {-1,-1};
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=34;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    pair <int,int> ans = search_2d(nums,target);
    cout<<"The position of target is ("<<ans.first<<","<<ans.second<<")";
    return 0;
}