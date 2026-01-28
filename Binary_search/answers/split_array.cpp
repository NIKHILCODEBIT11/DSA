#include<bits/stdc++.h>
using namespace std;


int count_partition(vector <int> &nums,int k,int i){
    int sub_arr_sum=0;int partition=1;
    for(int j=0;j<nums.size();j++){
        if(sub_arr_sum+nums[j]>i){
            partition++;
            sub_arr_sum=nums[j];
        }
        else{
            sub_arr_sum+=nums[j];
        }
    }
    return partition;
}

int largestSubarraySumMinimized(vector<int> &nums, int k){
    if(nums.size()<k){
        return -1;
    }
    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    for(int i=low;i<=high;i++){
        int partition=count_partition(nums,k,i);
        if(partition<=k){
            return i;
        }
    }
    return -1;
}


int main() {
    vector<int> a = {10, 20, 30, 40};
    int k = 2;
    cout << "The minimum of largest sum is "<<largestSubarraySumMinimized(a, k);
    return 0;
}
