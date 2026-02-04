#include<bits/stdc++.h>
using namespace std;

double med(vector <int>&nums1,vector <int>&nums2){
    int n1=nums1.size();
    int n2=nums2.size();
    if(n2<n1){
        return med(nums2,nums1);
    }
    int low=0;
    int high=n1;
    int left=(n1+n2+1)/2;
    while(low<=high){
        int mid1=(low+high)/2.0;
        int mid2=left-mid1;
        int l1,l2,r1,r2;
        if(mid1>0){
            l1=nums1[mid1-1];
        }
        else{
            l1=INT_MIN;
        }

        if(mid1<n1){
            r1=nums1[mid1];
        }
        else{
            r1=INT_MAX;
        }

        l2 = (mid2 > 0) ? nums2[mid2 - 1] : INT_MIN;
        r2 = (mid2 < n2) ? nums2[mid2]     : INT_MAX;

        if(l1<=r2 && l2<=r1){
            if((n1+n2)%2==1){
                return max(l1,l2);
            }
            else{
                return (max(l1,l2)+min(r1,r2))/2.0;
            }
        }
        else if (l1 > r2) {
            high = mid1 - 1;
        }
        else {
            low = mid1 + 1;
        }
    }
}

int main() {
    vector<int> a = {2, 3, 4, 6};
    vector<int> b = {3, 4, 7, 9, 22, 23};

    cout << "Median = " << med(a, b);
    return 0;
}