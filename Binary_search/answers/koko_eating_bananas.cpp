#include<bits/stdc++.h>
using namespace std;

int findmax(vector <int> &v){               // Used for calculating maximum/high in function "rate"
    int max_i=INT_MIN;
    for(int i=0;i<v.size();i++){
        max_i=max(max_i,v[i]);
    }
    return max_i;
}

int calculate_total_hour(vector <int> &nums,int hourly){        // Used for calculating total_hour for each pile of banana mentioned with default rate of   "mid"   bananas per hour
    int total_hour=0;
    for(int i=0;i<nums.size();i++){
        total_hour+=ceil((double)nums[i]/(double)hourly);
    }
    return total_hour;
}

int rate(vector <int> &nums,int hour){              // It will check and update low, high and will ultimately give the final "rate"
    int low=1,high=findmax(nums);
    while(low<=high){
        int mid=(low+high)/2;
        int total_hour=calculate_total_hour(nums,mid);
        if(total_hour<=hour){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return low;         // "low" index will be the   MINIMUM   value or "rate"
}



/*

Consider pile as :-     [3,6,7,11]   with h=8

suppose i assume      rate = 3 bananas/hour

so, time= 1 + 2 + 3 + 4 = 10hours   >  8 hours, so reduce    value of "rate"


min start value = 1

max start value = maximum element from the given array of pile i.e,   11

PROOF :-

For rate = 11 :-
time = 1 + 1 + 1 + 1 = 4   WHICH IS THE ANSSWER EVEN IF I TAKE   rate = 12,13,14,15,16 ..........

So, my answer will lie between [1 2 3 4 5 6 7 8 9 10 11]



ceil(4/3)=2  as 4/3=1.333 which with ceil gives 2

            1       2      3       4       5       6       7       8       9       10      11
            no      no     no     yes     yes     yes     yes     yes     yes     yes      yes

1st         low                                   mid                                      high
2nd         low            mid            high
3rd                               low     high
                                 and mid
4th                        high   low   


Reason for using double() in ceil :-

used double because ceil() works on floating-point numbers, not integers.

with integer :-
7 / 3 = 2          // decimal LOST
ceil(2) = 2 ❌

with double :-
ceil(2.333...) = 3

*/


int main(){
    vector <int> nums={3,4,7,9,12};
    int hours;
    cout<<"Enter hours :- ";
    cin>>hours;
    int ans=rate(nums,hours);
    cout<<"The minimum  value is "<<ans;
    return 0;
}