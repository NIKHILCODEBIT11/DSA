#include<bits/stdc++.h>
using namespace std;

/*
linear approach :-          It takes     O(N)    time complexity

finding sqrt of "n"
I will start from i=0 and keep on continuing till i="n" and return floor value

ans=1       // Default
for(int i=0i<=n;i++){
    if(i*i<=n){
        ans=i;
    }
    else{
        break;
    }
}

*/

int sqrt(int n){
    int ans=0;
    int low=0,high=n;
    while(low<=high){
        // long long mid=(low+high)/2;             // It is useful but even long long has capacity til     9*(10)^18    for which i should use :-
        int mid=low+(high-low)/2;

        // if(mid*mid<=n){                  // It is useful but even long long has capacity til     9*(10)^18    for which i should use :-
        if(mid<=n/mid){    
            ans=mid;
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return ans;         // I can also return    "high"
}

int main(){
    int n;
    cout<<"Enter value :- ";
    cin>>n;
    cout<<"The floor value of sqrt of "<<n<<" is "<<sqrt(n);
    return 0;
}

// Explaination for returning "high"

/*

Instead of returning "ans" i can also return "high" as "high" is the first index which has possible answer and "low" is the
first index where answer is not possible.


EXPLAINATION :-

After binary search ends,
high points to the largest value that satisfies the condition
and low points to the first value that violates it.

So returning high gives the same result as ans.

n = 10
floor(sqrt(10)) = 3

Binary search trace
low	high	mid	mid*mid <= 10	action
0	10	5	❌ (25 > 10)	high = 4
0	4	2	✅ (4 ≤ 10)	low = 3
3	4	3	✅ (9 ≤ 10)	low = 4
4	4	4	❌ (16 > 10)	high = 3

*/