#include<bits/stdc++.h>
using namespace std;

bool canbeplaced(vector <int> &nums,int distance,int total_cows){
    int cow=1,last=nums[0];
    for(int i=1;i<nums.size();i++){
        if(nums[i]-last>=distance){
            cow+=1;
            last=nums[i];
        }
        if(cow==total_cows){
            return true;
        }
    }
    return false;
}

int min_distance(vector <int> &nums,int total_cows){
    sort(nums.begin(),nums.end());
    for(int i=1;i<=nums[nums.size()-1]-nums[0];i++){
        if(canbeplaced(nums,i,total_cows)==true){
            continue;
        }
        else{
            return i-1;
        }
    }
    return -1;
}

int main(){
    vector <int> nums={0,3,7,4,9,10};
    int total_cows=4;
    int min_dist=min_distance(nums,total_cows);
    cout<<"The maximum value of minimum distance among cows is "<<min_dist;
    return 0;
}