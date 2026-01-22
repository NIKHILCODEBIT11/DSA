#include<bits/stdc++.h>
using namespace std;

/*
The below function is indeed cirrect for finding first and last occurence but since i am performing binary search than   "SURELY"
it will take total "2*log(N)" each "log(N)"" for each binary search{first and last}, but by writin separate functions for finding
"first" and "last" occurences i can "MAY BE" sace "1*log(n)" time.
*/

/*
pair<int,int> search(vector <int>&nums,int target){
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

    low=0;
    high=nums.size()-1;
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
    return {first,last};
}
*/



/*

By using below separate functions   :-  See conclusion at function          pair <int,int> first_last(vector <int>&nums,int target)

*/
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
    
/*
Here, i   "MAY"     save    "1*log(N)"      as if the target is missing then only in search of  "first"     i will know about it 
and hence, I can avoid the time of finding      "last"      as,if there is no first occurence then surely there won't be
the last occurence.

This simple logical thinking can make the interviewer impress.

*/

    if(first==-1){
        return {-1,-1};
    }
    int last=last_(nums,target);
    return {first,last};
}

int main(){
    vector <int> nums={2,3,4,6,17,19};
    int n;
    cout<<"Enter target value : ";
    cin>>n;
    pair <int,int> res=first_last(nums,n);
    cout<<"The first occurence of "<<n<<" is "<<res.first<<" and the last occurence is "<<res.second;
    return 0;
}