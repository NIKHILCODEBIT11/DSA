#include<bits/stdc++.h>
using namespace std;

int func(int mid,int m,int n){
    long long ans=1;
    for(int i=1;i<n+1;i++){
        ans=ans*mid;
        if(ans>m){     // The case where ans > m suppose i have to find 10th root of 27 and after some iterations i got ans=3 where mid^n starts coming close to m, but 3^10 is already large than 27 then no use of moving ahead
            return 2;
        }
    }
    if(ans==m){         // The case where ans matches to target m
            return 1;
        }
    return 0;
}
int nth_root(int m,int n){
    int low=1,high=m;
    while(low<=high){
        int mid=low+(high-low)/2;
        
        int midn=func(mid,m,n);        // It calculates    (m)^n
        if(midn==1){
            return mid;
        }
        else if(midn==0){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return -1;
}


/*
GOAL:
-----
Find the integer n-th root of a given number m.
That is, find an integer x such that:
    x^n == m
If no such integer exists, return -1.

APPROACH:
---------
We use Binary Search because:
- The possible answer range is from 1 to m
- If x^n < m, we need a larger x
- If x^n > m, we need a smaller x
This monotonic behavior allows binary search.

There are two main parts:

1) func(mid, m, n):
-------------------
This helper function compares mid^n with m safely.

- We compute mid^n step-by-step using a loop instead of pow()
  to avoid floating-point inaccuracies and overflow.
- While multiplying, we check:
    - If ans > m:
        We immediately stop because further multiplication
        will only increase the value (mid >= 1).
        Hence mid^n will definitely be greater than m.
        We return 2 (mid is too large).
    - If ans == m:
        We found the exact n-th root, return 1.
- If the loop ends and ans < m:
    mid^n is smaller than m, return 0.

Return values meaning:
    1 -> mid^n == m (perfect root found)
    0 -> mid^n < m  (mid is too small)
    2 -> mid^n > m  (mid is too large)

2) nth_root(m, n):
------------------
- We perform binary search in the range [1, m].
- For each mid, we call func(mid, m, n).
- Based on the result:
    - If func returns 1, mid is the answer.
    - If func returns 0, move right (low = mid + 1).
    - If func returns 2, move left (high = mid - 1).
- If binary search finishes without finding a match,
  return -1 (no integer n-th root exists).

WHY ans > m CHECK IS IMPORTANT:
-------------------------------
- Prevents unnecessary computations
- Avoids integer overflow
- Improves performance
- Allows early termination when mid is too large

TIME & SPACE COMPLEXITY:
------------------------
Time Complexity:
    O(n * log m)
    - log m from binary search
    - n from power calculation

Space Complexity:
    O(1) (constant extra space)
*/


int main(){
    int target,n;
    cout<<"Enter target value :- ";
    cin>>target;
    cout<<"Enter n :- ";
    cin>>n;
    cout<<"The "<<n<<"th root of "<<target<<" is "<<nth_root(target,n);
    return 0;
}


