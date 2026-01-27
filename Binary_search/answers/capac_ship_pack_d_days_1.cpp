#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE :-
int days_required(vector <int> &wts,int capacity){      // 1    2   3   4   5   6   7   8   9   10      days=5
    int load=0,days=1;
    for(int i=0;i<wts.size();i++){
        if(load+wts[i]>capacity){
            days+=1;
            load=wts[i];
        }
        else{
            load+=wts[i];
        }
    }
    return days;
}

int final_capac(vector <int> &wts,int threshold_days){
    for(int capacity=*max_element(wts.begin(),wts.end());capacity<=accumulate(wts.begin(),wts.end(),0);capacity++){
        int days=days_required(wts,capacity);
        if(days<=threshold_days){
            return capacity;
        }
    }
}

int main(){
    vector <int> wts={1,2,3,4,5,6,7,8,9,10};
    int threshold_days=5;
    int capacity=final_capac(wts,threshold_days);
    cout<<"The minimum capacity of ship is "<<capacity;
    return 0;
}