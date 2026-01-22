#include<bits/stdc++.h>
using namespace std;

// BRUTEFORCE APPROACH :-
/*
vector <int> find_union(vector <int> a,vector <int> b){
    set <int> st;
    for(int i=0;i<a.size();i++){
        st.insert(a[i]);
    }
    for(int i=0;i<b.size();i++){
        st.insert(b[i]);
    }
    vector <int> unionn;
    for(auto it : st){
        unionn.push_back(it);
    }
    return unionn;
}
*/

// OPTIMAL APPROACH :-
vector <int> find_union(vector <int> a,vector <int> b){
    int n1=a.size();
    int n2=b.size();
    int i=0;
    int j=0;
    vector <int> unionn;
    while(i<n1 && j<n2){
        if(a[i]<=b[j]){
            if(unionn.size()==0 || unionn.back()!=a[i]){
                unionn.push_back(a[i]);
            }
            i++;
        }
        else{
            if(unionn.size()==0 || unionn.back()!=b[j]){
                unionn.push_back(b[j]);
            }
            j++;
        }
    }
    while(i<n1){
        if(unionn.size()==0 || unionn.back()!=a[i]){
            unionn.push_back(a[i]);
        }
        i++;
    }
    while(j<n2){
        if(unionn.size()==0 || unionn.back()!=b[j]){
            unionn.push_back(b[j]);
        }
        j++;
    }
    return unionn;
}

int main(){
    vector <int> a={1,2,3,3,4,4,4,5,6};
    vector <int> b={2,3,4,5,5,5,6};
    auto ans=find_union(a,b);
    for(auto it : ans){
        cout<<it<<" ";
    }
    return 0;
}