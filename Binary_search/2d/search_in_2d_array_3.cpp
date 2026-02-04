#include<bits/stdc++.h>
using namespace std;

bool search_2d(vector <vector<int>> &nums,int target){
    int low=0;
    int m=nums.size();
    int n=nums[0].size();
    int high=m*n-1;
    while(low<=high){
        int mid=(low+high)/2;
        int row=mid/m;
        int column=mid%n;
        if(nums[row][column]==target){
            return true;
        }
        else if(nums[row][column]<=target){
            low=mid+1;
        }
        else{
            high=mid-1;
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