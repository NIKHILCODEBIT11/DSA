#include<bits/stdc++.h>
using namespace std;

int missing(vector <int>&nums,int k){               //  {2  3     7   12}         k=5
    for(int i=0;i<nums.size();i++){
        if(nums[i]<=k){
            k++;
        }
        else{
            break;
        }
    }
    return k;
}

//      TIME COMPLEXITY :-   O(N)
//      SPACE COMPLEXITY :-  O(1)

int main(){
    vector <int> nums={2,3,6,7,9,12,14};
    int n;
    cout<<"Enter missing value to be found :- ";
    cin>>n;
    cout<<"The "<<n<<"th missing number is "<<missing(nums,n);
    return 0;
}