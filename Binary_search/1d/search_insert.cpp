#include<bits/stdc++.h>
using namespace std;

void insert(vector <int> &nums,int index,int target);

void search(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            high=mid-1;
            ans=mid;
        }
        else if(nums[mid]<target){
            low=mid+1;
        }
    }
    insert(nums,ans,target);
}

void insert(vector <int> &nums,int index,int target){
    nums.push_back(0);
    for(int i=nums.size()-1;i>index;i--){
        nums[i]=nums[i-1];
    }
    nums[index]=target;
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    cout<<"Before insertion :-"<<endl;
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<"\t";
    }
    cout<<endl;
    search(nums,n);
    cout<<"After inserting :-"<<endl;
    for(int i=0;i<nums.size();i++){
        cout<<nums[i]<<"\t";
    }
    return 0;
}