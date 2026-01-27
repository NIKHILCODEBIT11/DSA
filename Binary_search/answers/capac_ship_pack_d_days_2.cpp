#include<bits/stdc++.h>
using namespace std;

int days_required(vector <int> &wts,int capacity){      // 1    2   3   4   5   6   7   8   9   10      days=5
    int load=0,days=1;
    for(int i=0;i<wts.size();i++){
        if(load+wts[i]>capacity){
            days+=1;
            load=wts[i];
        }
        else{
            load+=wts[i];
        }
    }
    return days;
}

int final_capacity(vector<int> &nums,int threshold_days){
    int low=*max_element(nums.begin(),nums.end());
    int high=accumulate(nums.begin(),nums.end(),0);
    while(low<=high){
        int mid=low+(high-low)/2;
        if(days_required(nums,mid)<=threshold_days){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;
}

int main(){
    vector <int> wts={1,2,3,4,5,6,7,8,9,10};
    int threshold_days=5;
    int capacity=final_capacity(wts,threshold_days);
    cout<<"The minimum capacity of ship is "<<capacity;
    return 0;
}