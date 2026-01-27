#include<bits/stdc++.h>
using namespace std;

int missing(vector <int>&nums,int k){           //  {2  3     7   12}         k=5
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        int missing=nums[mid]-(mid+1);
        if(missing<k){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return low+k;           //      low + k = high + 1 + k
}

int main(){
    vector <int> nums={2,3,6,7,9,12,14};
    int n;
    cout<<"Enter missing value to be found :- ";
    cin>>n;
    cout<<"The "<<n<<"th missing number is "<<missing(nums,n);
    return 0;
}


/*

Derivation for returning            low + k

index :-        0       1       2       3       4
nums :-         2       3       4       7       12
missing :-      1       1       1       3       7

1st            low              mid            high
2nd                                    low     high
                                       mid
3rd                                            high
                                               low
                                               mid
4th                                    high    low                          here    high = low - 1
                                               mid


For finding the answer i firstly will need range of indexes where the required missing value is present
---------->   "low" started from lowest missing value and reached to that index range which has max missing value
---------->   "High" started from highest missing value and reached to that index range which has minimum missing value

consider arr[high]=7 with 3 missing values, 
so i can say            answer = arr[high] + more
as, i know answer is 9 so theoretically more should be 2

calculation of more :-

arr[high] = 7           missing = 3         more=2

as,         missing = arr[high] - (high + 1)

surely,         more = k - missing
------>   answer = arr[high] + k - (arr[high] - (high + 1))
------->      answer = high + 1 + k
------->      answer = low + k


########## Reason of derivation instead of directly returning "high" :-

consider  array         arr = [4 , 7 , 8]       and    k = 3
by looking i can confirm     ans = 3

and by calculating by binary search i would need range of indexes :-    low = index 0 (value = 4) but high is out of index as at left of 4 array ends
that's why new formula required.
*/