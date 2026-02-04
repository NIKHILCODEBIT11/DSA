#include<bits/stdc++.h>
using namespace std;

int max_index(vector<vector<int>> &nums,int n,int mid){     //  n :-  No. of rows
    int max_value=-1;
    int maxindex=-1;
    for(int i=0;i<n;i++){
        if(nums[i][mid]>max_value){
            max_value=nums[i][mid];
            maxindex=i;
        }
    }
    return maxindex;
}

vector <int>findpeak(vector <vector<int>> &nums){
    int n = nums.size();
    int m = nums[0].size();
    int low=0;
    int high=m-1;
    while(low<=high){
        int mid=(low+high)/2;
        int max_row_index=max_index(nums,n,mid);
        int left = mid-1 >= 0 ? nums[max_row_index][mid-1] : -1;
        int right = mid+1<m ? nums[max_row_index][mid+1] : -1;

        if(nums[max_row_index][mid] > left && nums[max_row_index][mid] > right){
            return {max_row_index,mid};
        }
        else if(nums[max_row_index][mid] < left){
            high=mid-1;
        }
        else{
            low=mid+1;
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
    cout<<boolalpha;            // By this only "BOOLEAN"  values will be printed      not      The target value of 33 is present : 1
    vector <int> ans = findpeak(nums);
    cout<<"The position of peak element is ("<<ans[0]<<","<<ans[1]<<")";
    return 0;
}