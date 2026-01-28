#include<bits/stdc++.h>
using namespace std;


// Brute force :-
long double min_max(vector <int>&nums,int k){
    vector <int> how_many(nums.size()-1,0);
    for(int gas_station=1;gas_station<=k;gas_station++){
        long double max_distance=-1;
        int max_index=-1;
        for(int i=0;i<nums.size()-1;i++){
            long double diff=nums[i+1]-nums[i];
            long double section_length=diff/(how_many[i]+1);
            if(section_length>max_distance){
                max_distance=section_length;
                max_index=i;
            }
        }
        how_many[max_index]++;
    }
    long double max_ans=-1;
    for(int i=0;i<nums.size()-1;i++){
        long double diff=nums[i+1]-nums[i];
        long double section_length=diff/(how_many[i]+1);
        max_ans=max(max_ans,section_length);
    }
    return max_ans;
}

int main(){
    vector <int> nums={2,4,6,7,9,13};
    int k=6;
    cout<<"The maximum distance is "<<min_max(nums,k);
    return 0;
}