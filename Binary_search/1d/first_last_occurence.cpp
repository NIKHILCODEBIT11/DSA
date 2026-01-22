#include<bits/stdc++.h>
using namespace std;
/*

dry run :-

    2 4 5 6 6 6 7 8 8 9 12 17 23

present :-

6

lb=3
ub-1=5

absen :-

10

lb=10
ub-1=9



*/

int lower_(vector <int>& nums,int target){
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
    return ans;
}

int upper_(vector <int> &nums,int target){
    int low=0;
    int high=nums.size()-1;
    int ans=nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>target){
            ans=mid;
            high=mid-1;
        }
        else if(nums[mid]<=target){
            low=mid+1;
        }
    }
    return ans;
}

pair<int,int> first_last(vector <int> &nums,int target){
    int lower=lower_(nums,target);
    int upper=upper_(nums,target);
    if(lower==nums.size() || nums[lower]!=target){
        return {-1,-1};
    }
    else{
        return {lower,upper-1};
    }
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    cout<<"The first occurence of "<<n<<" is "<<res.first<<" and last occurence is "<<res.second;
    return 0;
}


/*

Undefined Behavior (Important Concept) :-

------> If i just write              if(nums[lower]!=target)        instead of      if(lower==nums.size() || nums[lower]!=target)    

Undefined Behavior means:

Program may crash

Program may print random values

Program may seem to work today and fail tomorrow

Compiler is allowed to do anything

*/