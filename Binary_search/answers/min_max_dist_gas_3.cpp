#include<bits/stdc++.h>
using namespace std;

int number_of_gas_required(vector <int>&nums,int distance){
    int gases=0;
    for(int i=0;i<nums.size()-1;i++){
        int number_in_bet=(nums[i+1]-nums[i])/distance;
        if(number_in_bet*distance==(nums[i+1]-nums[i])/distance){                   //       chatgpt :-   gases += ceil(gap / dist) - 1;
            number_in_bet--;
        }
        gases+=number_in_bet;
    }
    return gases;
}

long double min_max(vector <int>&nums,int k){
    long double low=0,high=0;
    for(int i=0;i<nums.size();i++){
        high=max(high,(long double)(nums[i+1]-nums[i]));
    }
    while(high-low>1e-6){
        long double mid=(low+high)/2.0;
        int cnt=number_of_gas_required(nums,mid);
        if(cnt>k){
            low=mid;
        }
        else{
            high=mid;
        }
    }
    return high;
}

int main(){
    vector <int> nums={2,4,6,7,9,13};
    int k=6;
    cout<<"The maximum distance is "<<min_max(nums,k);
    return 0;
}