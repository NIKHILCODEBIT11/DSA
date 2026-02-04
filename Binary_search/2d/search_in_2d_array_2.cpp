#include<bits/stdc++.h>
using namespace std;

// I am given a sorted array and have to search a target and if it is present return true or else return false

// BINARYSEARCH :-

bool search_2d(vector <vector<int>> &nums,int target){
    int row=nums.size();
    int column=nums[0].size();
    for(int i=0;i<row;i++){
        if(nums[i][0] <= target && target <= nums[i][column-1]){
            int low=0;
            int high=column-1;
                while(low<=high){
                    int mid=(low+high)/2;
                    if(nums[i][mid]==target){
                        return true;
                    }
                    if(nums[i][mid] < target){
                        low=mid+1;
                    }
                    else{
                        high=mid-1;
                    }
                }
                
            }
        }
    return false;
}

int main(){
    vector<vector<int>> nums={
        {2,4,6,7,9},
        {21,23,25,26,27},
        {29,32,33,34,36},
        {37,39,40,42,26}
    };
    int target=35;
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    cout<<"The target value of "<<target<<" is present : "<<search_2d(nums,target);
    return 0;
}