#include<bits/stdc++.h>
using namespace std;

int kth(vector <int>&nums1,vector <int>&nums2,int k){
    if(nums1.size()>nums2.size()){
        return kth(nums2,nums1,k);
    }
    int n1=nums1.size();
    int n2=nums2.size();
    int left=k;
    int low=max(0,k-n2);
    int high=min(n1,k);
    while(low<=high){
        int mids1=(low+high)/2;
        int mids2=left-mids1;
        int l1,l2,r1,r2;
        if(mids1>0){
            l1=nums1[mids1-1];
        }
        else{
            l1=INT_MIN;
        }
        if(mids1<n1){
            r1=nums1[mids1];
        }
        else{
            r2=INT_MAX;
        }


        l2 = (mids2 > 0) ? nums2[mids2 - 1] : INT_MIN;
        r2 = (mids2 < n2) ? nums2[mids2]     : INT_MAX;

        if (l1 <= r2 && l2 <= r1) {
            return max(l1, l2);
        }
        else if (l1 > r2) {
            high = mids1 - 1;
        }
        else {
            low = mids1 + 1;
        }
    }
    return -1;
}

int main() {
    vector<int> a = {2, 3, 4, 6};
    vector<int> b = {3, 4, 7, 9, 22, 23};
    int k=6;

    cout << "kth element is :-" << kth(a, b,k);
    return 0;
}