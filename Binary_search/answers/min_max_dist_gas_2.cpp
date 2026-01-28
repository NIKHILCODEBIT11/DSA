#include<bits/stdc++.h>
using namespace std;

long double min_max(vector <int> &nums,int k){
    vector <int> how_many(nums.size()-1,0);
    priority_queue <pair<long double,int>> pq;
    for(int i=0;i<nums.size()-1;i++){
        pq.push({(nums[i+1]-nums[i]),i});
    }

    for(int gas=1;gas<=k;gas++){
        auto pt=pq.top();
        pq.pop();
        auto sec_ind=pt.second;
        how_many[sec_ind]++;
        long double indiff=nums[sec_ind+1]-nums[sec_ind];
        long double sec_len=indiff/(long double)(how_many[sec_ind]+1);
        pq.push({sec_len,sec_ind});
    }
    return pq.top().first;
}

int main(){
    vector <int> nums={2,4,6,7,9,13};
    int k=6;
    cout<<"The maximum distance is "<<min_max(nums,k);
    return 0;
}