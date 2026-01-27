#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE :-        [7 7 7 7 13 11 12 7]    M(NO. OF BOUQUETS) = 2   K(ADJ FLOWERS REQ) = 3

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
    auto min_max=min_and_max(nums);
    if(nums.size()<m*k){
        return -1;
    }
    for(int i=min_max.first;i<=min_max.second;i++){
        if(possible(nums,i,m,k)==true){
            return i;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={7,7,7,7,13,11,12,7};
    int m=2,k=3;
    cout<<"The minimum no of days are "<<final_days(nums,m,k);
    return 0;
}