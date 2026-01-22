#include<bits/stdc++.h>
using namespace std;

int first_(vector<int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int first=-1,last=-1;              //      int first,last=-1;     Writing like this is wrong         
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            high=mid-1;
            first=mid;
        }
        else{
            high=mid-1;
        }
    }
    return first;
}

int last_(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int last=-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            low=mid+1;
        }
        else if(nums[mid]==target){
            last=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return last;
}

pair <int,int> first_last(vector <int>&nums,int target){
    int first=first_(nums,target);
    if(first==-1){
        return {-1,-1};
    }
    int last=last_(nums,target);
    return {first,last};
}

int count_(vector<int> &nums,int target){
    pair <int,int> res=first_last(nums,target);
    if(res.first==-1){
        return 0;
    }
    else{
        return res.second-res.first+1;          //      Count       =       (last-first+1)
    }
}
int main(){
    vector <int> nums={2,3,4,6,17,17,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    int count=count_(nums,n);
    cout<<"The total number of occurences of "<<n<<" is "<<count;
    return 0;
}