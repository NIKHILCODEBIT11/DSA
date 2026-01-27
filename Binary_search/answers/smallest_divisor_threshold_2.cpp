#include<bits/stdc++.h>
using namespace std;

// BINARY SEARCH
int sum_bd(vector <int>&nums,int d){
    int sum=0;
    for(int i=0;i<nums.size();i++){
        sum+=ceil((double)nums[i]/(double)d);
    }
    return sum;
}

int smallest_divisor(vector <int>&nums,int threshold){
    int low=1,high=*max_element(nums.begin(),nums.end());

    int min_sum=sum_bd(nums,high);          // If the "MINIMUM SUM" possible due to max element of "nums" is greater than threshold then there will be no "smallest divisor" and so return -1
    if(min_sum  > threshold){
        return -1;
    }
    
    while(low<=high){
        int sum=0;
        int mid=low+(high-low)/2;
        if(sum_bd(nums,mid)<=threshold){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;
}

int main(){
    vector <int>nums={1,2,6,9};
    int threshold=7;
    cout<<"The smallest divisor is "<<smallest_divisor(nums,threshold);
    return 0;
}

/*

I am using Binary search for optimal answer because :-

(1) The answer lies in a continous side from which "minimum" is to be found

                    1       2       3       4       5       6       7       8       9
start   1st        low                              mid                            high'
        2nd        low     mid             high
        3rd                         low    high
                                    mid
final   4th                 high    low

HENCE,     "low"        points to the       "MINIMUM"       index and so i can return it


############################ VERY VERY IMPORTANT OBSERVATION :-

                "LOW"    and     "HIGH"     switch the    "polarity"     that means :-

                ----> "low" started with polarity of "NOT POSSIBLE"
                ----> "high" started with polarity of "POSSIBLE"

                ----> After all iterations :-
                ----> "low" switches polarity and reaches to the "POSSIBLE" (AND THAT TOO TO THE "MINIMUM" DIVISOR POLARITY)
                ----> "high" switches polarity and reaches to the "NOT POSSIBLE" 
*/