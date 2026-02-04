#include<bits/stdc++.h>
using namespace std;

// Optimal from 1st one 
double med(vector <int>& a,vector <int> &b){
    int n1=a.size(),n2=b.size();
    int i=0,j=0;
    int n=n1+n2;
    int index_1=n/2,index_2=index_1-1;
    int cnt=0;
    int ind1el=-1,ind2el=-1;
    while(i<n1 && j<n2){
        if(a[i]<b[j]){
            if(cnt==index_1){
                ind1el=a[i];
            }
            if(cnt==index_2){
                ind2el=a[i];
            }
            cnt++;
            i++;
        }
        else{
            if(cnt==index_1){
                ind1el=b[j];
            }
            if(cnt==index_2){
                ind2el=b[j];
            }
            cnt++;
            j++;
        }
    }
    while(i<n1){
        if(cnt==index_1){
            ind1el=a[i];
        }
        if(cnt==index_2){
            ind2el=a[i];
        }
        cnt++;
        i++;
    }

    while(j<n2){
        if(cnt==index_1){
            ind1el=b[j];
        }
        if(cnt==index_2){
            ind2el=b[j];
        }
        cnt++;
        j++;
    }

    if(n%2==0){
        return (ind1el+ind2el)/2.0;
    }
    else{
        return ind1el;
    }
}

int main(){
    vector <int> arr_1={2,3,4,6};
    vector <int> arr_2={3,4,7,9,22,23};

    int m=med(arr_1,arr_2);
    cout<<"The median value is "<<m;
    return 0;
}