#include<bits/stdc++.h>
using namespace std;

pair<int,int> med(vector <int>&arr_1,vector <int> &arr_2){
    vector <int> ans;
    int i,j;
    for(i=0,j=0;i<arr_1.size() && j<arr_2.size();){
        if(arr_1[i]<=arr_2[j]){
            ans.push_back(arr_1[i]);
            i++;
        }
        else{
            ans.push_back(arr_2[j]);
            j++;
        }
    }
    while(i<arr_1.size()){
        ans.push_back(arr_1[i]);
        i++;
    }
    while(j<arr_2.size()){
        ans.push_back(arr_2[j]);
        j++;
    }


    if(ans.size()%2==0){
        return {ans[(ans.size()/2)-1],ans[ans.size()/2]};
    }
    else{
        return {ans[(ans.size()/2)],ans[(ans.size()/2)]};
    }
}

int main(){
    vector <int> arr_1={2,3,4,6};
    vector <int> arr_2={3,4,7,9,22,23};

    pair <int,int> m=med(arr_1,arr_2);
    cout<<"The median value is "<<(m.first+m.second)/2.0;
    return 0;
}