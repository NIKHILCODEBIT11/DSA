#include<bits/stdc++.h>
using namespace std;

// BINARY SEARCH :-
/*

Why i followed binary search :-

Surely the possibility of "number of final days" is in different continous parts of "nums" 

                    7       8       9       10        12       13
                   not     not     not     not        yes      yes

Since, i know answer lying in right side is possible and on left side is not possible so i can use binary search

*/


bool possible(vector <int> &nums,int days,int m,int k){
    int no_of_bouquet=0,counter=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<=days){
            counter++;
        }else{
            no_of_bouquet+=counter/k;
            counter=0;
        }
    }
    no_of_bouquet+=counter/k;
    if(no_of_bouquet>=m){
        return true;
    }
    else{
        return false;
    }
}

pair <int,int> min_and_max(vector <int> &nums){
    int min=INT_MAX,max=INT_MIN;
    for(int i=0;i<nums.size();i++){
        if(nums[i]<min){
            min=nums[i];
        }
        if(nums[i]>max){
            max=nums[i];
        }
    }
    return {min,max};
}

int final_days(vector <int> &nums,int m,int k){
    long long val=m*1ll*k*1ll;
    if(nums.size()<val){
        return -1;
    }
    auto min_max=min_and_max(nums);
    int low=min_max.first,high=min_max.second;
    /*
    int maxDay = *max_element(nums.begin(), nums.end());
    if (!possible(nums, maxDay, m, k))
        return -1;

    It is completely useless given by chatgpt

    */

    // The reason of not returning -1 at end of final_days is that as i know, SURELY that answer exists so there is NO CHANCE OF GETTING NO ANSWER, and the only problematic scenariois checked for days<m*k
    while(low<=high){
        int mid=low+(high-low)/2;
        if(possible(nums,mid,m,k)){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;
}

int main(){
    vector <int> nums={7,8,9,10,12,13};
    int m=2,k=3;
    cout<<"The minimum no of days are "<<final_days(nums,m,k);
    return 0;
}