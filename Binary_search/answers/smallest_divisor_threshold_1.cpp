#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE :-
int smallest_divisor(vector <int>&nums,int threshold){
    for(int d=1;d<*max_element(nums.begin(),nums.end());d++){
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=ceil((double)nums[i]/(double)d);
        }
        if(sum<=threshold){
            return d;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={1,2,5,9};
    int threshold=6;
    int divisor=smallest_divisor(nums,threshold);
    cout<<"The smallest divisor is "<<divisor;
    return 0;
}