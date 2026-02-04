#include<bits/stdc++.h>
using namespace std;

int upper_bound(vector <int>&nums,int target){
    int low=0;
    int high=nums.size();
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<=target){
            low=mid+1;
        }
        else{
            high=mid-1;
            ans=mid;
        }
    }
    return ans;
}

int blackbox(vector <vector<int>>&nums,int target){
    int count=0;
    for(int i=0;i<nums.size();i++){
        count+=upper_bound(nums[i],target);
    }
    return count;
}

int median(vector <vector<int>> &nums){
    int low=INT_MAX;
    int high=INT_MIN;
    int row=nums.size();
    int column=nums[0].size();
    for(int i=0;i<nums.size();i++){
        low=min(low,nums[i][0]);
        high=max(high,nums[i][column-1]);
    }

    int required=(row*column)/2;
    while(low<=high){
        int mid=(low+high)/2;
        int cnt=blackbox(nums,mid);

        if(cnt <= required){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low;

}

int main() {
    vector<vector<int>> matrix = {
        { 1,  3,  5,  7,  9, 11, 13},
        { 2,  4,  6,  8, 10, 12, 14},
        {15, 17, 19, 21, 23, 25, 27},
        {16, 18, 20, 22, 24, 26, 28}
    };

    cout << "Median is: " << median(matrix) << endl;
    return 0;
}